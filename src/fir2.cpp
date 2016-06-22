#include <memory>
#include <iostream>
#include <cassert>
#include "fir2.h"
#include "fft.h"
#include "window.h"

Fir2::Fir2(int n, std::vector<double> f, std::vector<double> a,
           std::vector<double> window)
{
    CalcCoeffs(n, f, a, window);
}

/* only impl calcCoeffs(n, f, a) */
void Fir2::CalcCoeffs(int n, std::vector<double> f, std::vector<double> a,
                      std::vector<double> window)
{
    int t = f.size();
    if (t < 2 || f[0] != 0 || f[t - 1] != 1 || isNonDecrease(f) == false) {
        std::cout << "fir2: frequency must be nondecreasing starting from 0 and ending at 1\n";
        assert(0);
    } else if (t != a.size()) {
        std::cout << "fir2: frequency and magnitude vectors must be the same length\n";
        assert(0);
    }

    // Work with filter length instead of filter order
    n = n + 1;
    int npt;
    if (n < 1024)
        npt = 512;
    else
        npt = 2 ^ nextpow2(n);

    if (window.size() == 0)
        window = hamming(n);

    int lap = fix(npt / 25);

    // interpolate
    std::vector<std::complex<double>> H(npt*2, 0);
    npt = npt + 1;

    double nb = 1, ne = nb;
    H[0] = a[0];

    for (int i = 0; i < t - 1; i++) {
        double df = f[i + 1] - f[i];
        if (df == 0) {
            nb = ceil(nb - lap / 2);
            ne = nb + lap;
        } else {
            ne = fix(f[i + 1] * npt);
        }
        if (nb < 0 || ne > npt)
            assert(0);

        double inc = 0;
        for (int j = nb; j <= ne; j++) {
            if (nb == ne)
                inc = 0;
            else
                inc = 1.0 * (j - nb) / (ne - nb);
            H[j - 1] = inc * a[i + 1] + (1 - inc) * a[i];
        }
        nb = ne + 1;
    }

    // Fourier time-shift
    double dt = 0.5 * (n - 1);
    for (int j = 0; j < npt; j++) {
        std::complex<double> rad(0, -1 * dt * M_PI * j / (npt - 1));
        H[j] = H[j] * exp(rad);
    }

    for (int j = npt; j < 2*(npt-1); j++) {
        H[j] = conj(H[2*(npt-1)-j]);
    }

    std::unique_ptr<Fft> ifft = std::make_unique<Fft>(H.size(), FFTW_BACKWARD);
    std::vector<std::complex<double>> ht(H.size(), 0);
    ifft->Execute(H, ht);

    std::vector<double> b(n, 0);
    for (int j = 0; j < n; j++) {
        b[j] = ht[j].real() * window[j];
    }

    SetCoeffs(b);
}
