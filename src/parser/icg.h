#ifndef ICG_H
#define ICG_H

#include "ast.h"
#include <stdio.h>

typedef struct StackICEmitter StackICEmitter;

StackICEmitter* createStackICEmitter(FILE* output);
void destroyStackICEmitter(StackICEmitter* emitter);
int emitStackICProgram(StackICEmitter* emitter, ASTNode* ast);

#endif // ICG_H
