#include "tree_dot_converter.h"

TreeDotConverter::TreeDotConverter(const std::string& filename) {
    file = fopen(filename.c_str(), "wr");
}

TreeDotConverter::~TreeDotConverter() {
    fclose(file);
}

void TreeDotConverter::FillTree(Akinator) {

}

void TreeDotConverter::CreateFileAndSave(const Akinator& akinator) {
    // CreateFile
    Save(akinator);
}

void TreeDotConverter::Save(const Akinator& akinator) {
    // Traverse
}