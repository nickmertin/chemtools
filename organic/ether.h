#ifndef CHEMTOOLS_ETHER_H
#define CHEMTOOLS_ETHER_H


#include "compound.h"

namespace organic {
    class ether final : public compound {
    private:
        uint16_t left_length;
        uint16_t left_position;
        uint16_t right_length;
        uint16_t right_position;

    public:
        ether(uint16_t left_length, uint16_t left_position, uint16_t right_length, uint16_t right_position);

        std::string get_iupac_name() const noexcept override;

        base::formula get_formula() const noexcept override;
    };
}


#endif //CHEMTOOLS_ETHER_H
