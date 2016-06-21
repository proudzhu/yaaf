#include <vector>
#include <cmath>
#include "common.h"
#include "window.h"

std::vector<double> hamming(int l)
{
    int n = l - 1;
    if (n == 0)
        return std::vector<double>{1.0};

    std::vector<double> w(n + 1, 0.0);
    for (int i = 0; i <= n; i++) {
        w[i] = 0.54 - 0.46 * cos(2 * M_PI * i / n);
    }

    return w;
}
