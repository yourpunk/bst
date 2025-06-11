/**
 * ============================
 * Binary Search Tree Benchmark
 * ============================
 *
 * This program runs two tests on a custom binary search tree:
 *  - Inserting shuffled data (1,000,000 elements)
 *  - Inserting sorted data (40,000 elements)
 *
 * Each test builds the tree in parallel and checks correctness via in-order traversal.
 * Execution time is measured and printed in milliseconds.
 */

#include "tests.h"

#include <cstddef>
#include <cstdio>
#include <chrono>

constexpr size_t N1 = 1'000'000; // Number of elements for shuffled insert test
constexpr size_t N2 = 40'000;    // Number of elements for sorted insert test

// Runs a given test and prints execution time or error
template<typename Test>
void run_test(const char* test_name) {
    Test test{};

    try {
        auto begin = std::chrono::steady_clock::now();
        test.run_test();
        auto end = std::chrono::steady_clock::now();

        if (!test.verify()) {
            printf("%s       --- wrong result ---\n", test_name);
        } else {
            auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            printf("%s          %7ld ms\n", test_name, duration_ms.count());
        }
    } catch (...) {
        printf("%s      --- not implemented ---\n", test_name);
    }
}

int main() {
    run_test<shuffled_data<N1>>("Shuffled data");
    run_test<sorted_data<N2>>("Sorted data  ");

    return 0;
}
