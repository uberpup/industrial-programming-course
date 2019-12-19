#include "Akinator.h"
#include "string_operations.h"
#include "tree_dot_converter.h"

Akinator::Akinator(): root_(std::make_shared<QuestionNode>()), names_(), current_mode_(-1) {
    current_node_ = root_;
}

Akinator::QuestionNode::QuestionNode(const std::string& value) : is_question(true) {
    key = value;
}

Akinator::AnswerNode::AnswerNode(const std::string& value) {
    key = value;
    is_question = false;
}

void Akinator::Say(const std::string& words) {
    std::FILE* file = std::fopen("festival_text.txt", "wr");
    fprintf(file, "%s\n", words.c_str());
    std::fclose(file);
    system("./run_festival.sh");
}

void Akinator::Operate() {
    PrintRules();
    FirstStep();
    ChooseMode();
}

void Akinator::Add(const std::string& name, const std::string& feature = "") {
    if (!IsPresent(name)) {
        names_.insert(str_tolower(name));
    } else {
        printf("%s%s\n""Sorry, but ", name.c_str(), "is already in the tree.");
        printf("%s\n", "His/her features are:");
        Describe(name);
        return;
    }
    if (current_node_ == current_node_->parent.lock()->no) {      // Inserting new feature to the tree
        current_node_->parent.lock()->no =
                std::make_shared<QuestionNode>(feature);
        current_node_->parent.lock()->no->parent = current_node_->parent;
        current_node_->parent.lock()->no->no = current_node_;
        current_node_->parent = std::weak_ptr<QuestionNode>(
                current_node_->parent.lock()->no);
        current_node_->parent.lock()->yes =
                std::make_shared<AnswerNode>(name);
        current_node_->parent.lock()->yes->parent = current_node_->parent;
    } else {
        current_node_->parent.lock()->yes =
                std::make_shared<QuestionNode>(feature);
        current_node_->parent.lock()->yes->parent = current_node_->parent;
        current_node_->parent.lock()->yes->no = current_node_;
        current_node_->parent = std::weak_ptr<QuestionNode>(
                current_node_->parent.lock()->yes);
        current_node_->parent.lock()->yes =
                std::make_shared<AnswerNode>(name);
        current_node_->parent.lock()->yes->parent = current_node_->parent;
    }
}

void Akinator::Add(const std::string& name, bool direction) {
    if (!IsPresent(name)) {
        names_.insert(str_tolower(name));
    } else {
        printf("%s%s\n""Sorry, but ", name.c_str(), "is already in the tree.");
        printf("%s\n", "His/her features are:");
        Describe(name);
        return;
    }

    if (direction) {
        current_node_->yes = std::make_shared<AnswerNode>(name);
        current_node_->yes->parent = std::weak_ptr<QuestionNode>(current_node_);
    } else {
        current_node_->no = std::make_shared<AnswerNode>(name);
        current_node_->no->parent = std::weak_ptr<QuestionNode>(current_node_);
    }
}

void Akinator::AddToRoot(const std::string& name, const std::string& feature) {
    root_->yes =
            std::make_shared<QuestionNode>(feature);
    root_->yes->parent = std::weak_ptr<QuestionNode>(root_);

    current_node_ = root_->yes;
    current_node_->yes = std::make_shared<AnswerNode>(name);
    current_node_->yes->parent = std::weak_ptr<QuestionNode>(current_node_);

    names_.insert(str_tolower(name));
}

bool Akinator::IsPresent(const std::string& name) {
    if (str_tolower(name) == "kanye") {             // Easter egg
        system("./run_kanye.sh");
    }
    return !(names_.find(str_tolower(name)) == names_.end());
}

void Akinator::Traverse(const std::string& target) {
    auto current = root_;
    if (!current) {
        return;
    }

    if (current->key == target) {
        current_node_ = current;
        return;
    }

    std::stack<std::shared_ptr<Akinator::QuestionNode>> node_stack;
    node_stack.push(current);

    while (!node_stack.empty()) {
        current = node_stack.top();

        if (current->key == target) {
            current_node_ = current;
            return;
        }

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

    if (direction && current_node_->yes != nullptr) {     // has "yes" child
        current_node_ = current_node_->yes;
        return;
    }
    if (!direction && current_node_->no != nullptr) {
        current_node_ = current_node_->no;
        return;
    } else {
        printf("%s\n", "There's no one with given features."
                     " Who is your object?");
        std::string name;
        std::getline(std::cin, name);
        Add(str_tolower(name), direction);
        ChooseMode();
    }
}

std::stack<std::shared_ptr<Akinator::QuestionNode>> Akinator::Describe (
        const std::string& name, const int mode) {
    Traverse(str_tolower(name));

    std::stack<std::shared_ptr<QuestionNode>> d_stack;
    if (current_node_ == root_) {
        printf("%s%s\n", name.c_str(), " is not found");
        return {};
    }

    while (current_node_ != root_) {
        d_stack.push(current_node_);
        current_node_ = current_node_->parent.lock();
    }

    if (mode) {
        current_node_ = root_->yes;
        return d_stack;
    }

    printf("%s%s\n", name.c_str(), "'s description:");
    Say(name + "'s description:");

    size_t d_sz = d_stack.size() - 1;
    for (size_t i = 0; i < d_sz; ++i) {
        auto top = d_stack.top();
        d_stack.pop();
        if (top->yes == d_stack.top()) {
            printf("%s%s\n", "This object is ",
                    top->key.c_str());
            Say("This object is " + top->key);
        } else {
            printf("%s%s\n", "This object is not ",
                    top->key.c_str());
            Say("This object is not " + top->key);
        }
    }
    current_node_ = root_->yes;
    return {};
}

void Akinator::Distinguish(const std::string& name1, const std::string& name2) {
    if (!(IsPresent(name1) && IsPresent(name2))) {
        printf("%s\n", "Seems like one of the given objects is not in the tree yet");
        return;
    }
    if (str_tolower(name1) == str_tolower(name2)) {
        printf("%s\n", "Objects are identical");
        return;
    }
    auto stack_one = Describe(name1, 1);
    auto stack_two = Describe(name2, 1);
    auto top = stack_one.top();
    while (stack_one.top() == stack_two.top()) {
        top = stack_one.top();
        stack_one.pop();
        stack_two.pop();
    }
    if (top->yes == stack_one.top()) {
        printf("%s%s%s%s %s\n", name1.c_str(), " unlike ", name2.c_str(),
                " (is)", top->key.c_str());
        Say(name1 + " unlike " + name2 + " is" + top->key);
    } else {
        printf("%s%s%s%s %s\n", name2.c_str(), " unlike ", name1.c_str(),
                " (is)", top->key.c_str());
        Say(name2 + " unlike " + name1 + " is" + top->key);
    }
}

void Akinator::PrintRules() {
    printf("%s", "Hello, this is the MIPT Akinator."
                 " You either build me by yourself,"
                 " or load file of mipt-format proposal 1\n"
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
                 " in the written order, 4 is exit.\n"
                 " Answer the questions with Yes/No in any register."
                 " Let's go!\n");
}

void Akinator::FirstStep() {
    std::string name;
    std::string feature;
    printf("%s\n", "Add the first object");
    std::getline(std::cin, name);
    name = str_tolower(name);
    printf("%s\n", "And his/her feature");
    std::getline(std::cin, feature);
    feature = str_tolower(feature);
    AddToRoot(name, feature);
}

void Akinator::BreakMessage() {
    printf("%s\n", "Type 0 to go on the previous step,"
                 " 1 to save the current tree and exit,"
                 " 2 to exit without preservation");
    char in = take_first_from_input();

    switch (in) {
        case '0':
            return;
        case '1':
            SaveTree();
            exit_ = true;
            printf("%s\n", "Goodbye!");
            Say("Goodbye!");
            exit(0);
        case '2':
            exit_ = true;
            printf("%s\n", "Goodbye!");
            Say("Goodbye!");
            exit(0);
        default:
            printf("%s\n", "Inappropriate data. Consider checking the rules!");
            BreakMessage();
    }
}

void Akinator::BuildGuessMode() {
    while (current_node_ && current_node_->is_question) {
        std::string answer;
        printf("%s%s\n", current_node_->key.c_str(), "?");
        std::getline(std::cin, answer);
        answer = str_tolower(answer);

        bool destination = false;
        if (answer == "yes") {
            destination = true;
        } else if (answer != "no") {
            printf("%s\n", "Incorrect answer. Answer either Yes or No.");
            continue;
        }
        Step(destination);
    }
    if (!current_node_->is_question) {
        printf("%s%s%s\n", "Is it ", current_node_->key.c_str(), "?");
        std::string answer;
        std::getline(std::cin, answer);
        answer = str_tolower(answer);
        if (answer == "yes") {
            printf("%s\n", "Yeah!");
            current_node_ = root_->yes;
            return;
        } else {
            std::string name, feature;
            printf("%s\n", "Oh. Who is your object?");
            std::getline(std::cin, name);
            printf("%s%s%s%s%s\n", "Then what distinguishes ",
                   current_node_->key.c_str(), " and ", name.c_str(),
                   "?");
            std::getline(std::cin, feature);
            Add(str_tolower(name), str_tolower(feature));
            current_node_ = root_->yes;
        }
    }
}

void Akinator::DescribingMode() {
    std::string name;
    printf("%s\n", "Enter the name of your object");
    std::getline(std::cin, name);
    if (IsPresent(name)) {
        Describe(name);
    } else {
        printf("%s\n", "Seems like your object is not added yet");
        Say("Seems like your object is not added yet");
    }
}

void Akinator::DistinguishingMode() {
    std::string name1;
    std::string name2;
    printf("%s\n", "Enter the two names of distinguished ones on separate lines");
    std::getline(std::cin, name1);
    std::getline(std::cin, name2);
    Distinguish(name1, name2);
}


void Akinator::ChooseMode() {
    while (!exit_) {
        printf("%s\n", "Choose the mode: ");
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
                printf("%s\n", "Inappropriate data. Consider checking the rules!");
                ChooseMode();
                break;

        }
    }

}

void Akinator::SaveTree() {
    TreeDotConverter printer;
    printer.PrintTree(*this);
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