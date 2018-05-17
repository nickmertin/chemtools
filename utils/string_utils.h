#ifndef CHEMTOOLS_STRING_UTILS_H
#define CHEMTOOLS_STRING_UTILS_H


#include <vector>
#include <string>

namespace utils {
    template<class charT>
    std::vector<std::basic_string<charT>> split(std::basic_string<charT> str, charT delimiter) {
        size_t pos = 0;
        std::vector<std::basic_string<charT>> parts;
        do {
            size_t start = pos;
            if (start)
                ++start;
            pos = str.find(delimiter, start);
            parts.push_back(str.substr(start, (pos == std::basic_string<charT>::npos ? str.length() : pos) - start));
        } while (pos != std::basic_string<charT>::npos);
        return parts;
    }

    template<class charT>
    bool is_vowel(charT c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
}

#endif //CHEMTOOLS_STRING_UTILS_H
