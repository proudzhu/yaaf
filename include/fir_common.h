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

    std::vector<double> GetCoeffs() const;

    void SetCoeffs(const std::vector<double> &b);

private:
    std::vector<double> b_;

    std::vector<std::vector<double>> delayline_;

    void UpdateDelayLine(double xh, int ch);
};

#endif // FIRCOMMON_H
