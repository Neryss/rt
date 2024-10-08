#include "../includes/utils.h"

double  randomValue(int state)
{
    state *= (state + 195439) * (state + 124359) * (state + 845921);
    return (state /4294967295.0);
}

double  clamp(double value, double min, double max)
{
    if (value < min)
        return(min);
    if (value > max)
        return(max);
    return(value);
}

double random_double(double min, double max) {
    // Ensure min is less than max
    if (min > max) {
        double temp = min;
        min = max;
        max = temp;
    }
    // Generate a random double between 0 and 1, then scale to the range [min, max]
    double scale = rand() / (double)RAND_MAX; // rand() / RAND_MAX gives a number between 0 and 1
    return min + scale * (max - min);         // Scale and shift to the range [min, max]
}

double  maxd(double value, double max)
{
    if (value > max)
        return (value);
    return (max);
}

int     min(int a, int b)
{
    if (a < b)
        return (a);
    return (b);
}

double  degrees_to_radians(double degrees)
{
    return (degrees * M_PI / 180.0);
}


// double RandomValueNormalDistribution(int state)
// {
//     // Thanks to https://stackoverflow.com/a/6178290
//     float theta = 2 * 3.1415926 * RandomValue(state);
//     float rho = sqrt(-2 * log(RandomValue(state)));
//     return rho * cos(theta);
// }