#ifndef YAAF_IIR2_H
#define YAAF_IIR2_H

#include <vector>
#include "common.h"

class IIR2
{
public:
    IIR2(double freq, double fs = 44100, int ch = 2, FilterType type = PeakingEQ, double q = sqrt(2) / 2, double gain = 0)
    {
        a.resize(3, 0);
        b.resize(3, 0);
        x.resize(ch, std::vector<double>(3,0));
        y.resize(ch, std::vector<double>(3,0));

        calcCoeffs(freq, fs, q, gain, type);
    }

    ~IIR2() {}

    int process(AudioBuffer *inbuf, AudioBuffer *outbuf);

    void reset(void);

private:
    std::vector<double> a;
    std::vector<double> b;

    // history data
    std::vector<std::vector<double>> x;
    std::vector<std::vector<double>> y;

    void calcCoeffs(double freq, double fs, double q, double gain, FilterType type);
};

#endif // IIR2_H
