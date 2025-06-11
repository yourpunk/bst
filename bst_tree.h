#pragma once

#include <cstdint>
#include <mutex>
#include <vector>

class bst_tree {
public:
    // Class representing a node in the binary search tree
    class node {
    public:
        node* left{nullptr};   // Pointer to left subtree
        node* right{nullptr};  // Pointer to right subtree
        int64_t data;          // Value stored in this node
        int height = 1;        // Height of the node (used for balancing if needed)
        std::mutex node_mutex; // Mutex for thread-safe access

        explicit node(int64_t data) : data(data) {}
    };

    node* root{nullptr}; // Root of the tree

    ~bst_tree(); // Destructor to free memory

    // Insert a new value into the binary search tree
    void insert(int64_t data);

    // Build the tree from a sorted array
    void build_from_sorted_data(const std::vector<long int>&);
};
