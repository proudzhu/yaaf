#include "Catch/single_include/catch.hpp"

#include "test.h"
#include "fft.h"

TEST_CASE("fir2 fft") {
    std::vector<std::complex<double>> x{1,2,3,4,0,0,0,0};
    std::vector<std::complex<double>> hx(x.size(), 0);
    std::vector<std::complex<double>> xx(x.size(), 0);

    auto fft1 = std::make_unique<Fft>(x.size(), FFTW_FORWARD);
    auto ifft1 = std::make_unique<Fft>(x.size(), FFTW_BACKWARD);

    fft1->Execute(x, hx);
    ifft1->Execute(hx, xx);

    REQUIRE(check_vector_complex(x, xx) == true);
}
