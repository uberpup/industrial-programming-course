#ifndef AKINATOR_MIPT_TREE_DOT_CONVERTER_H
#define AKINATOR_MIPT_TREE_DOT_CONVERTER_H

#include <string>
#include "Akinator.h"

class TreeDotConverter {
public:
    template <typename T>
        void FillTree(Tree<T>);
    void FillTree(Akinator);

    template <typename T>
        void CreateFileAndSave(Tree<T>);
    void CreateFileAndSave(Akinator);

    template <typename T>
        void Save(Tree<T>);
    void Save(Akinator);
};

#endif //AKINATOR_MIPT_TREE_DOT_CONVERTER_H
