#include <vector>
#include <memory>
#include <algorithm>
#include "common.h"
#include "fft.h"
#include "lpc.h"

std::vector<double> lpc(std::vector<double> x, int n)
{
    int nfft = 1 << nextpow2(2*x.size() - 1);
    std::vector<std::complex<double>> xc(nfft, 0), hx(nfft, 0);

    std::transform(x.begin(), x.end(), xc.begin(), [](auto i) {
        return std::complex<double>(i, 0);
    });

    auto fft = std::make_unique<Fft>(nfft, FFTW_FORWARD);
    auto ifft = std::make_unique<Fft>(nfft, FFTW_BACKWARD);

    fft->Execute(xc, hx);

    std::transform(hx.begin(), hx.end(), hx.begin(), [](auto i) {
        return std::complex<double>(std::abs(i) * std::abs(i), 0);
    });

    ifft->Execute(hx, xc);

    std::vector<double> acf(xc.size(), 0);
    std::transform(xc.begin(), xc.end(), acf.begin(), [n](auto i) {
        return real(i) / n;
    });

    return levinson(acf, n);
}

std::vector<double> levinson(std::vector<double> acf, int p)
{
    double g = -acf[1] / acf[0];
    std::vector<double> a(p, 0);
    double v = (1 - g * g) * acf[0];

    a[0] = g;
    for (int t = 1;  t < p; t++) {
        double gtmp = acf[t+1];
        for (int i = t; i >= 1; i--) {
            gtmp += a[t-i] * acf[i];
        }
        g = -1 * gtmp / v;

        for (int i = 0; i < t; i++) {
            a[i] = a[i] + g * a[t-1-i];
        }
        a[t] = g;
        v = v * (1 - g * g);
    }

    a.insert(a.begin(), 1);

    return a;
}
