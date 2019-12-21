#include "derivator.h"
#include "tree_dot_converter.h"

//todo Дописать конструкторы, Распарсить с арифметическим приоритетом, Проверить что без упрощений работает, Написать упрощения

Derivator::Derivator() : root_(nullptr), operations_parser_() {
    current_node_ = root_;
    //FillBohr();
}

void Derivator::Build(const std::string& expression) {
    RecursiveDecent(expression);
}

void Derivator::RecursiveDecent(const std::string& str) {
    size_t idx = 0;
    auto value = GetE(str, idx);
    assert(str[idx] == '#');
    root_ = value;
}

inline std::shared_ptr<Derivator::Node> Derivator::GetE(const std::string& str, size_t& idx) {
    auto value = GetT(str, idx);
    while (str[idx] == '-' || str[idx] == '+') {
        char operation = str[idx];
        ++idx;
        auto next_value = GetT(str, idx);
        ssize_t func;
        if (operation == '+') {
            func = ADDITION;
        }
        if (operation == '-') {
            func = SUBTRACTION;
        }
        auto add_ptr = std::make_shared<Node>(0, func, false, value, next_value);
        auto parent_ptr = std::weak_ptr<Node>(add_ptr);
        value->parent = parent_ptr;
        next_value->parent = parent_ptr;
        value = add_ptr;
    }
    return value;
}


inline std::shared_ptr<Derivator::Node> Derivator::GetT(const std::string& str, size_t& idx) {
    auto value = GetP(str, idx);
    while (str[idx] == '*' || str[idx] == '/') {
        char operation = str[idx];
        ++idx;
        auto next_value = GetP(str, idx);
        ssize_t func;

        if (operation == '*') {
            func = MULTIPLICATION;
        }
        if (operation == '/') {
            func = DIVISION;
        }

        auto mul_ptr = std::make_shared<Node>(0, func, false, value, next_value);
        auto parent_ptr = std::weak_ptr<Node>(mul_ptr);
        value->parent = parent_ptr;
        next_value->parent = parent_ptr;
        value = mul_ptr;
    }
    return value;
}

inline std::shared_ptr<Derivator::Node> Derivator::GetP(const std::string& str, size_t& idx) {
    if (str[idx] == '(') {
        ++idx;
        auto value = GetE(str, idx);
        assert(str[idx] == ')');
        ++idx;
        return value;

    } else if (str[idx] >= 'A' && str[idx] <= 'z' &&
            str[idx] != 's' && str[idx] != 'c') {
        GetV(str, idx);
        Node variable;
        variable.is_const = false;
        variable.func = VARIABLE;
        return std::make_shared<Node>(variable);

    } else if (str[idx] == 's' || str[idx] == 'c') {
        return GetTrig(str, idx);
    } else {
        Node number;
        number.value = GetN(str, idx);
        number.is_const = true;
        number.func = -1;
        return std::make_shared<Node>(number);
    }
}

inline void Derivator::GetV(const std::string& str, size_t& idx) {
    std::string var_str;
    while (str[idx] >= 'A' && str[idx] <= 'z' &&
            str[idx] != 's' && str[idx] != 'c') {
        ++idx;
    }
}

std::shared_ptr<Derivator::Node> Derivator::GetTrig(const std::string& str, size_t& idx) {
    std::shared_ptr<Node> trig_ptr;
    while (str[idx] == 's' || str[idx] == 'c') {
        char operation = str[idx];
        ++idx;
        auto next_value = GetE(str, idx);
        ssize_t func;

        if (operation == 's') {
            func = SIN;
        }
        if (operation == 'c') {
            func = COS;
        }

        trig_ptr = std::make_shared<Node>(0, func, false,
                                               nullptr, next_value);
        next_value->parent = std::weak_ptr<Node>(trig_ptr);
    }
    return trig_ptr;
}

inline int Derivator::GetN(const std::string& str, size_t& idx) {
    int value = 0;
    while (str[idx] >= '0' && str[idx] <= '9') {
        value *= 10;
        value += str[idx] - '0';
        ++idx;
    }
    return value;
}

// todo add logarithm
std::shared_ptr<Derivator::Node> Derivator::TakeDerivative(
        std::shared_ptr<Node>& node) {
    if (node == root_) {
        if (root_->left != nullptr) {
            TakeDerivative(root_->left);
        }
        if (root_->right != nullptr) {
            TakeDerivative(root_->right);
        }
    }
    auto new_node = std::make_shared<Node>();
    std::shared_ptr<Node> newer_node;
    switch(node->func) {
        case ADDITION:
            new_node->func = ADDITION;
            new_node->left = TakeDerivative(node->left);
            new_node->right = TakeDerivative(node->right);
            break;
        case MULTIPLICATION:
            if (node->left->is_const) {
                new_node->func = MULTIPLICATION;
                new_node->left = SubTree(node->left);
                new_node->right = TakeDerivative(node->right);
                new_node->left->parent = new_node;
                new_node->right->parent = new_node;
            } else if (node->right->is_const) {
                new_node->func = MULTIPLICATION;
                new_node->left = TakeDerivative(node->left);
                new_node->right = SubTree(node->right);
                new_node->left->parent = new_node;
                new_node->right->parent = new_node;
            } else {
                new_node->func = ADDITION;

                new_node->left = std::make_shared<Node>(nullptr, nullptr, new_node);
                new_node->left->func = MULTIPLICATION;
                new_node->left->right = SubTree(node->right);
                new_node->left->left = TakeDerivative(node->right);

                new_node->right = std::make_shared<Node>(nullptr, nullptr, new_node);
                new_node->right->func = MULTIPLICATION;
                new_node->right->left = SubTree(node->left);
                new_node->right->right = TakeDerivative(node->right);
            }
            break;
        case POWER:
            newer_node = std::make_shared<Node>(nullptr, nullptr, new_node);
            newer_node->func = MULTIPLICATION;
            newer_node->left = SubTree(node->right);
            newer_node->left->parent.lock() = newer_node;

            newer_node->right = std::make_shared<Node>(nullptr, nullptr, newer_node);
            newer_node->right->func = POWER;
            newer_node->left = SubTree(node->left);
            newer_node->right->left = SubTree(node->right);
            newer_node->right->right->parent = newer_node->right;
            newer_node->right->value = node->right->value - 1;

            new_node->func = MULTIPLICATION;
            new_node->right = newer_node;
            new_node->left = TakeDerivative(node->left);
            new_node->left->parent = new_node;
            break;
        case SIN:
            newer_node = std::make_shared<Node>(nullptr, nullptr, new_node);
            newer_node->func = COS;
            newer_node->right = SubTree(node->right);
            newer_node->right->parent = newer_node;

            new_node->func = MULTIPLICATION;
            new_node->left = newer_node;

            new_node->right = TakeDerivative(node->right);
            new_node->right->parent = new_node;
            break;
        case COS:
            newer_node = std::make_shared<Node>(nullptr, nullptr, new_node);

            newer_node->func = MULTIPLICATION;
            newer_node->right = std::make_shared<Node>(nullptr, nullptr, new_node);
            newer_node->right->func = SIN;
            newer_node->right->right = SubTree(node->right);
            newer_node->right->right->parent = newer_node->right;

            newer_node->left = std::make_shared<Node>(nullptr, nullptr, new_node);
            newer_node->left->is_const = true;
            newer_node->left->value = -1;


            new_node->func = MULTIPLICATION;
            new_node->left = newer_node;

            new_node->right = TakeDerivative(node->right);
            new_node->right->parent = new_node;
            break;
        case VARIABLE:
            new_node->is_const = true;
            new_node->value = 1;
            break;
        default:
            break;
    }
    if (!node->func) {
        if (node->is_const) {
            new_node->is_const = true;
            new_node->value = 0;
        }
    }
    return new_node;
}

void Derivator::Calculate(std::shared_ptr<Node>& node) {
    if (node->func <= POWER) {
        switch (node->func) {
            case ADDITION:
                node->right->value += node->left->value;
                break;
            case SUBTRACTION:
                node->right->value -= node->left->value;
                break;
            case MULTIPLICATION:
                node->right->value *= node->left->value;
                break;
            case DIVISION:
                assert(node->right->value);
                node->right->value = node->left->value / node->right->value;
                break;
            case POWER:
                node->right->value = static_cast<int>(pow(node->left->value,
                        node->right->value));
                break;
            default:
                assert(false);
        }
    }
    Rehang(node);
}

std::shared_ptr<Derivator::Node> Derivator::SubTree(
        std::shared_ptr<Node>& node) {
    auto new_node = std::make_shared<Node>(*node);
    if (node->left != nullptr) {
        new_node->left = std::make_shared<Node>(*new_node->left);
        new_node->left->parent = std::weak_ptr<Node>(new_node);
    }
    if (node->right != nullptr) {
        new_node->right = std::make_shared<Node>(*new_node->right);
        new_node->right->parent = std::weak_ptr<Node>(new_node);
    }
    return new_node;
}

void Derivator::Rehang(std::shared_ptr<Node>& node) {
    assert(node != nullptr);
    if (node != root_) {
        if (node == node->parent.lock()->left) {
            node->parent.lock()->left = node->right;
        }
        else {
            node->parent.lock()->right = node->right;
        }
        node->right->parent = node->parent;
        node = nullptr;
    } else {
        root_ = node->right;
        root_->left = nullptr;
        root_->right = nullptr;
    }
}

void Derivator::SimplifyConsts(std::shared_ptr<Node>& node, bool& result) {
    if (node->left != nullptr) {
        SimplifyConsts(node->left, result);
    }
    if (node->right != nullptr) {
        SimplifyConsts(node->right, result);
    }
    if (node->is_const) return;
    if ((node->left != nullptr) && (node->right != nullptr)) {
        if (node->left->is_const && node->right->is_const) {
            Calculate(node);
            result = true;
        }
    }
}

void Derivator::SimplifyZeros(std::shared_ptr<Node>& node, bool& result) {
    if (node->left) {
        SimplifyZeros(node->left, result);
    }
    if (node->right) {
        SimplifyZeros(node->right, result);
    }
    if (node->is_const) return;
    if ((node->left != nullptr) && (node->right != nullptr)
            && (node->func == MULTIPLICATION)) {
        if (node->left->is_const && (node->left->value == 0)) {
            result = true;
            std::swap(node->left, node->right);
            Rehang(node);
        } else if (node->right->is_const && node->right->value == 0) {
            result = true;
            Rehang(node);
        }
    }
    if ((node->left != nullptr) && (node->right != nullptr) &&
            (node->func == DIVISION) && (node->left->value == 0)) {
        result = true;
        std::swap(node->left, node->right);
        Rehang(node);
    }
}

void Derivator::SimplifyOnes(std::shared_ptr<Node>& node, bool& result) {
    if (node->left != nullptr) {
        SimplifyOnes(node->left, result);
    }
    if (node->right != nullptr) {
        SimplifyOnes(node->right, result);
    }
    if (node->is_const) return;
    if ((node->left != nullptr) && (node->right != nullptr)
            && (node->func == MULTIPLICATION)) {
        if (node->left->is_const && node->left->value == 1) {
            result = true;
            Rehang(node);
        } else if (node->right->is_const && node->right->value == 1) {
            result = true;
            std::swap(node->left, node->right);
            Rehang(node);
        }
    }
    if ((node->left != nullptr) && (node->right != nullptr)
            && (node->right->value == 1) && (node->func == DIVISION)) {
        result = true;
        std::swap(node->left, node->right);
        Rehang(node);
    }
}

bool Derivator::Simplify(std::shared_ptr<Node>& node) {
    current_node_ = node;
    bool result = false;
    bool temp_result = false;
    SimplifyConsts(node, temp_result);
    if (temp_result) {
        result = true;
        temp_result = false;
    }
    node = current_node_;
    SimplifyOnes(node, temp_result);
    if (temp_result) {
        result = true;
        temp_result = false;
    }
    node = current_node_;
    SimplifyZeros(node, temp_result);
    if (temp_result) {
        result = true;
        temp_result = false;
    }
    return result;
}

void Derivator::SaveTree(const std::string& filename) {
    TreeDotConverter printer(filename);
    printer.PrintTree(*this);
}