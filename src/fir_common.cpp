#include <cassert>
#include "fir_common.h"

void FirCommon::UpdateDelayLine(double xh, int ch)
{
    auto &v = delayLine[ch];
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
    assert(delayLine[0].size() == b.size());

    for (int i = 0; i < inbuf->samples / inbuf->ch; i++) {
        for (int j = 0; j < inbuf->ch; j++) {
            double xh = inbuf->buf[i * inbuf->ch + j];
            UpdateDelayLine(xh, j);

            double tmp = 0.0;
            for (int k = 0; k < b.size(); k++)
                tmp += b[k] * delayLine[j][k];

            outbuf->buf[i * inbuf->ch + j] = (int16_t)std::min(32767, std::max(-32768, (int32_t)tmp));
        }
    }

    return inbuf->samples;
}

void FirCommon::Reset(void)
{
    return;
}

void FirCommon::SetCoeffs(std::vector<double> coeffs)
{
    b = coeffs;
    delayLine.resize(1, std::vector<double>(b.size(), 0));
}
