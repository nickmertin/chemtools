#include "base.h"

base::element &base::operator++(base::element &e) {
    auto _e = static_cast<uint8_t>(e);
    ++_e;
    return e = static_cast<element>(_e);
}

base::element &base::operator--(base::element &e) {
    auto _e = static_cast<uint8_t>(e);
    --_e;
    return e = static_cast<element>(_e);
}
