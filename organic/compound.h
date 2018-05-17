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
        struct carbon_detail {
            utils::var_array<group *, 4> groups;
            utils::ranged_numeric<int, 0, 3> bond_type;
        };

        virtual std::string get_iupac_name() const noexcept = 0;

        virtual base::formula get_formula() const noexcept = 0;

        virtual size_t size() const noexcept = 0;

        virtual carbon_detail &operator[](size_t index) noexcept = 0;

        virtual const carbon_detail &operator[](size_t index) const noexcept = 0;

        void set_bond_type(size_t index, utils::ranged_numeric<int, 1, 3> value);

        void add_group(size_t index, std::function<group *()> factory);

        void remove_group(size_t index, size_t group);
    };
}


#endif //CHEMTOOLS_COMPOUND_H
