# Witcher Tracker

This repository contains the C source code, documentation, and test scripts for the **Witcher Tracker** project, developed for the CMPE230 Systems Programming course at Boğaziçi University (Spring 2025).

---

##  Project Overview

Geralt of Rivia has lost his memory and all alchemical knowledge. This text‑based simulator helps Geralt rebuild his inventory and bestiary through a command‑driven interpreter:

- **Sentences**: Execute actions (loot, trade, brew, learn, encounter).
- **Questions**: Query inventory, bestiary, and recipes.
- **Exit**: Terminates the program.

The program enforces a strict grammar (BNF‑like) and manages dynamic data structures in C (resizable arrays, modular design, clear memory management).

---

##  Repository Structure

```
witcher-tracker-c/
├── src/                     # C source files
│   ├── main.c               # Program entry and dispatcher (execute_line)
│   ├── globals.h            # Global types, structs, and state declarations
│   ├── type_detections.c    # Lexical classification: sentences, questions, exit
│   ├── sentence_handle.c    # Handlers for LOOT, TRADE, BREW, LEARN, ENCOUNTER
│   ├── question_handle.c    # Handlers for inventory and bestiary queries
│   ├── utils.c              # Utility functions: parsing, sanitization, comparators
│   └── capacity_ensuring.c  # Dynamic array resizing routines
├── docs/
│   ├── report.pdf           # Detailed design report and results
├── test/                    # Test harness and sample inputs/outputs
│   ├── checker.py
│   └── grader.py
├── test-cases/              # Test input/output pairs
│   ├── input1.txt
│   ├── output1.txt
│   ├── input2.txt
│   ├── output2.txt
│   └── ...
├── Makefile                 # Build and test automation
├── README.md                # This file
└── .gitignore               # Common C/C++ ignores
```

---

##  Build & Run Instructions

1. **Build**

   ```bash
   make
   ```
   - Compiles all `.c` files into the `witchertracker` executable.

2. **Run**

   ```bash
   ./witchertracker
   ```
   - Enters interactive mode. Type commands or questions followed by Enter.
   - To exit, enter:
     ```text
     Exit
     ```

---

##  Automated Testing

- **Single case check**:
  ```bash
  python3 test/checker.py ./witchertracker test-cases/input1.txt test-cases/output1.txt
  ```

- **Full grading (run on all cases)**:
  ```bash
  python3 test/grader.py ./witchertracker test-cases/
  ```

---
##  Supported Commands & Grammar

### Sentence Types

| Command       | Syntax Example                                              | Behavior                                      |
|---------------|-------------------------------------------------------------|-----------------------------------------------|
| LOOT          | `Geralt loots 5 Rebis, 3 Aether`                            | Add ingredients to inventory                  |
| TRADE         | `Geralt trades 2 Wyvern trophy for 8 Vitriol, 1 Rebis`      | Exchange trophies for ingredients             |
| BREW          | `Geralt brews Swallow`                                      | Craft a potion if formula & ingredients exist |
| LEARN (effect)| `Geralt learns Igni sign is effective against..`           | Add or update bestiary entries                |
| LEARN (recipe)| `Geralt learns Black Blood potion consists of 3 Vitriol,..`| Add or update potion formulae                 |
| ENCOUNTER     | `Geralt encounters Bruxa`                                   | Simulate combat and trophy rewards            |

### Question Types

| Query                         | Syntax Example                            | Response                                          |
|-------------------------------|-------------------------------------------|---------------------------------------------------|
| Total ingredient `<Name>`     | `Total ingredient Vitriol ?`              | Quantity of specified ingredient                  |
| Total ingredient ?            | `Total ingredient ?`                      | List all ingredients with quantities (alphabetical) |
| Total potion `<Name>`         | `Total potion Swallow ?`                  | Quantity of specified potion                      |
| Total potion ?                | `Total potion ?`                          | List all potions                                  |
| Total trophy `<Name>`         | `Total trophy Basilisk ?`                 | Quantity of specified trophy                      |
| Total trophy ?                | `Total trophy ?`                          | List all trophies                                 |
| What is effective against ?   | `What is effective against Bruxa ?`       | List signs & potions effective                   |
| What is in `<Potion>` ?       | `What is in Black Blood ?`                | Ingredients for specified potion (sorted by qty) |

**Note**: Any malformed or out-of-grammar line produces `INVALID`.

---

##  Data Structures & Memory Management

- Dynamic arrays for ingredients, potions, trophies, signs, monsters, and formulas.
- Doubling strategy: Each `ensure_*_capacity()` function reallocates arrays when full.
- Modular design: Each subsystem in its own `.c`/`.h` file.
- Strict input sanitization and lexical analysis layer before execution.

---

##  Documentation & Report

See `docs/report.pdf` for:

- Detailed architecture and module breakdown
- Grammar specification (BNF) and examples
- Memory usage and complexity analysis
- Test case results and performance measurements

---

##  License

This project is licensed under the MIT License. See the `LICENSE` file for details.
