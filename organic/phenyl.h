#ifndef CHEMTOOLS_PHENYL_H
#define CHEMTOOLS_PHENYL_H


#include "group.h"

namespace organic {
    class phenyl final : public group {
    public:
        std::string get_name() override;

        base::formula get_formula() override;

        nomenclature get_nomenclature() override;
    };
}


#endif //CHEMTOOLS_PHENYL_H
