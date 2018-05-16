#ifndef CHEMTOOLS_RANGED_NUMERIC_H
#define CHEMTOOLS_RANGED_NUMERIC_H


#include <type_traits>
#include "exception.h"

namespace utils {
    template<class N, N min, N max>
    struct ranged_numeric {
    public:
        N value;

        ranged_numeric(N value) : value(value) {
            if (value < min || value > max)
                throw(EX_BOUNDS);
        }

        ranged_numeric(const ranged_numeric<N, min, max> &other) : ranged_numeric(other.value) {}

        ranged_numeric &operator=(const ranged_numeric<N, min, max> &other) {
            new (this) ranged_numeric<N, min, max>(other.value);
        }

        operator N() const {
            return value;
        }
    };
}


#endif //CHEMTOOLS_RANGED_NUMERIC_H
