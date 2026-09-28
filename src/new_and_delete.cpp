#include "new_and_delete.h"

#include <iostream>
#include <memory>

void newAndDelete() {
    std::cout << "=== The new and delete Operators ===" << '\n';

    // --- 1. Allocating arrays on the heap ---
    std::cout << "\n--- 1. Heap Arrays with new[] ---" << '\n';

    // ! DISCUSSION: Stack vs Heap — why do we need the heap?
    //   So far, every variable we've created lives on the STACK:
    //     int x = 42;          // stack — automatic lifetime
    //   Stack variables are fast and automatically cleaned up when the
    //   function returns. But they have limitations:
    //     1. Fixed size — the compiler must know the size at compile time
    //     2. Short lifetime — destroyed when the scope ends
    //   The HEAP lets us allocate memory at runtime with a size we choose,
    //   and that memory persists until we explicitly free it.

    int size = 5;

    // SOLUTION: Use 'new' to allocate an array of 'size' ints on the heap
    int* heapArray = new int[size];
    //
    // ! DISCUSSION: What does 'new int[size]' actually do?
    //   1. Asks the OS for (size * sizeof(int)) bytes of heap memory
    //   2. Returns a pointer to the first element of that block
    //   The pointer (heapArray) itself lives on the stack, but the
    //   array it points to lives on the heap.
    //
    // ! DISCUSSION: new int[5] vs new int(5) — careful!
    //   new int[5]  — allocates an ARRAY of 5 ints (uninitialized)
    //   new int(5)  — allocates a SINGLE int with value 5
    //   Mixing these up is a common and dangerous mistake.
    //
    // ! DISCUSSION: Why is this better than int arr[size]?
    //   Variable-length arrays (VLAs) like int arr[size] are NOT
    //   standard C++. Some compilers allow them as extensions, but
    //   they're on the stack (limited space) and can't outlive the
    //   function. new int[size] is the portable, standard way to
    //   create a runtime-sized array.

    // SOLUTION: Use a for loop to fill the array with values 10, 20, 30, 40, 50
    for (int i = 0; i < size; ++i) {
        heapArray[i] = (i + 1) * 10;
    }

    // SOLUTION: Print all elements of the heap array using a for loop
    std::cout << "Heap array: ";
    for (int i = 0; i < size; ++i) {
        std::cout << heapArray[i] << " ";
    }
    std::cout << '\n';

    // --- 2. Freeing arrays with delete[] ---
    // ? SEE DIAGRAM: images/delete_and_nullptr.png — shows what happens to the pointer after delete[]
    std::cout << "\n--- 2. Freeing Arrays with delete[] ---" << '\n';

    // SOLUTION: Use 'delete[]' to free the heap array
    delete[] heapArray;
    //
    // ! DISCUSSION: Why must we call delete[]?
    //   Unlike stack variables, heap memory is NOT automatically freed.
    //   If we lose the pointer without calling delete[], that memory is
    //   leaked — the program still "owns" it but can never access or
    //   free it. Over time, leaks can exhaust available memory.
    //
    // ! DISCUSSION: Why delete[] and not delete?
    //   delete frees a single object. delete[] frees an array.
    //   Using the wrong one is undefined behavior:
    //     delete heapArray;    // WRONG — allocated with new[]
    //     delete[] heapArray;  // CORRECT — matches new[]
    //   The rule is simple: new pairs with delete, new[] pairs with delete[].
    //   delete[] knows how many elements to free because the allocator
    //   stores the count (usually just before the array in memory).

    // SOLUTION: Set heapArray to nullptr after deleting
    heapArray = nullptr;
    //
    // ! DISCUSSION: Why set to nullptr after delete[]?
    //   After delete[], the pointer still holds the old address — it's
    //   now a "dangling pointer." Accessing *heapArray after delete[] is
    //   undefined behavior. Setting it to nullptr makes the invalid
    //   state visible:
    //     if (heapArray != nullptr) { /* safe to use */ }
    //   Deleting nullptr is guaranteed safe (it does nothing), so
    //   accidental double-delete won't crash.

    std::cout << "Array memory freed and pointer set to nullptr" << '\n';

    // --- 3. Smart pointers: unique_ptr ---
    // ? SEE DIAGRAM: images/unique_ptr.png — shows exclusive ownership, make_unique, and automatic cleanup
    std::cout << "\n--- 3. Smart Pointers: unique_ptr ---" << '\n';

    // ! DISCUSSION: The problem with raw new/delete
    //   Manual memory management is error-prone:
    //     - Forget delete[]? Memory leak.
    //     - Delete twice? Undefined behavior (often a crash).
    //     - Exception thrown before delete[]? Memory leak.
    //   Smart pointers solve all of these by tying the heap memory's
    //   lifetime to a stack object. When the smart pointer goes out of
    //   scope, it automatically calls delete (or delete[]).
    //
    // ! DISCUSSION: "So why did we just learn raw new/delete?"
    //   Fair question! In modern C++ you should almost always prefer
    //   smart pointers. But raw pointers still matter because:
    //     1. Smart pointers USE new/delete under the hood — when something
    //        goes wrong, the debugger shows you raw pointers and addresses.
    //        You can't debug what you don't understand.
    //     2. Existing codebases are full of raw new/delete. You'll read
    //        and maintain far more code than you write.
    //     3. Some APIs (C libraries, OS calls, hardware interfaces) give
    //        you raw pointers — you need to know how to manage them.
    //     4. Data structures like linked lists, trees, and the dynamic
    //        array we'll build in the future require understanding allocation
    //        at this level — it's the foundation everything else sits on.

    // SOLUTION: Create a std::unique_ptr<int> called 'smartValue' using std::make_unique<int>(99)
    auto smartValue = std::make_unique<int>(99);
    //
    // ! DISCUSSION: What does 'auto' mean here?
    //   auto tells the compiler: "figure out the type for me."
    //   The right-hand side is std::make_unique<int>(99), which returns a
    //   std::unique_ptr<int> — so that's what smartValue becomes.
    //   Without auto, you'd write:
    //     std::unique_ptr<int> smartValue = std::make_unique<int>(99);
    //   auto avoids repeating the type and keeps the line readable.
    //   It does NOT mean "untyped" — the type is still fully known at
    //   compile time, just deduced instead of spelled out.
    //
    // ! DISCUSSION: What is unique_ptr?
    //   unique_ptr is a smart pointer that OWNS the heap memory exclusively.
    //   - Only one unique_ptr can point to a given object (no copies)
    //   - When it goes out of scope, it calls delete automatically
    //   - Use std::make_unique<T>(...) to create one (safer than new)
    //
    // ! DISCUSSION: Why make_unique instead of new?
    //   std::make_unique<int>(99) is preferred over unique_ptr<int>(new int(99)):
    //   1. Shorter and cleaner syntax
    //   2. Exception-safe — no risk of leaking if another argument throws
    //   3. Makes the intent clear: "I want a unique_ptr"

    // SOLUTION: Print the value by dereferencing the unique_ptr (use * just like a raw pointer)
    std::cout << "Smart value: " << *smartValue << '\n';

    // SOLUTION: Create a unique_ptr to a dynamic array of 3 ints
    auto smartArray = std::make_unique<int[]>(3);
    //
    // ! DISCUSSION: unique_ptr with arrays
    //   std::make_unique<int[]>(3) allocates an array of 3 ints on the heap.
    //   The unique_ptr knows it's an array and will call delete[] (not delete)
    //   when it goes out of scope. You can use [] indexing on it.

    // SOLUTION: Fill the smart array with values 100, 200, 300
    smartArray[0] = 100;
    smartArray[1] = 200;
    smartArray[2] = 300;

    // SOLUTION: Print all elements of the smart array
    std::cout << "Smart array: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << smartArray[i] << " ";
    }
    std::cout << '\n';

    // ! DISCUSSION: Notice — no delete needed!
    //   When smartValue and smartArray go out of scope at the closing }
    //   of this function, their destructors automatically free the heap
    //   memory. This is called RAII (Resource Acquisition Is Initialization):
    //   tie the resource's lifetime to an object's lifetime.

    std::cout << "\nSmart pointers automatically clean up — no delete needed!" << '\n';

    // --- 4. Smart pointers: shared_ptr ---
    // ? SEE DIAGRAM: images/shared_ptr.png — shows shared ownership, make_shared, and reference counting
    std::cout << "\n--- 4. Smart Pointers: shared_ptr ---" << '\n';

    // ! DISCUSSION: unique_ptr vs shared_ptr — quick comparison
    //
    //                 unique_ptr              shared_ptr
    //   ─────────────────────────────────────────────────────
    //   Owners        ONE only                Multiple (shared)
    //   Copies?       No (use std::move)      Yes (ref count ++)
    //   Overhead      Zero extra cost         Control block + count
    //   Cleanup       When owner dies         When last owner dies
    //   Create with   std::make_unique<T>()   std::make_shared<T>()
    //   ─────────────────────────────────────────────────────
    //
    //   Rule of thumb: use unique_ptr by default. Only reach for
    //   shared_ptr when multiple parts of code truly need to share
    //   ownership of the same object.

    // SOLUTION: Create a shared_ptr<int> called 'sharedA' using std::make_shared<int>(77)
    auto sharedA = std::make_shared<int>(77);

    // SOLUTION: Create a second shared_ptr<int> called 'sharedB' that copies sharedA
    auto sharedB = sharedA;
    //
    // ! DISCUSSION: How does shared_ptr allow copies?
    //   shared_ptr keeps a reference count. When you copy it, the count
    //   goes up. When a copy is destroyed, the count goes down. The
    //   heap memory is only freed when the count reaches zero.
    //
    //   You can also std::move a shared_ptr — this transfers ownership
    //   without touching the ref count (faster than copying, since no
    //   atomic increment/decrement is needed).

    // SOLUTION: Print the value through both pointers and the reference count
    std::cout << "sharedA value: " << *sharedA << '\n';
    std::cout << "sharedB value: " << *sharedB << '\n';
    std::cout << "Reference count: " << sharedA.use_count() << '\n';

    std::cout << "Both pointers share the same heap memory!" << '\n';
}
