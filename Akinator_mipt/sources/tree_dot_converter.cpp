#include "tree_dot_converter.h"

TreeDotConverter::TreeDotConverter(const std::string& filename) {
    file = fopen(filename.c_str(), "wr");
}

TreeDotConverter::~TreeDotConverter() {
    fclose(file);
}

template <typename T>
void TreeDotConverter::FillTree(Tree<T>) {

}

void TreeDotConverter::FillTree(Akinator) {

}

template <typename T>
void TreeDotConverter::CreateFileAndSave(Tree<T>) {

}

void TreeDotConverter::CreateFileAndSave(Akinator) {

}

template <typename T>
void TreeDotConverter::Save(Tree<T>) {

}

void TreeDotConverter::Save(Akinator) {

}