#ifndef CHEMTOOLS_COMPLEX_COMPOUND_H
#define CHEMTOOLS_COMPLEX_COMPOUND_H


#include "../utils/ranged_numeric.h"
#include "group.h"
#include "../utils/var_array.h"
#include "compound.h"

namespace organic {
    class complex_compound : public compound {
    public:
        struct carbon_detail {
            utils::var_array<group *, 4> groups;
            utils::ranged_numeric<int, 0, 3> bond_type;
        };

        virtual carbon_detail &operator[](size_t index) noexcept = 0;

        virtual const carbon_detail &operator[](size_t index) const noexcept = 0;

        virtual size_t size() const noexcept = 0;

        void set_bond_type(size_t index, utils::ranged_numeric<int, 1, 3> value);

        void add_group(size_t index, std::function<group *()> factory);

        void remove_group(size_t index, size_t group);
    };
}


#endif //CHEMTOOLS_COMPLEX_COMPOUND_H
