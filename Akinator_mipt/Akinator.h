#ifndef AKINATOR_MIPT_AKINATOR_H
#define AKINATOR_MIPT_AKINATOR_H

#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include "tree.h"

/* Differs from Tree by having more functionality for current problem and by
 * interacting with user */

class Akinator : public Tree<std::string> {
public:
    Akinator();
    void Operate();
    void PrintFeatures();
    ~Akinator() = default;

private:
    struct QuestionNode : Tree<std::string>::PureNode {
        std::weak_ptr<Akinator::QuestionNode> no;
        std::weak_ptr<Akinator::QuestionNode> yes;
        std::weak_ptr<Akinator::QuestionNode> parent;
        bool is_question = true;
        QuestionNode() = default;
        QuestionNode(const std::string& value);
        ~QuestionNode() = default;
    };
    struct AnswerNode : QuestionNode {
        bool is_question = false;
        AnswerNode() = default;
        AnswerNode(const std::string& value);
        ~AnswerNode() = default;
    };

    static void PrintRules();
    void FirstStep();
    void ChooseMode();

    void Traverse(const std::string& target
            = "");
    std::stack<std::weak_ptr<QuestionNode>> WayToRoot(std::weak_ptr<QuestionNode> node);
    std::weak_ptr<QuestionNode> Step(bool direction);
    void Add(const std::string& name, const std::string& feature);
    void Add(const std::string& name, bool direction);
    void AddToRoot(const std::string& name, const std::string& feature);
    void Describe(const std::string& name);

    bool IsPresent(const std::string& name);

    void BuildGuessMode();
    void DescribingMode();
    void DistinguishingMode();
    void SaveTree();
    void BreakMessage();

    std::weak_ptr<QuestionNode> current_node;
    std::weak_ptr<QuestionNode> root;
    std::set<std::string> names;
    bool exit = false;
};

#endif //AKINATOR_MIPT_AKINATOR_H
