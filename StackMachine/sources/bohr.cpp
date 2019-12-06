#include "bohr.h"

Bohr::BohrNode::BohrNode(): suff_link(), term_link(), transitions(),
                            is_terminal(false), is_root(false),
                            wordlist_idxs() {}

Bohr::Bohr(): root(std::make_shared<BohrNode>()), wordlist(), pattern_size(0) {
    root->suff_link = std::weak_ptr<BohrNode>(root);  // Спецификация полей под корень
    root->term_link = std::weak_ptr<BohrNode>(root);
    root->is_root = true;
}

Bohr::Bohr(size_t pattern_size): root(std::make_shared<BohrNode>()), wordlist(),
                                 pattern_size(pattern_size) {
    root->suff_link = std::weak_ptr<BohrNode>(root);  // Спецификация полей под корень
    root->term_link = std::weak_ptr<BohrNode>(root);
    root->is_root = true;
}

bool Bohr::BohrNode::operator ==(const Bohr::BohrNode& rhv) {  // На всякий случай
    return transitions == rhv.transitions &&
           suff_link.lock() == rhv.suff_link.lock() &&
           term_link.lock() == rhv.term_link.lock() &&
           is_terminal == rhv.is_terminal &&
           is_root == rhv.is_root;
}

std::shared_ptr<Bohr::BohrNode> Bohr::BohrNode::FindTransition(char ch) {
    auto c_it = transitions.find(ch);
    if (c_it == transitions.cend()) {
        return nullptr;
    } else {
        return c_it->second;
    }
}

void Bohr::AddPattern(const std::string& pattern, size_t divider_count) {
    auto current_node = root;
    for (const char& ch : pattern) {
        auto neighbour_node = current_node->FindTransition(ch);
        if (neighbour_node == nullptr) {
            neighbour_node = std::make_shared<BohrNode>();
            if (current_node->is_root) {  // Первые символы ссылаются на корень
                neighbour_node->suff_link = std::weak_ptr<BohrNode>(root);
                neighbour_node->term_link = neighbour_node->suff_link;
            }
            current_node->transitions[ch] = neighbour_node;
        }
        current_node = neighbour_node;
    }

    if (!current_node->is_root) {
        current_node->is_terminal = true;
        current_node->wordlist_idxs.push_back(wordlist.size());
        wordlist.emplace_back(pattern,
                              (!wordlist.empty() ?
                               wordlist.back().second + pattern.length() :
                               pattern.length()) + divider_count);
    }
}

void Bohr::Init() {  // BFS
    std::queue<std::shared_ptr<BohrNode>> bfs_queue;
    bfs_queue.push(root);
    while (!bfs_queue.empty()) {
        auto current_node = bfs_queue.front();
        bfs_queue.pop();
        for (auto& map_el : current_node->transitions) {  // Строим суффиксные и терминальные ссылки
            const char ch = map_el.first;
            auto neighbour_node = map_el.second;

            auto temp_node = current_node->suff_link;
            while (true) {  // Суффиксные
                auto transition = temp_node.lock()->FindTransition(ch);
                if (transition != nullptr && transition != neighbour_node) {
                    neighbour_node->suff_link = transition;
                    break;
                } else {
                    if (temp_node.lock()->is_root) {
                        break;
                    }
                    temp_node = temp_node.lock()->suff_link;
                }
            }
            if (neighbour_node->suff_link.lock() == nullptr) {
                neighbour_node->suff_link = std::weak_ptr<BohrNode>(root);
                neighbour_node->term_link = neighbour_node->suff_link;
            }

            if (neighbour_node->suff_link.lock()->is_terminal) {  // Терминальные
                neighbour_node->term_link = neighbour_node->suff_link;
            } else {
                neighbour_node->term_link =
                        neighbour_node->suff_link.lock()->term_link;
            }

            bfs_queue.push(neighbour_node);
        }
    }
}

void Bohr::Step(const char ch, std::shared_ptr<BohrNode>& current_node) {
    while (current_node != nullptr) {
        auto candidate = current_node->FindTransition(ch);
        if (candidate != nullptr) {
            current_node = candidate;
            return;
        }
        if (candidate == nullptr && current_node == root) {
            return;
        }
        current_node = current_node->suff_link.lock();
    }

    if (!(current_node->is_root)) {  // Если никого не нашли
        current_node = root;
    }
}

std::vector<size_t> Bohr::PatternSearch(std::string& text, size_t extra_symbols) {  // Проверка вопросов в конце
    std::vector<size_t> pattern_indexes;
    std::deque<size_t> search_deque(pattern_size);
    size_t patterns_number = wordlist.size();

    auto current_node = root;
    for (size_t i = 0; i < text.length(); ++i) {
        Step(text[i], current_node);
        auto additional_node = current_node;
        while (!additional_node->is_root) {
            if (additional_node->is_terminal) {
                for (auto& idx : additional_node->wordlist_idxs) {
                    // Вычитаем из размера расстояние до предполагаемого начала слова
                    ++search_deque[search_deque.size() - wordlist[idx].second];
                }
            }
            additional_node = additional_node->term_link.lock();
        }

        if (search_deque.front() == patterns_number && i >= pattern_size - 1) {  // Все слова из куска встретились
            pattern_indexes.push_back(i - pattern_size + 1);
        }
        search_deque.pop_front();
        search_deque.push_back(0);

    }
    return pattern_indexes;
}

bool Bohr::IsPresent(const std::string &str) {
    auto current_node = root;

    for (auto& ch : str) {
        Step(ch, current_node);
        if (current_node->is_root) {
            return false;
        }
        if (current_node->is_terminal) {
            return true;
        }
    }
    return false;
}