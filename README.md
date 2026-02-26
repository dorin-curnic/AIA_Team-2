# Sorting Algorithm Analysis

## Overview
This project benchmarks and empirically compares five distinct sorting algorithms across various dataset sizes and topologies. It includes customized optimizations for handling integer edge cases, negative numbers, and specific dataset sizes.

## Implemented Algorithms
1. **Insertion Sort**: Fast for small datasets ($N \le 100$).
2. **Shell Sort**: Optimized using Ciura's geometric gap sequence.
3. **Intro Sort**: Median-of-Three pivot strategy with $O(n \log n)$ tight bounds.
4. **Merge Sort**: Stable sort featuring an Insertion Sort fallback sequence.
5. **Radix Sort**: Linear time capabilities separated for negative integer domains.

## Directory Structure
- `AIA_Team-2/`: Source code for the core testing infrastructure algorithms.
- `AIA_Team-2/data/`: Generated dataset permutations.
- `analysis_report.md`: The finalized empirical results and analysis.

## Building and Running

### 1. Build the Sorter
Compile the main program and all dependencies together:
```powershell
cd AIA_Team-2
g++ main.cpp flags.cpp utils.cpp insertion_sort.cpp shell_sort.cpp introsort.cpp merge_sort.cpp radix.cpp -o sorter.exe -lpsapi
```

### 2. Build the Data Generator
Compile the test data generator:
```powershell
g++ data_generator.cpp -o generator.exe
```

### 3. Build the Competition Executable
Compile the separate executable utilized specifically for the "Fastest Sorting Algorithm" competition, which runs Radix Sort natively on an absolute path search:
```powershell
g++ -O3 -std=c++17 comp.cpp radix.cpp utils.cpp -o comp.exe -lpsapi
```

## Usage

**Important:** Before running any executables, ensure you are in the correct directory:
```powershell
cd AIA_Team-2
```

### 1. Generate Data
Run the generator to securely create test files inside the `data/` directory (Sizes: 100 to 1M; Types: random, asc, desc, half-sorted, mixed):
```powershell
.\generator.exe
```

### 2. Run Sorter
Run the compiled sorter exploiting the flag-based CLI syntax:
```powershell
.\sorter.exe -a <algorithm> -s <size> -i <input_file> [-o <output_file> | -c]
```

**Flags:**
- `-a, --sortAlgorithm <alg>` : Algorithm choice (`insertion`, `shell`, `intro`, `merge`, `radix`).
- `-s, --size <N>`            : Positive integer size (e.g., `100`, `100000`).
- `-i, --inputFile <file>`    : Input file path (automatically resolves inside `data/`).
- `-o, --outputFile <file>`   : Optional. Destination to write the sorted array.
- `-c, --stdout`              : Optional. Outputs the sorted array directly to the console.
- `-h, --help`                : Shows program help.

**Examples:**

Compute and print the metrics for a Mixed 10,000 array using Intro Sort, outputting array to a file:
```powershell
.\sorter.exe -a intro -s 10000 -i input_10000_mixed.txt -o output.txt
```

Compute metrics and print output to console:
```powershell
.\sorter.exe -a radix -s 1000 -i input_1000_random.txt -c
```

### 3. Run Competition Executable
Run the pre-configured competition executable that actively searches your workspace recursively for `in.txt` (or whatever input file is passed) and provides absolute metrics:
```powershell
# Usage: .\comp.exe <input_file> [stdout|output_file]

# Calculate metrics exclusively
.\comp.exe input_1000000_random.txt

# Calculate metrics AND save the sorted array elements
.\comp.exe input_1000000_random.txt output.txt

# Calculate metrics AND dynamically print directly standard output
.\comp.exe input_1000000_random.txt stdout
```

## Algorithms

### 1. Insertion Sort
- **Mechanic**: Builds a sorted array one element at a time by shifting items.
- **Best Use Case**: Very small datasets ($N \le 100$) or arrays that are already mostly sorted natively.
- **Complexity**: Time $O(N^2)$ Avg/Worst | Space $O(1)$ | Stable.

### 2. Shell Sort
- **Mechanic**: An extension of Insertion Sort that swaps distant elements across specific "gaps", reducing the gap iteratively. 
- **Best Use Case**: Medium-sized arrays where recursion overhead is unwanted.
- **Complexity**: Time $O(N^{4/3})$ (with Ciura gap sequence) | Space $O(1)$ | Unstable.

### 3. Intro Sort
- **Mechanic**: A hybrid sorting algorithm starting with Quick Sort and switching to Heap Sort when recursion depth exceeds $2 \log N$.
- **Best Use Case**: General-purpose comparative algorithm; excellent for purely random large datasets.
- **Complexity**: Time $O(N \log N)$ Best/Worst/Avg | Space $O(\log N)$ | Unstable.

### 4. Merge Sort
- **Mechanic**: Divides the array into halves, recursively sorts them, and merges them securely. Employs an Insertion Sort fallback for sub-arrays $\le 100$.
- **Best Use Case**: When strict stability and thoroughly predictable $O(N \log N)$ bounds are required across any topology.
- **Complexity**: Time $O(N \log N)$ Best/Worst/Avg | Space $O(N)$ | Stable.

### 5. Radix Sort
- **Mechanic**: Non-comparative integer sort grouping by byte values. Splits positives/negatives to handle edge constraints correctly natively.
- **Best Use Case**: Very large datasets strictly bound to defined integer limits (e.g., millions of 32-bit sequences).
- **Complexity**: Time $O(d \cdot (N + K))$ | Space $O(N)$ | Stable.
