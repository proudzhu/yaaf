#ifndef FIR2_H
#define FIR2_H

#include <vector>
#include <memory>
#include "fir_common.h"

class Fir2 : public FirCommon
{
public:
    Fir2(int n, std::vector<double> f, std::vector<double> a)
        : Fir2(n, f, a, std::vector<double>())
    { }

    Fir2(int n, std::vector<double> f, std::vector<double> a, std::vector<double> window);

    ~Fir2() {}

private:
    void CalcCoeffs(int n, std::vector<double> f, std::vector<double> a, std::vector<double> window);
};

#endif // FIR2_H
