#include "branch.h"
#include "organic.h"

std::string organic::branch::get_name() {
    return get_chain_prefix(length) + "yl";
}

base::formula organic::branch::get_formula() {
    base::formula f;
    f[base::C] = static_cast<uint16_t>(length);
    f[base::H] = static_cast<uint16_t>(2 * length + 1);
    return f;
}

organic::group::nomenclature organic::branch::get_nomenclature() {
    return prefix;
}

organic::branch::branch(size_t length) : length(length) {}
