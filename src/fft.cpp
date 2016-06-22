#include <cassert>
#include "fft.h"

Fft::Fft(int n, int fftSign, int fftFlags)
    : size_(n), sign_(fftSign), flags_(fftFlags)
{
    in_ = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size_);
    out_ = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size_);

    p_ = fftw_plan_dft_1d(size_, in_, out_, sign_, flags_);
}

Fft::~Fft()
{
    fftw_destroy_plan(p_);
    fftw_free(in_);
    fftw_free(out_);
}

void Fft::Execute(std::vector<std::complex<double>> &h, std::vector<std::complex<double>> &H)
{
    assert(h.size() == size_);
    // fill in
    for (int i = 0; i < size_; i++) {
        in_[i][0] = h[i].real();
        in_[i][1] = h[i].imag();
    }

    fftw_execute(p_);

    // covert to std::complex
    int normal = 1;
    if (sign_ == FFTW_BACKWARD)
        normal = size_;

    for (int i = 0; i < size_; i++) {
        H[i] = std::complex<double>(out_[i][0] / normal, out_[i][1] / normal);
    }
}
