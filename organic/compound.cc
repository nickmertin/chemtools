#include <algorithm>
#include <sstream>
#include <functional>
#include "compound.h"
#include "organic.h"

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

organic::compound::compound() noexcept : details({{{}, 0}}) {}

organic::compound::compound(size_t length) {
    for (size_t i = 0; i < length; ++i)
        details.push_back({{}, i < length - 1});
}

std::string organic::compound::get_iupac_name() const noexcept {
    std::stringstream out;
    std::map<std::string, std::vector<int>> prefixes;
    for (int i = 0; i < details.size(); ++i) {
        const carbon_detail &d = details[i];
        for (auto g : d.groups) {
            if (g->get_nomenclature() == group::prefix)
                prefixes[g->get_name()].push_back(i + 1);
        }
    }
    bool hyphenate = false;
    for (auto &p : prefixes) {
        if (hyphenate)
            out << '-';
        else
            hyphenate = true;
        for (int i = 0; i < p.second.size(); ++i) {
            if (i)
                out << ',';
            out << p.second[i];
        }
        out << '-' << p.first;
    }
    if (hyphenate)
        out << '-';
    out << get_chain_prefix(details.size());
    std::vector<int> bondTypes;
    std::transform(details.cbegin(), details.cend(), std::back_inserter(bondTypes), [] (const auto &d) { return d.bond_type.value; });
    std::map<group::suffix_type, std::vector<int>> suffixes;
    for (int i = 0; i < bondTypes.size(); ++i)
        switch (bondTypes[i]) {
            case 2:
                suffixes[group::alkene].push_back(i + 1);
                break;
            case 3:
                suffixes[group::alkyne].push_back(i + 1);
                break;
        }
    for (const auto &d : details)
        for (int i = 0; i < d.groups.size(); ++i)
            if (d.groups[i]->get_nomenclature() == group::suffix)
                suffixes[d.groups[i]->get_suffix_type()].push_back(i + 1);
    if (*std::max_element(bondTypes.cbegin(), bondTypes.cend()) <= 1)
        out << (suffixes.empty() ? "ane" : "an");
    for (auto &s : suffixes) {
        out << '-';
        for (int i = 0; i < s.second.size(); ++i) {
            if (i)
                out << ',';
            out << s.second[i];
        }
        out << '-' << (s.first == suffixes.crbegin()->first ? last_suffix_names : suffix_names)[s.first];
    }
    return out.str();
}

base::formula organic::compound::get_formula() const noexcept {
    base::formula f;
    f[base::C] = static_cast<uint16_t>(details.size());
    for (size_t i = 0; i < details.size(); ++i)
        f[base::H] += 4 - details[i].bond_type - details[i].groups.size() - (i ? details[i - 1].bond_type.value : 0);
    for (const auto &d : details)
        for (auto g : d.groups)
            f += g->get_formula();
    return f;
}

void organic::compound::set_bond_type(size_t index, utils::ranged_numeric<int, 1, 3> value) {
    if (!index || index-- >= details.size() || details[index].groups.size() + value + (index ? details[index - 1].bond_type.value : 0) > 4)
        throw utils::EX_BOUNDS;
    details[index].bond_type = value.value;
}

void organic::compound::add_group(size_t index, std::function<group *()> factory) {
    if (!index || index-- >= details.size() || details[index].groups.size() + details[index].bond_type + (index ? details[index - 1].bond_type.value : 0) > 3)
        throw utils::EX_BOUNDS;
    details[index].groups.push_back(factory());
}

void organic::compound::remove_group(size_t index, size_t group) {
    if (!index || index-- >= details.size() || !group || group-- > details[index].groups.size())
        throw utils::EX_BOUNDS;
    utils::var_array<organic::group *, 3> new_groups;
    std::copy(details[index].groups.cbegin(), details[index].groups.cbegin() + group, std::back_inserter(new_groups));
    std::copy(details[index].groups.cbegin() + group + 1, details[index].groups.cend(), std::back_inserter(new_groups));
    delete details[index].groups[group];
    details[index].groups = new_groups;
}
