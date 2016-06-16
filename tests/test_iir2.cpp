#include <fstream>
#include <memory>
#include "iir2.h"

int main(int argc, char **argv)
{
    double fs = 44100;
    double freq = 300;
    FilterType type = HPF;
    int16_t buf[1024];

    AudioBuffer *inbuf = new AudioBuffer();
    inbuf->ch = 1;
    inbuf->fs = 44100;
    inbuf->samples = sizeof(buf) / sizeof(buf[0]);
    inbuf->buf = buf;

    AudioBuffer *outbuf = new AudioBuffer();
    outbuf->ch = 1;
    outbuf->fs = 44100;
    outbuf->samples = sizeof(buf) / sizeof(buf[0]);
    outbuf->buf = buf;

    std::ifstream input(argv[1], std::ios::binary);
    std::ofstream output(argv[2], std::ios::binary);

    IIR2 *iir2 = new IIR2(freq, fs, inbuf->ch, type, sqrt(2)/2, 0);

    int eof = 0;
    while (eof == 0) {
        input.read(reinterpret_cast<char *>(buf), sizeof(buf));
        if (input.gcount() < inbuf->samples / 2) {
            eof = 1;
            outbuf->samples = inbuf->samples = input.gcount() / 2;
        }
        iir2->process(inbuf, outbuf);

        output.write(reinterpret_cast<char *>(buf), sizeof(buf));
    }

    return 0;
}
