#include <fstream>
#include <memory>
#include "iir2.h"

int main(int argc, char **argv)
{
    double fs = 44100;
    double freq = 300;
    Iir2::FilterType type = Iir2::kHPF;
    int16_t buf[1024];

    auto inbuf = std::make_unique<AudioBuffer>();
    inbuf->ch = 1;
    inbuf->fs = 44100;
    inbuf->samples = sizeof(buf) / sizeof(buf[0]);
    inbuf->buf = buf;

    auto outbuf = std::make_unique<AudioBuffer>();
    outbuf->ch = 1;
    outbuf->fs = 44100;
    outbuf->samples = sizeof(buf) / sizeof(buf[0]);
    outbuf->buf = buf;

    std::ifstream input(argv[1], std::ios::binary);
    std::ofstream output(argv[2], std::ios::binary);

    auto iir2 = std::make_unique<Iir2>(freq, fs, inbuf->ch, type, sqrt(2)/2, 0);

    int eof = 0;
    while (eof == 0) {
        input.read(reinterpret_cast<char *>(buf), sizeof(buf));
        if (input.gcount() < inbuf->samples / 2) {
            eof = 1;
            outbuf->samples = inbuf->samples = input.gcount() / 2;
        }
        iir2->Process(inbuf.get(), outbuf.get());

        output.write(reinterpret_cast<char *>(buf), sizeof(buf));
    }

    return 0;
}
