#include <sstream>
#include "benzene.h"
#include "organic.h"
#include "../utils/string_utils.h"

organic::benzene::benzene() noexcept : details({
                                                       {{}, 1},
                                                       {{}, 2},
                                                       {{}, 1},
                                                       {{}, 2},
                                                       {{}, 1},
                                                       {{}, 2}
                                               }) {};

std::string organic::benzene::get_iupac_name() const noexcept {
    std::stringstream out;
    std::map<std::string, std::vector<int>> prefixes;
    std::map<group::suffix_type, std::vector<int>> suffixes;
    for (const auto &d : details)
        for (int i = 0; i < d.groups.size(); ++i)
            if (d.groups[i]->get_nomenclature() == group::suffix)
                suffixes[d.groups[i]->get_suffix_type()].push_back(i + 1);
    for (int i = 0; i < 6; ++i) {
        const carbon_detail &d = details[i];
        for (auto g : d.groups) {
            if (g->get_nomenclature() == group::prefix)
                prefixes[g->get_name()].push_back(i + 1);
        }
    }
    bool numbering = prefixes.size() + suffixes.size() > 1 && !(prefixes.size() == 1 && prefixes.crbegin()->second.size() == 1 && suffixes.empty() || prefixes.empty() && suffixes.size() == 1 && suffixes.crbegin()->second.size() == 1);
    bool hyphenate = false;
    for (auto &p : prefixes) {
        if (numbering) {
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
        out << get_numeric_prefix(p.second.size(), utils::is_vowel(p.first[0])) << p.first;
    }
    out << (suffixes[group::alcohol].empty() ? "benzene" : "phen");
    for (auto &s : suffixes) {
        if (s.second.empty())
            continue;
        if (numbering) {
            out << '-';
            for (int i = 0; i < s.second.size(); ++i) {
                if (i)
                    out << ',';
                out << s.second[i];
            }
            out << '-';
        }
        std::string name = get_suffix_name(s.first, s.first == suffixes.crbegin()->first);
        out << get_numeric_prefix(s.second.size(), utils::is_vowel(name[0])) << name;
    }
    return out.str();
}

base::formula organic::benzene::get_formula() const noexcept {
    base::formula f;
    f[base::C] = 6;
    f[base::H] = 12;
    for (const auto &d : details)
        for (const auto &g : d.groups) {
            --f[base::H];
            f += g->get_formula();
        }
    return f;
}

size_t organic::benzene::size() const noexcept {
    return 6;
}

organic::compound::carbon_detail &organic::benzene::operator[](size_t index) noexcept {
    return details[(index - 1) % 6];
}

const organic::compound::carbon_detail &organic::benzene::operator[](size_t index) const noexcept {
    return details[(index - 1) % 6];
}
