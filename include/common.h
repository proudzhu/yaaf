#ifndef COMMON_H
#define COMMON_H

#include <cstdint>
#include <cmath>

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
