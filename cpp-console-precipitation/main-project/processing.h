#pragma once
#include "precipitation.h"

// Возвращает суммарное количество осадков за указанный месяц
double process(const Precipitation* data, int count, int month);