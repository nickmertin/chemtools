#ifndef CHEMTOOLS_ORGANIC_H
#define CHEMTOOLS_ORGANIC_H


#include <string>
#include "group.h"

namespace organic {
    std::string get_chain_prefix(size_t length);
    std::string get_numeric_prefix(size_t n, bool vowel);
    std::string get_suffix_name(group::suffix_type type, bool last);
}

#endif //CHEMTOOLS_ORGANIC_H
