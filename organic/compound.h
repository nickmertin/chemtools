#ifndef CHEMTOOLS_COMPOUND_H
#define CHEMTOOLS_COMPOUND_H


#include <cstdlib>
#include <vector>
#include "group.h"
#include "../utils/ranged_numeric.h"
#include "../base/formula.h"
#include "../utils/var_array.h"

namespace organic {
    class compound final {
    private:
        struct carbon_detail {
            utils::var_array<group *, 3> groups;
            utils::ranged_numeric<int, 0, 3> bond_type;
        };

        std::vector<carbon_detail> details;

    public:
        compound() noexcept;
        compound(size_t length);
        std::string get_iupac_name() const noexcept;
        base::formula get_formula() const noexcept;
    };
}


#endif //CHEMTOOLS_COMPOUND_H
