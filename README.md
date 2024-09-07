
---

# CProject

This repository contains my **UCA** project code. The goal of these projects is to construct an assembler and a virtual machine (VM) translator, both of which are essential steps toward building a fully functioning computer system.

## Project Overview

### Assembler
First, we build an **Assembler** to translate Hack assembly language into Hack machine code. The assembler converts each symbolic instruction in the `.asm` file into binary instructions that can be executed by the Hack computer.

- **Input**: `.asm` file containing Hack assembly code.
- **Output**: `.hack` file containing binary machine code.
- **Key Concepts**: Symbol tables, parsing assembly language, binary translation.

### Virtual Machine Translator
Then, we implement a **VM translator** that translates a high-level virtual machine language into Hack assembly code. The translator supports both arithmetic/memory operations and program control, enabling the execution of complex programs with function calls and branching.

- **Input**: `.vm` file containing VM code.
- **Output**: `.asm` file containing Hack assembly code.
- **Key Concepts**:
    - **Stack Operations**: Handling `push` and `pop` operations to manage memory.
    - **Arithmetic Operations**: Executing basic arithmetic and logical operations (e.g., add, sub, neg, eq).
    - **Program Control**: Implementing control flow commands like `goto`, `if-goto`, and `label`.
    - **Function Calls**: Managing function definitions, calls, and recursion through the stack-based approach, including `call`, `function`, and `return`.

## Directory Structure
```plaintext
.
├── helper
│   ├── hashmap.c
│   ├── hashmap.h
│   ├── myhashmap.c
│   └── myhashmap.h
├── src
│   ├── HackAssembler
│   │   ├── AssemblerSecondPass.c
│   │   ├── AssemblerSecondPass.h
│   │   ├── AsssemblerFirstPass.c
│   │   ├── AsssemblerFirstPass.h
│   │   ├── HackAssembler.c
│   │   └── HackAssembler.h
│   └── VMEmulator
│       ├── VMCodeTranslator.c
│       ├── VMCodeTranslator.h
│       ├── VMEmulator.c
│       ├── VMEmulator.h
│       ├── VMParser.c
│       └── VMParser.h
├── tests
|   ├── HackAssemblyFiles
|   ├── VMFiles
|   ├── Test.h
|   └── MyHashmapTest.c
├── CMakeLists.txt
├── main.c
└── README.md
```

## How to Run

### Prerequisites

Make sure you have the following installed on your system:
- **CMake**: version 3.10 or higher
- **GCC** or another C compiler

### Steps
```bash
# Step 1: Create the build directory and navigate into it
mkdir build
cd build

# Step 2: Generate the build files using CMake
cmake ..

# Step 3: Compile the project
cmake --build .

# Step 4a: Run the Assembler (mode 1) for assembler with a file named Prog.asm
./nand2tetris Prog.asm 1

# Step 4b: Run the VM Translator (mode 2) for VM translator with a file named SimpleAdd.vm
./nand2tetris SimpleAdd.vm 2
```

## Tools and Technologies
- **Language**: C (for assembler and VM translator implementation)
- **Course**: [Nand2Tetris](https://www.nand2tetris.org)
- **Platform**: Hack platform for running the generated assembly and machine code.

## References
- [The Elements of Computing Systems - Nand2Tetris](https://www.nand2tetris.org/)
- [Course Textbook: "The Elements of Computing Systems"](https://mitpress.mit.edu/books/elements-computing-systems)

## Credits

This project uses a hashmap implementation from an open-source GitHub repository:

- [Hashmap Implementation by tidwall](https://github.com/tidwall/hashmap)

## Author
- [Kheyanshu Garg](https://github.com/Kendo007)

---
