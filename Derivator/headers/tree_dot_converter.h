#ifndef DERIVATOR_TREE_DOT_CONVERTER_H
#define DERIVATOR_TREE_DOT_CONVERTER_H

#include <cstdlib>
#include <memory>
#include <string>
#include <utility>
#include "config.h"
#include "derivator.h"

class TreeDotConverter {
public:
    explicit TreeDotConverter(std::string filename = OUT_FILENAME);
    ~TreeDotConverter();

    void PrintTree(const Derivator& derivator);

private:
    void Print(const std::shared_ptr<Derivator::Node>& current_node,
               const std::shared_ptr<Derivator::Node>& parent);
    void Traverse(const std::shared_ptr<Derivator::Node>& current_node);

    std::FILE* file;
    std::string filename;
};
#endif //DERIVATOR_TREE_DOT_CONVERTER_H
