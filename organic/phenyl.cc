#include "phenyl.h"

const static base::formula phenyl_formula = ([] () {
    base::formula f;
    f[base::C] = 6;
    f[base::H] = 11;
    return f;
})();

std::string organic::phenyl::get_name() {
    return "phenyl";
}

base::formula organic::phenyl::get_formula() {
    return phenyl_formula;
}

organic::group::nomenclature organic::phenyl::get_nomenclature() {
    return prefix;
}
