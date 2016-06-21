#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <vector>
#include <complex>
#include <limits>
#include <cassert>

#define EPS 0.000001;

inline bool check_float(double a, double b)
{
    return fabs(a - b) < EPS;
}

inline bool check_complex(std::complex<double> a, std::complex<double> b)
{
    return check_float(a.real(), b.real()) && check_float(a.imag(), b.imag());
}

inline bool check_vector(std::vector<double> a, std::vector<double> b)
{
    if (a.size() != b.size())
        return false;

    for (int i = 0; i < a.size(); i++) {
        if (check_float(a[i], b[i]) == false)
            return false;
    }

    return true;
}

inline bool check_vector_complex(std::vector<std::complex<double>> a, std::vector<std::complex<double>> b)
{
    if (a.size() != b.size())
        return false;

    for (int i = 0; i < a.size(); i++) {
        if (check_complex(a[i], b[i]) == false)
            return false;
    }

    return true;
}

template <typename T>
inline void print_vector(std::vector<T> v)
{
    for (auto x : v)
        std::cout << x << " ";
    std::cout << "\n";
}

#endif // TEST_H
