#include "Akinator.h"
#include "string_operations.cpp"

Akinator::Akinator(): Tree<std::string>(), current_node(), names() {
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
    // Тут конструируем узлы
    // Step в for'e
    // Вопрос с режимом в каждой итерации
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
        std::cout << "His her features are:" << std::endl;
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

bool Akinator::IsPresent(const std::string& name) {
    return !(names.find(str_tolower(name)) == names.end());
}

void Akinator::Traverse() {
    // pre-order
}

std::weak_ptr<Akinator::QuestionNode> Akinator::Step(bool direction) {
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

void Akinator::Describe(const std::string& name) {}

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
    Add(name, feature);
}

void Akinator::BreakMessage() {
    std::cout << "Type 0 to go on the previous step,"
                 " 1 to save the current tree and exit,"
                 " 2 to exit without preservation";
    char in = take_first_from_input();

    switch (in) {
        case 0:
            ChooseMode();
            break;
        case 1:
            SaveTree();
            std::cout << "Goodbye!" << std::endl;
            break;
        case 2:
            std::cout << "Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Inappropriate data. Consider checking the rules!";
            BreakMessage();
            break;
    }
}

void Akinator::BuildGuessMode() {}

void Akinator::DescribingMode() {}

void Akinator::DistinguishingMode() {}

void Akinator::SaveTree() {}

void Akinator::ChooseMode() {
    std::cout << "Choose the mode: " << std::endl;
    char in = take_first_from_input();

    switch(in) {
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
            std::cout << "Inappropriate data. Consider checking the rules!";
            ChooseMode();
            break;

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