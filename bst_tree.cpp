#include "bst_tree.h"
#include <mutex>
#include <vector>
#include <algorithm>
#include <random>
#include <algorithm>
 
void delete_node(bst_tree::node* node) {
    if (node == nullptr) {
        return;
    }
    delete_node(node->left);
    delete_node(node->right);
    delete node;
}
 
bst_tree::~bst_tree() {
    delete_node(root);
}
 
int height(bst_tree::node* n) {
    if (!n) return 0;
    return n->height;
}
 
int get_balance(bst_tree::node* n) {
    if (!n) return 0;
    return height(n->left) - height(n->right);
}
 
bst_tree::node* rotate_right(bst_tree::node* y) {
    bst_tree::node* x = y->left;
    bst_tree::node* T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
 
    return x;
}
 
bst_tree::node* rotate_left(bst_tree::node* x) {
    bst_tree::node* y = x->right;
    bst_tree::node* T2 = y->left;
 
    y->left = x;
    x->right = T2;
 
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
 
    return y;
}
 
bst_tree::node* insert_avl(bst_tree::node* node, int64_t key) {
    if (!node) return new bst_tree::node(key);
 
    if (key < node->data)
        node->left = insert_avl(node->left, key);
    else if (key > node->data)
        node->right = insert_avl(node->right, key);
    else
        return node; // No duplicates
 
    node->height = 1 + std::max(height(node->left), height(node->right));
 
    int balance = get_balance(node);
 
    // Left Left Case
    if (balance > 1 && key < node->left->data)
        return rotate_right(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->data)
        return rotate_left(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->data) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->data) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
 
    return node;
}
 
void bst_tree::insert(int64_t data) {
    static std::mutex root_mutex;
    std::lock_guard<std::mutex> lock(root_mutex);
    root = insert_avl(root, data);
}
