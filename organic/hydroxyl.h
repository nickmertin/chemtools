#ifndef CHEMTOOLS_HYDROXYL_H
#define CHEMTOOLS_HYDROXYL_H


#include "group.h"

namespace organic {
    class hydroxyl final : public group {
    public:
        std::string get_name() override;

        base::formula get_formula() override;

        nomenclature get_nomenclature() override;

        suffix_type get_suffix_type() override;
    };
}


#endif //CHEMTOOLS_HYDROXYL_H
