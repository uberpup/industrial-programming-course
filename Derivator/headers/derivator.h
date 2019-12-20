#ifndef DERIVATOR_DERIVATOR_H
#define DERIVATOR_DERIVATOR_H

#include <cassert>
#include <ctgmath>
#include <iostream>
#include <string>
#include "consts.h"
#include "tree.h"


class Derivator : Tree<int> {
    friend class TreeDotConverter;
private:
    struct Node : PureNode {
        int value;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        std::weak_ptr<Node> parent;
        ssize_t func;
        bool is_const = false;
        Node() : PureNode() {
            value = 0;
            func = NONE;
            is_const = true;
        }
        Node(std::shared_ptr<Node> left, std::shared_ptr<Node> right,
                std::weak_ptr<Node> parent) :
                left(left), right(right), parent(parent) {}
        Node(const Node& other_node) : Node() {
            value = other_node.value;
            func = other_node.func;
            is_const = other_node.is_const;
        }
        Node(int value, ssize_t func, bool is_const = false, std::shared_ptr<Node> left = nullptr,
                std::shared_ptr<Node> right = nullptr, std::weak_ptr<Node> parent = std::weak_ptr<Node>()) :
                value(value), func(func), is_const(is_const), left(left), right(right), parent(parent) {}
        ~Node() = default;
    };
    void Rehang(std::shared_ptr<Node>& node);
    void Calculate(std::shared_ptr<Node>& node);
    void SimplifyConsts(std::shared_ptr<Node>& node, bool& result);
    void SimplifyZeros(std::shared_ptr<Node>& node, bool& result);
    void SimplifyOnes(std::shared_ptr<Node>& node, bool& result);
    std::shared_ptr<Node> SubTree(std::shared_ptr<Node>& node);
    std::shared_ptr<Node> current_node_;

    void RecursiveDecent(const std::string& str);
    int GetN(const std::string& str, size_t& idx);
    std::shared_ptr<Node> GetE(const std::string& str, size_t& idx);
    std::shared_ptr<Node> GetT(const std::string& str, size_t& idx);
    std::shared_ptr<Node> GetP(const std::string& str, size_t& idx);

public:
    Derivator();
    void Build(const std::string& expression);
    std::shared_ptr<Node> TakeDerivative(std::shared_ptr<Node>& node);
    void SaveTree(const std::string& filename);
    bool Simplify(std::shared_ptr<Node>& node);
    std::shared_ptr<Node> root_;
};

#endif //DERIVATOR_DERIVATOR_H
