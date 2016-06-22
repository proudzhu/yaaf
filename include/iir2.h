#ifndef YAAF_IIR2_H
#define YAAF_IIR2_H

#include <vector>
#include "common.h"

class Iir2
{
public:
    Iir2(double freq, double fs = 44100, int ch = 2, FilterType type = PeakingEQ, double q = sqrt(2) / 2, double gain = 0)
    {
        a.resize(3, 0);
        b.resize(3, 0);
        x.resize(ch, std::vector<double>(3,0));
        y.resize(ch, std::vector<double>(3,0));

        CalcCoeffs(freq, fs, q, gain, type);
    }

    ~Iir2() {}

    int Process(AudioBuffer *inbuf, AudioBuffer *outbuf);

    void Reset(void);

private:
    std::vector<double> a;
    std::vector<double> b;

    // history data
    std::vector<std::vector<double>> x;
    std::vector<std::vector<double>> y;

    void CalcCoeffs(double freq, double fs, double q, double gain, FilterType type);
};

#endif // IIR2_H
