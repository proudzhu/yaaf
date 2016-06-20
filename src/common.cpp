#include <cmath>
#include <cassert>
#include "common.h"

bool isNonDecrease(std::vector<double> v)
{
    for (auto i = 0; i < v.size() - 1; i++) {
        double diff = v[i + 1] - v[i];
        if (diff < 0)
            return false;
    }

    return true;
}

double interp1(std::vector<double> x, std::vector<double> v, double xq)
{
    assert(x.size() == v.size());
    int i = 0;

    for (; i < x.size(); i++) {
        if (x[i] > xq)
            break;
    }

    return v[i-1] + (v[i] - v[i-1]) / (x[i] - x[i-1]) * (xq - x[i-1]);
}
