#include "Akinator.h"
#include "string_operations.h"

Akinator::Akinator(): root(std::make_shared<QuestionNode>()), names() {
    current_node = root;
}

Akinator::QuestionNode::QuestionNode(const std::string& value) : is_question(true) {
    key = value;
}

Akinator::AnswerNode::AnswerNode(const std::string& value) {
    key = value;
    is_question = false;
}

void Akinator::Operate() {
    PrintRules();
    FirstStep();
    ChooseMode();
}

void Akinator::Add(const std::string& name, const std::string& feature = "") {
    if (!IsPresent(name)) {
        names.insert(str_tolower(name));
    } else {
        printf("%s%s""Sorry, but ", name.c_str(), "is already in the tree.\n");
        printf("%s", "His/her features are:\n");
        Describe(name);
        return;
    }
    if (current_node == current_node->parent.lock()->no) {      // Inserting new feature to the tree
        current_node->parent.lock()->no =
                std::make_shared<QuestionNode>(feature);
        current_node->parent.lock()->no->parent = current_node->parent;
        current_node->parent.lock()->no->no = current_node;
        current_node->parent = std::weak_ptr<QuestionNode>(
                current_node->parent.lock()->no);
        current_node->parent.lock()->yes =
                std::make_shared<AnswerNode>(name);
    } else {
        current_node->parent.lock()->yes =
                std::make_shared<QuestionNode>(feature);
        current_node->parent.lock()->yes->parent = current_node->parent;
        current_node->parent.lock()->yes->no = current_node;
        current_node->parent = std::weak_ptr<QuestionNode>(
                current_node->parent.lock()->yes);
        current_node->parent.lock()->yes =
                std::make_shared<AnswerNode>(name);
    }
}

void Akinator::Add(const std::string& name, bool direction) {
    if (!IsPresent(name)) {
        names.insert(str_tolower(name));
    } else {
        printf("%s%s""Sorry, but ", name.c_str(), "is already in the tree.\n");
        printf("%s", "His/her features are:\n");
        Describe(name);
        return;
    }

    if (direction) {
        current_node->yes = std::make_shared<AnswerNode>(name);
        current_node->yes->parent = std::weak_ptr<QuestionNode>(current_node);
    } else {
        current_node->no = std::make_shared<AnswerNode>(name);
        current_node->yes->parent = std::weak_ptr<QuestionNode>(current_node);
    }
}

void Akinator::AddToRoot(const std::string& name, const std::string& feature) {
    root->yes =
            std::make_shared<QuestionNode>(feature);

    current_node = root->yes;
    current_node->yes = std::make_shared<AnswerNode>(name);
    current_node->yes->parent = std::weak_ptr<QuestionNode>(current_node);
}

bool Akinator::IsPresent(const std::string& name) {
    return !(names.find(str_tolower(name)) == names.end());
}

void Akinator::Traverse(const std::string& target) {
    auto current = root;
    if (!current) {
        return;
    }

    if (current->key == target) {
        current_node = current;
        return;
    }

    std::stack<std::shared_ptr<Akinator::QuestionNode>> node_stack;
    node_stack.push(current);

    while (!node_stack.empty()) {
        current = node_stack.top();
        // output.push_back(current->key);
        node_stack.pop();
        if (current->yes) {
            node_stack.push(current->yes);
        }
        if (current->no) {
            node_stack.push(current->no);
        }
    }
}

void Akinator::Step(bool direction) {

    if (direction && current_node->yes != nullptr) {     // has "yes" child
        current_node = current_node->yes;
        return;
    }
    if (!direction && current_node->no != nullptr) {
        current_node = current_node->no;
        return;
    } else {
        printf("%s", "There's no one with given features."
                     " Who is your object?\n");
        std::string name;
        std::cin >> name;
        Add(name, direction);
        ChooseMode();
    }
}

std::stack<std::shared_ptr<Akinator::QuestionNode>> Akinator::Describe(
        const std::string& name, const int mode) {
    Traverse(str_tolower(name));

    std::stack<std::shared_ptr<QuestionNode>> d_stack;
    if (current_node == root) {
        printf("%s%s", name.c_str(), " is not found\n");
        return {};
    }

    printf("%s%s", name.c_str(), "'s description: \n");

    while (current_node != root) {
        d_stack.push(current_node);
        current_node = current_node->parent.lock();
    }

    if (mode) {
        return d_stack;
    }

    for (size_t i = 0; i < d_stack.size() - 1; ++i) {
        // Нужно проверять направления
        auto top = d_stack.top();
        d_stack.pop();
        if (top->yes == d_stack.top()) {
            printf("%s%s%s", "This object is ",
                    d_stack.top()->key.c_str(), "\n");
        } else {
            printf("%s%s%s", "This object is not ",
                    d_stack.top()->key.c_str(), "\n");
        }
    }
    return {};
}

void Akinator::Distinguish(const std::string& name1, const std::string& name2) {
    auto stack_one = Describe(name1);
    auto stack_two = Describe(name2);
    // Пройтись по стекам
}

void Akinator::PrintRules() {
    printf("%s", "Hello, this is MIPT Akinator."
                 " You either build my by yourself,"
                 " or load dot-file of mipt-format"
                 " (More on github.com/andtit2001/mipt-format).\n"
                 " To build a tree you need to start with initializing first"
                 " object and his/her differentiating feature.\n"
                 " Then there will be 4 available modes:"
                 " Guessing-building with 'Yes/No' questions\n"
                 " Describing object's features\n"
                 " Distinguishing two objects\n"
                 " Saving the tree to mipt-format.\n"
                 " Mode is defined in the start of every iteration"
                 " by entering the number from 0 to 3,"
                 " in the written order, 4 is exit."
                 " Answer the questions with Yes/No in any register."
                 " Let's go!\n");
}

void Akinator::FirstStep() {
    std::string name;
    std::string feature;
    printf("%s", "Add the first object\n");
    std::cin >> name;
    name = str_tolower(name);
    printf("%s", "And his/her feature\n");
    std::cin >> feature;
    feature = str_tolower(feature);
    AddToRoot(name, feature);
}

void Akinator::BreakMessage() {
    printf("%s", "Type 0 to go on the previous step,"
                 " 1 to save the current tree and exit,"
                 " 2 to exit without preservation\n");
    char in = take_first_from_input();

    switch (in) {
        case 0:
            return;
        case 1:
            SaveTree();
            exit = true;
            printf("%s", "Goodbye!\n");
            return;
        case 2:
            exit = true;
            printf("%s", "Goodbye!\n");
            return;
        default:
            printf("%s", "Inappropriate data. Consider checking the rules!\n");
            BreakMessage();
    }
}

void Akinator::BuildGuessMode() {
    while (current_node && current_node->is_question) {
        std::string answer;
        printf("%s%s", current_node->key.c_str(), "?\n");
        std::cin >> answer;
        answer = str_tolower(answer);

        bool destination = false;
        if (answer == "yes") {
            destination = true;
        } else if (answer != "no") {
            printf("%s", "Incorrect answer. Answer either Yes or No.\n");
            continue;
        }
        Step(destination);
    }
    if (!current_node->is_question) {
        printf("%s%s%s","Is it ", current_node->key.c_str(), " ?\n");
        std::string answer;
        std::cin >> answer;
        answer = str_tolower(answer);
        if (answer == "yes") {
            printf("%s", "Yeah!\n");
            current_node = root->yes;
            return;
        } else {
            std::string name, feature;
            printf("%s", "Oh. Who is your object?\n");
            std::cin >> name;
            printf("%s%s%s%s%s", "Then what distinguishes ",
                    current_node->key.c_str(), " and ", name.c_str(),
                    " ?\n");
            std::cin >> feature;
            Add(name, feature);
            current_node = root->yes;
        }
    }
}

void Akinator::DescribingMode() {
    std::string name;
    printf("%s", "Enter the name of your object\n");
    std::cin >> name;
    if (IsPresent(name)) {
        Describe(name);
    } else {
        printf("%s", "Seems like your object is not added yet\n");
    }
}

void Akinator::DistinguishingMode() {
    std::string name1;
    std::string name2;
    printf("%s", "Enter the two names of distinguished ones\n");
    std::cin >> name1 >> name2;
    Distinguish(name1, name2);
}

void Akinator::SaveTree() {}

void Akinator::ChooseMode() {
    while (!exit) {
        printf("%s", "Choose the mode: \n");
        char in = take_first_from_input();

        switch (in) {
            case '0':         // Guess - build
                BuildGuessMode();
                break;
            case '1':         // Describe
                DescribingMode();
                break;
            case '2':         // Distinguish
                DistinguishingMode();
                break;
            case '3':         // Write
                SaveTree();
                break;
            case '4':         // Exit
                BreakMessage();
                break;
            default:
                printf("%s", "Inappropriate data. Consider checking the rules!\n");
                ChooseMode();
                break;

        }
    }

}

/*
    Greeting in Russian:
     "Привет, это МФТИшный Акинатор."
                 " Расклад такой - ты меня строишь сам,"
                 " либо подгружаешь dot-файл mipt-формата"
                 " (Подробнее - github.com/andtit2001/mipt-format).\n"
                 " При построении дерева нужно инициализировать первого"
                 " персонажа и его отличительную черту.\n"
                 " После этого будет доступно 4 режима:"
                 " Отгадывание-построение по вопросам 'Да/Нет'\n"
                 " Описание характеристик персонажа, находящегося в дереве\n"
                 " Различия двух персонажей\n"
                 " Запись нынешнего дерева в файл mipt-формата.\n"
                 " Режим определяется в начале каждой итерации"
                 " введением числа от 0 до 3,"
                 " в соответствии с порядком перечисления, 4 - выход."
                 " На вопросы отвечайте Да/Нет (в любом регистре). "
                 " Начинаем!\n"
 */