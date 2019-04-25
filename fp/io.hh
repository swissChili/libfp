//
// Created by ch on 4/24/19.
//

#ifndef LIBFP_IO_HH
#define LIBFP_IO_HH

#include <iostream>


namespace fp {
    template <typename T>
    void println(T i) {
        std::cout << i << std::endl;
    }
}


#endif //LIBFP_IO_HH
