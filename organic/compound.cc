#include <algorithm>
#include <sstream>
#include <functional>
#include "compound.h"
#include "organic.h"
#include "../utils/string_utils.h"

void organic::compound::set_bond_type(size_t index, utils::ranged_numeric<int, 1, 3> value) {
    if ((*this)[index].groups.size() + value + (index > 1 ? (*this)[index - 1].bond_type.value : 0) > 4)
        throw utils::EX_BOUNDS;
    (*this)[index].bond_type = value.value;
}

void organic::compound::add_group(size_t index, std::function<group *()> factory) {
    if ((*this)[index].groups.size() + (*this)[index].bond_type + (index > 1 ? (*this)[index - 1].bond_type.value : 0) > 3)
        throw utils::EX_BOUNDS;
    (*this)[index].groups.push_back(factory());
}

void organic::compound::remove_group(size_t index, size_t group) {
    if (!group || group-- > (*this)[index].groups.size())
        throw utils::EX_BOUNDS;
    utils::var_array<organic::group *, 4> new_groups;
    std::copy((*this)[index].groups.cbegin(), (*this)[index].groups.cbegin() + group, std::back_inserter(new_groups));
    std::copy((*this)[index].groups.cbegin() + group + 1, (*this)[index].groups.cend(), std::back_inserter(new_groups));
    delete (*this)[index].groups[group];
    (*this)[index].groups = new_groups;
}
