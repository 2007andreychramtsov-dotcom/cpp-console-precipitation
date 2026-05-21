#pragma once
#include "constants.h"

struct Precipitation {
    int day;
    int month;
    double amount;  // количество осадков
    char characteristic[MAX_CHARACTERISTIC_LENGTH];  // вид осадков (дождь, снег, мокрый снег и т.д.)
};
