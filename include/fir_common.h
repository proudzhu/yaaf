#ifndef FIRCOMMON_H
#define FIRCOMMON_H

#include <vector>
#include "common.h"

class FirCommon
{
public:
    FirCommon() { };

    ~FirCommon() { };

    int Process(AudioBuffer *inbuf, AudioBuffer *outbuf);

    void Reset(void);

    void SetCoeffs(std::vector<double> b);

    std::vector<double> b;

private:
    std::vector<std::vector<double>> delayLine;

    void UpdateDelayLine(double xh, int ch);
};

#endif // FIRCOMMON_H
