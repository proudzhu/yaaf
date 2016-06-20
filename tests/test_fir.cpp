#include "Catch/single_include/catch.hpp"

#include "firCommon.h"
#include "common.h"

bool check_array(int16_t *x, int16_t *y, int size)
{
    for (int i = 0; i < size; i++) {
        if (x[i] != y[i])
            return false;
    }

    return true;
}

TEST_CASE("firCommon process") {
    int16_t bufin[10] = {1000,2000,3000,0,0,0,0,0,0,0};
    int16_t bufout[10] = {0};
    int16_t expectout[10] = {1000,2500,4250,2125,1000,375,0,0,0,0};

    AudioBuffer *inbuf = new AudioBuffer();
    inbuf->ch = 1;
    inbuf->fs = 44100;
    inbuf->samples = sizeof(bufin) / sizeof(bufin[0]);
    inbuf->buf = bufin;

    AudioBuffer *outbuf = new AudioBuffer();
    outbuf->ch = 1;
    outbuf->fs = 44100;
    outbuf->samples = sizeof(bufout) / sizeof(bufout[0]);
    outbuf->buf = bufout;

    std::vector<double> b{1,0.5,0.25,0.125,0,0,0,0};
    firCommon *fir = new firCommon();
    fir->setCoeffs(b);

    fir->process(inbuf, outbuf);

    REQUIRE(check_array(bufout, expectout, 10));
}
