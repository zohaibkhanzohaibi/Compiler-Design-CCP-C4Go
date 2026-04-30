%{
#include "ast.h"
#include "semantic.h"
#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ANSI color codes
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"

extern int yylineno; // Declare yylineno from lexer
extern FILE* yyin;   // Declare yyin from lexer
extern int yylex();  // Declare yylex
extern char** global_argv;

// Define yyerror
void yyerror(const char *s) {
    fprintf(stderr, COLOR_RED "Error at line %d: %s\n" COLOR_RESET, yylineno, s);
}
%}

%code requires {
#include "ast.h"
#include "semantic.h"
}

// Union for semantic values
%union {
    int num;
    double fnum;
    char* str;
    ASTNode* node;
}

// Token declarations
%token <str> PACKAGE IMPORT FUNC RETURN VAR IF ELSE FOR
%token <str> INT_TYPE FLOAT64_TYPE STRING_TYPE BOOL_TYPE VOID_TYPE TRUE FALSE STRUCT INTERFACE MAP SLICE CHAN TYPE
%token <str> IDENTIFIER STRING
%token <num> INTEGER INCREMENT
%token <fnum> FLOAT
%token PLUS MINUS MULTIPLY DIVIDE ASSIGN EQ NEQ LT GT LTE GTE AND OR LSHIFT RSHIFT BITAND BITOR BITXOR
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA DOT DECLARE_ASSIGN 

// Precedence and associativity
%left OR
%left AND
%left EQ NEQ
%left LT GT LTE GTE
%left LSHIFT RSHIFT
%left PLUS MINUS
%left MULTIPLY DIVIDE
%left BITAND BITOR BITXOR

// Type declarations for non-terminals
%type <node> program imports type_decls functions field_decls method_decls type receiver return_type parameters statements statement arguments expression

%%
// Grammar rules
program:
    PACKAGE IDENTIFIER SEMICOLON imports type_decls functions
    { 
      $$ = createProgramNode($4, $5, $6);
      if (semanticAnalyze($$)) { // perform semantic analysis
            fprintf(stderr, COLOR_RED "PARSER: Semantic errors detected, exiting...\n" COLOR_RESET);
            YYABORT; // This will make Bison return 1 from yyparse()
      }
      printf(COLOR_GREEN "PARSER: Program parsed successfully\n" COLOR_RESET);
      printAST($$, 0, 0, NULL); // Print AST for debugging
      printAST($$, 0, 1, "ast.json"); // Print AST to JSON file
      printf(COLOR_GREEN "PARSER: AST created successfully\n" COLOR_RESET);

        CodegenContext* context = createCodegenContext(
          (global_argv && global_argv[1]) ? global_argv[1] : "input.go",
          "output.ic");
        if (context && generateCode($$, context) == 0) {
          printf(COLOR_GREEN "BACKEND: Stack IC written to output.ic\n" COLOR_RESET);
        } else {
          fprintf(stderr, COLOR_RED "BACKEND: Code generation failed\n" COLOR_RESET);
        }
        freeCodegenContext(context);
    }
    ;

imports:
    /* empty */
    { $$ = NULL; }
    | IMPORT STRING SEMICOLON imports
    { 
      $$ = createImportNode($2, $4);
      printf(COLOR_BLUE "PARSER: Import statement parsed\n" COLOR_RESET); 
    }
    ;

type_decls:
    /* empty */
    { $$ = NULL; }
    | TYPE IDENTIFIER STRUCT LBRACE field_decls RBRACE SEMICOLON type_decls
    { 
       $$ = createStructNode($2, $5);
       $$->next = $8;
       printf(COLOR_BLUE "PARSER: Struct declaration parsed\n" COLOR_RESET); 
    }
    | TYPE IDENTIFIER INTERFACE LBRACE method_decls RBRACE SEMICOLON type_decls
    { 
       $$ = createInterfaceNode($2, $5);
       $$->next = $8;
       printf(COLOR_BLUE "PARSER: Interface declaration parsed\n" COLOR_RESET); 
    }
    ;

field_decls:
    /* empty */
    { $$ = NULL; }
    | IDENTIFIER type SEMICOLON field_decls
    { 
      $$ = createFieldNode($1, $2, $4);
      printf(COLOR_BLUE "PARSER: Field declaration parsed\n" COLOR_RESET); 
    }
    ;

method_decls:
    /* empty */
    { $$ = NULL; }
    | IDENTIFIER LPAREN parameters RPAREN type SEMICOLON method_decls
    { 
      $$ = createMethodNode($1, $3, $5, $7);
      printf(COLOR_BLUE "PARSER: Method declaration parsed\n" COLOR_RESET); 
    }
    ;

type:
    INT_TYPE
    { $$ = createTypeNode("int"); }
    | FLOAT64_TYPE
    { $$ = createTypeNode("float64"); }
    | STRING_TYPE
    { $$ = createTypeNode("string"); }
    | BOOL_TYPE
    { $$ = createTypeNode("bool"); }
    | VOID_TYPE
    { $$ = createTypeNode("void"); }
    | MAP LBRACE type RBRACE type
    { $$ = createMapTypeNode($3, $5); }
    | SLICE LBRACE RBRACE type
    { $$ = createSliceTypeNode($4); }
    | CHAN type
    { $$ = createChanTypeNode($2); }
    | IDENTIFIER  // Allow IDENTIFIER as a type for structs and interfaces
    { $$ = createTypeNode($1); }
    ;

functions:
    /* empty */
    { $$ = NULL; }
    | FUNC receiver IDENTIFIER LPAREN parameters RPAREN return_type LBRACE statements RBRACE functions
    {
        ASTNode* newFunction = createFunctionNode($3, $2, $5, $7, $9, $11);
        printf(COLOR_BLUE "PARSER: Function parsed : %s\n" COLOR_RESET, $3);
        $$ = newFunction;
    }
    ;

receiver:
    /* empty */
    { $$ = NULL; }
    | LPAREN IDENTIFIER IDENTIFIER RPAREN
    {
      $$ = createReceiverNode($2, $3);
      printf(COLOR_BLUE "PARSER: Receiver parsed\n" COLOR_RESET);
    }
    ;

return_type:
    /* empty */
    { $$ = createTypeNode("void"); }
    | type
    { $$ = $1; }
    ;

parameters:
    /* empty */
    { $$ = NULL; }
    | IDENTIFIER type COMMA parameters
    { 
      $$ = createParameterNode($1, $2, $4);
      printf(COLOR_BLUE "PARSER: Parameter parsed\n" COLOR_RESET); 
    }
    | IDENTIFIER type
    { 
      $$ = createParameterNode($1, $2, NULL);
      printf(COLOR_BLUE "PARSER: Parameter parsed\n" COLOR_RESET); 
    }
    ;

statements:
    /* empty */
    { $$ = NULL; }
    | statement statements
    { 
      if ($1 != NULL && $2 != NULL) {
        $1->next = $2;
      }
      $$ = $1;
    }
    ;

statement:
    RETURN expression SEMICOLON
    { 
      $$ = createReturnNode($2, NULL);
      printf(COLOR_BLUE "PARSER: Return statement parsed\n" COLOR_RESET); 
    }
    | VAR IDENTIFIER type SEMICOLON
    { 
      $$ = createVarDeclNode($2, $3, NULL);
      printf(COLOR_BLUE "PARSER: Variable declaration parsed\n" COLOR_RESET); 
    }
    | VAR IDENTIFIER type ASSIGN expression SEMICOLON
    { 
      $$ = createVarDeclAssignNode($2, $3, $5, NULL);
      printf(COLOR_BLUE "PARSER: Variable declaration with assignment parsed\n" COLOR_RESET); 
    }
    | IDENTIFIER ASSIGN expression SEMICOLON
    { 
      $$ = createAssignNode($1, $3, NULL);
      printf(COLOR_BLUE "PARSER: Assignment statement parsed\n" COLOR_RESET); 
    }
    | IDENTIFIER DOT IDENTIFIER ASSIGN expression SEMICOLON
    { 
      $$ = createStructFieldAssignNode($1, $3, $5, NULL);
      printf(COLOR_BLUE "PARSER: Struct field assignment parsed\n" COLOR_RESET); 
    }
    | IDENTIFIER DOT IDENTIFIER LPAREN arguments RPAREN SEMICOLON
    { 
      $$ = createMethodCallNode($1, $3, $5, NULL);
      printf(COLOR_BLUE "PARSER: Method call parsed\n" COLOR_RESET); 
    }
    | IDENTIFIER LPAREN arguments RPAREN SEMICOLON
    {
      $$ = createCallNode($1, $3);
      printf(COLOR_BLUE "PARSER: Function call parsed\n" COLOR_RESET); 
    }
    | IF expression LBRACE statements RBRACE ELSE LBRACE statements RBRACE
    { 
      $$ = createIfNode($2, $4, $8);
      printf(COLOR_BLUE "PARSER: If-else statement parsed\n" COLOR_RESET); 
    }
    | FOR IDENTIFIER DECLARE_ASSIGN expression SEMICOLON expression SEMICOLON IDENTIFIER INCREMENT LBRACE statements RBRACE
    { 
      // Create an AST node for the increment operation
      ASTNode* incrementNode = createBinaryOpNode("+", createIdentifierNode($8), createLiteralNode("int", &(int){1}));
      $$ = createForNode($4, $6, incrementNode, $11);
      printf(COLOR_BLUE "PARSER: For loop parsed\n" COLOR_RESET); 
    }
    | error SEMICOLON
    { 
      printf(COLOR_RED "PARSER: Error recovery\n" COLOR_RESET); 
      $$ = NULL;
    }
    ;

arguments:
    /* empty */
    { $$ = NULL; }
    | expression
    { $$ = createArgumentNode($1, NULL); }
    | expression COMMA arguments
    { $$ = createArgumentNode($1, $3); }
    ;

expression:
    INTEGER
    { 
      int value = $1;
      $$ = createLiteralNode("int", &value);
      printf(COLOR_BLUE "PARSER: Integer expression parsed\n" COLOR_RESET); 
    }
    | FLOAT
    { 
      double value = $1;
      $$ = createLiteralNode("float", &value);
      printf(COLOR_BLUE "PARSER: Float expression parsed\n" COLOR_RESET); 
    }
    | STRING
    { 
      $$ = createLiteralNode("string", $1);
      printf(COLOR_BLUE "PARSER: String expression parsed\n" COLOR_RESET); 
    }
    | TRUE
    { 
      bool value = true;
      $$ = createLiteralNode("bool", &value);
      printf(COLOR_BLUE "PARSER: True expression parsed\n" COLOR_RESET); 
    }
    | FALSE
    { 
      bool value = false;
      $$ = createLiteralNode("bool", &value);
      printf(COLOR_BLUE "PARSER: False expression parsed\n" COLOR_RESET); 
    }
    | IDENTIFIER
    { 
      $$ = createIdentifierNode($1);
      printf(COLOR_BLUE "PARSER: Identifier expression parsed\n" COLOR_RESET); 
    }
    | IDENTIFIER DOT IDENTIFIER
    { 
      $$ = createStructFieldAccessNode($1, $3);
      printf(COLOR_BLUE "PARSER: Struct field access parsed\n" COLOR_RESET); 
    }
    | IDENTIFIER DOT IDENTIFIER LPAREN arguments RPAREN
    { 
      $$ = createMethodCallNode($1, $3, $5, NULL);
      printf(COLOR_BLUE "PARSER: Method call parsed\n" COLOR_RESET); 
    }
    | IDENTIFIER LPAREN arguments RPAREN
    { 
      $$ = createCallNode($1, $3);
      printf(COLOR_BLUE "PARSER: Function call parsed\n" COLOR_RESET); 
    }
    | expression PLUS expression
    { 
      $$ = createBinaryOpNode("+", $1, $3);
      printf(COLOR_BLUE "PARSER: Addition expression parsed\n" COLOR_RESET); 
    }
    | expression MINUS expression
    { 
      $$ = createBinaryOpNode("-", $1, $3);
      printf(COLOR_BLUE "PARSER: Subtraction expression parsed\n" COLOR_RESET); 
    }
    | expression MULTIPLY expression
    { 
      $$ = createBinaryOpNode("*", $1, $3);
      printf(COLOR_BLUE "PARSER: Multiplication expression parsed\n" COLOR_RESET); 
    }
    | expression DIVIDE expression
    { 
      $$ = createBinaryOpNode("/", $1, $3);
      printf(COLOR_BLUE "PARSER: Division expression parsed\n" COLOR_RESET); 
    }
    | expression EQ expression
    { 
      $$ = createBinaryOpNode("==", $1, $3);
      printf(COLOR_BLUE "PARSER: Equality expression parsed\n" COLOR_RESET); 
    }
    | expression NEQ expression
    { 
      $$ = createBinaryOpNode("!=", $1, $3);
      printf(COLOR_BLUE "PARSER: Inequality expression parsed\n" COLOR_RESET); 
    }
    | expression LT expression
    { 
      $$ = createBinaryOpNode("<", $1, $3);
      printf(COLOR_BLUE "PARSER: Less-than expression parsed\n" COLOR_RESET); 
    }
    | expression GT expression
    { 
      $$ = createBinaryOpNode(">", $1, $3);
      printf(COLOR_BLUE "PARSER: Greater-than expression parsed\n" COLOR_RESET); 
    }
    | expression LTE expression
    { 
      $$ = createBinaryOpNode("<=", $1, $3);
      printf(COLOR_BLUE "PARSER: Less-than-or-equal expression parsed\n" COLOR_RESET); 
    }
    | expression GTE expression
    { 
      $$ = createBinaryOpNode(">=", $1, $3);
      printf(COLOR_BLUE "PARSER: Greater-than-or-equal expression parsed\n" COLOR_RESET); 
    }
    | expression AND expression
    { 
      $$ = createBinaryOpNode("&&", $1, $3);
      printf(COLOR_BLUE "PARSER: Logical AND expression parsed\n" COLOR_RESET); 
    }
    | expression OR expression
    { 
      $$ = createBinaryOpNode("||", $1, $3);
      printf(COLOR_BLUE "PARSER: Logical OR expression parsed\n" COLOR_RESET); 
    }
    | expression LSHIFT expression
    { 
      $$ = createBinaryOpNode("<<", $1, $3);
      printf(COLOR_BLUE "PARSER: Left shift expression parsed\n" COLOR_RESET); 
    }
    | expression RSHIFT expression
    { 
      $$ = createBinaryOpNode(">>", $1, $3);
      printf(COLOR_BLUE "PARSER: Right shift expression parsed\n" COLOR_RESET); 
    }
    | expression BITAND expression
    { 
      $$ = createBinaryOpNode("&", $1, $3);
      printf(COLOR_BLUE "PARSER: Bitwise AND expression parsed\n" COLOR_RESET); 
    }
    | expression BITOR expression
    { 
      $$ = createBinaryOpNode("|", $1, $3);
      printf(COLOR_BLUE "PARSER: Bitwise OR expression parsed\n" COLOR_RESET); 
    }
    | expression BITXOR expression
    { 
      $$ = createBinaryOpNode("^", $1, $3);
      printf(COLOR_BLUE "PARSER: Bitwise XOR expression parsed\n" COLOR_RESET); 
    }
    | LPAREN expression RPAREN
    { 
      $$ = $2;
      printf(COLOR_BLUE "PARSER: Parenthesized expression parsed\n" COLOR_RESET); 
    }
    ;

%%

char** global_argv;

int main(int argc, char **argv) {
  global_argv = argv;
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        yyin = file;
    }
      int parseResult = yyparse();
      return parseResult || backendErrorFlag;
}
