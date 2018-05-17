#ifndef CHEMTOOLS_BRANCH_H
#define CHEMTOOLS_BRANCH_H


#include "group.h"
#include "../utils/var_array.h"

namespace organic {
    class branch final : public group {
    private:
        size_t length;

    public:
        branch(size_t length);

        std::string get_name() override;

        base::formula get_formula() override;

        nomenclature get_nomenclature() override;
    };
}


#endif //CHEMTOOLS_BRANCH_H
