#!/usr/bin/env python3
"""Tiny stack VM for GoLite stack IC output."""

from __future__ import annotations

import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple


@dataclass
class Instruction:
    op: str
    args: List[str]
    raw: str


class VMError(RuntimeError):
    pass


class StackVM:
    def __init__(self, instructions: List[Instruction]) -> None:
        self.instructions = instructions
        self.stack: List[Any] = []
        self.locals: Dict[str, Any] = {}
        self.labels = self._build_labels(instructions)
        self.ip = 0
        self.halted = False

    @staticmethod
    def _build_labels(instructions: List[Instruction]) -> Dict[str, int]:
        labels: Dict[str, int] = {}
        for index, instr in enumerate(instructions):
            if instr.op == "LABEL" and instr.args:
                labels[instr.args[0]] = index
        return labels

    def push(self, value: Any) -> None:
        self.stack.append(value)

    def pop(self) -> Any:
        if not self.stack:
            raise VMError("Stack underflow")
        return self.stack.pop()

    def _binary_numeric(self, func) -> None:
        right = self.pop()
        left = self.pop()
        self.push(func(left, right))

    def _binary_compare(self, func) -> None:
        right = self.pop()
        left = self.pop()
        self.push(1 if func(left, right) else 0)

    def jump_to(self, label: str) -> None:
        if label not in self.labels:
            raise VMError(f"Unknown label: {label}")
        self.ip = self.labels[label]

    def run(self) -> None:
        while not self.halted and self.ip < len(self.instructions):
            instr = self.instructions[self.ip]
            self.execute(instr)
            self.ip += 1

    def execute(self, instr: Instruction) -> None:
        op = instr.op
        args = instr.args

        if op in {"MODULE", "IMPORT", "FUNC", "ENDFUNC"}:
            return
        if op == "HALT":
            self.halted = True
            return
        if op == "LABEL":
            return
        if op == "LOCAL":
            if not args:
                raise VMError("LOCAL requires a variable name")
            self.locals[args[0]] = None
            return
        if op == "LOAD":
            if not args:
                raise VMError("LOAD requires a variable name")
            name = args[0]
            if name not in self.locals:
                raise VMError(f"Undeclared variable: {name}")
            value = self.locals[name]
            if value is None:
                raise VMError(f"Variable not initialized: {name}")
            self.push(value)
            return
        if op == "STORE":
            if not args:
                raise VMError("STORE requires a variable name")
            self.locals[args[0]] = self.pop()
            return
        if op == "PUSH_INT":
            self.push(int(args[0]))
            return
        if op == "PUSH_FLOAT":
            self.push(float(args[0]))
            return
        if op == "PUSH_STRING":
            self.push(self._parse_string_arg(args))
            return
        if op == "PUSH_BOOL":
            self.push(int(args[0]))
            return
        if op == "ADD":
            self._binary_numeric(lambda a, b: a + b)
            return
        if op == "SUB":
            self._binary_numeric(lambda a, b: a - b)
            return
        if op == "MUL":
            self._binary_numeric(lambda a, b: a * b)
            return
        if op == "DIV":
            self._binary_numeric(lambda a, b: a / b)
            return
        if op == "GT":
            self._binary_compare(lambda a, b: a > b)
            return
        if op == "LT":
            self._binary_compare(lambda a, b: a < b)
            return
        if op == "GE":
            self._binary_compare(lambda a, b: a >= b)
            return
        if op == "LE":
            self._binary_compare(lambda a, b: a <= b)
            return
        if op == "EQ":
            self._binary_compare(lambda a, b: a == b)
            return
        if op == "NE":
            self._binary_compare(lambda a, b: a != b)
            return
        if op == "AND":
            self._binary_compare(lambda a, b: bool(a) and bool(b))
            return
        if op == "OR":
            self._binary_compare(lambda a, b: bool(a) or bool(b))
            return
        if op == "JZ":
            if not args:
                raise VMError("JZ requires a label")
            condition = self.pop()
            if not bool(condition):
                self.jump_to(args[0])
            return
        if op == "JMP":
            if not args:
                raise VMError("JMP requires a label")
            self.jump_to(args[0])
            return
        if op == "PRINTLN":
            count = int(args[0]) if args else 1
            values = [self.pop() for _ in range(count)][::-1]
            print(*values)
            return
        if op == "RET":
            self.halted = True
            return
        if op == "CALL" or op == "CALL_METHOD" or op == "LOAD_FIELD" or op == "STORE_FIELD" or op == "PARAM" or op == "RECEIVER" or op == "FIELD" or op == "METHOD" or op == "STRUCT" or op == "INTERFACE" or op == "ENDSTRUCT" or op == "ENDINTERFACE":
            return
        if op == "POP":
            self.pop()
            return
        raise VMError(f"Unsupported instruction: {instr.raw}")

    @staticmethod
    def _parse_string_arg(args: List[str]) -> str:
        if not args:
            return ""
        joined = " ".join(args)
        if joined.startswith('"') and joined.endswith('"') and len(joined) >= 2:
            return joined[1:-1]
        return joined


def tokenize_instruction(line: str) -> Optional[Instruction]:
    stripped = line.strip()
    if not stripped or stripped.startswith(";"):
        return None
    parts = stripped.split()
    return Instruction(op=parts[0], args=parts[1:], raw=stripped)


def load_program(path: Path) -> List[Instruction]:
    instructions: List[Instruction] = []
    for line in path.read_text(encoding="utf-8").splitlines():
        instr = tokenize_instruction(line)
        if instr is not None:
            instructions.append(instr)
    return instructions


def main(argv: List[str]) -> int:
    if len(argv) < 2:
        print("Usage: python stack_vm.py <output.ic>")
        return 1

    program_path = Path(argv[1])
    if not program_path.exists():
        print(f"File not found: {program_path}")
        return 1

    instructions = load_program(program_path)
    vm = StackVM(instructions)
    try:
        vm.run()
    except VMError as exc:
        print(f"VM ERROR: {exc}")
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
