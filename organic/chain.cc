#include <sstream>
#include <algorithm>
#include "chain.h"
#include "compound.h"
#include "../utils/string_utils.h"
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

organic::chain::chain() noexcept : chain(1) {}

organic::chain::chain(size_t length) noexcept {
    for (size_t i = 0; i < length; ++i)
        details.push_back({{}, i < length - 1});
}

std::string organic::chain::get_iupac_name() const noexcept {
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
        if (details.size() > 1) {
            if (hyphenate)
                out << '-';
            else
                hyphenate = true;
            for (int i = 0; i < p.second.size(); ++i) {
                if (i)
                    out << ',';
                out << p.second[i];
            }
            out << '-';
        }
        out << (utils::is_vowel(p.first[0]) ? numeric_prefix_vowel : numeric_prefix)[p.second.size()] << p.first;
    }
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
        if (details.size() > (s.first == group::alcohol ? 1 : 2)) {
            out << '-';
            for (int i = 0; i < s.second.size(); ++i) {
                if (i)
                    out << ',';
                out << s.second[i];
            }
            out << '-';
        }
        out << (utils::is_vowel(suffix_names[s.first][0]) ? numeric_prefix_vowel : numeric_prefix)[s.second.size()] << (s.first == suffixes.crbegin()->first ? last_suffix_names : suffix_names)[s.first];
    }
    return out.str();
}

base::formula organic::chain::get_formula() const noexcept {
    base::formula f;
    f[base::C] = static_cast<uint16_t>(size());
    for (size_t i = 0; i <= size(); ++i)
        f[base::H] += 4 - details[i].bond_type - details[i].groups.size() - (i ? details[i - 1].bond_type.value : 0);
    for (const auto &d : details)
        for (auto g : d.groups)
            f += g->get_formula();
    return f;
}

size_t organic::chain::size() const noexcept {
    return details.size();
}

organic::compound::carbon_detail &organic::chain::operator[](size_t index) noexcept {
    return details[index - 1];
}

const organic::compound::carbon_detail &organic::chain::operator[](size_t index) const noexcept {
    return details[index - 1];
}
