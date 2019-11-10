#include "Akinator.h"

std::string str_tolower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); }
    );
    return str;
}

char take_first_from_input() {
    std::string input;
    std::cin >> input;
    char in = input[0];     // Смотрим на один символ из ввода,
    // чтобы остальная его часть не мешалась если что
    return in;
}

void Akinator::Add(std::string name, std::string feature) {

    //current_node.lock()->
}

void Akinator::PrintRules() {
    printf("%s", "Привет, это МФТИшный Акинатор."
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
                 " Начинаем!\n");
}

void Akinator::FirstStep() {
    std::string name;
    std::string feature;
    std::cout << "Добавьте первого персонажа" << std::endl;
    std::cin >> name;
    name = str_tolower(name);
    std::cout << "И его отличительное качество" << std::endl;
    std::cin >> feature;
    feature = str_tolower(feature);
    Add(name, feature);
}

void Akinator::BreakMessage() {
    std::cout << "Введите 0 если хотите вернуться,"
                 " 1 если хотите сохранить дерево в файл и выйти,"
                 " 2 если хотите выйти без сохранения";
    char in = take_first_from_input();

    switch (in) {
        case 0:
            ChooseMode();
            break;
        case 1:
            SaveTree();
            std::cout << "До скорых встреч!" << std::endl;
            break;
        case 2:
            std::cout << "До скорых встреч!" << std::endl;
            break;
        default:
            std::cout << "Некорректные данные. Может посмотрите в описание?!";
            BreakMessage();
            break;
    }
}

void Akinator::SaveTree() {}

void Akinator::ChooseMode() {
    std::cout << "Выберите режим: " << std::endl;
    char in = take_first_from_input();

    switch(in) {
        case 0:         // Отгадывание - запись

            break;
        case 1:         // Описание

            break;
        case 2:         // Различия

            break;
        case 3:         // Запись

            break;
        case 4:         // Выход
            BreakMessage();
            break;
        default:
            std::cout << "Некорректные данные. Может посмотрите в описание?!";
            ChooseMode();
            break;

    }

}

void Akinator::Operate() {
    PrintRules();
    FirstStep();
    ChooseMode();
    // Тут конструируем узлы
    // Traverse в for'e
    // Вопрос с режимом в каждой итерации
}
