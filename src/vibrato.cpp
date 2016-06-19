#include <cassert>
#include "vibrato.h"

void vibrato::updateDelayLine(double xh, int ch)
{
    auto &v = delayLine[ch];
    int i;

    // delayLine = [xh, delayLine(1:M-1)]
    for (i = v.size() - 1; i > 0; i--)
        v[i] = v[i - 1];
    v[0] = xh;
}

int vibrato::process(AudioBuffer *inbuf, AudioBuffer *outbuf)
{
    assert(inbuf->ch == outbuf->ch);
    assert(inbuf->fs == outbuf->fs);
    assert(inbuf->samples == outbuf->samples);

    for (int i = 0; i < inbuf->samples / inbuf->ch; i++) {
        for (int j = 0; j < inbuf->ch; j++) {
            double xh = inbuf->buf[i * inbuf->ch + j];
            updateDelayLine(xh, j);

            double mod = sin(modFM * 2 * M_PI * i);
            double zeiger = 1 + delayM + widthM * mod;
            double frac = zeiger - floor(zeiger);
            double tmp = delayLine[j][i+1] * frac + delayLine[j][i] * (1 - frac);

            outbuf->buf[i * outbuf->ch + j] = (int16_t)std::min(32767, std::max(-32768, (int32_t)tmp));
        }
    }
}

void vibrato::reset(void)
{
    return;
}
