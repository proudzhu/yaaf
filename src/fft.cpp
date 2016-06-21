#include "fftw3.h"
#include "fft.h"

std::vector<std::complex<double>> fft(std::vector<std::complex<double>> h)
{
    int N = h.size();
    fftw_complex *in, *out;
    fftw_plan p;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

    // fill in
    for (int i = 0; i < N; i++) {
        in[i][0] = h[i].real();
        in[i][1] = h[i].imag();
    }

    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(p); /* repeat as needed */

    // covert to std::complex
    std::vector<std::complex<double>> H(N, 0);
    for (int i = 0; i < N; i++) {
        H[i] = std::complex<double>(out[i][0], out[i][1]);
    }

    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);

    return H;
}

std::vector<std::complex<double>> ifft(std::vector<std::complex<double>> H)
{
    int N = H.size();
    fftw_complex *in, *out;
    fftw_plan p;

    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

    // fill in
    for (int i = 0; i < N; i++) {
        in[i][0] = H[i].real();
        in[i][1] = H[i].imag();
    }

    p = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);

    fftw_execute(p); /* repeat as needed */

    // covert to std::complex
    std::vector<std::complex<double>> h(N, 0);
    for (int i = 0; i < N; i++) {
        h[i] = std::complex<double>(out[i][0]/N, out[i][1]/N);
    }

    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);

    return h;
}
