# CS Advanced Workshop – C Language

This repository contains a structured academic project written in C, developed as part of the "Advanced Workshop in Computer Science" course at HIT (Holon Institute of Technology).

The project includes several exercises focused on algorithmic problem-solving, dynamic memory management, and data structure implementation in the C programming language.

---

## ✨ Project Overview

The project consists of three modular exercises:

### 1. Prime Analyzer
- Finds all prime numbers in a given range [`n1`, `n2`].
- Computes the sum of digits for each prime.
- Dynamically allocates memory for the result array using `realloc`.

### 2. Max-Neighbor Matrix
- Reads a static 4×5 matrix.
- Builds a new matrix where each cell contains the **maximum** among its adjacent (up/down/left/right) neighbors.
- Demonstrates pointer manipulation and matrix traversal.

### 3. Dynamic Matrix & Rule-Based Linked Lists
- Reads a dynamic matrix of integers.
- Creates two linked lists based on:
  - List A: values where `value == row + column`.
  - List B: values forming an arithmetic progression `i → j → value`.

---

## 🔧 Technologies & Concepts

- **Language:** C (GCC-compatible)
- **Memory Management:** `malloc`, `realloc`, `free`
- **Data Structures:** `struct`, dynamic arrays, linked lists
- **Topics Covered:**
  - Prime checking
  - Digit sum computation
  - Matrix neighbor comparison
  - Dynamic allocation of 2D arrays
  - List creation and traversal
  - Menu-driven CLI interface

---

## 📁 File Structure

| File                     | Description                            |
|--------------------------|----------------------------------------|
| `main.c`                 | Full project implementation             |
| `assignment-specification.pdf` | Original task description in Hebrew |
| `README.md`              | You're reading it :)                    |
| `.gitignore` *(optional)*| Excludes build files or IDE configs     |

---

## 🖥️ How to Run

1. Compile:
   ```bash
   gcc main.c -o workshop
