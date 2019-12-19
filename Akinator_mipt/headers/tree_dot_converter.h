#ifndef AKINATOR_MIPT_TREE_DOT_CONVERTER_H
#define AKINATOR_MIPT_TREE_DOT_CONVERTER_H

#include <cstdlib>
#include <memory>
#include <string>
#include <utility>
#include "Akinator.h"

class TreeDotConverter {
public:
    explicit TreeDotConverter(std::string filename = "../out.dot");
    ~TreeDotConverter();
    //template <typename T>
    //    void FillTree(Tree<T>);
    void FillTree(Akinator& akinator);

    //template <typename T>
    //    void PrintTree(Tree<T>);
    void PrintTree(const Akinator& akinator);

private:
    std::string ParseQuote();
    void AddNode(Akinator& akinator, const std::string& str);
    void ChangeObjectCondition();
    void Print(const std::shared_ptr<Akinator::QuestionNode>& current_node,
            const std::shared_ptr<Akinator::QuestionNode>& parent);
    void Traverse(const std::shared_ptr<Akinator::QuestionNode>& current_node);
    char obj_condition = 0;      // 0 - question, 1 - yes, -1 - no
    bool search_condition = false; // false - not searching for quotes,
    std::FILE* file;
    std::string filename;
    std::string buffered_string;
};

#endif //AKINATOR_MIPT_TREE_DOT_CONVERTER_H
