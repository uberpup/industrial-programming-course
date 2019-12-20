#include "tree_dot_converter.h"

TreeDotConverter::TreeDotConverter(std::string filename) :
        filename(std::move(filename)) {}

TreeDotConverter::~TreeDotConverter() {}

void TreeDotConverter::PrintTree(const Derivator& derivator) {
    file = std::fopen(filename.c_str(), "w");
    fprintf(file, "%s\n", "digraph G {");
    assert(derivator.root_ != nullptr);
    fprintf(file, "node%zu [label = root];\n", derivator.root_.get());
    Traverse(derivator.root_);
    fprintf(file, "\n%s", "}");
    fclose(file);
}

void TreeDotConverter::Print(const std::shared_ptr<Derivator::Node>& current_node,
                             const std::shared_ptr<Derivator::Node>& parent) {
    fprintf(file, "node%zu [label = \"", current_node.get());
    if (!current_node->is_const) {
        fprintf(file, "%s\"]\n", FUNC_NAMES[current_node->func].c_str());
    } else {
        fprintf(file, "%d\"]\n", current_node->value);
    }
    fprintf(file, "node%zu -> node%zu;\n", parent.get(), current_node.get());
    fflush(file);
}

void TreeDotConverter::Traverse(const std::shared_ptr<Derivator::Node>& current_node) {
    if (current_node->left != nullptr) {
        Print(current_node->left, current_node);
        Traverse(current_node->left);
    }
    if (current_node->right != nullptr) {
        Print(current_node->right, current_node);
        Traverse(current_node->right);
    }
    if (current_node->left == nullptr && current_node->right == nullptr) {
        return;
    }
}