#include "Easing.h"

double easeInBack(double x) {
    const double c1 = 1.70158;
    const double c3 = c1 + 1;

    return c3 * x * x * x - c1 * x * x;
}
