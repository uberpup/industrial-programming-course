#include "tree_dot_converter.h"

TreeDotConverter::TreeDotConverter(std::string filename) :
        filename(std::move(filename)) {}

TreeDotConverter::~TreeDotConverter() {}

void TreeDotConverter::PrintTree(const Akinator& akinator) {
    file = std::fopen(filename.c_str(), "w");
    fprintf(file, "%s\n", "digraph G {");
    Traverse(akinator.root_);
    fprintf(file, "\n%s", "}");
    fclose(file);
}

void TreeDotConverter::Print(const std::shared_ptr<Akinator::QuestionNode>& current_node,
                             const std::shared_ptr<Akinator::QuestionNode>& parent) {
    if (current_node->is_question) {
        fprintf(file, "\"%s\" [color = %s];\n", current_node->key.c_str(), "gray80");
    } else {
        fprintf(file, "\"%s\" [color = %s];\n", current_node->key.c_str(), "royalblue2");
    }
    fflush(file);
    fprintf(file, "\"%s\" -> \"%s\" [label=\"  %s\"];\n", parent->key.c_str(),
            current_node->key.c_str(), (parent->yes == current_node ? "Yeah" : "No"));
    fflush(file);
}

void TreeDotConverter::Traverse(const std::shared_ptr<Akinator::QuestionNode>& current_node) {
    if (current_node->yes != nullptr) {
        Print(current_node->yes, current_node);
        Traverse(current_node->yes);
    }
    if (current_node->no != nullptr) {
        Print(current_node->no, current_node);
        Traverse(current_node->no);
    }
    if (current_node->yes == nullptr && current_node->no == nullptr) {
        return;
    }
}

void TreeDotConverter::FillTree(Akinator& akinator) {
    file = fopen(filename.c_str(), "r");
    char in = fgetc(file);
    while (in != EOF) {
        switch (in) {
            case '{':
                search_condition = true;
                break;
            case '}':
                ChangeObjectCondition();
                search_condition = false;
                break;
            case '"':
                if (search_condition) {
                    AddNode(akinator, ParseQuote());   // Add to the tree
                }
                break;
            default:
                break;
        }
        in = fgetc(file);
    }
}

void TreeDotConverter::AddNode(Akinator& akinator, const std::string& str) {
    if (akinator.current_node_ == akinator.root_) {
        if (buffered_string.empty()) {
            buffered_string = str;
            return;
        } else {
            akinator.AddToRoot(str, buffered_string);
            buffered_string = "";
            return;
        }
    }
    if (obj_condition == 0) {
        //
    }
    if (obj_condition == 1) {
        akinator.Add(str, true);
        return;
    }
    if (obj_condition == -1) {
        akinator.Add(str, false);
    }
}

void TreeDotConverter::ChangeObjectCondition() {
    if (obj_condition == 0) {
        obj_condition = -1;
        return;
    }
    if (obj_condition == -1) {
        obj_condition = 1;
        return;
    }
    if (obj_condition == 1) {
        obj_condition = -1;
        return;
    }
}

std::string TreeDotConverter::ParseQuote() {
    std::string result;
    char in = fgetc(file);
    while (in != '"') {
        in = fgetc(file);
        result.push_back(in);
    }
    return result;
}