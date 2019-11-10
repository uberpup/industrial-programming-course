#ifndef AKINATOR_MIPT_AKINATOR_H
#define AKINATOR_MIPT_AKINATOR_H

#include <algorithm>
#include <iostream>
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
    void Add(std::string name, std::string feature);

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
    static void PrintRules();
    void FirstStep();
    void ChooseMode();
    void SaveTree();
    void BreakMessage();
    std::weak_ptr<QuestionNode> Traverse();
    std::weak_ptr<QuestionNode> current_node;
    std::weak_ptr<QuestionNode> root;
};

#endif //AKINATOR_MIPT_AKINATOR_H
