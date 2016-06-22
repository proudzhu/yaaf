#ifndef YAAF_IIR2_H
#define YAAF_IIR2_H

#include <vector>
#include "common.h"

class Iir2
{
public:
    typedef enum
    {
        kNone,
        kHPF,
        kLPF,
        kLowShelf,
        kHighShelf,
        kPeakingEQ,
        kFilterTypeNum
    } FilterType;

    Iir2(double freq, double fs = 44100, int ch = 2, FilterType type = kPeakingEQ, double q = sqrt(2) / 2, double gain = 0)
    {
        a_.resize(3, 0);
        b_.resize(3, 0);
        x_.resize(ch, std::vector<double>(3,0));
        y_.resize(ch, std::vector<double>(3,0));

        CalcCoeffs(freq, fs, q, gain, type);
    }

    ~Iir2() {}

    int Process(AudioBuffer *inbuf, AudioBuffer *outbuf);

    void Reset(void);

private:
    std::vector<double> a_;
    std::vector<double> b_;

    // history data
    std::vector<std::vector<double>> x_;
    std::vector<std::vector<double>> y_;

    void CalcCoeffs(double freq, double fs, double q, double gain, FilterType type);
};

#endif // IIR2_H
