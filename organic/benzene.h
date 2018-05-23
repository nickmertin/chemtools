#ifndef CHEMTOOLS_BENZENE_H
#define CHEMTOOLS_BENZENE_H


#include "compound.h"

namespace organic {
    class benzene final : public compound {
        carbon_detail details[6];

    public:
        benzene() noexcept;

        std::string get_iupac_name() const noexcept override;

        base::formula get_formula() const noexcept override;

        size_t size() const noexcept override;

        carbon_detail &operator[](size_t index) noexcept override;

        const carbon_detail &operator[](size_t index) const noexcept override;
    };
}


#endif //CHEMTOOLS_BENZENE_H
