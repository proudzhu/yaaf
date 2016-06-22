#ifndef VIBRATO_H
#define VIBRATO_H

#include <vector>
#include "common.h"

class Vibrato
{
public:
    Vibrato(double fs, double freq, double w, int ch = 1)
        : sampleRate(fs), modFreq(freq), width(w), delay(w),
          widthM(round(width * fs)), delayM(round(delay * fs)),
          modFM(modFreq / sampleRate)
    {
        int l = 2 + delayM + widthM * 2;
        delayLine.resize(ch, std::vector<double>(l, 0));
    }

    int Process(AudioBuffer *inbuf, AudioBuffer *outbuf);

    void Reset(void);

private:
    double sampleRate;
    double modFreq;
    double width;
    double delay;

    double widthM;
    double delayM;
    double modFM;

    std::vector<std::vector<double>> delayLine;

    void UpdateDelayLine(double xh, int ch);
};

#endif // VIBRATO_H
