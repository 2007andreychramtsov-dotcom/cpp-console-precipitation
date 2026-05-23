#include "processing.h"

double process(const Precipitation* data, int count, int month)
{
    double total = 0.0;
    for (int i = 0; i < count; i++) {
        if (data[i].month == month) {
            total += data[i].amount;
        }
    }
    return total;
}