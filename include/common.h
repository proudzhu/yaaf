#ifndef COMMON_H
#define COMMON_H

#include <vector>
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

/* check if a vector is nondecreasing */
bool isNonDecrease(std::vector<double> v);

/* round towards zero */
inline int fix(double x)
{
    return (int)x;
}

/* next higher power of 2 */
inline int nextpow2(int i)
{
    return ceil(log2(std::abs(i)));
}

/* linear interp */
double interp1(std::vector<double> x, std::vector<double> v, double xq);

#endif // COMMON_H
