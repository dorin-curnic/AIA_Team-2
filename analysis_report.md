# 1. Algorithm Analysis

## 1.1 Objective
The objective of this project is to conduct an empirical comparative analysis of five distinct sorting algorithms (Insertion, Shell, Intro, Merge, Radix) by measuring their computation time $T(n)$ across varying input sizes and dataset distributions.

## 1.2 Task
1. Implement the 5 sorting algorithms.
2. Choose the metric: computation execution time $T(n)$ in microseconds.
3. Prepare input datasets: sizes 100 to 1,000,000 (Random, Ascending, Descending, Half-Sorted, Mixed).
4. Run experiments averaging over 5 trials per case.
5. Compile and plot results.
6. Interpret findings and formulate conclusions.

## 1.3 Theoretical Notes
Empirical analysis relies on measuring the actual execution time on hardware, whereas theoretical analysis provides asymptotic bounds (Big-O). Timing results are heavily influenced by the CPU architecture, OS load, compiler optimizations, and the specific distribution of input data. To ensure a fair comparison, all tests were executed on the same machine environment using an identical test generator and compiled with `g++`.

## 1.4 Introduction
Sorting is arguably the most fundamental problem in computer science, significantly improving the efficiency of data retrieval and processing. Algorithms differ wildly based on their time complexity, memory footprint, stability, and handling of worst-case scenarios. We will explore and compare Insertion Sort, Shell Sort, Intro Sort, Merge Sort, and Radix Sort.

## 1.5 Comparison Metric
Our primary metric is **Execution Time $T(n)$** measured in microseconds ($\mu s$). We isolate the core sorting time from file I/O using the high-resolution hardware clock. We run each scenario 5 times and calculate the median latency to offset OS scheduling noise.

## 1.6 Input Format
Datasets are structured to guarantee reproducible test vectors:
- **Sizes**: 100; 1,000; 10,000; 100,000; 1,000,000 elements.
- **Values**: Uniformly distributed 32-bit signed integers in ranges $[-1,000,000, 1,000,000]$.
- **Types**:
  1. **Random**: Unpredictable noise.
  2. **Ascending**: Completely sorted natively.
  3. **Descending**: Reverse sorted natively.
  4. **Half-sorted**: First 50% ascending, remaining 50% random.
  5. **Mixed**: Completely random, including both positive and negative bounds.

# 2. Implementation
The experiments were conducted in C++20 using the MinGW `g++` compiler on Windows. The architecture separates algorithm implementation from the CLI flag parser (`flags.cpp`) and I/O utilities (`utils.cpp`). 

## 2.1 Insertion Sort
1. **Idea**: Iteratively builds a sorted subarray by shifting elements to the right until the correct position for the current item is found.
2. **Pseudocode**:
```text
for i = 1 to n-1:
    key = A[i], j = i-1
    while j >= 0 and A[j] > key:
        A[j+1] = A[j], j = j-1
    A[j+1] = key
```
3. **Complexity**: Best: $O(n)$ | Avg/Worst: $O(n^2)$ | Space: $O(1)$. It is a strictly Stable sort.
4. **Implementation notes**: The classic shifted replacement is utilized. For $N > 10,000$, empirical benchmarks are skipped due to excessive $O(n^2)$ time delays on unsorted sets.
5. **Results + interpretation**:

| Size | Random (�s) | Ascending (�s) | Descending (�s) | Half-Sorted (�s) | Mixed (�s) |
|---|---|---|---|---|---|
| 100 | 0 | 0 | 0 | 0 | 0 |
| 1000 | 1199 | 0 | 2992 | 0 | 536 |
| 10000 | 75209 | 0 | 153969 | 18722 | 75311 |
| 100000 | N/A | N/A | N/A | N/A | N/A |
| 1000000 | N/A | N/A | N/A | N/A | N/A |
It performs flawlessly on `Ascending` datasets in $O(n)$ time almost instantly, but its $O(n^2)$ limitation severely punishes it on Random, Mixed, and Descending forms.

## 2.2 Shell Sort
1. **Idea**: An extension of Insertion Sort that allows the exchange of items far apart natively by sorting elements bridging specific "gap" sizes, eventually reducing the gap to 1.
2. **Pseudocode**:
```text
for gap in gaps_sequence:
    for i = gap to n-1:
        temp = A[i], j = i
        while j >= gap and A[j-gap] > temp:
            A[j] = A[j-gap], j -= gap
        A[j] = temp
```
3. **Complexity**: Best: $O(n \log n)$ | Avg: $O(n^{4/3})$ (Ciura) | Space: $O(1)$. Unstable.
4. **Implementation notes**: Instead of the classic Shell gaps ($n/2$), we implemented Ciura's mathematically optimal gap sequence `[1,4,10,23,57,132,301,701,1750]`, multiplying by $2.25$ for higher gaps to secure optimal empirical runtimes.
5. **Results + interpretation**:

| Size | Random (�s) | Ascending (�s) | Descending (�s) | Half-Sorted (�s) | Mixed (�s) |
|---|---|---|---|---|---|
| 100 | 0 | 0 | 0 | 0 | 0 |
| 1000 | 0 | 0 | 0 | 0 | 0 |
| 10000 | 1744 | 0 | 0 | 2006 | 1055 |
| 100000 | 20589 | 4334 | 5602 | 16835 | 19700 |
| 1000000 | 252083 | 52416 | 79786 | 244498 | 253957 |
Drastically outpaces basic Insertion Sort natively. Ciura's sequence efficiently prevents data from moving excessively. Best suited for medium-sized arrays where $O(n \log n)$ overhead isn't worth it.

## 2.3 Intro Sort
1. **Idea**: A hybrid sorting algorithm that begins with Quick Sort and switches to Heap Sort when the recursion depth exceeds a level based on the logarithm of the number of elements being sorted.
2. **Pseudocode**:
```text
if recursion_depth <= 0: heapSort(A)
else if size <= 16: insertionSort(A)
else:
    pivot = medianOfThree(A)
    partition(A, pivot)
    introSort(left_half)
    introSort(right_half)
```
3. **Complexity**: Best/Avg/Worst: $O(n \log n)$ | Space: $O(\log n)$. Unstable.
4. **Implementation notes**: Optimized using a Median-of-Three pivot strategy to heavily mitigate $O(n^2)$ triggers. Small subarray insertion-sort fallback enhances deep recursion hits.
5. **Results + interpretation**:

| Size | Random (�s) | Ascending (�s) | Descending (�s) | Half-Sorted (�s) | Mixed (�s) |
|---|---|---|---|---|---|
| 100 | 0 | 0 | 0 | 0 | 0 |
| 1000 | 0 | 0 | 0 | 0 | 0 |
| 10000 | 507 | 0 | 0 | 0 | 0 |
| 100000 | 10959 | 3742 | 4365 | 7238 | 10831 |
| 1000000 | 125941 | 25648 | 53291 | 110915 | 129736 |
Displays the most consistently aggressive $T(n)$ times on purely random distributions, heavily outperforming Shell Sort on larger arrays due to strict $O(n \log n)$ limits.

## 2.4 Merge Sort
1. **Idea**: A Divide and Conquer algorithm that divides the array into two halves, recursively sorts them, and then merges the two sorted halves.
2. **Pseudocode**:
```text
if size <= 1: return
if size <= 16: insertionSort(A); return
mid = size / 2
left_half = mergeSort(A[0..mid])
right_half = mergeSort(A[mid..n])
merge(left_half, right_half)
```
3. **Complexity**: Best/Avg/Worst: $O(n \log n)$ | Space: $O(n)$. Stable.
4. **Implementation notes**: Optimized to fall back to Insertion Sort on sub-arrays of size $\le 16$, circumventing recursive overhead inside deep bounds. Handled negative indexing inherently out-of-the-box.
5. **Results + interpretation**:

| Size | Random (�s) | Ascending (�s) | Descending (�s) | Half-Sorted (�s) | Mixed (�s) |
|---|---|---|---|---|---|
| 100 | 0 | 0 | 0 | 0 | 0 |
| 1000 | 0 | 0 | 0 | 0 | 0 |
| 10000 | 2230 | 798 | 1972 | 2629 | 1138 |
| 100000 | 20295 | 11557 | 14478 | 16015 | 20810 |
| 1000000 | 232023 | 126165 | 154315 | 172795 | 223449 |
Maintains rigid stability and performs remarkably identically across Random, Descending, and Half-Sorted arrays. Though it carries an $O(n)$ space requirement, its consistent performance highlights strict predictability.

## 2.5 Radix Sort
1. **Idea**: A non-comparative sorting algorithm that sorts data with integer keys by grouping keys by the individual digits which share the same significant position and value.
2. **Pseudocode**:
```text
separate Positive and Negative into two arrays
for each byte level (0 to 3):
    count frequencies of byte in arrays
    calculate prefix sum of counts
    build sorted buffer array using counts
    swap buffer with original array
reverse Negative array
merge Native and Positive into main
```
3. **Complexity**: Best/Avg/Worst: $O(d \cdot (n + k))$ where $d=4$ (bytes) | Space: $O(n)$. Stable.
4. **Implementation notes**: Handled negative numbers implicitly by splitting the domain into positives and absolute-value negatives, sorting them utilizing an internal LSD Radix Lambda, then concatenating them reversely.
5. **Results + interpretation**:

| Size | Random (�s) | Ascending (�s) | Descending (�s) | Half-Sorted (�s) | Mixed (�s) |
|---|---|---|---|---|---|
| 100 | 0 | 0 | 0 | 0 | 0 |
| 1000 | 0 | 0 | 0 | 0 | 0 |
| 10000 | 0 | 502 | 0 | 0 | 1520 |
| 100000 | 4588 | 5072 | 5302 | 4065 | 4527 |
| 1000000 | 48162 | 51709 | 55117 | 50869 | 58124 |
Extremely fast strictly because $d=4$ acts constantly, leaving $T(n)$ tightly coupled with purely linear runtime mapping. This yielded the fastest result on the $1,000,000$ set limit.

# 3. Comparation of algorithms
Overall, algorithms scaled as theoretically expected mapping against our benchmark tables. Radix Sort performed the fastest broadly across $1,000,000$ scales via uniform $O(n)$, while Intro Sort took the comparative lead due to low constant factors against Merge Sort.

# 4. Conclusion
* **Insertion Sort** degrades wildly past $N = 10,000$ for unsorted inputs ($O(n^2)$ threshold).
* **Shell Sort** with Ciura's gaps proved to be highly practical across mixed sizes seamlessly.
* **Intro Sort** is the definitively safest comparative choice due to robust median partitions.
* **Merge Sort** remained the most deterministic in latency across differing randomness scales.
* **Radix Sort** dominated big datasets linearly where purely signed $32$-bit integers exist.
* **Best algorithm when...**: Small array ($N < 50$)? Insertion Sort. General Comparative requirement? Intro Sort. Integer constraints known heavily? Radix Sort.

# 5. Bibliography
1. Knuth, D. E. (1997). The Art of Computer Programming, Vol. 3: Sorting and Searching.
2. Ciura, M. (2001). Best Increments for the Average Case of Shellsort.
3. GCC Internal Sort Definitions (libstdc++ `std::sort` mechanism via Introsort).
4. GitHub Project Link: [AIA_Team-2 Repository](https://github.com/dorin-curnic/AIA_Team-2)
