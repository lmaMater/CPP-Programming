#include <iostream>
#include "polynomial.h"


int main() {
    // Pow
    static_assert(Pow<1, 100>::value == 1);
    static_assert(Pow<2, 0>::value == 1);
    static_assert(Pow<2, 10>::value == 1024);

    // Polynomial
    static_assert(Polynomial<0, 100, 3, 2, 1>::value == 100);
    const int x = 2;
    static_assert(Polynomial<x, 1, 1>::value == 3);
    static_assert(Polynomial<x, 0, 1, 2>::value == 10);
    static_assert(Polynomial<x, 2, 2, 2, 2, 2, 2>::value == 126);

    // Out
    std::cout<< Polynomial<10, 3, 2, 1>() << '\n';
    std::cout<< Polynomial<10, 3, 2, 1>::value << '\n';
}