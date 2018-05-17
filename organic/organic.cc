#include "organic.h"

const static std::string chain_prefix[11] = {
        "",
        "meth",
        "eth",
        "prop",
        "but",
        "pent",
        "hex",
        "hept",
        "oct",
        "non",
        "dec"
};

const static std::string numeric_prefix[11] = {
        "",
        "",
        "di",
        "tri",
        "tetra",
        "penta",
        "hexa",
        "hepta",
        "octa",
        "ennea",
        "deca"
};

const static std::string numeric_prefix_vowel[11] = {
        "",
        "",
        "di",
        "tri",
        "tetr",
        "pent",
        "hex",
        "hept",
        "oct",
        "enne",
        "dec"
};

const static std::string suffix_names[3] = {
        "en",
        "yn",
        "ol"
};

const static std::string last_suffix_names[3] = {
        "ene",
        "yne",
        "ol"
};

std::string organic::get_chain_prefix(size_t length) {
    return chain_prefix[length];
}

std::string organic::get_numeric_prefix(size_t n, bool vowel) {
    return (vowel ? numeric_prefix : numeric_prefix_vowel)[n];
}

std::string organic::get_suffix_name(organic::group::suffix_type type, bool last) {
    return (last ? last_suffix_names : suffix_names)[type];
}
