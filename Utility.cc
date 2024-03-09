
#include "Utility.h"

static double Utility::normalizeImageToOne(double x) {
    return x/255.0;
}

static double Utility::normalizeImageToTernary(double x) {
    double output = x / 85.0;
    output = output + 0.5 - (output<0);
    output = (int)output-1;
    return output;
}