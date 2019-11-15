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
        std::weak_ptr<Node> left;
        std::weak_ptr<Node> right;          // Люди - листья
        std::shared_ptr<Node> parent;
        Node() = default;
        ~Node() = default;
    };
    void Add(const T& key, bool direction);
    std::shared_ptr<Node> current_node;
    std::shared_ptr<Node> root;
};
#endif //AKINATOR_MIPT_TREE_H
