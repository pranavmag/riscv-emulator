# riscv-toolchain

A complete, self-hosted RISC-V toolchain built from scratch in C++ — no external dependencies beyond the standard library. The project consists of a cycle-accurate CPU emulator and a C compiler that targets it directly, producing flat binaries that run end-to-end on the emulator.

Built alongside study of Patterson & Hennessy's *Computer Organization and Design: RISC-V Edition* and documented on [YouTube](https://www.youtube.com/@NootNavDev).

---

## Repository Structure

```
riscv-toolchain/
├── emulator/          # RISC-V CPU emulator (RV32I + M + F)
│   └── src/
│       ├── decoder.h / decoder.cpp        # Instruction decode logic
│       ├── interpreter.h / interpreter.cpp # Execution, pipeline, memory
│       └── main.cpp                        # Entry point, mode selection
├── compiler/          # C subset compiler targeting the emulator (in progress)
│   └── src/
│       └── main.cpp
├── shared/            # Shared types (IR structs, etc.) — header-only
│   └── include/shared/
└── CMakeLists.txt     # Root CMake — C++20, out-of-source builds enforced
```

---

## Emulator

A cycle-accurate RISC-V emulator supporting the full **RV32I + RV32M + RV32F** ISA. Two execution modes are implemented: single-cycle and a 5-stage pipelined core with hazard handling.

### ISA Coverage

| Extension | Instructions |
|-----------|-------------|
| RV32I | All base integer instructions — arithmetic, logic, shifts, branches, loads, stores, jumps, environment |
| RV32M | MUL, MULH, MULHU, MULHSU, DIV, DIVU, REM, REMU |
| RV32F | FLW, FSW, FADD.S, FSUB.S, FMUL.S, FDIV.S, FSQRT.S, FMIN, FMAX, FMADD.S, FMSUB.S, FNMADD.S, FNMSUB.S, FSGNJ.S, FSGNJN.S, FSGNJX.S, FCVT.W.S, FCVT.WU.S, FCVT.S.W, FCVT.S.WU, FMV.X.W, FMV.W.X, FEQ.S, FLT.S, FLE.S, FCLASS.S |

### Pipeline (5-Stage)

The pipelined core implements the classic **IF → ID → EX → MEM → WB** stages with:

- Double-buffered pipeline registers simulating hardware clock edges
- **Data hazard resolution** via full forwarding (EX/MEM and MEM/WB paths)
- **Load-use hazard** detection with 1-cycle stall insertion
- **Control hazard** resolution via predict-not-taken with 2-cycle flush on misprediction

### Memory & ABI

- 64KB byte-addressed, little-endian flat memory
- Stack pointer initialized to top of memory (`0x10000`)
- Loads raw flat `.bin` files — no ELF parsing
- Custom ECALL ABI: `a7=1` prints integer in `a0`; `a7=93` exits

### Modes

| Mode | Description |
|------|-------------|
| Disassembler | Decode 32-bit binary strings and print assembly mnemonics |
| Manual interpreter | Enter binary instructions, execute, dump register state |
| Binary interpreter | Load a `.bin` file, run, dump register state |

### Verification

Verified against a Fibonacci sequence program (compiled with xPack RISC-V Embedded GCC) producing correct results across register file, branches, and loop control flow.

---

## Compiler (In Progress)

A C subset compiler targeting the emulator directly. The goal is a complete, self-contained toolchain where source code is compiled entirely in-house and executed on the emulator without any external tools in the loop.

### Architecture

```
Source (.c)
    └── Lexer           → token stream
    └── Parser          → Abstract Syntax Tree (AST)
    └── IR Generator    → flat three-address IR with virtual registers
    └── Register Allocator (Naive / Stack-Based)
    └── Code Generator  → RISC-V assembly (.s)
    └── xPack as        → object file        [v1: external]
    └── objcopy         → flat binary (.bin) [v1: external]
    └── Emulator        → execution
```

The IR layer decouples the front end from code generation, making the allocator swappable without touching the rest of the pipeline.

### Calling Convention

Standard RISC-V Base Integer Calling Convention (as per Patterson & Hennessy):
- Arguments in `a0`–`a7`, return value in `a0`, return address in `ra`
- Stack frame managed with callee-saved prologue/epilogue

### Target Language Subset (v1)

- Integer variables and arithmetic (`int`, `+`, `-`, `*`, `/`, `%`)
- Comparison and logical operators
- `if` / `else`
- `while` loops
- Functions with arguments and return values
- `print(x)` via ECALL

---

## Build

**Requirements:** CMake 3.20+, a C++20-capable compiler (MSVC, GCC, or Clang)

```bash
git clone https://github.com/pranavmag/riscv-emulator
cd riscv-toolchain

mkdir build
cd build
cmake ..
cmake --build .
```

In-source builds are explicitly rejected by the root CMakeLists.

**Visual Studio:** Open the `riscv-toolchain/` folder directly via **File → Open → Folder**. Visual Studio detects the CMakeLists automatically — no `.sln` or `.vcxproj` needed.

---

## Roadmap

### Emulator

- [x] Instruction decoder — all RV32I formats (R, I, S, B, J, U)
- [x] Single-cycle execution engine
- [x] Byte-addressed memory with little-endian read/write
- [x] Flat `.bin` file loading
- [x] Disassembler mode
- [x] Program counter and fetch-decode-execute loop
- [x] Branches, loads, stores, jumps
- [x] RV32M extension (multiply/divide)
- [x] RV32F extension (single-precision float)
- [x] 5-stage pipeline with forwarding and hazard detection
- [x] Fibonacci verification

### Compiler

- [ ] Lexer — tokenize C subset source
- [ ] Parser — recursive descent, build AST
- [ ] IR Generator — three-address IR with virtual registers
- [ ] Naive register allocator — all variables on stack
- [ ] Code generator — emit RISC-V assembly
- [ ] End-to-end: compile and run a C program on the emulator
- [ ] Upgrade to linear scan register allocator

### Toolchain

- [ ] Binary emitter — emit `.bin` directly (remove xPack dependency)
- [ ] CMake integration — single command builds and runs a `.c` file

---

## Learning Resources

- Patterson & Hennessy — *Computer Organization and Design: RISC-V Edition*
- Nystrom — *Crafting Interpreters*

Documented on YouTube: [NootNavDev](https://www.youtube.com/@NootNavDev)
