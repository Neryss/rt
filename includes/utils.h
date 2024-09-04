#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdlib.h>

double  randomValue(int state);
double  clamp(double value, double min, double max);
double  random_double(double min, double max);
double  maxd(double value, double max);
int     min(int a, int b);

#endif