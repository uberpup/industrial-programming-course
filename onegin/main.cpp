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
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>

struct StartingLettersCmp {  // Cmp for 1st point of problem description
    bool operator()(const std::string_view& first, const std::string_view& second) const;
};

struct EndingLettersCmp {  // Cmp for 2nd point of problem description
    bool operator()(const std::string_view& first, const std::string_view& second) const;
};

int main() {
    // Internal constants
    const char* INPUT_FILENAME = "poem.txt";
    const char* OUTPUT_FILENAME = "boosted_poem.txt";
    const char SEPARATOR = '\n';
    const char STRINGVIEW_SEPARATOR = '\0';

    // Data structures
    std::FILE* in_file = std::fopen(INPUT_FILENAME, "r");
    std::FILE* out_file = std::fopen(OUTPUT_FILENAME, "w");
    std::vector<char> buf;
    std::vector<std::string_view> string_manager;

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

    string_manager.reserve(lines_count);
    string_manager.emplace_back(std::string_view(&buf[0]));
    for (size_t i = 1; i < buf.size(); ++i) {
        if (buf[i - 1] == STRINGVIEW_SEPARATOR) {
            string_manager.emplace_back(std::string_view(&buf[i]));
        }
    }

    std::sort(string_manager.begin(), string_manager.end(), StartingLettersCmp());
    for (const auto& str_view : string_manager) {  // Point 1
        if (str_view.length() > 0) {
            fputs(&str_view[0], out_file);
            fputc('\n', out_file);
        }
    }

    std::sort(string_manager.begin(), string_manager.end(), EndingLettersCmp());
    for (const auto& str_view : string_manager) { // Point 2
        if (str_view.length() > 0) {
            fputs(&str_view[0], out_file);
            fputc('\n', out_file);
        }
    }

    for (const char& ch : buf) { // Point 3
        if (ch == '\0') {
            fputc('\n', out_file);
        } else {
            fputc(ch, out_file);
        }
    }

    std::fclose(in_file);
    std::fclose(out_file);
    return 0;
}

bool StartingLettersCmp::operator()(const std::string_view& first, const std::string_view& second) const {
    size_t i = 0;
    size_t j = 0;
    while (i < first.length() && j < second.length()) {
        while (i < first.length() && !isalpha(first[i])) { ++i; }
        while (j < second.length() && !isalpha(second[j])) { ++j;}
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