#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>
#include "formula.h"
#include "table.h"

base::formula::formula() {
    memset(counts, 0, sizeof(counts));
}

uint16_t &base::formula::operator[](base::element e) {
    return counts[e];
}

uint16_t base::formula::operator[](base::element e) const {
    return counts[e];
}

std::string base::formula::str() const {
    std::map<std::string, int> parts;
    for (element e = H; e < ELEMENT_COUNT; ++e)
        if (counts[e] && e != C && (e != H || !counts[C]))
            parts[table[e].symbol] = counts[e];
    std::stringstream out;
    if (counts[C]) {
        out << "C" << counts[C];
        if (counts[H])
            out << "H" << counts[H];
    }
    else if (counts[H])
        parts["H"] = counts[H];
    for (auto &p : parts) {
        out << p.first << p.second;
    }
    return out.str();
}

base::formula base::formula::operator+(const base::formula &other) const {
    formula r;
    std::transform(counts, counts + ELEMENT_COUNT, other.counts, r.counts, [] (uint16_t a, uint16_t b) { return a + b; });
    return r;
}

base::formula &base::formula::operator+=(const base::formula &other) {
    return *this = *this + other;
}
