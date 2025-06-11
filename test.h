#pragma once

#include "bst_tree.h"

#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <cstdint>
#include <random>

/**
 * Base class for both our test types.
 * 
 * Both tests insert a sequence of values 0..N-1 into a binary search tree
 * — either in sorted or shuffled order.
 * Since the logic is almost identical, we use a shared base class.
 */
template<size_t N>
class base_test {
public:
    std::vector<int64_t> data; // Data to be inserted into the BST
    bst_tree tree{};           // Instance of the binary search tree

    base_test() : data(N) {
        // Fill vector with sequence 0..N-1
        std::iota(data.begin(), data.end(), 0);
    }

    void run_test() {
        /**
         * Each number from the vector `data` is inserted into the tree using parallel threads.
         *
         * Dynamic scheduling is used here to preserve some insertion order consistency.
         * If static scheduling were used, threads with higher indices would begin inserting
         * from the middle of the array (e.g., at index k*N/omp_get_num_threads()), which would
         * mess up any order guarantees.
         */
        #pragma omp parallel for schedule(dynamic)
        for (auto n : data) {
            tree.insert(n);
        }
    }

    bool verify() {
        /**
         * We perform an in-order traversal of the tree and collect its contents into a vector.
         * If the tree structure is correct (according to BST rules), the result must be sorted.
         */
        std::vector<int64_t> content;
        std::function<void(bst_tree::node*)> inorder = [&](bst_tree::node* node) {
            if (node != nullptr) {
                inorder(node->left);
                content.push_back(node->data);
                inorder(node->right);
            }
        };
        inorder(tree.root);

        // Check if the in-order result matches the sorted sequence 0..N-1
        if (content.size() != N) return false;
        for (size_t i = 0; i < N; i++) {
            if (content[i] != static_cast<int64_t>(i)) return false;
        }
        return true;
    }
};

/**
 * Test variant where input data is shuffled before insertion.
 * Inherits from `base_test` and just randomizes the input sequence.
 */
template<size_t N>
class shuffled_data : public base_test<N> {
public:
    shuffled_data() {
        std::shuffle(this->data.begin(), this->data.end(), std::mt19937(0)); // NOLINT(*-msc51-cpp)
    }
};

/**
 * Test variant with sorted input (same as base_test).
 * We define the constructor explicitly to avoid weird GCC 10.2 move constructor error.
 */
template<size_t N>
class sorted_data : public base_test<N> {
public:
    sorted_data() = default;
};
