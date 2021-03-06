#include <fstream>
#include <memory>
#include "comb_filter.h"

int main(int argc, char **argv)
{
    int16_t bufin[1024];
    int16_t bufout[1024];

    auto inbuf = std::make_unique<AudioBuffer>();
    inbuf->ch = 1;
    inbuf->fs = 44100;
    inbuf->samples = sizeof(bufin) / sizeof(bufin[0]);
    inbuf->buf = bufin;

    auto outbuf = std::make_unique<AudioBuffer>();
    outbuf->ch = 1;
    outbuf->fs = 44100;
    outbuf->samples = sizeof(bufout) / sizeof(bufout[0]);
    outbuf->buf = bufout;

    std::ifstream input(argv[1], std::ios::binary);
    std::ofstream output(argv[2], std::ios::binary);

    auto comb = std::make_unique<CombFilter>(10, 0.5, -0.5, 1, inbuf->ch);

    int eof = 0;
    while (eof == 0) {
        input.read(reinterpret_cast<char *>(bufin), sizeof(bufin));
        if (input.gcount() < inbuf->samples / 2) {
            eof = 1;
            outbuf->samples = inbuf->samples = input.gcount() / 2;
        }
        comb->Process(inbuf.get(), outbuf.get());

        output.write(reinterpret_cast<char *>(bufout), sizeof(bufout));
    }

    return 0;
}
