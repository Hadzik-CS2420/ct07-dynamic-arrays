# Code-Together 07: Dynamic Arrays (Resize + Copy)

## Overview

An in-class code-together activity covering heap allocation, dynamic memory management, and the resize-copy pattern used by `std::vector`. Students complete TODO items in three source files while the instructor walks through concepts using discussion comments.

> ▶️ **Watch it run, one step at a time.** Your repo has
> `images/stepper.html` — **double-click it** to open it in your browser and
> press **Next**. It steps through `new`/`delete`, `unique_ptr`, and the resize-copy pattern — including the few steps where **two arrays are alive at once**, which is the part a still picture cannot show. Nothing to install, and it works offline.
>
> The still pictures of the same ideas are in `images/`, and the Diagrams
> table below says what each one is for.

## Files

| File | Focus | TODOs |
|---|---|---|
| `new_and_delete.cpp` | `new[]`/`delete[]` for arrays, `unique_ptr`, `shared_ptr` | 13 |
| `dynamic_arrays.cpp` | Resize + copy pattern (how `std::vector` works) | 18 |
| `two_dimensional_arrays.cpp` | Dynamic 2D arrays (pointer-to-pointer and flat) | 11 |

## Teaching Order

Work through the files in the order `main.cpp` calls them:

### 1. `new_and_delete.cpp` — Foundation

1. **Heap arrays with `new[]`** — runtime-sized arrays on the heap, stack vs heap
2. **Freeing arrays with `delete[]`** — matching `new[]` with `delete[]`, dangling pointers, nullptr
3. **`unique_ptr`** — automatic cleanup, `make_unique`, array support (the "better way")
4. **`shared_ptr`** — shared ownership, reference counting

### 2. `dynamic_arrays.cpp` — The Big Picture

1. **Initial dynamic array** — capacity vs count, allocating with `new`
2. **Adding elements** — filling the array, hitting capacity
3. **Resizing** — double capacity, allocate new, copy, delete old
4. **Adding after resize** — using the extra capacity
5. **Cleanup** — freeing the final array

### 3. `two_dimensional_arrays.cpp` — Applying new/delete in 2D

1. **Static 2D arrays** — quick review of stack-based `int grid[2][3]`
2. **Dynamic 2D arrays** — pointer-to-pointer (`int**`), allocating spine + rows
3. **Freeing 2D arrays** — reverse order: rows first, then spine
4. **Flat array as 2D** — single allocation with index math (`row * cols + col`)

## Diagrams

SVG sources are in `images/svg/`, PNG exports in `images/`.

| Diagram | Referenced In | Shows |
|---|---|---|
| `delete_and_nullptr` | `new_and_delete.cpp` | 3-step visual: valid pointer → dangling pointer after `delete[]` → safe state after `nullptr` |
| `unique_ptr` | `new_and_delete.cpp` | Exclusive ownership, `make_unique` under the hood, move semantics, automatic cleanup |
| `shared_ptr` | `new_and_delete.cpp` | Shared ownership, `make_shared` under the hood, reference counting lifecycle |
| `resize_copy` | `dynamic_arrays.cpp` | 3-step resize lifecycle: full → allocate/copy/delete → room to grow |
| `static_2d_array` | `two_dimensional_arrays.cpp` | Conceptual grid vs actual flat memory layout for `int grid[2][3]` |
| `two_d_spine` | `two_dimensional_arrays.cpp` | Step 1: spine allocation — array of uninitialized pointers |
| `two_d_rows` | `two_dimensional_arrays.cpp` | Step 2: full picture after row allocation + delete order |
| `two_d_flat` | `two_dimensional_arrays.cpp` | Flat array layout, index formula, pointer-to-pointer vs flat comparison |
| `lifetime_step_by_step` | Canvas concept page | One heap `int` through four moments &mdash; raw `new`/`delete` beside `unique_ptr`, showing they only diverge at the closing brace |

## Comment Conventions

Uses [Better Comments](https://marketplace.visualstudio.com/items?itemName=OmarRwemi.BetterComments) for VS 2022:

| Prefix | Color | Purpose |
|---|---|---|
| `// !` | Important (red) | `DISCUSSION:` teaching notes for instructor walkthrough |
| `// ?` | Question (blue) | `SEE DIAGRAM:` references to visual aids |
| `// TODO:` | Task (orange) | Student exercises (main branch) |

