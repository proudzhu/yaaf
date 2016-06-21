#ifndef FFT_H
#define FFT_H

#undef _GLIBCXX_USE_C99_COMPLEX

#include <vector>
#include <complex>

std::vector<std::complex<double>> fft(std::vector<std::complex<double>> h);

std::vector<std::complex<double>> ifft(std::vector<std::complex<double>> H);

#endif // FFT_H
