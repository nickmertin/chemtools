#ifndef CHEMTOOLS_TABLE_H
#define CHEMTOOLS_TABLE_H


#include <string>
#include "base.h"

namespace base {
    struct table_entry {
        std::string symbol;
        std::string name;
        double atomic_mass;
        double electronegativity;
        double radius_atom;
        double radius_ion;
        double radius_vdw;
        double ionization_energy;
        double electron_affinity;
        double melting_point;
        double boiling_point;
        double density;
        state standard_state;
        bonding_type bonding;
        group_block block;
    };

    extern table_entry table[ELEMENT_COUNT];
}

#endif //CHEMTOOLS_TABLE_H
