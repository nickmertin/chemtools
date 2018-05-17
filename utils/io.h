#ifndef CHEMTOOLS_IO_H
#define CHEMTOOLS_IO_H


#include <string>

namespace utils {
    template<class T>
    T parse(const std::string &s);

    template<>
    long parse<long>(const std::string &s) {
        return std::stol(s);
    }

    template<>
    unsigned long parse<unsigned long>(const std::string &s) {
        return std::stoul(s);
    }

    template<>
    long long parse<long long>(const std::string &s) {
        return std::stoll(s);
    }

    template<>
    unsigned long long parse<unsigned long long>(const std::string &s) {
        return std::stoull(s);
    }
}

#endif //CHEMTOOLS_IO_H
