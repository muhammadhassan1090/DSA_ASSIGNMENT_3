# DSA_ASSIGNMENT_3
# Non-Comparison Sorting Algorithms 

This repository contains C++ implementations of various non-comparison sorting algorithms as required for the CS250 Fall 2025 semester project.

## Group Members
* [MUHAMMAD HASSAN]
* [DAWOOD AKBAR]

## Implemented Algorithms
1.  **Counting Sort (Stable)**: Preserves relative order of equal elements.
2.  **Counting Sort (Non-Stable)**: Optimized for space/speed when stability isn't needed.
3.  **LSD Radix Sort**: Least Significant Digit sorting using Counting Sort as a subroutine.
4.  **Bucket Sort**: Distributes elements into buckets based on range.
5.  **Pigeonhole Sort**: Maps elements to lists matching their values.

## How to Compile and Run
Ensure you have a C++ compiler installed (G++ or MSVC).

### Using G++ (Terminal)
1.  Navigate to the directory containing `main.cpp`.
2.  Compile the code:
    ```bash
    g++ -o sorter main.cpp
    ```
3.  Run the executable:
    ```bash
    ./sorter
    ```

### Using Visual Studio
1.  Open the `.sln` file or create a new "Console App" project.
2.  Add `main.cpp` to the Source Files.
3.  Press **F5** to build and run.

## Experimental Setup
The `main` function automatically runs a benchmark suite across input sizes of 1,000, 10,000, and 50,000 integers. The data is generated using a Uniform Distribution to test average-case performance.
