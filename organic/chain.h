#ifndef CHEMTOOLS_CHAIN_H
#define CHEMTOOLS_CHAIN_H


#include <strings.h>
#include "complex_compound.h"

namespace organic {
    class chain final : public complex_compound {
    private:
        utils::var_array<carbon_detail, 10> details;

    public:
        chain() noexcept;

        explicit chain(size_t length) noexcept;

        std::string get_iupac_name() const noexcept override;

        base::formula get_formula() const noexcept override;

        size_t size() const noexcept override;

        carbon_detail &operator[](size_t index) noexcept override;

        const carbon_detail &operator[](size_t index) const noexcept override;
    };
}


#endif //CHEMTOOLS_CHAIN_H
