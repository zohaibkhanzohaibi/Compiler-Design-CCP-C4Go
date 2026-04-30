#include "icg.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

struct StackICEmitter {
	FILE* output;
	int labelCounter;
};

static void emitLine(StackICEmitter* emitter, const char* format, ...)
{
	if (!emitter || !emitter->output)
	{
		return;
	}

	va_list args;
	va_start(args, format);
	vfprintf(emitter->output, format, args);
	fputc('\n', emitter->output);
	va_end(args);
}

static char* duplicateString(const char* text)
{
	if (!text)
	{
		return NULL;
	}

	size_t length = strlen(text) + 1;
	char* copy = (char*)malloc(length);
	if (!copy)
	{
		return NULL;
	}

	memcpy(copy, text, length);
	return copy;
}

static char* makeLabel(StackICEmitter* emitter, const char* prefix)
{
	char buffer[64];
	snprintf(buffer, sizeof(buffer), "%s_%d", prefix, emitter->labelCounter++);
	return duplicateString(buffer);
}

static const char* mapBinaryOpcode(const char* op)
{
	if (strcmp(op, "+") == 0) return "ADD";
	if (strcmp(op, "-") == 0) return "SUB";
	if (strcmp(op, "*") == 0) return "MUL";
	if (strcmp(op, "/") == 0) return "DIV";
	if (strcmp(op, "==") == 0) return "EQ";
	if (strcmp(op, "!=") == 0) return "NE";
	if (strcmp(op, "<") == 0) return "LT";
	if (strcmp(op, ">") == 0) return "GT";
	if (strcmp(op, "<=") == 0) return "LE";
	if (strcmp(op, ">=") == 0) return "GE";
	if (strcmp(op, "&&") == 0) return "AND";
	if (strcmp(op, "||") == 0) return "OR";
	if (strcmp(op, "&") == 0) return "BITAND";
	if (strcmp(op, "|") == 0) return "BITOR";
	if (strcmp(op, "^") == 0) return "BITXOR";
	if (strcmp(op, "<<") == 0) return "LSHIFT";
	if (strcmp(op, ">>") == 0) return "RSHIFT";
	return NULL;
}

static const char* describeType(ASTNode* typeNode)
{
	if (!typeNode)
	{
		return "void";
	}

	if (typeNode->type == NODE_TYPE)
	{
		return typeNode->typeDecl.name;
	}

	if (typeNode->type == NODE_MAP_TYPE)
	{
		return "map";
	}

	if (typeNode->type == NODE_SLICE_TYPE)
	{
		return "slice";
	}

	if (typeNode->type == NODE_CHAN_TYPE)
	{
		return "chan";
	}

	return "unknown";
}

static int emitExpression(StackICEmitter* emitter, ASTNode* expression);
static int emitStatement(StackICEmitter* emitter, ASTNode* statement);

static int emitArguments(StackICEmitter* emitter, ASTNode* arguments)
{
	int count = 0;
	ASTNode* current = arguments;

	while (current)
	{
		if (current->type == NODE_ARGUMENT && current->argument.expression)
		{
			if (emitExpression(emitter, current->argument.expression) != 0)
			{
				return -1;
			}
			count++;
		}
		current = current->argument.next;
	}

	return count;
}

static int emitCallable(StackICEmitter* emitter, const char* owner, const char* name, ASTNode* arguments)
{
	int argumentCount = emitArguments(emitter, arguments);
	if (argumentCount < 0)
	{
		return -1;
	}

	if ((owner && strcmp(owner, "fmt") == 0 && strcmp(name, "Println") == 0) ||
		(!owner && strcmp(name, "Println") == 0))
	{
		emitLine(emitter, "PRINTLN %d", argumentCount);
		return 0;
	}

	if (owner)
	{
		emitLine(emitter, "CALL_METHOD %s %s %d", owner, name, argumentCount);
	}
	else
	{
		emitLine(emitter, "CALL %s %d", name, argumentCount);
	}

	return 1;
}

static int emitExpression(StackICEmitter* emitter, ASTNode* expression)
{
	if (!expression)
	{
		return 0;
	}

	switch (expression->type)
	{
		case NODE_LITERAL:
			if (strcmp(expression->literal.type, "int") == 0)
			{
				emitLine(emitter, "PUSH_INT %d", expression->literal.intValue);
			}
			else if (strcmp(expression->literal.type, "float64") == 0)
			{
				emitLine(emitter, "PUSH_FLOAT %g", expression->literal.floatValue);
			}
			else if (strcmp(expression->literal.type, "string") == 0)
			{
				emitLine(emitter, "PUSH_STRING %s", expression->literal.stringValue);
			}
			else if (strcmp(expression->literal.type, "bool") == 0)
			{
				emitLine(emitter, "PUSH_BOOL %d", expression->literal.boolValue ? 1 : 0);
			}
			return 0;

		case NODE_IDENTIFIER:
			emitLine(emitter, "LOAD %s", expression->identifier.name);
			return 0;

		case NODE_BINARY_OP:
		{
			const char* opcode = mapBinaryOpcode(expression->binaryOp.op);
			if (!opcode)
			{
				emitLine(emitter, "; unsupported binary op %s", expression->binaryOp.op);
				return 0;
			}

			if (emitExpression(emitter, expression->binaryOp.left) != 0)
			{
				return -1;
			}
			if (emitExpression(emitter, expression->binaryOp.right) != 0)
			{
				return -1;
			}
			emitLine(emitter, "%s", opcode);
			return 0;
		}

		case NODE_CALL:
			return emitCallable(emitter, NULL, expression->call.functionName, expression->call.arguments);

		case NODE_METHOD_CALL:
			return emitCallable(emitter, expression->methodCall.structName, expression->methodCall.methodName, expression->methodCall.arguments);

		case NODE_STRUCT_FIELD_ACCESS:
			emitLine(emitter, "LOAD_FIELD %s %s", expression->structFieldAccess.structName, expression->structFieldAccess.fieldName);
			return 0;

		case NODE_ARGUMENT:
			return emitExpression(emitter, expression->argument.expression);

		default:
			emitLine(emitter, "; unsupported expression node %d", expression->type);
			return 0;
	}
}

static int emitStatementList(StackICEmitter* emitter, ASTNode* statement)
{
	ASTNode* current = statement;
	while (current)
	{
		if (emitStatement(emitter, current) != 0)
		{
			return -1;
		}
		current = current->next;
	}

	return 0;
}

static int emitForUpdate(StackICEmitter* emitter, ASTNode* update)
{
	if (!update)
	{
		return 0;
	}

	if (update->type == NODE_BINARY_OP &&
		update->binaryOp.left &&
		update->binaryOp.left->type == NODE_IDENTIFIER &&
		update->binaryOp.right &&
		update->binaryOp.right->type == NODE_LITERAL &&
		strcmp(update->binaryOp.op, "+") == 0)
	{
		if (emitExpression(emitter, update->binaryOp.left) != 0)
		{
			return -1;
		}
		if (emitExpression(emitter, update->binaryOp.right) != 0)
		{
			return -1;
		}
		emitLine(emitter, "ADD");
		emitLine(emitter, "STORE %s", update->binaryOp.left->identifier.name);
		return 0;
	}

	if (emitExpression(emitter, update) != 0)
	{
		return -1;
	}
	emitLine(emitter, "POP");
	return 0;
}

static int emitStatement(StackICEmitter* emitter, ASTNode* statement)
{
	if (!statement)
	{
		return 0;
	}

	switch (statement->type)
	{
		case NODE_VAR_DECL:
			emitLine(emitter, "LOCAL %s", statement->varDecl.name);
			return 0;

		case NODE_VAR_DECL_ASSIGN:
			emitLine(emitter, "LOCAL %s", statement->varDeclAssign.name);
			if (emitExpression(emitter, statement->varDeclAssign.expression) != 0)
			{
				return -1;
			}
			emitLine(emitter, "STORE %s", statement->varDeclAssign.name);
			return 0;

		case NODE_ASSIGN:
			if (emitExpression(emitter, statement->assign.expression) != 0)
			{
				return -1;
			}
			emitLine(emitter, "STORE %s", statement->assign.name);
			return 0;

		case NODE_STRUCT_FIELD_ASSIGN:
			if (emitExpression(emitter, statement->structFieldAssign.expression) != 0)
			{
				return -1;
			}
			emitLine(emitter, "STORE_FIELD %s %s", statement->structFieldAssign.structName, statement->structFieldAssign.fieldName);
			return 0;

		case NODE_RETURN:
			if (statement->returnStmt.expression)
			{
				if (emitExpression(emitter, statement->returnStmt.expression) != 0)
				{
					return -1;
				}
			}
			emitLine(emitter, "RET");
			return 0;

		case NODE_CALL:
		{
			int produced = emitCallable(emitter, NULL, statement->call.functionName, statement->call.arguments);
			if (produced > 0)
			{
				emitLine(emitter, "POP");
			}
			return 0;
		}

		case NODE_METHOD_CALL:
		{
			int produced = emitCallable(emitter, statement->methodCall.structName, statement->methodCall.methodName, statement->methodCall.arguments);
			if (produced > 0)
			{
				emitLine(emitter, "POP");
			}
			return 0;
		}

		case NODE_IF:
		{
			char* elseLabel = makeLabel(emitter, "else");
			char* endLabel = makeLabel(emitter, "endif");

			if (emitExpression(emitter, statement->ifStmt.condition) != 0)
			{
				free(elseLabel);
				free(endLabel);
				return -1;
			}

			emitLine(emitter, "JZ %s", elseLabel);
			if (emitStatementList(emitter, statement->ifStmt.thenBranch) != 0)
			{
				free(elseLabel);
				free(endLabel);
				return -1;
			}
			emitLine(emitter, "JMP %s", endLabel);
			emitLine(emitter, "LABEL %s", elseLabel);
			if (emitStatementList(emitter, statement->ifStmt.elseBranch) != 0)
			{
				free(elseLabel);
				free(endLabel);
				return -1;
			}
			emitLine(emitter, "LABEL %s", endLabel);

			free(elseLabel);
			free(endLabel);
			return 0;
		}

		case NODE_FOR:
		{
			char* beginLabel = makeLabel(emitter, "for_begin");
			char* endLabel = makeLabel(emitter, "for_end");

			emitLine(emitter, "LABEL %s", beginLabel);

			if (statement->forStmt.init)
			{
				if (emitExpression(emitter, statement->forStmt.init) != 0)
				{
					free(beginLabel);
					free(endLabel);
					return -1;
				}
				emitLine(emitter, "POP");
			}

			if (statement->forStmt.condition)
			{
				if (emitExpression(emitter, statement->forStmt.condition) != 0)
				{
					free(beginLabel);
					free(endLabel);
					return -1;
				}
				emitLine(emitter, "JZ %s", endLabel);
			}

			if (emitStatementList(emitter, statement->forStmt.body) != 0)
			{
				free(beginLabel);
				free(endLabel);
				return -1;
			}

			if (emitForUpdate(emitter, statement->forStmt.update) != 0)
			{
				free(beginLabel);
				free(endLabel);
				return -1;
			}

			emitLine(emitter, "JMP %s", beginLabel);
			emitLine(emitter, "LABEL %s", endLabel);

			free(beginLabel);
			free(endLabel);
			return 0;
		}

		case NODE_ARGUMENT:
			return emitExpression(emitter, statement->argument.expression);

		default:
			emitLine(emitter, "; unsupported statement node %d", statement->type);
			return 0;
	}
}

static int emitParameters(StackICEmitter* emitter, ASTNode* parameter)
{
	ASTNode* current = parameter;
	while (current)
	{
		if (current->type == NODE_PARAMETER)
		{
			emitLine(emitter, "PARAM %s %s", current->parameter.name, describeType(current->parameter.type));
		}
		current = current->parameter.next;
	}

	return 0;
}

static int emitFields(StackICEmitter* emitter, ASTNode* field)
{
	ASTNode* current = field;
	while (current)
	{
		if (current->type == NODE_FIELD)
		{
			emitLine(emitter, "FIELD %s %s", current->field.name, describeType(current->field.type));
		}
		current = current->field.next;
	}

	return 0;
}

static int emitMethods(StackICEmitter* emitter, ASTNode* method)
{
	ASTNode* current = method;
	while (current)
	{
		if (current->type == NODE_METHOD)
		{
			emitLine(emitter, "METHOD %s %s", current->method.name, describeType(current->method.returnType));
			emitParameters(emitter, current->method.parameters);
		}
		current = current->method.next;
	}

	return 0;
}

static int emitTypeDecls(StackICEmitter* emitter, ASTNode* typeDecl)
{
	ASTNode* current = typeDecl;
	while (current)
	{
		if (current->type == NODE_STRUCT)
		{
			emitLine(emitter, "STRUCT %s", current->structDecl.name);
			emitFields(emitter, current->structDecl.fields);
			emitLine(emitter, "ENDSTRUCT");
		}
		else if (current->type == NODE_INTERFACE)
		{
			emitLine(emitter, "INTERFACE %s", current->interfaceDecl.name);
			emitMethods(emitter, current->interfaceDecl.methods);
			emitLine(emitter, "ENDINTERFACE");
		}
		current = current->next;
	}

	return 0;
}

static int emitFunction(StackICEmitter* emitter, ASTNode* function)
{
	emitLine(emitter, "FUNC %s", function->function.name);

	if (function->function.receiver)
	{
		emitLine(emitter, "RECEIVER %s %s", function->function.receiver->receiver.name, function->function.receiver->receiver.type);
	}

	emitParameters(emitter, function->function.parameters);

	if (emitStatementList(emitter, function->function.body) != 0)
	{
		return -1;
	}

	if (!function->function.body || function->function.body->type != NODE_RETURN)
	{
		emitLine(emitter, "RET");
	}

	emitLine(emitter, "ENDFUNC");
	return 0;
}

static int emitFunctions(StackICEmitter* emitter, ASTNode* function)
{
	ASTNode* current = function;
	while (current)
	{
		if (current->type == NODE_FUNCTION)
		{
			if (emitFunction(emitter, current) != 0)
			{
				return -1;
			}
		}
		current = current->next;
	}

	return 0;
}

StackICEmitter* createStackICEmitter(FILE* output)
{
	StackICEmitter* emitter = (StackICEmitter*)malloc(sizeof(StackICEmitter));
	if (!emitter)
	{
		return NULL;
	}

	emitter->output = output;
	emitter->labelCounter = 0;
	return emitter;
}

void destroyStackICEmitter(StackICEmitter* emitter)
{
	free(emitter);
}

int emitStackICProgram(StackICEmitter* emitter, ASTNode* ast)
{
	if (!emitter || !ast || ast->type != NODE_PROGRAM)
	{
		return 1;
	}

	emitLine(emitter, "; GoLite stack IC");
	emitLine(emitter, "MODULE %s", "main");

	if (ast->program.imports)
	{
		ASTNode* current = ast->program.imports;
		while (current)
		{
			if (current->type == NODE_IMPORT)
			{
				emitLine(emitter, "IMPORT %s", current->import.path);
			}
			current = current->next;
		}
	}

	if (emitTypeDecls(emitter, ast->program.type_decls) != 0)
	{
		return 1;
	}

	if (emitFunctions(emitter, ast->program.functions) != 0)
	{
		return 1;
	}

	emitLine(emitter, "HALT");
	return 0;
}
