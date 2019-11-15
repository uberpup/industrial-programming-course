#include "tree.h"

template <typename T>
void Tree<T>::Traverse() {
    auto current = root;
    if (!current) {
        return;
    }

    std::stack<std::shared_ptr<Node>> node_stack;
    node_stack.push(current);

    while (!node_stack.empty()) {
        current = node_stack.top();
        // output.push_back(current->key);
        node_stack.pop();
        if (current->right.lock()) {
            node_stack.push(current->right.lock());
        }
        if (current->left.lock()) {
            node_stack.push(current->left.lock());
        }
    }
}

template <typename T>
void Tree<T>::Add(const T& key, bool direction) {
    auto new_node_ptr = std::make_shared<Node>(key);
    new_node_ptr->parent = current_node;

    if (direction) {
        current_node.lock()->right = std::weak_ptr<Node>(new_node_ptr);
    } else {
        current_node.lock()->left = std::weak_ptr<Node>(new_node_ptr);
    }
}