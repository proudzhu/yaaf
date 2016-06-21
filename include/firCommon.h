#ifndef FIRCOMMON_H
#define FIRCOMMON_H

#include <vector>
#include "common.h"

class firCommon
{
public:
    firCommon() { };

    ~firCommon() { };

    int process(AudioBuffer *inbuf, AudioBuffer *outbuf);

    void reset(void);

    void setCoeffs(std::vector<double> b);

    std::vector<double> b;

private:
    std::vector<std::vector<double>> delayLine;

    void updateDelayLine(double xh, int ch);
};

#endif // FIRCOMMON_H
