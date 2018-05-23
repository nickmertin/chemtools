#ifndef CHEMTOOLS_COMPOUND_H
#define CHEMTOOLS_COMPOUND_H


#include <cstdlib>
#include <vector>
#include <functional>
#include "group.h"
#include "../utils/ranged_numeric.h"
#include "../base/formula.h"
#include "../utils/var_array.h"

namespace organic {
    class compound {
    public:
        virtual std::string get_iupac_name() const noexcept = 0;

        virtual base::formula get_formula() const noexcept = 0;
    };
}


#endif //CHEMTOOLS_COMPOUND_H
