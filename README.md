# Analysis and Complexity of Algorithms (AZA)

## Introduction
This repository contains a C++ implementation and experimental comparison of two algorithms for solving the **Subset Sum Problem**.

Given an array of positive integers and a target sum, the goal is to find if any subset of the array adds up exactly to the target. The project demonstrates how algorithmic optimizations (pruning and early exit) can drastically reduce the search space compared to a naive brute-force approach.

## Implementations

### 1. Baseline Solver (Naive Backtracking)
A standard depth-first search (DFS) that explores all possible subsets.
- **Complexity:** `O(2^n)` time, `O(n)` space.
- **Behavior:** Explores the entire binary decision tree regardless of whether a solution is found, resulting in exactly `2^(n+1) - 1` function calls for any input.

### 2. Improved Solver (Pruned Backtracking)
An optimized DFS that adds three key techniques to cut off dead ends early:
- **P1 (Overshoot Pruning):** Stops if the running sum exceeds the target.
- **P2 (Undershoot Pruning):** Precomputes a `suffix` sum array. If the current sum plus the maximum possible sum of remaining elements is less than the target, the branch is abandoned.
- **E1 (Early Exit):** Stops searching immediately once a valid subset is found (since only one solution is required).

## Experiments & Results

The benchmark (`experiments.cpp`) evaluates both solvers on three types of instances: **solvable**, **random**, and **unsatisfiable** (adversarial), with array sizes `n = 20, 25, 30`.

### Key Takeaways:
- **Massive Speedup:** On solvable and random instances, the Improved solver finds a solution almost instantly (up to 7 orders of magnitude fewer recursive calls) due to early exit and pruning.
- **Worst-Case Preserved:** On adversarial inputs (e.g., all numbers are multiples of 4, and the target is not), pruning rarely triggers. Both algorithms still exhibit exponential growth `O(2^n)`, though the Improved solver makes roughly 3x fewer calls.

## How to Run

### Prerequisites
- `g++` with C++17 support

### Build
```bash
g++ -std=c++17 -O2 -Wall -Wextra baseline.cpp improved.cpp experiments.cpp -o experiments
```

### Run

#### Mac/Linux
```bash
./experiments > results.txt
```

#### Windows PowerShell
```bash
.\experiments.exe > results.txt
```
