#include "semantic.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// ANSI color codes
#define COLOR_RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"

// Global variables
Scope *globalScope = NULL;
Scope *currentScope = NULL;
Symbol *currentFunction = NULL;
int errorFlag = 0;

// Initialize global scope
void initGlobalScope()
{
    globalScope = (Scope *)malloc(sizeof(Scope));
    globalScope->symbols = NULL;
    globalScope->parent = NULL;
    currentScope = globalScope;
}

// Error reporting
void reportError(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    fprintf(stderr, COLOR_RED "Semantic Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, COLOR_RESET "\n");
    va_end(args);
    errorFlag = 1;
}

// Clean up global scope
void cleanupSemanticAnalyzer()
{
    if (globalScope)
    {
        Symbol *current = globalScope->symbols;
        while (current)
        {
            Symbol *next = current->next;
            free(current->name);
            free(current->dataType);
            free(current);
            current = next;
        }
        free(globalScope);
        globalScope = NULL;
        currentScope = NULL;
    }
}

// Create a new scope
void enterScope()
{
    Scope *newScope = (Scope *)malloc(sizeof(Scope));
    newScope->symbols = NULL;
    newScope->parent = currentScope;
    currentScope = newScope;
}

// Exit current scope while preserving global declarations
void exitScope()
{
    if (!currentScope || currentScope == globalScope)
        return;

    Scope *parentScope = currentScope->parent;

    // Move struct and interface declarations to global scope
    Symbol *current = currentScope->symbols;
    while (current)
    {
        Symbol *next = current->next;
        if (current->type == SYMBOL_STRUCT || current->type == SYMBOL_INTERFACE)
        {
            // Remove from current scope
            if (current == currentScope->symbols)
            {
                currentScope->symbols = next;
            }
            else
            {
                Symbol *prev = currentScope->symbols;
                while (prev->next != current)
                    prev = prev->next;
                prev->next = next;
            }
            // Add to global scope
            current->next = globalScope->symbols;
            globalScope->symbols = current;
        }
        current = next;
    }

    // Free remaining symbols
    current = currentScope->symbols;
    while (current)
    {
        Symbol *next = current->next;
        if (current->type != SYMBOL_STRUCT && current->type != SYMBOL_INTERFACE)
        {
            free(current->name);
            free(current->dataType);
            free(current);
        }
        current = next;
    }

    free(currentScope);
    currentScope = parentScope;
}

// Find struct type
Symbol *findStructType(char *structName)
{
    Scope *scope = globalScope;
    Symbol *symbol = scope->symbols;
    while (symbol)
    {
        if (symbol->type == SYMBOL_STRUCT && strcmp(symbol->name, structName) == 0)
        {
            return symbol;
        }
        symbol = symbol->next;
    }
    return NULL;
}

// Helper function to find a field in a struct
Symbol *findStructField(char *structName, char *fieldName)
{
    // First try to find if structName is a variable
    Symbol *varSymbol = findSymbol(structName);

    if (varSymbol && varSymbol->type == SYMBOL_VARIABLE)
    {
        // Look up the struct type for this variable
        Symbol *structSymbol = findStructType(varSymbol->dataType);
        if (structSymbol)
        {
            ASTNode *field = structSymbol->fields;
            while (field)
            {
                if (strcmp(field->field.name, fieldName) == 0)
                {
                    Symbol *fieldSymbol = (Symbol *)malloc(sizeof(Symbol));
                    fieldSymbol->name = strdup(fieldName);
                    fieldSymbol->type = SYMBOL_VARIABLE;
                    fieldSymbol->dataType = strdup(field->field.type->typeDecl.name);
                    fieldSymbol->next = NULL;
                    return fieldSymbol;
                }
                field = field->field.next;
            }
        }
    }

    // If not found as variable, try direct struct lookup
    Symbol *structSymbol = findStructType(structName);
    if (structSymbol)
    {
        ASTNode *field = structSymbol->fields;
        while (field)
        {
            if (strcmp(field->field.name, fieldName) == 0)
            {
                Symbol *fieldSymbol = (Symbol *)malloc(sizeof(Symbol));
                fieldSymbol->name = strdup(fieldName);
                fieldSymbol->type = SYMBOL_VARIABLE;
                fieldSymbol->dataType = strdup(field->field.type->typeDecl.name);
                fieldSymbol->next = NULL;
                return fieldSymbol;
            }
            field = field->field.next;
        }
    }

    return NULL;
}

// Enhanced symbol management
Symbol *addSymbol(char *name, SymbolType type, char *dataType)
{
    if (!currentScope)
    {
        reportError("No active scope for symbol %s", name);
        
        return NULL;
    }

    // Check for duplicate declaration in current scope
    Symbol *existing = currentScope->symbols;
    while (existing)
    {
        if (strcmp(existing->name, name) == 0)
        {
            reportError("Symbol %s already declared in current scope", name);
            
            return NULL;
        }
        existing = existing->next;
    }

    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
    symbol->name = strdup(name);
    symbol->type = type;
    symbol->dataType = strdup(dataType);
    symbol->next = currentScope->symbols;
    symbol->parameters = NULL;
    symbol->fields = NULL;
    currentScope->symbols = symbol;
    return symbol;
}

// Find symbol in any scope
Symbol *findSymbol(char *name)
{
    Scope *scope = currentScope;
    while (scope)
    {
        Symbol *symbol = scope->symbols;
        while (symbol)
        {
            if (strcmp(symbol->name, name) == 0)
            {
                return symbol;
            }
            symbol = symbol->next;
        }
        scope = scope->parent;
    }
    return NULL;
}

// Pre-declare functions in the global scope
void preDeclareFunction(ASTNode *node)
{
    if (!node)
        return;
    if (node->type == NODE_FUNCTION)
    {
        char *returnType = node->function.return_type ? node->function.return_type->typeDecl.name : "void";
        Symbol *functionSymbol = addSymbol(node->function.name, SYMBOL_FUNCTION, returnType);

        // Store parameters
        ASTNode *param = node->function.parameters;
        ASTNode *paramList = NULL;
        while (param)
        {
            ASTNode *newParam = createParameterNode(param->parameter.name,
                                                    param->parameter.type,
                                                    paramList);
            paramList = newParam;
            param = param->parameter.next;
        }
        functionSymbol->parameters = paramList;

        if (node->function.next)
        {
            preDeclareFunction(node->function.next);
        }
    }
}

// Check interface implementation
void checkInterfaceImplementation(Symbol *structSymbol, Symbol *interfaceSymbol)
{
    ASTNode *interfaceMethod = interfaceSymbol->fields;
    while (interfaceMethod)
    {
        bool methodFound = false;
        ASTNode *structMethod = structSymbol->fields;

        while (structMethod)
        {
            if (strcmp(interfaceMethod->method.name, structMethod->method.name) == 0)
            {
                // Check method signature compatibility
                methodFound = true;
                break;
            }
            structMethod = structMethod->method.next;
        }

        if (!methodFound)
        {
            reportError("Struct %s does not implement method %s required by interface %s",
                        structSymbol->name, interfaceMethod->method.name, interfaceSymbol->name);
            
            return;
        }

        interfaceMethod = interfaceMethod->method.next;
    }
}

// Analyze struct declarations
void analyzeStruct(ASTNode *node)
{
    if (!node || node->type != NODE_STRUCT)
        return;

    Symbol *structSymbol = addSymbol(node->structDecl.name, SYMBOL_STRUCT, node->structDecl.name);
    structSymbol->fields = node->structDecl.fields;

    // Analyze fields
    ASTNode *field = node->structDecl.fields;
    while (field)
    {
        if (field->type != NODE_FIELD)
        {
            reportError("Invalid field in struct %s", node->structDecl.name);
            
            continue;
        }

        // Verify field type
        if (field->field.type->type == NODE_TYPE)
        {
            Symbol *typeSymbol = findSymbol(field->field.type->typeDecl.name);
            if (!typeSymbol && strcmp(field->field.type->typeDecl.name, "string") != 0 && strcmp(field->field.type->typeDecl.name, "int") != 0)
            {
                reportError("Unknown type %s for field %s in struct %s",
                            field->field.type->typeDecl.name,
                            field->field.name,
                            node->structDecl.name);
                
            }
        }

        field = field->field.next;
    }
}

// Analyze interface declarations
void analyzeInterface(ASTNode *node)
{
    if (!node || node->type != NODE_INTERFACE)
        return;

    Symbol *interfaceSymbol = addSymbol(node->interfaceDecl.name, SYMBOL_INTERFACE, "interface");
    interfaceSymbol->fields = node->interfaceDecl.methods;

    // Analyze methods
    ASTNode *method = node->interfaceDecl.methods;
    while (method)
    {
        if (method->type != NODE_METHOD)
        {
            reportError("Invalid method in interface %s", node->interfaceDecl.name);
            
            continue;
        }

        // Add method to interface symbol
        method = method->method.next;
    }
}

// Get the type of an AST node
char *getType(ASTNode *node)
{
    if (!node)
        return "unknown";

    switch (node->type)
    {
    case NODE_LITERAL:
        return node->literal.type;

    case NODE_IDENTIFIER:
    {
        Symbol *symbol = findSymbol(node->identifier.name);
        if (!symbol)
        {
            reportError("Undeclared identifier: %s", node->identifier.name);
            
        }
        return symbol->dataType;
    }

    case NODE_STRUCT_FIELD_ACCESS:
    {
        Symbol *field = findStructField(node->structFieldAccess.structName,
                                        node->structFieldAccess.fieldName);
        if (!field)
        {
            reportError("Unknown field %s in struct %s",
                        node->structFieldAccess.fieldName,
                        node->structFieldAccess.structName);
            
        }
        char *fieldType = strdup(field->dataType);
        free(field->name);
        free(field->dataType);
        free(field);
        return fieldType;
    }

    case NODE_BINARY_OP:
    {
        char *leftType = getType(node->binaryOp.left);
        char *rightType = getType(node->binaryOp.right);

        // Handle string concatenation
        if (strcmp(node->binaryOp.op, "+") == 0 &&
            strcmp(leftType, "string") == 0 &&
            strcmp(rightType, "string") == 0)
        {
            return "string";
        }

        // Strict type checking for other operations
        if (strcmp(leftType, rightType) != 0)
        {
            reportError("Type mismatch in binary operation '%s': cannot operate on types %s and %s",
                        node->binaryOp.op, leftType, rightType);
            
        }

        return leftType;
    }

    case NODE_CALL:
    {
        Symbol *func = findSymbol(node->call.functionName);
        if (!func)
        {
            reportError("Undeclared function: %s", node->call.functionName);
            
        }
        return func->dataType;
    }

    case NODE_METHOD_CALL:
    {
        Symbol *structVar = findSymbol(node->methodCall.structName);
        if (!structVar)
        {
            reportError("Undeclared variable: %s", node->methodCall.structName);
            
        }
        // Find the method in the struct type
        Symbol *structType = findStructType(structVar->dataType);
        if (!structType)
        {
            reportError("Unknown struct type: %s", structVar->dataType);
            
        }
        // TODO: Implement method lookup in struct type
        return "void"; // Temporary return type
    }

    case NODE_ARGUMENT:
        return getType(node->argument.expression);

    default:
        return "unknown";
    }
}

// Check types in an AST node
void checkTypes(ASTNode *node)
{
    if (!node)
        return;

    switch (node->type)
    {
    case NODE_BINARY_OP:
        checkTypes(node->binaryOp.left);
        checkTypes(node->binaryOp.right);
        getType(node);
        break;

    case NODE_ASSIGN:
    {
        Symbol *symbol = findSymbol(node->assign.name);
        if (!symbol)
        {
            reportError("Undeclared variable: %s", node->assign.name);
            return;
        }

        checkTypes(node->assign.expression);
        char *exprType = getType(node->assign.expression);
        if (strcmp(symbol->dataType, exprType) != 0)
        {
            reportError("Type mismatch in assignment to %s: cannot assign %s to variable of type %s",
                        node->assign.name, exprType, symbol->dataType);
            
        }
        break;
    }

    case NODE_STRUCT_FIELD_ASSIGN:
    {
        Symbol *field = findStructField(node->structFieldAssign.structName,
                                        node->structFieldAssign.fieldName);
        if (!field)
        {
            reportError("Unknown field %s in struct %s",
                        node->structFieldAssign.fieldName,
                        node->structFieldAssign.structName);
            
        }

        checkTypes(node->structFieldAssign.expression);
        char *exprType = getType(node->structFieldAssign.expression);
        if (strcmp(field->dataType, exprType) != 0)
        {
            reportError("Type mismatch in field assignment: cannot assign %s to field of type %s",
                        exprType, field->dataType);
            
        }

        free(field->name);
        free(field->dataType);
        free(field);
        break;
    }

    case NODE_VAR_DECL_ASSIGN:
    {
        Symbol *symbol = addSymbol(node->varDeclAssign.name,
                                   SYMBOL_VARIABLE,
                                   node->varDeclAssign.type->typeDecl.name);

        checkTypes(node->varDeclAssign.expression);
        char *exprType = getType(node->varDeclAssign.expression);
        char *declaredType = node->varDeclAssign.type->typeDecl.name;

        if (strcmp(declaredType, exprType) != 0)
        {
            reportError("Type mismatch in variable declaration: cannot assign %s to variable of type %s",
                        exprType, declaredType);
            
        }
        break;
    }

    case NODE_CALL:
    {
        Symbol *func = findSymbol(node->call.functionName);
        if (!func)
        {
            reportError("Undeclared function: %s", node->call.functionName);
            
        }

        ASTNode *arg = node->call.arguments;
        ASTNode *param = func->parameters;

        while (arg && param)
        {
            checkTypes(arg);
            char *paramType = param->parameter.type->typeDecl.name;
            char *argType = getType(arg);

            if (strcmp(argType, paramType) != 0)
            {
                reportError("Type mismatch in argument for function %s: expected %s, got %s",
                            node->call.functionName, paramType, argType);
                
            }

            arg = arg->argument.next;
            param = param->parameter.next;
        }

        if (arg || param)
        {
            reportError("Argument count mismatch in function call %s",
                        node->call.functionName);
            
        }
        break;
    }

    case NODE_RETURN:
    {
        if (!currentFunction)
        {
            reportError("Return statement outside function");
            
        }

        checkTypes(node->returnStmt.expression);
        char *exprType = getType(node->returnStmt.expression);
        if (strcmp(currentFunction->dataType, exprType) != 0)
        {
            reportError("Return type mismatch in function %s: returning %s, expected %s",
                        currentFunction->name, exprType, currentFunction->dataType);
            
        }
        break;
    }
    }
}

// Main semantic analysis function
int semanticAnalyze(ASTNode *node)
{
    if (!node)
        return errorFlag;

    switch (node->type)
    {
    case NODE_PROGRAM:
        if (!globalScope)
            initGlobalScope();

        // First pass: Pre-declare all structs and interfaces
        ASTNode *current = node->program.type_decls;
        while (current)
        {
            if (current->type == NODE_STRUCT)
            {
                Symbol *structSymbol = addSymbol(current->structDecl.name,
                                                 SYMBOL_STRUCT,
                                                 current->structDecl.name);
                structSymbol->fields = current->structDecl.fields;
            }
            
            if (current->type == NODE_INTERFACE)
            {
                Symbol *interfaceSymbol = addSymbol(current->interfaceDecl.name,
                                                    SYMBOL_INTERFACE,
                                                    "interface");
                interfaceSymbol->fields = current->interfaceDecl.methods;
            }
            current = current->next;
        }

        // Second pass: Pre-declare all functions once.
        // preDeclareFunction walks the linked function list recursively.
        preDeclareFunction(node->program.functions);

        // Third pass: Analyze everything in detail
        current = node->program.functions;
        while (current)
        {
            if (current->type == NODE_STRUCT)
                analyzeStruct(current);
            else if (current->type == NODE_INTERFACE)
                analyzeInterface(current);
            else if (current->type == NODE_FUNCTION)
                semanticAnalyze(current);
            current = current->next;
        }
        // Clean up after processing the node
        cleanupSemanticAnalyzer();
        break;

    case NODE_FUNCTION:
    {
        enterScope();
        // Set current function before analyzing the body
        currentFunction = findSymbol(node->function.name);

        // Add receiver to scope if it exists
        if (node->function.receiver)
        {
            addSymbol(node->function.receiver->receiver.name,
                      SYMBOL_VARIABLE,
                      node->function.receiver->receiver.type);
        }

        // Add parameters to scope
        ASTNode *param = node->function.parameters;
        while (param)
        {
            addSymbol(param->parameter.name,
                      SYMBOL_VARIABLE,
                      param->parameter.type->typeDecl.name);
            param = param->parameter.next;
        }

        semanticAnalyze(node->function.body);
        currentFunction = NULL; // Clear current function
        exitScope();
        break;
    }

    case NODE_VAR_DECL:
        addSymbol(node->varDecl.name, SYMBOL_VARIABLE,
                  node->varDecl.type->typeDecl.name);
        semanticAnalyze(node->next);
        break;

    case NODE_VAR_DECL_ASSIGN:
    case NODE_ASSIGN:
    case NODE_CALL:
    case NODE_RETURN:
    case NODE_BINARY_OP:
    case NODE_STRUCT_FIELD_ASSIGN:
        checkTypes(node);
        semanticAnalyze(node->next);
        break;

    case NODE_STRUCT:
        analyzeStruct(node);
        semanticAnalyze(node->next);
        break;

    default:
        if (node->next)
        {
            semanticAnalyze(node->next);
        }
        break;
    }
    return errorFlag;
}
