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
    public:
        struct carbon_detail {
            utils::var_array<group *, 3> groups;
            utils::ranged_numeric<int, 0, 3> bond_type;
        };

        utils::var_array<carbon_detail, 10> details;

        compound() noexcept;

        explicit compound(size_t length);

        std::string get_iupac_name() const noexcept;

        base::formula get_formula() const noexcept;

        void set_bond_type(size_t index, utils::ranged_numeric<int, 1, 3> value);

        void add_group(size_t index, std::function<group *()> factory);

        void remove_group(size_t index, size_t group);
    };
}


#endif //CHEMTOOLS_COMPOUND_H
