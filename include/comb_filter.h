#ifndef COMB_FILTER_H
#define COMB_FILTER_H

#include <memory>
#include <vector>
#include <cmath>
#include "common.h"

class CombFilter
{
public:
    CombFilter(int delay, double bl, double fb, double ff, int ch = 1)
        : delayM(delay), blend(bl), feedBack(fb), feedForward(ff)
    {
        delayLine.resize(ch, std::vector<double>(delayM, 0));
    }

    ~CombFilter() {}

    int Process(AudioBuffer *inbuf, AudioBuffer *outbuf);

    void Reset(void);

private:
    int delayM;
    double blend;
    double feedBack;
    double feedForward;

    std::vector<std::vector<double>> delayLine;

    void UpdateDelayLine(double xh, int ch);
};

// specify comb filter type
class FirCombFilter : public CombFilter
{
    FirCombFilter(int delay, double bl, double ff, int ch = 1)
        : CombFilter(delay, bl, 0, ff, ch)
    { }
};

class IirCombFilter : public CombFilter
{
    IirCombFilter(int delay, double fb, int ch = 1)
        : CombFilter(delay, 1, fb, 0, ch)
    { }

};

class AllpassCombFilter : public CombFilter
{
    AllpassCombFilter(int delay, double bl, int ch = 1)
        : CombFilter(delay, bl, -bl, 1, ch)
    { }
};

class DelayCombFilter : public CombFilter
{
    DelayCombFilter(int delay, int ch = 1)
        : CombFilter(delay, 0, 0, 1, ch)
    { }
};

#endif // COMB_FILTER_H
