#pragma once
#include "precipitation.h"

// Фильтрует массив data по критерию selector, результат помещает в result
// Возвращает количество отобранных элементов
int filterData(const Precipitation* data, int count,
               Precipitation* result,
               bool (*selector)(const Precipitation*));

// Критерии отбора
bool isRain(const Precipitation* p);           // дни, в которые шёл дождь
bool isLowAmount(const Precipitation* p);      // дни с количеством осадков < 1.5
