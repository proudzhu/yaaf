#ifndef FIR2_H
#define FIR2_H

#include <vector>
#include <memory>
#include "firCommon.h"

class fir2 : public firCommon
{
public:
    fir2(int n, std::vector<double> f, std::vector<double> a)
        : fir2(n, f, a, std::vector<double>())
    { }

    fir2(int n, std::vector<double> f, std::vector<double> a, std::vector<double> window);

    ~fir2() {}

private:
    void calcCoeffs(int n, std::vector<double> f, std::vector<double> a, std::vector<double> window);
};

#endif // FIR2_H
