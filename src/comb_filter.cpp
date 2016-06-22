#include <algorithm>
#include <cassert>
#include "comb_filter.h"

void CombFilter::UpdateDelayLine(double xh, int ch)
{
    auto &v = delayline_[ch];
    int i;

    // delayLine = [xh, delayLine(1:M-1)]
    for (i = v.size() - 1; i > 0; i--)
        v[i] = v[i - 1];
    v[0] = xh;
}

int CombFilter::Process(AudioBuffer *inbuf, AudioBuffer *outbuf)
{
    assert(inbuf->ch == outbuf->ch);
    assert(inbuf->fs == outbuf->fs);
    assert(inbuf->samples == outbuf->samples);

    for (int i = 0; i < inbuf->samples / inbuf->ch; i++) {
        for (int j = 0; j < inbuf->ch; j++) {
            double xh = inbuf->buf[i * inbuf->ch + j] + feedback_ * delayline_[j][delay_ - 1];
            UpdateDelayLine(xh, j);

            double tmp = feedforward_ * delayline_[j][delay_ - 1] + blend_ * xh;
            outbuf->buf[i * outbuf->ch + j] = (int16_t)std::min(32767, std::max(-32768, (int32_t)tmp));
        }
    }
}

void CombFilter::Reset(void)
{
    std::for_each(delayline_.begin(), delayline_.end(), [](auto &h) {
        std::fill(h.begin(), h.end(), 0);
    });
}
