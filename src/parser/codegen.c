#include "codegen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int backendErrorFlag = 0;

static void codegenError(const char* message)
{
	fprintf(stderr, "CODEGEN ERROR: %s\n", message);
	backendErrorFlag = 1;
}

CodegenContext* createCodegenContext(const char* input_file, const char* output_file)
{
	CodegenContext* context = (CodegenContext*)malloc(sizeof(CodegenContext));
	if (!context)
	{
		codegenError("Failed to allocate code generation context");
		return NULL;
	}

	memset(context, 0, sizeof(CodegenContext));
	if (input_file)
	{
		strncpy(context->input_file, input_file, sizeof(context->input_file) - 1);
	}
	if (output_file)
	{
		strncpy(context->output_file, output_file, sizeof(context->output_file) - 1);
	}
	else
	{
		strncpy(context->output_file, "output.ic", sizeof(context->output_file) - 1);
	}

	return context;
}

void freeCodegenContext(CodegenContext* context)
{
	free(context);
}

int generateCode(ASTNode* ast, CodegenContext* context)
{
	if (!ast || !context)
	{
		codegenError("Invalid input to code generator");
		return 1;
	}

	backendErrorFlag = 0;

	FILE* output = fopen(context->output_file, "w");
	if (!output)
	{
		codegenError("Failed to open output file");
		return 1;
	}

	StackICEmitter* emitter = createStackICEmitter(output);
	if (!emitter)
	{
		fclose(output);
		codegenError("Failed to create stack IC emitter");
		return 1;
	}

	fprintf(output, "; Source: %s\n", context->input_file);

	if (emitStackICProgram(emitter, ast) != 0)
	{
		destroyStackICEmitter(emitter);
		fclose(output);
		codegenError("Failed to emit stack IC");
		return 1;
	}

	destroyStackICEmitter(emitter);
	fclose(output);
	printf("BACKEND: Stack IC written to %s\n", context->output_file);
	return 0;
}
