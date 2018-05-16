#include <algorithm>
#include <sstream>
#include "compound.h"

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
        for (int j = 0; j < d.groups.size(); ++j) {
            group *g = d.groups[j];
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
    out << chain_prefix[details.size()];
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
        out << '-' << (s.first == suffixes.rbegin()->first ? suffix_names : last_suffix_names)[s.first];
    }
    return out.str();
}

base::formula organic::compound::get_formula() const noexcept {
    base::formula f;
    f[base::C] = static_cast<uint16_t>(details.size());
    for (size_t i = 0; i < details.size(); ++i)
        f[base::H] += 4 - details[i].bond_type - details[i].groups.size() - (i ? details[i - 1].bond_type.value : 0);
    for (const auto &d : details)
        for (int i = 0; i < d.groups.size(); ++i)
            f += d.groups[i]->get_formula();
    return f;
}
