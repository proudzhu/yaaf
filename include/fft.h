#ifndef FFT_H
#define FFT_H

#undef _GLIBCXX_USE_C99_COMPLEX

#include <vector>
#include <complex>
#include "fftw3.h"

class Fft
{
public:
    Fft(int n) : Fft(n, FFTW_FORWARD)
    { }

    Fft(int n, int fftSign) : Fft(n, fftSign, FFTW_ESTIMATE)
    { }

    Fft(int n, int fftSign, int fftFlags);

    ~Fft();

    void Execute(std::vector<std::complex<double>> &h, std::vector<std::complex<double>> &H);

private:
    int size_, sign_, flags_;
    fftw_complex *in_, *out_;
    fftw_plan p_;
};

#endif // FFT_H
