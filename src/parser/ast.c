#include "ast.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  // For mkdir
#ifdef _WIN32
#include <direct.h>
#endif

// Forward declaration of astToJSON
cJSON* astToJSON(ASTNode* node);

// Ensure the build directory exists
void ensureBuildFolderExists() {
    struct stat st = {0};
    if (stat("build", &st) == -1) {
#ifdef _WIN32
        mkdir("build");
#else
        mkdir("build", 0700); // Create build directory with read/write/execute permissions
#endif
    }
}

// Convert a linked list of AST nodes to JSON
cJSON* astToJSONList(ASTNode* node) {
    cJSON* jsonArray = cJSON_CreateArray();
    while (node != NULL) {
        cJSON_AddItemToArray(jsonArray, astToJSON(node));
        node = node->next;
    }
    return jsonArray;
}

// Print a linked list of AST nodes
void printASTList(ASTNode* node, int indent, int asJSON, const char* filename) {
    while (node != NULL) {
        printAST(node, indent, asJSON, filename);
        node = node->next;
    }
}

// Create a Program Node
ASTNode* createProgramNode(ASTNode* imports, ASTNode* type_decls, ASTNode* functions) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_PROGRAM;
    node->next = NULL;
    node->program.imports = imports;
    node->program.type_decls = type_decls; // Add type declarations
    node->program.functions = functions;
    return node;
}


// Create a Function Node
ASTNode* createFunctionNode(char* name, ASTNode* receiver, ASTNode* parameters, ASTNode* return_type, ASTNode* body, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_FUNCTION;
    node->next = next;
    node->function.name = strdup(name);
    node->function.receiver = receiver; // Set the receiver
    node->function.parameters = parameters;
    node->function.return_type = return_type;
    node->function.body = body;
    node->function.next = next; // Set the next pointer
    return node;
}

// Create an If Node
ASTNode* createIfNode(ASTNode* condition, ASTNode* thenBranch, ASTNode* elseBranch) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_IF;
    node->next = NULL; // No next pointer needed here
    node->ifStmt.condition = condition;
    node->ifStmt.thenBranch = thenBranch;
    node->ifStmt.elseBranch = elseBranch;
    return node;
}

// Create a For Node
ASTNode* createForNode(ASTNode* init, ASTNode* condition, ASTNode* update, ASTNode* body) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_FOR;
    node->next = NULL; // No next pointer needed here
    node->forStmt.init = init;
    node->forStmt.condition = condition;
    node->forStmt.update = update;
    node->forStmt.body = body;
    return node;
}

// Create a Binary Operation Node
ASTNode* createBinaryOpNode(char* op, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_BINARY_OP;
    node->next = NULL; // No next pointer needed here
    node->binaryOp.op = strdup(op);
    node->binaryOp.left = left;
    node->binaryOp.right = right;
    return node;
}

// Create a Literal Node
ASTNode* createLiteralNode(char* type, void* value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_LITERAL;
    node->next = NULL; // No next pointer needed here
    
    if (strcmp(type, "int") == 0) {
        node->literal.intValue = *(int*)value;
        node->literal.type = strdup(type);
    } else if (strcmp(type, "float") == 0) {
        node->literal.floatValue = *(double*)value;
        node->literal.type = strdup("float64");
    } else if (strcmp(type, "string") == 0) {
        node->literal.stringValue = strdup((char*)value);
        node->literal.type = strdup(type);
    } else if (strcmp(type, "bool") == 0) {
        node->literal.boolValue = *(bool*)value;
        node->literal.type = strdup(type);
    }
    return node;
}

// Create an Identifier Node
ASTNode* createIdentifierNode(char* name) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_IDENTIFIER;
    node->next = NULL; // No next pointer needed here
    node->identifier.name = strdup(name);
    return node;
}

// Create a Call Node
ASTNode* createCallNode(char* functionName, ASTNode* arguments) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_CALL;
    node->next = NULL; // No next pointer needed here
    node->call.functionName = strdup(functionName);
    node->call.arguments = arguments;
    return node;
}

// Create a Struct Node
ASTNode* createStructNode(char* name, ASTNode* fields) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_STRUCT;
    node->next = NULL; // No next pointer needed here
    node->structDecl.name = strdup(name);
    node->structDecl.fields = fields;
    return node;
}

// Create an Interface Node
ASTNode* createInterfaceNode(char* name, ASTNode* methods) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_INTERFACE;
    node->next = NULL; // No next pointer needed here
    node->interfaceDecl.name = strdup(name);
    node->interfaceDecl.methods = methods;
    return node;
}

// Create an Import Node
ASTNode* createImportNode(char* path, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_IMPORT;
    node->next = next;
    node->import.path = strdup(path);
    node->import.next = next;
    return node;
}

// Create a Field Node
ASTNode* createFieldNode(char* name, ASTNode* type, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_FIELD;
    node->next = next;
    node->field.name = strdup(name);
    node->field.type = type;
    node->field.next = next;
    return node;
}

// Create a Method Node
ASTNode* createMethodNode(char* name, ASTNode* parameters, ASTNode* returnType, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_METHOD;
    node->next = next;
    node->method.name = strdup(name);
    node->method.parameters = parameters;
    node->method.returnType = returnType;
    node->method.next = next;
    return node;
}

// Create a Receiver Node
ASTNode* createReceiverNode(char* name, char* type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_RECEIVER;
    node->next = NULL; // No next pointer needed here
    node->receiver.name = strdup(name);
    node->receiver.type = strdup(type);
    return node;
}

// Create a Parameter Node
ASTNode* createParameterNode(char* name, ASTNode* type, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_PARAMETER;
    node->next = next;
    node->parameter.name = strdup(name);
    node->parameter.type = type;
    node->parameter.next = next;
    return node;
}

// Create a Return Node
ASTNode* createReturnNode(ASTNode* expression, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_RETURN;
    node->next = next;
    node->returnStmt.expression = expression;
    node->returnStmt.next = next;
    return node;
}

// Create a Variable Declaration Node
ASTNode* createVarDeclNode(char* name, ASTNode* type, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_VAR_DECL;
    node->next = next;
    node->varDecl.name = strdup(name);
    node->varDecl.type = type;
    node->varDecl.next = next;
    return node;
}

// Create a Variable Declaration with Assignment Node
ASTNode* createVarDeclAssignNode(char* name, ASTNode* type, ASTNode* expression, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_VAR_DECL_ASSIGN;
    node->next = next;
    node->varDeclAssign.name = strdup(name);
    node->varDeclAssign.type = type;
    node->varDeclAssign.expression = expression;
    node->varDeclAssign.next = next;
    return node;
}

// Create an Assignment Node
ASTNode* createAssignNode(char* name, ASTNode* expression, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGN;
    node->next = next;
    node->assign.name = strdup(name);
    node->assign.expression = expression;
    node->assign.next = next;
    return node;
}

// Create a Struct Field Assignment Node
ASTNode* createStructFieldAssignNode(char* structName, char* fieldName, ASTNode* expression, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_STRUCT_FIELD_ASSIGN;
    node->next = next;
    node->structFieldAssign.structName = strdup(structName);
    node->structFieldAssign.fieldName = strdup(fieldName);
    node->structFieldAssign.expression = expression;
    node->structFieldAssign.next = next;
    return node;
}

// Create a Method Call Node
ASTNode* createMethodCallNode(char* structName, char* methodName, ASTNode* arguments, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_METHOD_CALL;
    node->next = next;
    node->methodCall.structName = strdup(structName);
    node->methodCall.methodName = strdup(methodName);
    node->methodCall.arguments = arguments;
    node->methodCall.next = next;
    return node;
}

// Create a Struct Field Access Node
ASTNode* createStructFieldAccessNode(char* structName, char* fieldName) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_STRUCT_FIELD_ACCESS;
    node->next = NULL;
    node->structFieldAccess.structName = strdup(structName);
    node->structFieldAccess.fieldName = strdup(fieldName);
    return node;
}

// Create a Map Type Node
ASTNode* createMapTypeNode(ASTNode* keyType, ASTNode* valueType) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_MAP_TYPE;
    node->next = NULL;
    node->mapType.keyType = keyType;
    node->mapType.valueType = valueType;
    return node;
}

// Create a Slice Type Node
ASTNode* createSliceTypeNode(ASTNode* elementType) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_SLICE_TYPE;
    node->next = NULL;
    node->sliceType.elementType = elementType;
    return node;
}

// Create a Channel Type Node
ASTNode* createChanTypeNode(ASTNode* elementType) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_CHAN_TYPE;
    node->next = NULL;
    node->chanType.elementType = elementType;
    return node;
}

// Create a Type Node
ASTNode* createTypeNode(char* type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_TYPE;
    node->next = NULL; // No next pointer needed here
    node->typeDecl.name = strdup(type);
    return node;
}

// Create an Argument Node
ASTNode* createArgumentNode(ASTNode* expression, ASTNode* next) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = NODE_ARGUMENT;
    node->next = next;
    node->argument.expression = expression;
    node->argument.next = next;
    return node;
}

// Convert AST to JSON
cJSON* astToJSON(ASTNode* node) {
    if (!node) return NULL;

    cJSON* jsonNode = cJSON_CreateObject();

    switch (node->type) {
        case NODE_PROGRAM:
            cJSON_AddStringToObject(jsonNode, "type", "Program");
            cJSON_AddItemToObject(jsonNode, "imports", astToJSON(node->program.imports));
            cJSON_AddItemToObject(jsonNode, "type_decls", astToJSON(node->program.type_decls));
            cJSON_AddItemToObject(jsonNode, "functions", astToJSONList(node->program.functions));
            break;
        case NODE_FUNCTION:
            cJSON_AddStringToObject(jsonNode, "type", "Function");
            cJSON_AddStringToObject(jsonNode, "name", node->function.name);
            if (node->function.receiver) {
                cJSON_AddItemToObject(jsonNode, "receiver", astToJSON(node->function.receiver));
            } else {
                cJSON_AddNullToObject(jsonNode, "receiver");
            }
            cJSON_AddItemToObject(jsonNode, "parameters", astToJSON(node->function.parameters));
            cJSON_AddItemToObject(jsonNode, "returnType", astToJSON(node->function.return_type));
            cJSON_AddItemToObject(jsonNode, "body", astToJSONList(node->function.body));
            cJSON_AddItemToObject(jsonNode, "next", astToJSON(node->function.next)); // Traverse the next function
            break;
        case NODE_IF:
            cJSON_AddStringToObject(jsonNode, "type", "If");
            cJSON_AddItemToObject(jsonNode, "condition", astToJSON(node->ifStmt.condition));
            cJSON_AddItemToObject(jsonNode, "thenBranch", astToJSON(node->ifStmt.thenBranch));
            cJSON_AddItemToObject(jsonNode, "elseBranch", astToJSON(node->ifStmt.elseBranch));
            break;
        case NODE_FOR:
            cJSON_AddStringToObject(jsonNode, "type", "For");
            cJSON_AddItemToObject(jsonNode, "init", astToJSON(node->forStmt.init));
            cJSON_AddItemToObject(jsonNode, "condition", astToJSON(node->forStmt.condition));
            cJSON_AddItemToObject(jsonNode, "update", astToJSON(node->forStmt.update));
            cJSON_AddItemToObject(jsonNode, "body", astToJSON(node->forStmt.body));
            break;
        case NODE_BINARY_OP:
            cJSON_AddStringToObject(jsonNode, "type", "BinaryOp");
            cJSON_AddStringToObject(jsonNode, "op", node->binaryOp.op);
            cJSON_AddItemToObject(jsonNode, "left", astToJSON(node->binaryOp.left));
            cJSON_AddItemToObject(jsonNode, "right", astToJSON(node->binaryOp.right));
            break;
        case NODE_LITERAL:
            cJSON_AddStringToObject(jsonNode, "type", "Literal");
            cJSON_AddStringToObject(jsonNode, "literalType", node->literal.type);
            if (strcmp(node->literal.type, "int") == 0) {
                cJSON_AddNumberToObject(jsonNode, "value", node->literal.intValue);
            } else if (strcmp(node->literal.type, "float") == 0) {
                cJSON_AddNumberToObject(jsonNode, "value", node->literal.floatValue);
            } else if (strcmp(node->literal.type, "string") == 0) {
                cJSON_AddStringToObject(jsonNode, "value", node->literal.stringValue);
            }
            break;
        case NODE_IDENTIFIER:
            cJSON_AddStringToObject(jsonNode, "type", "Identifier");
            cJSON_AddStringToObject(jsonNode, "name", node->identifier.name);
            break;
        case NODE_CALL:
            cJSON_AddStringToObject(jsonNode, "type", "Call");
            cJSON_AddStringToObject(jsonNode, "functionName", node->call.functionName);
            cJSON_AddItemToObject(jsonNode, "arguments", astToJSON(node->call.arguments));
            break;
        case NODE_STRUCT:
            cJSON_AddStringToObject(jsonNode, "type", "Struct");
            cJSON_AddStringToObject(jsonNode, "name", node->structDecl.name);
            cJSON_AddItemToObject(jsonNode, "fields", astToJSON(node->structDecl.fields));
            break;
        case NODE_INTERFACE:
            cJSON_AddStringToObject(jsonNode, "type", "Interface");
            cJSON_AddStringToObject(jsonNode, "name", node->interfaceDecl.name);
            cJSON_AddItemToObject(jsonNode, "methods", astToJSON(node->interfaceDecl.methods));
            break;
        case NODE_IMPORT:
            cJSON_AddStringToObject(jsonNode, "type", "Import");
            cJSON_AddStringToObject(jsonNode, "path", node->import.path);
            cJSON_AddItemToObject(jsonNode, "next", astToJSON(node->import.next));
            break;
        case NODE_FIELD:
            cJSON_AddStringToObject(jsonNode, "type", "Field");
            cJSON_AddStringToObject(jsonNode, "name", node->field.name);
            cJSON_AddItemToObject(jsonNode, "type", astToJSON(node->field.type));
            cJSON_AddItemToObject(jsonNode, "next", astToJSON(node->field.next));
            break;
        case NODE_METHOD:
            cJSON_AddStringToObject(jsonNode, "type", "Method");
            cJSON_AddStringToObject(jsonNode, "name", node->method.name);
            cJSON_AddItemToObject(jsonNode, "parameters", astToJSON(node->method.parameters));
            cJSON_AddItemToObject(jsonNode, "returnType", astToJSON(node->method.returnType));
            cJSON_AddItemToObject(jsonNode, "next", astToJSON(node->method.next));
            break;
        case NODE_RECEIVER:
            cJSON_AddStringToObject(jsonNode, "type", "Receiver");
            cJSON_AddStringToObject(jsonNode, "name", node->receiver.name);
            cJSON_AddStringToObject(jsonNode, "type", node->receiver.type);
            break;
        case NODE_PARAMETER:
            cJSON_AddStringToObject(jsonNode, "type", "Parameter");
            cJSON_AddStringToObject(jsonNode, "name", node->parameter.name);
            cJSON_AddItemToObject(jsonNode, "type", astToJSON(node->parameter.type));
            cJSON_AddItemToObject(jsonNode, "next", astToJSON(node->parameter.next));
            break;
        case NODE_RETURN:
            cJSON_AddStringToObject(jsonNode, "type", "Return");
            cJSON_AddItemToObject(jsonNode, "expression", astToJSON(node->returnStmt.expression));
            cJSON_AddItemToObject(jsonNode, "next", astToJSON(node->returnStmt.next));
            break;
        case NODE_VAR_DECL:
            cJSON_AddStringToObject(jsonNode, "type", "VarDecl");
            cJSON_AddStringToObject(jsonNode, "name", node->varDecl.name);
            cJSON_AddItemToObject(jsonNode, "type", astToJSON(node->varDecl.type));
            cJSON_AddItemToObject(jsonNode, "next", astToJSON(node->varDecl.next));
            break;
        case NODE_VAR_DECL_ASSIGN:
            cJSON_AddStringToObject(jsonNode, "type", "VarDeclAssign");
            cJSON_AddStringToObject(jsonNode, "name", node->varDeclAssign.name);
            cJSON_AddItemToObject(jsonNode, "type", astToJSON(node->varDeclAssign.type));
            cJSON_AddItemToObject(jsonNode, "expression", astToJSON(node->varDeclAssign.expression));
            cJSON_AddItemToObject(jsonNode, "next", astToJSON(node->varDeclAssign.next));
            break;
        case NODE_ASSIGN:
            cJSON_AddStringToObject(jsonNode, "type", "Assign");
            cJSON_AddStringToObject(jsonNode, "name", node->assign.name);
            cJSON_AddItemToObject(jsonNode, "expression", astToJSON(node->assign.expression));
            cJSON_AddItemToObject(jsonNode, "next", astToJSON(node->assign.next));
            break;
        case NODE_STRUCT_FIELD_ASSIGN:
            cJSON_AddStringToObject(jsonNode, "type", "StructFieldAssign");
            cJSON_AddStringToObject(jsonNode, "structName", node->structFieldAssign.structName);
            cJSON_AddStringToObject(jsonNode, "fieldName", node->structFieldAssign.fieldName);
            cJSON_AddItemToObject(jsonNode, "expression", astToJSON(node->structFieldAssign.expression));
            cJSON_AddItemToObject(jsonNode, "next", astToJSON(node->structFieldAssign.next));
            break;
        case NODE_METHOD_CALL:
            cJSON_AddStringToObject(jsonNode, "type", "MethodCall");
            cJSON_AddStringToObject(jsonNode, "structName", node->methodCall.structName);
            cJSON_AddStringToObject(jsonNode, "methodName", node->methodCall.methodName);
            cJSON_AddItemToObject(jsonNode, "arguments", astToJSON(node->methodCall.arguments));
            cJSON_AddItemToObject(jsonNode, "next", astToJSON(node->methodCall.next));
            break;
        case NODE_STRUCT_FIELD_ACCESS:
            cJSON_AddStringToObject(jsonNode, "type", "StructFieldAccess");
            cJSON_AddStringToObject(jsonNode, "structName", node->structFieldAccess.structName);
            cJSON_AddStringToObject(jsonNode, "fieldName", node->structFieldAccess.fieldName);
            break;
        case NODE_MAP_TYPE:
            cJSON_AddStringToObject(jsonNode, "type", "MapType");
            cJSON_AddItemToObject(jsonNode, "keyType", astToJSON(node->mapType.keyType));
            cJSON_AddItemToObject(jsonNode, "valueType", astToJSON(node->mapType.valueType));
            break;
        case NODE_SLICE_TYPE:
            cJSON_AddStringToObject(jsonNode, "type", "SliceType");
            cJSON_AddItemToObject(jsonNode, "elementType", astToJSON(node->sliceType.elementType));
            break;
        case NODE_CHAN_TYPE:
            cJSON_AddStringToObject(jsonNode, "type", "ChanType");
            cJSON_AddItemToObject(jsonNode, "elementType", astToJSON(node->chanType.elementType));
            break;
        case NODE_TYPE:
            cJSON_AddStringToObject(jsonNode, "type", "Type");
            cJSON_AddStringToObject(jsonNode, "name", node->typeDecl.name);
            break;
        case NODE_ARGUMENT:
            cJSON_AddStringToObject(jsonNode, "type", "Argument");
            cJSON_AddItemToObject(jsonNode, "expression", astToJSON(node->argument.expression));
            cJSON_AddItemToObject(jsonNode, "next", astToJSON(node->argument.next));
            break;
        default:
            cJSON_AddStringToObject(jsonNode, "type", "Unknown");
            break;
    }

    return jsonNode;
}

// Save AST as JSON
void saveASTAsJSON(ASTNode* node, const char* filename) {
    ensureBuildFolderExists();
    cJSON* json = astToJSON(node);
    char* jsonString = cJSON_Print(json);
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "build/%s", filename);
    FILE* file = fopen(filepath, "w");
    if (file) {
        fprintf(file, "%s", jsonString);
        fclose(file);
    } else {
        fprintf(stderr, "Error opening file %s\n", filepath);
    }
    free(jsonString);
    cJSON_Delete(json);
}

// Print the AST (for debugging)
void printAST(ASTNode* node, int indent, int asJSON, const char* filename) {
    if (asJSON) {
        saveASTAsJSON(node, filename);
    } else {
        if (!node) return;
        for (int i = 0; i < indent; i++) printf("  ");
        switch (node->type) {
            case NODE_PROGRAM:
                printf("Program\n");
                printAST(node->program.imports, indent + 1, asJSON, filename);
                printAST(node->program.type_decls, indent + 1, asJSON, filename);
                printASTList(node->program.functions, indent + 1, asJSON, filename);
                break;
            case NODE_FUNCTION:
                printf("Function: %s\n", node->function.name);
                if (node->function.receiver) {
                    printf("  Receiver: %s %s\n", node->function.receiver->receiver.name, node->function.receiver->receiver.type);
                } else {
                    printf("  Receiver: None\n");
                }
                printAST(node->function.parameters, indent + 1, asJSON, filename);
                printf("  Return Type: %s\n", node->function.return_type ? node->function.return_type->typeDecl.name : "void");
                printASTList(node->function.body, indent + 1, asJSON, filename);
                printAST(node->function.next, indent, asJSON, filename); // Traverse the next function
                break;
            case NODE_IF:
                printf("If\n");
                printAST(node->ifStmt.condition, indent + 1, asJSON, filename);
                printAST(node->ifStmt.thenBranch, indent + 1, asJSON, filename);
                printAST(node->ifStmt.elseBranch, indent + 1, asJSON, filename);
                break;
            case NODE_FOR:
                printf("For\n");
                printAST(node->forStmt.init, indent + 1, asJSON, filename);
                printAST(node->forStmt.condition, indent + 1, asJSON, filename);
                printAST(node->forStmt.update, indent + 1, asJSON, filename);
                printAST(node->forStmt.body, indent + 1, asJSON, filename);
                break;
            case NODE_BINARY_OP:
                printf("BinaryOp: %s\n", node->binaryOp.op);
                printAST(node->binaryOp.left, indent + 1, asJSON, filename);
                printAST(node->binaryOp.right, indent + 1, asJSON, filename);
                break;
            case NODE_LITERAL:
                printf("Literal: %s\n", node->literal.type);
                break;
            case NODE_IDENTIFIER:
                printf("Identifier: %s\n", node->identifier.name);
                break;
            case NODE_CALL:
                printf("Call: %s\n", node->call.functionName);
                printAST(node->call.arguments, indent + 1, asJSON, filename);
                break;
            case NODE_STRUCT:
                printf("Struct: %s\n", node->structDecl.name);
                printAST(node->structDecl.fields, indent + 1, asJSON, filename);
                break;
            case NODE_INTERFACE:
                printf("Interface: %s\n", node->interfaceDecl.name);
                printAST(node->interfaceDecl.methods, indent + 1, asJSON, filename);
                break;
            case NODE_IMPORT:
                printf("Import: %s\n", node->import.path);
                printAST(node->import.next, indent + 1, asJSON, filename);
                break;
            case NODE_FIELD:
                printf("Field: %s\n", node->field.name);
                printAST(node->field.type, indent + 1, asJSON, filename);
                printAST(node->field.next, indent + 1, asJSON, filename);
                break;
            case NODE_METHOD:
                printf("Method: %s\n", node->method.name);
                printAST(node->method.parameters, indent + 1, asJSON, filename);
                printAST(node->method.returnType, indent + 1, asJSON, filename);
                printAST(node->method.next, indent + 1, asJSON, filename);
                break;
            case NODE_RECEIVER:
                printf("Receiver: %s %s\n", node->receiver.name, node->receiver.type);
                break;
            case NODE_PARAMETER:
                printf("Parameter: %s\n", node->parameter.name);
                printAST(node->parameter.type, indent + 1, asJSON, filename);
                printAST(node->parameter.next, indent + 1, asJSON, filename);
                break;
            case NODE_RETURN:
                printf("Return\n");
                printAST(node->returnStmt.expression, indent + 1, asJSON, filename);
                printAST(node->returnStmt.next, indent + 1, asJSON, filename);
                break;
            case NODE_VAR_DECL:
                printf("VarDecl: %s\n", node->varDecl.name);
                printAST(node->varDecl.type, indent + 1, asJSON, filename);
                printAST(node->varDecl.next, indent + 1, asJSON, filename);
                break;
            case NODE_VAR_DECL_ASSIGN:
                printf("VarDeclAssign: %s\n", node->varDeclAssign.name);
                printAST(node->varDeclAssign.type, indent + 1, asJSON, filename);
                printAST(node->varDeclAssign.expression, indent + 1, asJSON, filename);
                printAST(node->varDeclAssign.next, indent + 1, asJSON, filename);
                break;
            case NODE_ASSIGN:
                printf("Assign: %s\n", node->assign.name);
                printAST(node->assign.expression, indent + 1, asJSON, filename);
                printAST(node->assign.next, indent + 1, asJSON, filename);
                break;
            case NODE_STRUCT_FIELD_ASSIGN:
                printf("StructFieldAssign: %s.%s\n", node->structFieldAssign.structName, node->structFieldAssign.fieldName);
                printAST(node->structFieldAssign.expression, indent + 1, asJSON, filename);
                printAST(node->structFieldAssign.next, indent + 1, asJSON, filename);
                break;
            case NODE_METHOD_CALL:
                printf("MethodCall: %s.%s\n", node->methodCall.structName, node->methodCall.methodName);
                printAST(node->methodCall.arguments, indent + 1, asJSON, filename);
                printAST(node->methodCall.next, indent + 1, asJSON, filename);
                break;
            case NODE_STRUCT_FIELD_ACCESS:
                printf("StructFieldAccess: %s.%s\n", node->structFieldAccess.structName, node->structFieldAccess.fieldName);
                break;
            case NODE_MAP_TYPE:
                printf("MapType\n");
                printAST(node->mapType.keyType, indent + 1, asJSON, filename);
                printAST(node->mapType.valueType, indent + 1, asJSON, filename);
                break;
            case NODE_SLICE_TYPE:
                printf("SliceType\n");
                printAST(node->sliceType.elementType, indent + 1, asJSON, filename);
                break;
            case NODE_CHAN_TYPE:
                printf("ChanType\n");
                printAST(node->chanType.elementType, indent + 1, asJSON, filename);
                break;
            case NODE_TYPE:
                printf("Type: %s\n", node->typeDecl.name);
                break;
            case NODE_ARGUMENT:
                printf("Argument\n");
                printAST(node->argument.expression, indent + 1, asJSON, filename);
                printAST(node->argument.next, indent + 1, asJSON, filename);
                break;
            default:
                printf("Unknown Node\n");
                break;
        }
    }
}
