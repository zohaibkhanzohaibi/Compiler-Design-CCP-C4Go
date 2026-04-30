# Compiler and tools
CC = gcc
FLEX = flex
BISON = bison

# Directories
SRC_DIR = src
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
TEST_DIR = test
BUILD_DIR = build

# Targets
TARGET = $(BUILD_DIR)/go_compiler
TEST_FILES = $(wildcard $(TEST_DIR)/test*.go)

# Source files
LEXER_SRC = $(LEXER_DIR)/lexer.l
PARSER_SRC = $(PARSER_DIR)/parser.y
AST_SRC = $(PARSER_DIR)/ast.c
SEMANTIC_SRC = $(PARSER_DIR)/semantic.c
ICG_SRC = $(PARSER_DIR)/icg.c
OPTIMIZE_SRC = $(PARSER_DIR)/optimize.c
CODEGEN_SRC = $(PARSER_DIR)/codegen.c
CJSON_SRC = $(PARSER_DIR)/cJSON.c

# Generated files
LEXER_OUT = $(BUILD_DIR)/lex.yy.c
PARSER_OUT_C = $(BUILD_DIR)/parser.tab.c
PARSER_OUT_H = $(BUILD_DIR)/parser.tab.h

# Default target
all: $(TARGET)

# Build the compiler
$(TARGET): $(LEXER_OUT) $(PARSER_OUT_C) $(AST_SRC) $(SEMANTIC_SRC) $(ICG_SRC) $(OPTIMIZE_SRC) $(CODEGEN_SRC) $(CJSON_SRC)
	$(CC) $(LEXER_OUT) $(PARSER_OUT_C) $(AST_SRC) $(SEMANTIC_SRC) $(ICG_SRC) $(OPTIMIZE_SRC) $(CODEGEN_SRC) $(CJSON_SRC) -o $(TARGET) -I$(PARSER_DIR) -g

# Generate lexer
$(LEXER_OUT): $(LEXER_SRC)
	$(FLEX) -o $(LEXER_OUT) $(LEXER_SRC)

# Generate parser
$(PARSER_OUT_C) $(PARSER_OUT_H): $(PARSER_SRC)
	$(BISON) -d -o $(PARSER_OUT_C) $(PARSER_SRC)

# Clean up generated files
clean:
	rm -rf $(BUILD_DIR)/*

# Test the compiler with test files
test: $(TARGET)
	@for file in $(TEST_FILES); do \
		echo "Testing $$file..."; \
		$(TARGET) $$file; \
		echo "----------------------------------------"; \
	done

# Use the compiler on a specific source file
compile: $(TARGET)
	@if [ -z "$(SOURCE_FILE)" ]; then \
		echo "Error: SOURCE_FILE variable is not set."; \
		exit 1; \
	fi
	$(TARGET) $(SOURCE_FILE)