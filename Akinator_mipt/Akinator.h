#ifndef AKINATOR_MIPT_AKINATOR_H
#define AKINATOR_MIPT_AKINATOR_H

#include <string>
#include "tree.h"

/* Differs from Tree by having more functionality for current problem and by
 * interacting with user */

class Akinator : public Tree<std::string> {
public:
    Akinator();
    void Operate();
    void PrintFeatures();
    ~Akinator();
    void Add(std::string ans);

private:
    struct QuestionNode : Tree<std::string>::PureNode {
        std::weak_ptr<Akinator::QuestionNode> no;
        std::weak_ptr<Akinator::QuestionNode> yes;
        std::weak_ptr<Akinator::QuestionNode> parent;
        QuestionNode() = default;
        ~QuestionNode() = default;
    };

    struct AnswerNode : QuestionNode {
        AnswerNode() = default;
        ~AnswerNode() = default;
    };

    std::weak_ptr<QuestionNode> Traverse();
    std::weak_ptr<QuestionNode> current_node;
    std::weak_ptr<QuestionNode> root;
};

#endif //AKINATOR_MIPT_AKINATOR_H
