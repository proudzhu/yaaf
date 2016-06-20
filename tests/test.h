#ifndef TEST_H
#define TEST_H

#include <vector>
#include <cassert>

inline bool check_float(double a, double b)
{
    return fabs(a - b) / a < 1e-03;
}

inline bool check_vector(std::vector<double> a, std::vector<double> b)
{
    assert(a.size() == b.size());

    for (int i = 0; i < a.size(); i++) {
        if (check_float(a[i], b[i]) == false)
            return false;
    }

    return true;
}

#endif // TEST_H
