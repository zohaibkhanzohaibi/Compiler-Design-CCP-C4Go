# C4Go - A Lightweight Compiler for a Subset of Go 🚀

This project implements a lexer and parser for a subset of the Go programming language. The implementation is designed to handle basic Go constructs and provide a foundation for further development.

## Features Handled

### 1. Lexer Features 🔍
- **Keywords**: `package`, `import`, `func`, `return`, `var`, `if`, `else`, `for`, `int`, `float64`, `string`, `bool`, `true`, `false`, `struct`, `interface`, `type`, `map`, `slice`, `chan`.
- **Identifiers**: Valid Go identifiers (e.g., `x`, `myVar`, `MyStruct`).
- **Literals**:
  - Integers (e.g., `10`).
  - Floats (e.g., `3.14`).
  - Strings (e.g., `"hello"`).
- **Operators**:
  - Arithmetic: `+`, `-`, `*`, `/`.
  - Comparison: `==`, `!=`, `<`, `>`, `<=`, `>=`.
  - Logical: `&&`, `||`.
  - Bitwise: `&`, `|`, `^`, `<<`, `>>`.
  - Assignment: `=`, `:=`, `++`.
- **Punctuation**: `(`, `)`, `{`, `}`, `;`, `,`, `.`.

### 2. Parser Features 🔧
- **Program Structure**:
  - `package` declaration.
  - `import` statements.
  - `type` declarations for `struct` and `interface`.
  - `func` declarations with support for method receivers.
- **Statements**:
  - Variable declarations (`var`).
  - Assignments (`=`, `:=`).
  - Control flow:
    - `if`-`else` statements.
    - `for` loops.
  - Function calls and method calls.
  - `return` statements.
- **Expressions**:
  - Arithmetic, comparison, logical, and bitwise expressions.
  - Struct field access (e.g., `p.name`).
  - Method calls (e.g., `fmt.Println`).
- **Error Recovery**:
  - Skips invalid statements and continues parsing.
- **AST Creation**:
  - The parser generates an Abstract Syntax Tree (AST) representing the parsed program.
  - The AST includes nodes for all supported program structures, statements, and expressions.
  - The AST is structured to facilitate further analysis and code generation.
- **Semantic Analysis**:
  - The parser performs semantic analysis to ensure the correctness of the parsed program.
  - Semantic analysis includes type checking, scope resolution, and validation of method receivers.
  - Errors detected during semantic analysis are reported with relevant error messages.

### 3. Supported Go Constructs 📦
- **Structs**:
  ```go
  type Person struct {
      name string;
      age  int;
  };
  ```
- **Interfaces**:
  ```go
  type Writer interface {
      Write(data string);
  };
  ```
- **Functions**:
  ```go
  func add(a int, b int) int {
      return a + b;
  }
  ```
- **Methods**:
  ```go
  func (p Person) PrintName() {
      fmt.Println(p.name);
  }
  ```
- **Control Flow**:
  ```go
  if x > 5 {
      fmt.Println("x is greater than 5");
  } else {
      fmt.Println("x is less than or equal to 5");
  }
  ```
- **Loops**:
  ```go
  for i := 0; i < 10; i++ {
      fmt.Println(i);
  }
  ```

## Remaining Features 🚧

The following Go features are **not yet implemented**:

### 1. Lexer
- **Complex Numbers**: Go supports complex numbers (e.g., `1+2i`), which are not yet handled.
- **Runes**: Go supports rune literals (e.g., `'a'`), which are not yet handled.
- **More Operators**: Some operators like `%` (modulus) and `...` (variadic) are not yet handled.

### 2. Parser
- **Advanced Types**:
  - Arrays and slices (e.g., `[]int`, `[5]int`).
  - Maps (e.g., `map[string]int`).
  - Channels (e.g., `chan int`).
- **Advanced Control Flow**:
  - `switch` statements.
  - `defer` statements.
  - `goto` statements.
- **Concurrency**:
  - Goroutines (`go` keyword).
  - Channel operations (`<-`).
- **Error Handling**:
  - `panic` and `recover`.
- **Type Assertions and Type Switches**:
  - Type assertions (e.g., `x.(int)`).
  - Type switches.
- **Variadic Functions**:
  - Functions with variadic parameters (e.g., `func sum(nums ...int)`).

### 3. Semantic Analysis
- **Package Management**:
  - Handle imports and package-level declarations.

### 4. Code Generation
- **Intermediate Code Generation (ICG)**:
  - Generate three-address code or another intermediate representation.
- **Optimization**:
  - Perform optimizations like constant folding, dead code elimination, etc.
- **Target Code Generation**:
  - Generate machine code or assembly for a specific target architecture.

## Design Decision: Semicolons ✏️
- **Explicit Semicolons**:
  - Unlike the Go compiler, which automatically inserts semicolons, our lexer and parser require explicit semicolons (`;`) to terminate statements.
  - This decision was made to keep the implementation simple and avoid the complexity of automatic semicolon insertion.

## Future Work 🔮

The next steps include:
- Implementing the remaining lexer and parser features.
- Developing code generation capabilities.
- Enhancing error handling and recovery mechanisms.


