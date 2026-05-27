#pragma once
#include "precipitation.h"
#include "processing.h"

// Возвращает суммарное количество осадков за указанный месяц
double process(const Precipitation* data, int count, int month);