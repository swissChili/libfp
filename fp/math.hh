//
// Created by ch on 4/24/19.
//

#ifndef LIBFP_MATH_HH
#define LIBFP_MATH_HH

#include <functional>

namespace fp {
    std::function<int(int)> sumc(int a) {
        return [a](int b) {
            return a + b;
        };
    }

    int sum(int a, int b) {
        return a + b;
    }
}


#endif //LIBFP_MATH_HH
