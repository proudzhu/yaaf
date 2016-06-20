#ifndef FIR2_H
#define FIR2_H

#include <vector>
#include "firCommon.h"

class fir2 : firCommon
{
public:
    fir2(int n, std::vector<double> f, std::vector<double> a)
        : fir2(n, f, a, 0, 0, std::vector<double>())
    { }

    fir2(int n, std::vector<double> f, std::vector<double> a, std::vector<double> window)
        : fir2(n, f, a, 0, 0, window)
    { }

    fir2(int n, std::vector<double> f, std::vector<double> a, int32_t npt)
        : fir2(n, f, a, npt, 0, std::vector<double>())
    { }

    fir2(int n, std::vector<double> f, std::vector<double> a, int32_t npt, std::vector<double> window)
        : fir2(n, f, a, npt, 0, window)
    { }

    fir2(int n, std::vector<double> f, std::vector<double> a, int32_t npt, int32_t lap)
        : fir2(n, f, a, npt, lap, std::vector<double>())
    { }

    fir2(int n, std::vector<double> f, std::vector<double> a, int32_t npt, int32_t lap, std::vector<double> window);

    ~fir2() {}

private:

    void calcCoeffs(int n, std::vector<double> f, std::vector<double> a, int32_t npt, int32_t lap, std::vector<double> window);
};

#endif // FIR2_H
