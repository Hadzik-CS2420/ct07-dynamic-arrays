#include "two_dimensional_arrays.h"

#include <iostream>

void twoDimensionalArrays() {
    std::cout << "\n=== Two Dimensional Arrays ===" << '\n';

    // --- 1. Static 2D arrays (review) ---
    std::cout << "\n--- 1. Static 2D Arrays (Review) ---" << '\n';

    // ? SEE DIAGRAM: images/static_2d_array.png — conceptual grid vs actual flat memory layout
    //
    // ! DISCUSSION: A 2D array is an "array of arrays"
    //   int grid[2][3] creates 2 rows, each with 3 columns.
    //   In memory, it's laid out as one contiguous block:
    //     [1, 2, 3, 4, 5, 6]  (row 0 then row 1, back to back)
    //   grid[r][c] accesses row r, column c.

    int grid[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    std::cout << "Static 2D array:" << '\n';
    for (int r = 0; r < 2; ++r) {
        std::cout << "  Row " << r << ": ";
        for (int c = 0; c < 3; ++c) {
            std::cout << grid[r][c] << " ";
        }
        std::cout << '\n';
    }

    // --- 2. Dynamic 2D array with new ---
    std::cout << "\n--- 2. Dynamic 2D Array (Heap Allocated) ---" << '\n';

    int rows = 3;
    int cols = 4;

    // ! DISCUSSION: Why can't we just write new int[rows][cols]?
    //   The compiler needs to know the column size at compile time for
    //   a true 2D array. With runtime sizes, we use a different approach:
    //   an array of pointers, where each pointer points to a row.
    //
    // ! DISCUSSION: The "pointer to pointer" pattern
    //   int** table creates a pointer that points to an array of int*.
    //   Each int* in that array points to a row of ints.
    //   So you follow two pointers to reach a value — see the diagram above.

    // ? SEE DIAGRAM: images/two_d_spine.png — what the spine allocation looks like
    //
    // SOLUTION: Allocate an array of int* pointers with 'rows' elements
    int** table = new int*[rows];
    //
    // ! DISCUSSION: What does new int*[rows] allocate?
    //   It allocates an array of 'rows' pointers on the heap.
    //   Each pointer is uninitialized — they don't point anywhere yet.
    //   We need a second step to allocate each row.

    // SOLUTION: Use a for loop to allocate each row
    for (int i = 0; i < rows; ++i) {
        table[i] = new int[cols];
    }
    //
    // ? SEE DIAGRAM: images/two_d_rows.png — full picture after loop + delete order + flat alternative
    //
    // ! DISCUSSION: Why two separate allocations?
    //   The first new creates the "spine" (array of row pointers).
    //   Each loop iteration creates one "rib" (a row of actual ints).
    //   Total allocations: 1 + rows = 4 calls to new.
    //   This means we'll need 4 calls to delete[] later — one for each
    //   row, plus one for the spine.

    // SOLUTION: Fill the table with values where table[r][c] = (r * cols) + c + 1
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            table[r][c] = (r * cols) + c + 1;
        }
    }

    // SOLUTION: Print the 2D array using nested for loops
    std::cout << "Dynamic 2D array:" << '\n';
    for (int r = 0; r < rows; ++r) {
        std::cout << "  Row " << r << ": ";
        for (int c = 0; c < cols; ++c) {
            std::cout << table[r][c] << " ";
        }
        std::cout << '\n';
    }

    // --- 3. Freeing a dynamic 2D array ---
    std::cout << "\n--- 3. Freeing a Dynamic 2D Array ---" << '\n';

    // SOLUTION: Use a for loop to delete[] each row first
    for (int i = 0; i < rows; ++i) {
        delete[] table[i];
    }
    //
    // ! DISCUSSION: Why delete rows before the spine?
    //   If we delete the spine (table) first, we lose the pointers to
    //   each row — those rows become memory leaks! Always free in
    //   REVERSE order of allocation:
    //     Allocate:  spine first, then rows
    //     Free:      rows first, then spine

    // SOLUTION: Delete the spine (the array of pointers) with delete[] table
    delete[] table;
    // SOLUTION: Set table to nullptr
    table = nullptr;

    std::cout << "2D array memory freed (rows first, then spine)" << '\n';

    // --- 4. Flat 1D array as a 2D array ---
    // ? SEE DIAGRAM: images/two_d_flat.png — flat array layout, index formula, and comparison
    std::cout << "\n--- 4. Flat Array as 2D (Alternative Approach) ---" << '\n';

    // ! DISCUSSION: The pointer-to-pointer approach has downsides:
    //   - Multiple allocations (slow, fragmented memory)
    //   - Each row is a separate heap block (poor cache performance)
    //   - Easy to leak memory (must free each row individually)
    //   An alternative: allocate ONE flat array and use index math.
    //     index = row * cols + col
    //   This gives contiguous memory, one allocation, one delete[].

    // SOLUTION: Allocate a single flat array of size rows * cols
    int* flat = new int[rows * cols];

    // SOLUTION: Fill it using flat[r * cols + c] = (r * cols) + c + 1
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            flat[r * cols + c] = (r * cols) + c + 1;
        }
    }

    // SOLUTION: Print the flat array as a 2D grid using the index formula
    std::cout << "Flat array as 2D:" << '\n';
    for (int r = 0; r < rows; ++r) {
        std::cout << "  Row " << r << ": ";
        for (int c = 0; c < cols; ++c) {
            std::cout << flat[r * cols + c] << " ";
        }
        std::cout << '\n';
    }

    // SOLUTION: Free the flat array with delete[] and set to nullptr
    delete[] flat;
    flat = nullptr;

    std::cout << "Flat array freed (just one delete[]!)" << '\n';

    // ! DISCUSSION: Which approach is better?
    //   For most purposes, the flat array is preferred:
    //     - One allocation, one deallocation
    //     - Contiguous memory (cache-friendly)
    //     - Simpler cleanup
    //   The pointer-to-pointer approach is useful when rows have
    //   different lengths (a "jagged array"), but that's uncommon.
}
