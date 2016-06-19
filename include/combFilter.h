#ifndef COMB_FILTER_H
#define COMB_FILTER_H

#include <memory>
#include <vector>
#include <cmath>
#include "common.h"

class combFilter
{
public:
    combFilter(int delay, double bl, double fb, double ff, int ch = 1)
        : delayM(delay), blend(bl), feedBack(fb), feedForward(ff)
    {
        delayLine.resize(ch, std::vector<double>(delayM, 0));
    }

    ~combFilter() {}

    int process(AudioBuffer *inbuf, AudioBuffer *outbuf);

    void reset(void);

private:
    int delayM;
    double blend;
    double feedBack;
    double feedForward;

    std::vector<std::vector<double>> delayLine;

    void updateDelayLine(double xh, int ch);
};

// specify comb filter type
class firCombFilter : combFilter
{
    firCombFilter(int delay, double bl, double ff, int ch = 1)
        : combFilter(delay, bl, 0, ff, ch)
    { }
};

class iirCombFilter : combFilter
{
    iirCombFilter(int delay, double fb, int ch = 1)
        : combFilter(delay, 1, fb, 0, ch)
    { }

};

class allpassCombFilter : combFilter
{
    allpassCombFilter(int delay, double bl, int ch = 1)
        : combFilter(delay, bl, -bl, 1, ch)
    { }
};

class delayCombFilter : combFilter
{
    delayCombFilter(int delay, int ch = 1)
        : combFilter(delay, 0, 0, 1, ch)
    { }
};

#endif // COMB_FILTER_H
