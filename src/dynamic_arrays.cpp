#include "dynamic_arrays.h"

#include <iostream>

// Helper: prints the contents and capacity of a dynamic array
void printArray(const int* arr, int count, int capacity) {
    std::cout << "  [";
    for (int i = 0; i < count; ++i) {
        std::cout << arr[i];
        if (i < count - 1) std::cout << ", ";
    }
    std::cout << "]  (count=" << count << ", capacity=" << capacity << ")" << '\n';
}

void dynamicArrays() {
    std::cout << "\n=== Dynamic Arrays (Resize + Copy) ===" << '\n';

    // ! DISCUSSION: The problem — arrays can't change size
    //   When we write new int[5], we get exactly 5 slots. If we need a
    //   6th element, we can't just "extend" the array — there might be
    //   other data right after it in memory. We need to:
    //     1. Allocate a NEW, bigger array
    //     2. Copy existing elements into it
    //     3. Delete the old array
    //   This is exactly what std::vector does behind the scenes!
    //
    // ! DISCUSSION: "Wait — didn't we just learn smart pointers are better?"
    //   Yes! In your own code, prefer smart pointers and std::vector.
    //   Here we use raw new/delete ON PURPOSE because we're building
    //   the internals of a container — this is what std::vector does
    //   under the hood. You need to understand this level so you can
    //   debug containers, implement data structures (linked lists,
    //   trees), and work with APIs that hand you raw pointers.

    // --- 1. Setting up a dynamic array ---
    std::cout << "\n--- 1. Initial Dynamic Array ---" << '\n';

    int capacity = 4;
    int count = 0;

    // ! DISCUSSION: count vs capacity
    //   capacity = how many elements the array CAN hold (total space)
    //   count    = how many elements are actually USED
    //   We start with capacity=4 but count=0 (empty array with room for 4).
    //   This separation is key — it lets us add elements without resizing
    //   every single time.

    // SOLUTION: Allocate a dynamic array of 'capacity' ints on the heap
    int* arr = new int[capacity];

    std::cout << "Empty array created";
    // SOLUTION: Call printArray(arr, count, capacity) to display the state
    printArray(arr, count, capacity);

    // --- 2. Adding elements ---
    std::cout << "\n--- 2. Adding Elements ---" << '\n';

    // SOLUTION: Add the value 10 to the array at index 'count', then increment count
    arr[count] = 10; count++;
    // SOLUTION: Add 20 the same way
    arr[count] = 20; count++;
    // SOLUTION: Add 30 the same way
    arr[count] = 30; count++;

    std::cout << "After adding 10, 20, 30:";
    // SOLUTION: Call printArray to display the state
    printArray(arr, count, capacity);

    // SOLUTION: Add 40 to fill the array to capacity
    arr[count] = 40; count++;

    std::cout << "After adding 40 (full!):";
    // SOLUTION: Call printArray to display the state
    printArray(arr, count, capacity);

    // ! DISCUSSION: Now count == capacity. The array is full!
    //   If we try to add another element with arr[count] = 50, we'd be
    //   writing past the end of the array — undefined behavior.
    //   We need to RESIZE before adding more.

    // --- 3. Resizing: allocate, copy, delete ---
    // ? SEE DIAGRAM: images/resize_copy.png — shows full → allocate new → copy → delete old → grow
    std::cout << "\n--- 3. Resizing the Array ---" << '\n';

    // ! DISCUSSION: The resize strategy
    //   We DOUBLE the capacity each time we run out of space.
    //   Why double instead of adding 1?
    //     - Adding 1: resize on EVERY insertion → O(n) copies each time
    //     - Doubling: resize rarely → O(1) on average per insertion
    //   This is the same strategy std::vector uses. The tradeoff is
    //   we may waste up to half the allocated space, but the time
    //   savings are enormous for large arrays.
    //
    //   The O(n) and O(1) notation above is called "Big O" (said
    //   "big-oh of n" and "big-oh of one") — a way to describe how an
    //   algorithm's cost grows as the input gets larger. We'll formalize
    //   Big O when we hit linked lists, where the contrast with arrays
    //   makes it really click.

    std::cout << "Array is full (count == capacity). Need to resize!" << '\n';

    // Step 1: Double the capacity
    // SOLUTION: Set a new variable 'newCapacity' to capacity * 2
    int newCapacity = capacity * 2;
    std::cout << "New capacity: " << newCapacity << '\n';

    // Step 2: Allocate a new, bigger array
    // SOLUTION: Allocate a new array of 'newCapacity' ints
    int* newArr = new int[newCapacity];

    // Step 3: Copy existing elements from old to new
    // SOLUTION: Use a for loop to copy arr[i] to newArr[i] for each existing element
    for (int i = 0; i < count; ++i) {
        newArr[i] = arr[i];
    }
    //
    // ! DISCUSSION: Why use a loop instead of a bulk copy?
    //   For plain ints a raw byte copy would work, but for objects
    //   with constructors/destructors (like std::string) you MUST
    //   use proper assignment so each object is correctly constructed
    //   in the new location. Loop-copying is the safe, general habit.

    std::cout << "Copied " << count << " elements to new array" << '\n';

    // Step 4: Delete the old array
    // SOLUTION: delete[] the old array (arr)
    delete[] arr;
    //
    // ! DISCUSSION: Why must we delete the OLD array?
    //   We allocated it with new[], so we own that memory. The new
    //   array is a separate allocation. If we just reassign arr to
    //   newArr without deleting, the old memory leaks.

    // Step 5: Update the pointer and capacity
    // SOLUTION: Point arr to newArr (arr = newArr)
    arr = newArr;
    // SOLUTION: Update capacity to newCapacity
    capacity = newCapacity;
    //
    // ! DISCUSSION: After arr = newArr, both pointers refer to the same memory.
    //   We don't delete newArr separately — arr now "owns" it.
    //   We just moved ownership from the old block to the new one.
    //
    //   "Don't we need to set newArr to nullptr too?"
    //   No — newArr is a local variable that we never use again after
    //   this line. It's NOT dangling: the memory it points to is still
    //   alive (arr is using it). Setting it to nullptr would be harmless
    //   but pointless. We only nullptr a pointer when we might
    //   accidentally use it later — newArr just falls out of scope.

    std::cout << "Resized!";
    // SOLUTION: Call printArray to display the state
    printArray(arr, count, capacity);

    // --- 4. Adding more elements after resize ---
    std::cout << "\n--- 4. Adding After Resize ---" << '\n';

    // SOLUTION: Add 50, 60, 70 to the array
    arr[count] = 50; count++;
    arr[count] = 60; count++;
    arr[count] = 70; count++;

    std::cout << "After adding 50, 60, 70:";
    // SOLUTION: Call printArray to display the state
    printArray(arr, count, capacity);

    // ! DISCUSSION: We added 3 more elements without resizing because
    //   capacity (8) is still greater than count (7). The doubling
    //   strategy gave us room to grow!

    // --- 5. Cleanup ---
    std::cout << "\n--- 5. Cleanup ---" << '\n';

    // SOLUTION: delete[] arr and set to nullptr
    delete[] arr;
    arr = nullptr;

    std::cout << "Dynamic array freed" << '\n';

    // ! DISCUSSION: Putting it all together
    //   What we just built is the core algorithm behind std::vector:
    //     - Start with a small capacity
    //     - Track count vs capacity
    //     - When full: double capacity, allocate, copy, delete old
    //     - When done: free all memory
    //   std::vector wraps this in a class with:
    //     - push_back() that auto-resizes
    //     - A destructor that auto-frees
    //     - Bounds checking with .at()
    //     - Move semantics for efficiency
    //   Understanding this manual version helps you appreciate what
    //   the STL containers do for you — and debug them when things go wrong.
}
