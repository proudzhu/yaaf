#include "Catch/single_include/catch.hpp"

#include <iostream>
#include "test.h"
#include "fir2.h"
#include "fft.h"

TEST_CASE("fir2 fft") {
    std::vector<std::complex<double>> x{1,2,3,4,0,0,0,0};
    std::vector<std::complex<double>> hx = fft(x);
    std::vector<std::complex<double>> xx = ifft(hx);

    REQUIRE(check_vector_complex(x, xx) == true);
}

TEST_CASE("fir2") {
    std::vector<double> f{0,0.5,1};
    std::vector<double> a{-3,-1,-3};
    std::vector<double> result{-6.12745098030829e-07,-0.000216611676779447,
                          -0.219281497639320,0.000784957787907526,
                          -1.99804687500000,0.000784957787908005,
                          -0.219281497639320,-0.000216611676779372,
                          -6.12745098047783e-07};

    fir2 *ff = new fir2(8, f, a);

    REQUIRE(check_vector(ff->b,result) == true);
}
