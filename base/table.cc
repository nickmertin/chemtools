#include "table.h"
#include <cmath>

base::table_entry base::table[base::ELEMENT_COUNT] = {
#include "table.inc"
};
