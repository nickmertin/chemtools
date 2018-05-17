#include "halogen.h"
#include "../utils/map_parser.h"

const static std::map<std::string, organic::halogen::type> parser_map {
        {"fluorine", organic::halogen::fluorine},
        {"chlorine", organic::halogen::chlorine},
        {"bromine", organic::halogen::bromine},
        {"iodine", organic::halogen::iodine}
};

const static std::string halogen_group_names[4] = {
        "fluoro",
        "chloro",
        "bromo",
        "iodo"
};

const static base::element halogen_elements[4] = {
        base::F,
        base::Cl,
        base::Br,
        base::I
};

std::function<organic::halogen::type(const std::string &)> organic::halogen::get_parser() {
    return utils::map_parser<type>(parser_map);
}

organic::halogen::halogen(organic::halogen::type element) : element(element) {}

std::string organic::halogen::get_name() {
    return halogen_group_names[element];
}

base::formula organic::halogen::get_formula() {
    base::formula f;
    f[halogen_elements[element]] = 1;
    return f;
}

organic::group::nomenclature organic::halogen::get_nomenclature() {
    return prefix;
}
