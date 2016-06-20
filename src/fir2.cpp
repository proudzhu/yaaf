#include <iostream>
#include <cassert>
#include "fir2.h"
#include "window.h"

fir2::fir2(int n, std::vector<double> f, std::vector<double> a,
           int32_t npt, int32_t lap,
           std::vector<double> window)
{
    calcCoeffs(n, f, a, npt, lap, window);
}

/* only impl calcCoeffs(n, f, a) */
void fir2::calcCoeffs(int n, std::vector<double> f, std::vector<double> a,
                      int32_t npt, int32_t lap,
                      std::vector<double> window)
{
    int t = f.size();
    if (t < 2 || f[0] != 0 || f[t - 1] != 1 || isNonDecrease(f)) {
        std::cout << "fir2: frequency must be nondecreasing starting from 0 and ending at 1\n";
        assert(0);
    } else if (t != a.size()) {
        std::cout << "fir2: frequency and magnitude vectors must be the same length\n";
        assert(0);
    }

    // Work with filter length instead of filter order
    n = n + 1;
    if (n < 1024)
        npt = 512;
    else
        npt = 2 ^ nextpow2(n);

    if (window.size() == 0)
        window = hamming(n + 1);

    lap = fix(npt / 25);

    // interpolate
    std::vector<double> H(npt, 0);
    npt = npt + 1;

    double nb = 1, ne = nb;
    H[0] = a[0];

    for (int i = 0; i < t; i++) {
        double df = f[i + 1] - f[i];
        if (df == 0) {
            nb = ceil(nb - lap / 2);
            ne = nb + lap;
        } else {
            ne = fix(f[i + 1] * npt);
        }
        if (nb < 0 || ne > npt)
            assert(0);


    }


}
