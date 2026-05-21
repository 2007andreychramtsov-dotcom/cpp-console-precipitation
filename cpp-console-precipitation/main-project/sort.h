#pragma once
#include "precipitation.h"

// Тип указателя на функцию сравнения:
// возвращает <0, 0 или >0
typedef int (*CompareFunc)(const Precipitation*, const Precipitation*);

// Два метода сортировки
void shakerSort(Precipitation* data, int count, CompareFunc cmp);
void quickSort(Precipitation* data, int count, CompareFunc cmp);

// Два критерия сравнения
int compareByAmount(const Precipitation* a, const Precipitation* b);
int compareByCharacteristicMonthDay(const Precipitation* a, const Precipitation* b);
