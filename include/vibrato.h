#ifndef VIBRATO_H
#define VIBRATO_H

#include <vector>
#include "common.h"

class Vibrato
{
public:
    Vibrato(double fs, double freq, double w, int ch = 1)
        : samplerate_(fs), modfreq_(freq), width_(w), delay_(w),
          width_m_(round(width_ * fs)), delay_m_(round(delay_ * fs)),
          modfreq_m_(modfreq_ / samplerate_)
    {
        int l = 2 + delay_m_ + width_m_ * 2;
        delayline_.resize(ch, std::vector<double>(l, 0));
    }

    int Process(AudioBuffer *inbuf, AudioBuffer *outbuf);

    void Reset(void);

private:
    double samplerate_;
    double modfreq_;
    double width_;
    double delay_;

    double width_m_;
    double delay_m_;
    double modfreq_m_;

    std::vector<std::vector<double>> delayline_;

    void UpdateDelayLine(double xh, int ch);
};

#endif // VIBRATO_H
