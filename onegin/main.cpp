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
const char* INPUT_FILENAME = "poem.txt";
const char* OUTPUT_FILENAME = "boosted_poem.txt";
const char SEPARATOR = '\n';
const char STRINGVIEW_SEPARATOR = '\0';

struct TxtManager{
    TxtManager();
    void ReadFormat(std::FILE* in_file);
    template <typename Cmp>
        void SortStrings();
    void SortStrings();  // Non-template specialization
    void WriteSorted(std::FILE* out_file);
    void WriteOriginal(std::FILE* out_file);
private:
    std::vector<char> buf;
    std::vector<std::string_view> strings;
};

struct StartingLettersCmp {  // Cmp for 1st point of problem description
    bool operator()(const std::string_view& first, const std::string_view& second) const;
};

struct EndingLettersCmp {  // Cmp for 2nd point of problem description
    bool operator()(const std::string_view& first, const std::string_view& second) const;
};

int main() {
    // Data structures
    std::FILE* in_file = std::fopen(INPUT_FILENAME, "r");
    std::FILE* out_file = std::fopen(OUTPUT_FILENAME, "w");
    TxtManager text_manager;
    text_manager.ReadFormat(in_file);

    text_manager.SortStrings<StartingLettersCmp>();
    text_manager.WriteSorted(out_file);  // Point 1

    text_manager.SortStrings<EndingLettersCmp>();
    text_manager.WriteSorted(out_file);  // Point 2

    text_manager.WriteOriginal(out_file);  // Point 3

    std::fclose(in_file);
    std::fclose(out_file);
    return 0;
}

TxtManager::TxtManager(): buf(), strings() {}

void TxtManager::ReadFormat(std::FILE* in_file) {
    size_t lines_count = 0;
    size_t idx = 0;
    while (std::fscanf(in_file,"%c", &buf[idx]) == 1) {
        if (buf[idx] == SEPARATOR){
            buf[idx] =  STRINGVIEW_SEPARATOR;
            ++lines_count;
        }
        ++idx;
    }
    buf.push_back('\0');

    strings.reserve(lines_count);
    strings.emplace_back(std::string_view(&buf[0]));
    for (size_t i = 1; i < buf.size(); ++i) {
        if (buf[i - 1] == STRINGVIEW_SEPARATOR) {
            strings.emplace_back(std::string_view(&buf[i]));
        }
    }
}

void TxtManager::WriteSorted(std::FILE* out_file) {
    for (const auto& str_view : strings) {
        if (str_view.length() > 0) {
            fputs(&str_view[0], out_file);
            fputc('\n', out_file);
        }
    }
}

void TxtManager::WriteOriginal(std::FILE* out_file) {
    for (const char& ch : buf) {
        if (ch == '\0') {
            fputc('\n', out_file);
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
    std::sort(strings.begin(), strings.end(), std::greater());
}

bool StartingLettersCmp::operator()(const std::string_view& first, const std::string_view& second) const {
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

bool EndingLettersCmp::operator()(const std::string_view& first, const std::string_view& second) const {
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