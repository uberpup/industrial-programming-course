#ifndef DERIVATOR_BOHR_H
#define DERIVATOR_BOHR_H

#include <deque>
#include <queue>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

const char DIVIDER = '?';

class Bohr {
public:
    struct BohrNode {
        BohrNode();
        std::map<const char, std::shared_ptr<BohrNode>> transitions;
        std::weak_ptr<BohrNode> term_link;
        std::weak_ptr<BohrNode> suff_link;
        bool is_terminal;  // Если терминальная, то храним индекс внутри словаря
        bool is_root;
        std::vector<size_t> wordlist_idxs;

        bool operator ==(const BohrNode& rhv);
        std::shared_ptr<BohrNode> FindTransition(char ch);
        ~BohrNode() = default;
    };
    std::vector<std::pair<std::string, size_t>> wordlist;  // Строка и расстояние до начала
    size_t pattern_size;
    std::shared_ptr<BohrNode> root;

    Bohr();
    explicit Bohr(size_t pattern_size);
    void AddPattern(const std::string& pattern, size_t divider_count);
    void Init();
    void Step(char ch, std::shared_ptr<BohrNode>& current_node);
    [[nodiscard]] bool IsPresent(const std::string& str);
    std::vector<size_t> PatternSearch(std::string& text, size_t extra_symbols);
    ~Bohr() = default;
};

#endif //DERIVATOR_BOHR_H
