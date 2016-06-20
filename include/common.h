#ifndef COMMON_H
#define COMMON_H

#include <cstdint>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct
{
    int ch;
    int fs;
    int samples;
    int16_t *buf;
} AudioBuffer;

typedef enum
{
    NONE,
    HPF,
    LPF,
    LowShelf,
    HighShelf,
    PeakingEQ,
    FilterTypeNum
} FilterType;

#endif // COMMON_H
