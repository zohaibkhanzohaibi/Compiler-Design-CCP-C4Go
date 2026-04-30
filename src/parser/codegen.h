#ifndef CODEGEN_H
#define CODEGEN_H

#include "icg.h"

typedef struct CodegenContext {
	char input_file[256];
	char output_file[256];
} CodegenContext;

extern int backendErrorFlag;

CodegenContext* createCodegenContext(const char* input_file, const char* output_file);
int generateCode(ASTNode* ast, CodegenContext* context);
void freeCodegenContext(CodegenContext* context);

#endif // CODEGEN_H
