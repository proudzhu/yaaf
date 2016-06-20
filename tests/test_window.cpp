#include "Catch/single_include/catch.hpp"

#include <vector>
#include <cassert>
#include "window.h"

bool check_float(double a, double b)
{
    return fabs(a - b) / a < 1e-03;
}

bool check_vector(std::vector<double> a, std::vector<double> b)
{
    assert(a.size() == b.size());

    for (int i = 0; i < a.size(); i++) {
        if (check_float(a[i], b[i]) == false)
            return false;
    }

    return true;
}

TEST_CASE("hamming window") {
    REQUIRE(check_vector(hamming(1), std::vector<double>{1.0}));
    REQUIRE(check_vector(hamming(2), std::vector<double>{0.08, 0.08}));
    REQUIRE(check_vector(hamming(3), std::vector<double>{0.08, 1.0, 0.08}));
    REQUIRE(check_vector(hamming(4), std::vector<double>{0.08, 0.77, 0.77, 0.08}));
    REQUIRE(check_vector(hamming(10), std::vector<double>{0.0800, 0.1876, 0.4601, 0.7700, 0.9723,
                                                  0.9723, 0.7700, 0.4601, 0.1876, 0.0800}));
}
