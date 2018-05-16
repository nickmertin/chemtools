#ifndef CHEMTOOLS_GROUP_H
#define CHEMTOOLS_GROUP_H


#include "../base/formula.h"

namespace organic {
    class group {
    public:
        enum nomenclature {
            prefix,
            suffix
        };

        enum suffix_type {
            alkene,
            alkyne,
            alcohol,
            none = -1
        };

        virtual std::string get_name() = 0;
        virtual base::formula get_formula() = 0;
        virtual nomenclature get_nomenclature() = 0;
        virtual suffix_type get_suffix_type();
    };
}


#endif //CHEMTOOLS_GROUP_H
