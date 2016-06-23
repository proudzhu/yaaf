#include "Catch/single_include/catch.hpp"

#include "zero_crossing.h"
#include "test.h"

TEST_CASE("zero crossing") {
    std::vector<double> x{1,-1,1,1,-2,1,0,0,1,0,-1};
    double rate = zero_crossing(x);

    REQUIRE(check_float(rate, 0.4) == true);
}
