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

std::string organic::get_chain_prefix(size_t length) {
    return chain_prefix[length];
}
