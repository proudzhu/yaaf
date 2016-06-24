#ifndef LPC_H
#define LPC_H

std::vector<double> lpc(std::vector<double> x, int n);

std::vector<double> levinson(std::vector<double> acf, int p);

#endif
