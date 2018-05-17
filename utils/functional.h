#ifndef CHEMTOOLS_FUNCTIONAL_H
#define CHEMTOOLS_FUNCTIONAL_H


#include <functional>

namespace utils {
    template<class T, class U, class... args>
    std::function<T(args ...)> cast_result(std::function<U(args ...)> function) {
        return [function] (const args &...a) { return T(function(a...)); };
    };
}

#endif //CHEMTOOLS_FUNCTIONAL_H
