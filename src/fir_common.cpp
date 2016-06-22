#include <cassert>
#include "fir_common.h"

void FirCommon::UpdateDelayLine(double xh, int ch)
{
    auto &v = delayline_[ch];
    int i;

    // delayLine = [xh, delayLine(1:M-1)]
    for (i = v.size() - 1; i > 0; i--)
        v[i] = v[i - 1];
    v[0] = xh;
}

int FirCommon::Process(AudioBuffer *inbuf, AudioBuffer *outbuf)
{
    assert(inbuf->ch == outbuf->ch);
    assert(inbuf->fs == outbuf->fs);
    assert(inbuf->samples == outbuf->samples);
    assert(delayline_[0].size() == b_.size());

    for (int i = 0; i < inbuf->samples / inbuf->ch; i++) {
        for (int j = 0; j < inbuf->ch; j++) {
            double xh = inbuf->buf[i * inbuf->ch + j];
            UpdateDelayLine(xh, j);

            double tmp = 0.0;
            for (int k = 0; k < b_.size(); k++)
                tmp += b_[k] * delayline_[j][k];

            outbuf->buf[i * inbuf->ch + j] = (int16_t)std::min(32767, std::max(-32768, (int32_t)tmp));
        }
    }

    return inbuf->samples;
}

void FirCommon::Reset(void)
{
    return;
}

std::vector<double> FirCommon::GetCoeffs(void) const
{
    return b_;
}

void FirCommon::SetCoeffs(const std::vector<double> &coeffs)
{
    b_ = coeffs;
    delayline_.resize(1, std::vector<double>(b_.size(), 0));
}
