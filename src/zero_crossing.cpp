#include "zero_crossing.h"

double zero_crossing(std::vector<double> x)
{
    int count = 0;

    for (int i = 1; i < x.size(); i++) {
        if ((x[i-1] < 0 && x[i] > 0) ||
            (x[i-1] > 0 && x[i] < 0))
            count += 1;
    }

    return 1.0 * count / (x.size() - 1);
}
