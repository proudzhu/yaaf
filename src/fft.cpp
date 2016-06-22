#include <cassert>
#include "fft.h"

fft::fft(int n, int fftSign, int fftFlags)
    : size(n), sign(fftSign), flags(fftFlags)
{
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);

    p = fftw_plan_dft_1d(size, in, out, sign, flags);
}

fft::~fft()
{
    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
}

void fft::execute(std::vector<std::complex<double>> &h, std::vector<std::complex<double>> &H)
{
    assert(h.size() == size);
    // fill in
    for (int i = 0; i < size; i++) {
        in[i][0] = h[i].real();
        in[i][1] = h[i].imag();
    }

    fftw_execute(p);

    // covert to std::complex
    int normal = 1;
    if (sign == FFTW_BACKWARD)
        normal = size;

    for (int i = 0; i < size; i++) {
        H[i] = std::complex<double>(out[i][0] / normal, out[i][1] / normal);
    }
}
