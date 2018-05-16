#ifndef CHEMTOOLS_FORMULA_H
#define CHEMTOOLS_FORMULA_H


#include <map>
#include "base.h"

namespace base {
    class formula final {
    private:
        uint16_t counts[ELEMENT_COUNT];

    public:
        formula();

        uint16_t &operator[](element e);
        uint16_t operator[](element e) const;

        std::string str() const;

        formula operator+(const formula &other) const;
        formula &operator+=(const formula &other);
    };
}


#endif //CHEMTOOLS_FORMULA_H
