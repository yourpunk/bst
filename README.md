# 🌲 Parallel Binary Search Tree Playground

This project is a no-BS benchmark suite for testing multithreaded insertion into a custom Binary Search Tree.  
It's all about raw performance and correctness when inserting large datasets in parallel.

> 🛠️ BST logic (`bst_tree.cpp`) was implemented by me. It supports thread-safe insertions using fine-grained locks.  
> Everything else just stress-tests it — sorted vs shuffled data, parallel vs chaos.

## 🚀 What It Does

It runs two tests:

- `Shuffled data`: inserts 1,000,000 integers in random order, fully parallelized.
- `Sorted data`: inserts 40,000 integers in sorted order — a known worst-case for vanilla BSTs.

Each test:
- builds the tree in parallel (`#pragma omp parallel for`)
- verifies correctness via in-order traversal (should be sorted if the tree is valid)
- times the whole thing and prints it in milliseconds

## 📦 Files

| File            | Description |
|------------------|-------------|
| `bst_tree.h/cpp` | ⭐ My implementation. Thread-safe BST with per-node locks. |
| `tests.h`        | Base test + sorted/shuffled variants. |
| `main.cpp`       | Runs both tests and prints the results. |

## 🧪 How to Run

Make sure you have OpenMP enabled:

```bash
g++ -std=c++17 -fopenmp main.cpp bst_tree.cpp -o bst_test
./bst_test
```
Expected output looks like this:

```kotlin
Shuffled data          1234 ms
Sorted data             450 ms
```
If the tree fails validation or throws, you'll get:

```wasm
Shuffled data       --- wrong result ---
Sorted data         --- not implemented ---
```

## 🧠 Why This Exists
I wanted to write my own binary search tree from scratch — no STL, no black box, just me vs threads.
Thread-safe insert into a BST is a classic challenge, and I wanted to actually build one instead of just reading academic PDFs about it.

This project helped me:
- understand fine-grained locking
- stress-test tree structures with sorted vs randomized inputs
- practice writing clean tests that validate correctness under pressure

## 📜 License
**MIT**. Steal, fork, improve. But don’t ship this in production unless you know what you’re doing.

## 👤 Author
🦾 Crafted by Aleksandra Kenig (aka [yourpunk](https://github.com/yourpunk)).<br>
💌 Wanna collab or throw some feedback? You know where to find me.
