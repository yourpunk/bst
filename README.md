# 🌲 Parallel Binary Search Tree Playground

A high-performance, fine-grained **thread-safe Binary Search Tree (BST)** implementation in C++ with OpenMP-based concurrent insertion benchmarking.  
This project focuses on **lock-aware parallelism**, **structural integrity under load**, and **realistic stress-testing scenarios** for symbolic tree structures.

---

## 🚀 Overview

This repository contains:

- A **custom BST implementation** with per-node mutex protection
- A minimal **benchmark harness** for evaluating insertion speed and correctness
- Real-world inspired test cases:
  - `Shuffled data`: simulates unordered insert workload
  - `Sorted data`: worst-case input for BSTs (left-leaning degeneracy)

---

## ⚙️ Core Concepts

| Component            | Implementation |
|----------------------|----------------|
| Thread Safety        | Fine-grained per-node locks (top-down path locking) |
| Concurrency Model    | OpenMP-based parallel loop insertion |
| Validation           | In-order traversal for BST correctness |
| Performance Metric   | Time (ms) to insert and validate N nodes |

---

## 🧠 Why

Concurrent binary tree structures are a classic systems programming challenge — balancing mutability, correctness, and performance.  
This project was built to:

- Explore low-level **fine-grained locking** patterns
- Investigate performance under **structured and chaotic insert orders**
- Benchmark how tree balance impacts real-time throughput
- Learn how far raw C++ + OpenMP can go without third-party abstractions

---

## 📦 Project Structure

```bash
.
├── bst_tree.h / .cpp    # ⭐ Core BST logic — per-node locking, insert, validation
├── tests.h              # Test setup: sorted vs shuffled input
├── main.cpp             # Benchmark runner
├── Makefile             # Build configuration
├── LICENSE
└── README.md            # This file
```

---

## 🧪 How to Run
Ensure OpenMP is supported by your compiler (GCC/Clang with -fopenmp).

``` bash
make        # or manually: g++ -std=c++17 -fopenmp main.cpp bst_tree.cpp -o bst_test
./bst_test
```
Expected output:

```text
[+] Running shuffled insert test...
Result: valid BST  | Time: 1234 ms

[+] Running sorted insert test...
Result: valid BST  | Time: 450 ms
```

---

## 🔐 Thread Safety Model
Insertions are made safe through per-node mutexes.
Locking strategy:
- Acquires locks top-down, from root to leaf
- Avoids deadlocks via consistent lock ordering
- Prevents structural races during concurrent inserts
- Multiple writers allowed — only paths to specific insert points are locked
This design ensures maximum concurrency with minimal blocking, especially under randomized input.

---

## 📈 Benchmark Logic
Each benchmark:
- Generates N integers (either shuffled or sorted)
- Spawns an OpenMP `parallel for` region
- Each thread performs a lock-aware insert of one integer
- Validates the final tree via in-order traversal
- Reports total insertion + validation time in ms

---

## 🧩 Design Trade-offs

|Trade-off|	Rationale|
|---|---|
|No balancing (e.g., AVL)	|Focus on raw locking / correctness, not AVL logic|
|OpenMP > std::thread pool	| Simpler syntax, compiler-parallelized|
|Lock per node	| More scalable than monolithic locking|

---

## 🔄 Extensions / TODO

- Add delete() and search() with locking
- Compare against STL containers (std::set, std::map) under load
- Enable lock-free / optimistic inserts (e.g., with atomics)
- Add histogram of depth per insert (tree balance monitor)
- Graphviz / DOT export for tree shape visualization

---

## 📜 License

MIT — use it, fork it, stress it.
Just don’t deploy it without understanding the race conditions you're creating 😉

---

## 👤 Author
🦾 Crafted by Aleksandra Kenig (aka [yourpunk](https://github.com/yourpunk)) - game developer, systems nerd, and tree violence enthusiast.

> If you're building real-time systems or hiring for low-level concurrency — let's talk.
