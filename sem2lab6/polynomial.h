// Pow

template<int X, int P>
struct Pow {
    static const long long value = X * Pow<X, P - 1>::value;
};

template<int X>
struct Pow<X, 0> {
    static const long long value = 1;
};

// SumOfMonomials
// SumOfMonomials
template<int X, unsigned CurPow, int... Coefs>
struct SumOfMonomials;

template<int X, unsigned CurPow, int CurCoef, int... OtherCoefs>
struct SumOfMonomials<X, CurPow, CurCoef, OtherCoefs...> {
    static const long long value = CurCoef * Pow<X, CurPow>::value +
                                   SumOfMonomials<X, CurPow + 1, OtherCoefs...>::value;
};

template<int X, unsigned CurPow>
struct SumOfMonomials<X, CurPow> {
    static const long long value = 0;
};

template<int X, int... Coefs>
struct Polynomial {
    static const long long value = SumOfMonomials<X, 0, Coefs...>::value;
};

// Out
template<int X, int CurCoef, int... OtherCoefs>
std::ostream &operator<<(std::ostream &out, Polynomial<X, CurCoef, OtherCoefs...>) {
    out << CurCoef << ' ';
    out << Polynomial<X, OtherCoefs...>();
    return out;
}

template<int X>
std::ostream &operator<<(std::ostream &out, Polynomial<X>) {
    return out;
}
