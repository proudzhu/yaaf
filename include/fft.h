#ifndef FFT_H
#define FFT_H

#undef _GLIBCXX_USE_C99_COMPLEX

#include <vector>
#include <complex>
#include "fftw3.h"

class fft
{
public:
    fft(int n) : fft(n, FFTW_FORWARD)
    { }

    fft(int n, int fftSign) : fft(n, fftSign, FFTW_ESTIMATE)
    { }

    fft(int n, int fftSign, int fftFlags);

    ~fft();

    void execute(std::vector<std::complex<double>> &h, std::vector<std::complex<double>> &H);

private:
    int size, sign, flags;
    fftw_complex *in, *out;
    fftw_plan p;
};

#endif // FFT_H
