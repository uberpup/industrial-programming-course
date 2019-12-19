#ifndef AKINATOR_MIPT_TREE_H
#define AKINATOR_MIPT_TREE_H

#include <memory>
#include <stack>

template <typename T>
class Tree {
public:
    Tree() = default;
    ~Tree() = default;

protected:
    struct PureNode {
        T key;
        PureNode() = default;
        ~PureNode() = default;
    };
    void Traverse();

private:
    struct Node : PureNode {
        T key;                // значение
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;          // Люди - листья
        std::weak_ptr<Node> parent;
        Node() = default;
        ~Node() = default;
    };
    void Add(const T& key, bool direction);
    std::shared_ptr<Node> current_node_;
    std::shared_ptr<Node> root_;
};
#endif //AKINATOR_MIPT_TREE_H
