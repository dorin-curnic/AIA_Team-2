# Sorting Algorithm Analysis

## Overview
This project benchmarks various sorting algorithms. Currently optimized for **Insertion Sort** (100 elements).

## Building and Running

### 1. Build the Sorter
Compile the main program:
```powershell
g++ -o sorter.exe main.cpp insertion_sort.cpp utils.cpp
```

### 2. Build the Data Generator
Compile the test data generator:
```powershell
g++ data_generator.cpp -o generator.exe
```

## Usage

### 1. Generate Data
Run the generator to create test files (input_*.txt):
```powershell
.\generator.exe
```

### 2. Run Sorter
Run the compiled sorter with the following syntax:
```powershell
.\sorter.exe <algorithm_name> <input_file> [output_file]
```

- `algorithm_name`: Currently supports `insertion_sort`.
- `input_file`: Path to the input `.txt` file (e.g., `input_100_random.txt`).
- `output_file`: (Optional) Path to save the sorted output. Use `stdout` to print to console.

**Examples:**

Sort to a file:
```powershell
.\sorter.exe insertion_sort input_100_random.txt output.txt
```

Sort and print to console:
```powershell
.\sorter.exe insertion_sort input_100_random.txt stdout
```

## Algorithms
### Insertion Sort
- **Best for**: Small datasets (~100 elements).
- **Time Complexity**: O(n^2).
- **Space Complexity**: O(1).
