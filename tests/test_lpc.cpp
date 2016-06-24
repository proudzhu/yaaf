#include "Catch/single_include/catch.hpp"

#include <vector>
#include "lpc.h"
#include "test.h"

TEST_CASE("levinson") {
    std::vector<double> acf{3.75,2.5,1.375,0.5,
                            0,0,0,0,0,0,0,0,0,
                            0.5,1.375,2.5};
    int n = 8;
    std::vector<double> ret{1,-0.749942474644213,0.0638849763258328,0.0796747950227877,
                            0.0951416094002375,-0.125382842399785,0.0277236686060605,
                            0.0187894985834128,-0.00597727910042100};

    REQUIRE(check_vector(levinson(acf, n), ret) == true);
}

TEST_CASE("lpc") {
    std::vector<double> x{1,2,3,4,0,0,0,0};
    int n = 8;
    std::vector<double> ret{1,-0.749942474644213,0.0638849763258328,0.0796747950227877,
                            0.0951416094002375,-0.125382842399785,0.0277236686060605,
                            0.0187894985834128,-0.00597727910042100};

    REQUIRE(check_vector(lpc(x, n), ret) == true);
}
