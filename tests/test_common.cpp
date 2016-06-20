#include "Catch/single_include/catch.hpp"

#include "common.h"
#include "test.h"

TEST_CASE("fix") {
    REQUIRE(fix(-2.1) == -2);
    REQUIRE(fix(2.1) == 2);
    REQUIRE(fix(0) == 0);
}

TEST_CASE("isNonDecrease") {
    REQUIRE(isNonDecrease(std::vector<double>{0,0.2,0.2,0.8,1}) == true);
    REQUIRE(isNonDecrease(std::vector<double>{0,0.2,0.1}) == false);
}

TEST_CASE("nextpow2") {
    REQUIRE(nextpow2(-6) == 3);
    REQUIRE(nextpow2(-3) == 2);
    REQUIRE(nextpow2(-2) == 1);
    REQUIRE(nextpow2(2) == 1);
    REQUIRE(nextpow2(3) == 2);
    REQUIRE(nextpow2(6) == 3);
}

TEST_CASE("interp1 linear") {
    std::vector<double> x{0,2,4,6,8,10,12};
    std::vector<double> v{1,2,4,9,15,30,32};
    REQUIRE(check_float(interp1(x, v, 5.5), 7.7500));
}
