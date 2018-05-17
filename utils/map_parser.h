#ifndef CHEMTOOLS_MAP_PARSER_H
#define CHEMTOOLS_MAP_PARSER_H


#include <map>

namespace utils {
    template<class T>
    class map_parser final {
    private:
        std::map<std::string, T> map;

    public:
        explicit map_parser(const std::map<std::string, T> &map) : map(map) {}

        const T &operator()(const std::string &key) const {
            return map.at(key);
        }
    };
}


#endif //CHEMTOOLS_MAP_PARSER_H
