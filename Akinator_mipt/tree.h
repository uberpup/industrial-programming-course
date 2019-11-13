#ifndef AKINATOR_MIPT_TREE_H
#define AKINATOR_MIPT_TREE_H

#include <memory>
template <typename T>
class Tree {
public:
    Tree();
    ~Tree() = default;

protected:
    struct PureNode {
        T key;
        PureNode() = default;
        ~PureNode() = default;
    };
    struct Node : PureNode {
        T key;                // значение
        std::weak_ptr<Node> left;
        std::weak_ptr<Node> right;          // Люди - листья
        std::weak_ptr<Node> parent;
        Node() = default;
        ~Node() = default;
    };
    void Add();             // arg
    void Traverse();
    std::weak_ptr<Node> root;
};
#endif //AKINATOR_MIPT_TREE_H
