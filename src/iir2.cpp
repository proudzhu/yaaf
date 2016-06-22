#include <vector>
#include <algorithm>
#include <cassert>
#include "iir2.h"

int Iir2::Process(AudioBuffer *inbuf, AudioBuffer *outbuf)
{
    assert(inbuf->ch == outbuf->ch);
    assert(inbuf->fs == outbuf->fs);
    assert(inbuf->samples == outbuf->samples);

    for (int i = 0; i < inbuf->samples / inbuf->ch; i++) {
        for (int j = 0; j < inbuf->ch; j++) {
            auto &xj = x_[j];
            auto &yj = y_[j];

            xj[2] = xj[1];
            xj[1] = xj[0];
            xj[0] = inbuf->buf[i * inbuf->ch + j];
            yj[2] = yj[1];
            yj[1] = yj[0];
            yj[0] = b_[0] * xj[0] + b_[1] * xj[1] + b_[2] * xj[2] - a_[1] * yj[1] - a_[2] * yj[2];

            outbuf->buf[i * inbuf->ch + j] = (int16_t)std::min(32767, std::max(-32768, (int32_t)yj[0]));
        }
    }

    return inbuf->samples;
}

void Iir2::CalcCoeffs(double freq, double fs, double q, double gain, FilterType type)
{
    double A = pow(10, gain / 40);
    double w0 = 2 * M_PI * freq / fs;
    double alpha = sin(w0) / (2 * q);

    switch (type) {
    case kHPF:
        b_[0] = (1 + cos(w0)) / 2;
        b_[1] = -(1 + cos(w0));
        b_[2] = (1 + cos(w0)) / 2;
        a_[0] = 1 + alpha;
        a_[1] = -2 * cos(w0);
        a_[2] = 1 - alpha;
        break;
    case kLPF:
        b_[0] = (1 - cos(w0)) / 2;
        b_[1] = 1 - cos(w0);
        b_[2] = (1 - cos(w0)) / 2;
        a_[0] = 1 + alpha;
        a_[1] = -2 * cos(w0);
        a_[2] = 1 - alpha;
        break;
    case kLowShelf:
        b_[0] = A * ((A + 1) - (A - 1) * cos(w0) + 2 * sqrt(A) * alpha);
        b_[1] = 2 * A * ((A - 1) - (A + 1) * cos(w0));
        b_[2] = A * ((A + 1) - (A - 1) * cos(w0) - 2 * sqrt(A) * alpha);
        a_[0] = (A + 1) + (A - 1) * cos(w0) + 2 * sqrt(A) * alpha;
        a_[1] = -2 * ((A - 1) + (A + 1) * cos(w0));
        a_[2] = (A + 1) + (A - 1) * cos(w0) - 2 * sqrt(A) * alpha;
        break;
    case kHighShelf:
        b_[0] = A * ((A + 1) + (A - 1) * cos(w0) + 2 * sqrt(A) * alpha);
        b_[1] = -2 * A * ((A - 1) + (A + 1) * cos(w0));
        b_[2] = A * ((A + 1) + (A - 1) * cos(w0) - 2 * sqrt(A) * alpha);
        a_[0] = (A + 1) - (A - 1) * cos(w0) + 2 * sqrt(A) * alpha;
        a_[1] = 2 * ((A - 1) - (A + 1) * cos(w0));
        a_[2] = (A + 1) - (A - 1) * cos(w0) - 2 * sqrt(A) * alpha;
        break;
    case kPeakingEQ:
        b_[0] = 1 + alpha * A;
        b_[1] = -2 * cos(w0);
        b_[2] = 1 - alpha * A;
        a_[0] = 1 + alpha / A;
        a_[1] = -2 * cos(w0);
        a_[2] = 1 - alpha / A;
        break;
    default:
        assert(0);
        break;
    }

    b_[0] = b_[0] / a_[0];
    b_[1] = b_[1] / a_[0];
    b_[2] = b_[2] / a_[0];
    a_[1] = a_[1] / a_[0];
    a_[2] = a_[2] / a_[0];
    a_[0] = 1.0;
}

void Iir2::Reset(void)
{
    std::for_each(x_.begin(), x_.end(), [](auto &h) {
        std::fill(h.begin(), h.end(), 0);
    });
    std::for_each(y_.begin(), y_.end(), [](auto &h) {
        std::fill(h.begin(), h.end(), 0);
    });
}
