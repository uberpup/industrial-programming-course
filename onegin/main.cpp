/*  Problem description:
    Input file has a poetic text filled with separate lines.
    Output file has to have three versions of the input text:
        1. Sorted lexicographically by letters
        2. Sorted lexicographically by letters in inverted string
        3. Original text
*/

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <functional>
#include <string_view>
#include <vector>

// Internal constants
const char* INPUT_FILENAME = "../poem.txt";
const char* OUTPUT_FILENAME = "../boosted_poem.txt";
const char SEPARATOR = '\n';
const char STRINGVIEW_SEPARATOR = '\0';

//! Struct uniting buffer, strings and operations among them
struct TxtManager {
    //! Trivial constructor
    TxtManager();

    //! Reading text from in_file and initialize both buf and strings
    void ReadFormat(std::FILE* in_file);

    //! Sorting strings using template comparator Cmp
    template <typename Cmp>
        void SortStrings();

    //! Sorting strings using std::greater
    void SortStrings();  // Non-template specialization

    //! fputs() of strings after sorting
    void WriteSorted(std::FILE* out_file);

    //! fputs() of strings in the default order
    void WriteOriginal(std::FILE* out_file);

    //! Default destructor
    ~TxtManager() = default;
private:
    //! Allocating memory for buf using fseek() and ftell()
    void ReserveFileSize(std::FILE* in_file);

    //! Swapping amputated with attached in buf
    size_t Tokenize(char amputated, char attached);

    std::vector<char> buf;
    std::vector<std::string_view> strings;
};

//! Cmp for lexicographical order
struct StartingLettersCmp {  // Cmp for 1st point of problem description
    bool operator()(const std::string_view& first, const std::string_view& second) const;
};

//! Cmp for lexicographical order in inverted strings
struct EndingLettersCmp {  // Cmp for 2nd point of problem description
    bool operator()(const std::string_view& first, const std::string_view& second) const;
};

int main() {
    // Data structures
    std::FILE* in_file = std::fopen(INPUT_FILENAME, "r");
    assert(in_file != nullptr);

    std::FILE* out_file = std::fopen(OUTPUT_FILENAME, "w");
    assert(out_file != nullptr);

    TxtManager text_manager;
    text_manager.ReadFormat(in_file);
    std::fclose(in_file);

    text_manager.SortStrings<StartingLettersCmp>();  // Point 1
    text_manager.WriteSorted(out_file);

    text_manager.SortStrings<EndingLettersCmp>();  // Point 2
    text_manager.WriteSorted(out_file);

    text_manager.WriteOriginal(out_file);  // Point 3

    std::fclose(out_file);

    return 0;
}

TxtManager::TxtManager():
    buf(),
    strings()
    {}

void TxtManager::ReadFormat(std::FILE* in_file) {  // Зачистка пустых строк при сортировке
    ReserveFileSize(in_file);
    buf.resize(std::fread(&buf[0], sizeof(char), buf.size(), in_file)); // in case fread() is smaller

    auto lines_count = Tokenize(SEPARATOR, STRINGVIEW_SEPARATOR);
    assert(!buf.empty());
    buf.push_back(STRINGVIEW_SEPARATOR);  // If last SEPARATOR was not provided

    strings.reserve(lines_count);  // memchr/strchr/c-шные строки
    strings.emplace_back(std::string_view(&buf[0]));
    for (size_t i = 1; i < buf.size(); ++i) {
        if (buf[i - 1] == STRINGVIEW_SEPARATOR) {
            strings.emplace_back(std::string_view(&buf[i]));
        }
    }
    assert(!strings.empty());
}

void TxtManager::ReserveFileSize(std::FILE *in_file) {
    std::fseek(in_file, 0, SEEK_END);

    buf.reserve(std::ftell(in_file));
    assert(!buf.empty());

    std::fseek(in_file, 0, SEEK_SET);
}

size_t TxtManager::Tokenize(char amputated, char attached) {
    size_t lines_count = 0;
    for (size_t idx = 0; idx < buf.size(); ++idx) {
        if (buf[idx] == amputated) {
            buf[idx] = attached;
            ++lines_count;
        }
    }
    return lines_count;
}

void TxtManager::WriteSorted(std::FILE* out_file) {
    for (const auto& str_view : strings) {
        if (str_view.length() > 0) {
            fputs(&str_view[0], out_file);
            fputc(SEPARATOR, out_file);
        }
    }
}

void TxtManager::WriteOriginal(std::FILE* out_file) {
    for (const char& ch : buf) {  // Running through original buffer
        if (ch == STRINGVIEW_SEPARATOR) {
            fputc(SEPARATOR, out_file);
        } else {
            fputc(ch, out_file);
        }
    }
}

template<typename Cmp>
void TxtManager::SortStrings() {
    std::sort(strings.begin(), strings.end(), Cmp());
}

void TxtManager::SortStrings() {
    std::sort(strings.begin(), strings.end(), std::greater<>());
}

bool StartingLettersCmp::operator()(const std::string_view& first,
        const std::string_view& second) const {  // Объединить компараторы
    size_t i = 0;
    size_t j = 0;
    while (i < first.length() && j < second.length()) {
        while (i < first.length() && !isalpha(first[i])) { ++i; }
        while (j < second.length() && !isalpha(second[j])) { ++j; }
        if (i >= first.length() || j >= second.length()) {
            break;
        }
        if (first[i] > second[j]) {
            return true;
        } else if (first[i] < second[j]) {
            return false;
        } else {
            ++i;
            ++j;
        }
    }
    return false;
}

bool EndingLettersCmp::operator()(const std::string_view& first,
        const std::string_view& second) const {
    size_t i = first.length();
    size_t j = second.length();
    while (i >= 0 && j >= 0) {
        while (i >= 0 && !isalpha(first[i])) { --i; }
        while (j >= 0 && !isalpha(second[j])) { --j; }
        if (i < 0 || j < 0) {
            break;
        }
        if (first[i] > second[j]) {
            return true;
        } else if (first[i] < second[j]) {
            return false;
        } else {
            ++i;
            ++j;
        }
    }
    return false;
}