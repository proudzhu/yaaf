#include <cassert>
#include "vibrato.h"

void Vibrato::UpdateDelayLine(double xh, int ch)
{
    auto &v = delayline_[ch];
    int i;

    // delayLine = [xh, delayLine(1:M-1)]
    for (i = v.size() - 1; i > 0; i--)
        v[i] = v[i - 1];
    v[0] = xh;
}

int Vibrato::Process(AudioBuffer *inbuf, AudioBuffer *outbuf)
{
    assert(inbuf->ch == outbuf->ch);
    assert(inbuf->fs == outbuf->fs);
    assert(inbuf->samples == outbuf->samples);

    for (int i = 0; i < inbuf->samples / inbuf->ch; i++) {
        for (int j = 0; j < inbuf->ch; j++) {
            double xh = inbuf->buf[i * inbuf->ch + j];
            UpdateDelayLine(xh, j);

            double mod = sin(modfreq_m_ * 2 * M_PI * i);
            double zeiger = 1 + delay_m_ + width_m_ * mod;
            double frac = zeiger - floor(zeiger);
            double tmp = delayline_[j][i+1] * frac + delayline_[j][i] * (1 - frac);

            outbuf->buf[i * outbuf->ch + j] = (int16_t)std::min(32767, std::max(-32768, (int32_t)tmp));
        }
    }

    return inbuf->samples;
}

void Vibrato::Reset(void)
{
    return;
}
