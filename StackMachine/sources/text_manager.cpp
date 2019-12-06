#include "text_manager.h"

TxtManager::TxtManager():
        buf(),
        strings()
{}

void TxtManager::ReadFormat(std::FILE* in_file) {
    ReserveFileSize(in_file);
    buf.resize(std::fread(buf.data(), sizeof(char), buf.size(), in_file)); // in case fread() is smaller

    auto lines_count = Tokenize(SEPARATOR, STRINGVIEW_SEPARATOR);
    assert(buf.capacity());
    buf.push_back(STRINGVIEW_SEPARATOR);  // If last SEPARATOR was not provided

    strings.reserve(lines_count);
    strings.emplace_back(std::string(&buf[0]));
    for (size_t i = 1; i < buf.size(); ++i) {
        if (buf[i - 1] == STRINGVIEW_SEPARATOR) {
            strings.emplace_back(std::string(&buf[i]));
        }
    }
    assert(!strings.empty());
}

void TxtManager::ReserveFileSize(std::FILE *in_file) {
    std::fseek(in_file, 0, SEEK_END);

    buf.resize(std::ftell(in_file));
    assert(buf.capacity());

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

void TxtManager::WriteText(std::FILE* out_file) {
    for (const auto& str_view : strings) {
        if (str_view.length() > 0) {
            fputs(&str_view[0], out_file);
            fputc(SEPARATOR, out_file);
        }
    }
}

void TxtManager::WriteBuf(std::FILE* out_file) {
    for (const char& ch : buf) {  // Running through original buffer
        if (ch == STRINGVIEW_SEPARATOR) {
            fputc(SEPARATOR, out_file);
        } else {
            fputc(ch, out_file);
        }
    }
}
