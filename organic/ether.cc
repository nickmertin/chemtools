#include <sstream>
#include "ether.h"
#include "organic.h"
#include "../base/stdint_suffix.h"

organic::ether::ether(uint16_t left_length, uint16_t left_position, uint16_t right_length, uint16_t right_position) : left_length(left_length), left_position(left_position), right_length(right_length), right_position(right_position) {
    if (!left_length || !right_length || left_position > left_length || right_position > right_length)
        throw utils::EX_BOUNDS;
}

std::string organic::ether::get_iupac_name() const noexcept {
    struct part {
        bool numbered;
        std::string name;
        size_t position;
    };
    std::stringstream out;
    if (left_length == right_length) {
        if (left_length > 2)
            out << std::min(left_position, right_position) << ',' << std::max(left_position, right_position) << '-';
        out << "di" << get_chain_prefix(left_length) << "ylether";
    }
    else {
        part left{left_length > 2, get_chain_prefix(left_length), left_position};
        part right{right_length > 2, get_chain_prefix(right_length), right_position};
        if (left.name > right.name)
            std::swap(left, right);
        if (left.numbered)
            out << left.position << '-';
        out << left.name << "yl";
        if (right.numbered)
            out << '-' << right.position << '-';
        out << right.name << "ylether";
    }
    return out.str();
}

base::formula organic::ether::get_formula() const noexcept {
    base::formula f;
    f[base::C] = left_length + right_length;
    f[base::H] = (left_length + right_length) * 2_u16 + 2_u16;
    f[base::O] = 1;
    return f;
}
