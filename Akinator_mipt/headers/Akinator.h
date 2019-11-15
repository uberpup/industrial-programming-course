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
    ~Akinator() = default;

private:
    struct QuestionNode : Tree<std::string>::PureNode {
        std::shared_ptr<Akinator::QuestionNode> no;
        std::shared_ptr<Akinator::QuestionNode> yes;
        std::weak_ptr<Akinator::QuestionNode> parent;
        bool is_question{};
        QuestionNode() = default;
        explicit QuestionNode(const std::string& value);
        ~QuestionNode() = default;
    };
    struct AnswerNode : QuestionNode {
        AnswerNode() = default;
        explicit AnswerNode(const std::string& value);
        ~AnswerNode() = default;
    };

    static void PrintRules();
    void FirstStep();
    void ChooseMode();

    void Traverse(const std::string& target = "");
    void Step(bool direction);
    void Add(const std::string& name, const std::string& feature);
    void Add(const std::string& name, bool direction);
    void AddToRoot(const std::string& name, const std::string& feature);
    std::stack<std::shared_ptr<QuestionNode>> Describe(const std::string& name,
            int mode = 0);
    void Distinguish(const std::string& name1, const std::string& name2);

    bool IsPresent(const std::string& name);

    void BuildGuessMode();
    void DescribingMode();
    void DistinguishingMode();
    void SaveTree();
    void BreakMessage();

    std::shared_ptr<QuestionNode> current_node;
    std::shared_ptr<QuestionNode> root;
    std::set<std::string> names;
    bool exit = false;
};

#endif //AKINATOR_MIPT_AKINATOR_H
