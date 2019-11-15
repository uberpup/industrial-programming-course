#include "Akinator.h"
#include "string_operations.h"

Akinator::Akinator(): current_node(), names() {
    current_node = root;
}

Akinator::QuestionNode::QuestionNode(const std::string& value) : QuestionNode() {
    key = value;
}

Akinator::AnswerNode::AnswerNode(const std::string& value) : AnswerNode() {
    key = value;
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
        std::cout << "Sorry, but " << name << "is already in tree." << std::endl;
        std::cout << "His/her features are:" << std::endl;
        Describe(name);
        return;
    }
    auto new_question_ptr = std::make_shared<QuestionNode>(feature + "?");
    auto new_node_ptr = std::make_shared<AnswerNode>(name);
    new_question_ptr->parent = current_node.lock()->parent;
    new_question_ptr->no = current_node;
    new_question_ptr->yes = std::weak_ptr<QuestionNode>(new_node_ptr);
    // Нужно сделать QuestionNode с feature, опустить соседнюю ветку
    // и прихерачить новый лист
    // проверить на правильность видов указателей !
}

void Akinator::Add(const std::string& name, bool direction) {
    if (!IsPresent(name)) {
        names.insert(str_tolower(name));
    } else {
        std::cout << "Sorry, but " << name << "is already in tree." << std::endl;
        std::cout << "His/her features are:" << std::endl;
        Describe(name);
        return;
    }

    auto new_node_ptr = std::make_shared<AnswerNode>(name);
    new_node_ptr->parent = current_node;

    if (direction) {
        current_node.lock()->yes = std::weak_ptr<AnswerNode>(new_node_ptr);
    } else {
        current_node.lock()->no = std::weak_ptr<AnswerNode>(new_node_ptr);
    }
}

void Akinator::AddToRoot(const std::string& name, const std::string& feature) {
    auto new_question_ptr = std::make_shared<QuestionNode>(feature + "?");
    root.lock()->yes =  std::weak_ptr<QuestionNode>(new_question_ptr);

    current_node = root.lock()->yes;
    auto new_node_ptr = std::make_shared<AnswerNode>(name);
    new_node_ptr->parent = current_node;
    current_node.lock()->yes = std::weak_ptr<AnswerNode>(new_node_ptr);
}

bool Akinator::IsPresent(const std::string& name) {
    return !(names.find(str_tolower(name)) == names.end());
}

void Akinator::Traverse(const std::string& target) {
    auto current = root;
    if (!current.lock()) {
        return;
    }

    if (current.lock()->key == target) {
        current_node = current;
        return;
    }

    std::stack<std::weak_ptr<Akinator::QuestionNode>> node_stack;
    node_stack.push(current);

    while (!node_stack.empty()) {
        current = node_stack.top();
        // output.push_back(current->key);
        node_stack.pop();
        if (current.lock()->yes.lock()) {
            node_stack.push(current.lock()->yes);
        }
        if (current.lock()->no.lock()) {
            node_stack.push(current.lock()->no);
        }
    }
}

void Akinator::Step(bool direction) {

    if (direction && current_node.lock()->yes.lock()) {     // has "yes" child
        current_node = current_node.lock()->yes;
    }
    if (!direction && current_node.lock()->no.lock()) {
        current_node = current_node.lock()->no;
    } else {
        std::cout << "There's no one with given features."
                     " Who is your character?" << std::endl;
        std::string name;
        std::cin >> name;
        Add(name, direction);
    }
}

std::stack<std::weak_ptr<Akinator::QuestionNode>> Akinator::Describe(
        const std::string& name, const int mode) {
    Traverse(str_tolower(name));

    std::stack<std::weak_ptr<QuestionNode>> d_stack;
    if (current_node.lock() == root.lock()) {
        std::cout << name << " is not found" << std::endl;
        return {};
    }

    std::cout << name << "'s description: " << std::endl;

    while (current_node.lock() != root.lock()) {
        d_stack.push(current_node);
        current_node = current_node.lock()->parent;
    }

    if (mode) {
        return d_stack;
    }

    for (size_t i = 0; i < d_stack.size() - 1; ++i) {
        // Нужно проверять направления
        auto top = d_stack.top();
        d_stack.pop();
        if (top.lock()->yes.lock() == d_stack.top().lock()) {
            std::cout << "This character is " << d_stack.top().lock()->key
                    << std::endl;
        } else {
            std::cout << "This character is not " << d_stack.top().lock()->key
                    << std::endl;
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
                 " character and his/her differentiating feature.\n"
                 " Then there will be 4 available modes:"
                 " Guessing-building with 'Yes/No' questions\n"
                 " Describing character's features\n"
                 " Distinguishing two characters\n"
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
    std::cout << "Add the first character" << std::endl;
    std::cin >> name;
    name = str_tolower(name);
    std::cout << "And his/her feature" << std::endl;
    std::cin >> feature;
    feature = str_tolower(feature);
    AddToRoot(name, feature);
}

void Akinator::BreakMessage() {
    std::cout << "Type 0 to go on the previous step,"
                 " 1 to save the current tree and exit,"
                 " 2 to exit without preservation";
    char in = take_first_from_input();

    switch (in) {
        case 0:
            return;
        case 1:
            SaveTree();
            exit = true;
            std::cout << "Goodbye!" << std::endl;
            return;
        case 2:
            exit = true;
            std::cout << "Goodbye!" << std::endl;
            return;
        default:
            std::cout << "Inappropriate data. Consider checking the rules!"
                    << std::endl;
            BreakMessage();
    }
}

void Akinator::BuildGuessMode() {
    while (current_node.lock() && current_node.lock()->is_question) {
        std::string answer;
        std::cout << current_node.lock()->key << std::endl;
        std::cin >> answer;
        answer = str_tolower(answer);

        bool destination = false;
        if (answer == "yes") {
            destination = true;
        } else if (answer != "no") {
            std::cout << "Incorrect answer. Answer either Yes or No."
                    << std::endl;
            continue;
        }
        Step(destination);
    }
    if (!current_node.lock()->is_question) {
        std::cout << "Is it " << current_node.lock()->key << " ?" << std::endl;
        std::string answer;
        std::cin >> answer;
        answer = str_tolower(answer);
        if (answer == "yes") {
            std::cout << "Yeah!";
            return;
        } else {
            std::string name, feature;
            std::cout << "Oh. Who is your character?" << std::endl;
            std::cin >> name;
            std::cout << "Then what differs " << current_node.lock()->key
                    << " and " << name << " ?" << std::endl;
            std::cin >> feature;
            Add(name, feature);
        }
    }
}

void Akinator::DescribingMode() {
    std::string name;
    std::cout << "Enter the name of your character " << std::endl;
    std::cin >> name;
    if (IsPresent(name)) {
        Describe(name);
    } else {
        std::cout << "Seems like your character is not added yet" << std::endl;
    }
}

void Akinator::DistinguishingMode() {
    std::string name1;
    std::string name2;
    std::cout << "Enter the two names of distinguished ones" << std::endl;
    std::cin >> name1 >> name2;
    Distinguish(name1, name2);
}

void Akinator::SaveTree() {}

void Akinator::ChooseMode() {
    while (!exit) {
        std::cout << "Choose the mode: " << std::endl;
        char in = take_first_from_input();

        switch (in) {
            case 0:         // Guess - build
                BuildGuessMode();
                break;
            case 1:         // Describe
                DescribingMode();
                break;
            case 2:         // Distinguish
                DistinguishingMode();
                break;
            case 3:         // Write
                SaveTree();
                break;
            case 4:         // Exit
                BreakMessage();
                break;
            default:
                std::cout << "Inappropriate data. Consider checking the rules!"
                        << std::endl;
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