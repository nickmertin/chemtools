#ifndef CHEMTOOLS_HALOGEN_H
#define CHEMTOOLS_HALOGEN_H


#include <functional>
#include "group.h"

namespace organic {
    class halogen final : public group {
    public:
        enum type {
            fluorine,
            chlorine,
            bromine,
            iodine
        };

        static std::function<type(const std::string &)> get_parser();

        type element;

        halogen(type element);

        std::string get_name() override;

        base::formula get_formula() override;

        nomenclature get_nomenclature() override;
    };
}


#endif //CHEMTOOLS_HALOGEN_H
