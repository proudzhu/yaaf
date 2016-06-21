#include "Catch/single_include/catch.hpp"

#include <vector>
#include "window.h"
#include "test.h"

TEST_CASE("hamming window") {
    REQUIRE(check_vector(hamming(1), std::vector<double>{1.0}));
    REQUIRE(check_vector(hamming(2), std::vector<double>{0.08, 0.08}));
    REQUIRE(check_vector(hamming(3), std::vector<double>{0.08, 1.0, 0.08}));
    REQUIRE(check_vector(hamming(4), std::vector<double>{0.08, 0.77, 0.77, 0.08}));
    REQUIRE(check_vector(hamming(10), std::vector<double>{0.0800000000000000,
                                                          0.187619556165270,
                                                          0.460121838273212,
                                                          0.770000000000000,
                                                          0.972258605561518,
                                                          0.972258605561518,
                                                          0.770000000000000,
                                                          0.460121838273212,
                                                          0.187619556165270,
                                                          0.0800000000000000}));
}
