#include "hydroxyl.h"

const static base::formula hydroxyl_formula = ([] () {
    base::formula f;
    f[base::O] = 1;
    f[base::H] = 1;
    return f;
})();

std::string organic::hydroxyl::get_name() {
    return "ol";
}

base::formula organic::hydroxyl::get_formula() {
    return hydroxyl_formula;
}

organic::group::nomenclature organic::hydroxyl::get_nomenclature() {
    return suffix;
}

organic::group::suffix_type organic::hydroxyl::get_suffix_type() {
    return alcohol;
}
