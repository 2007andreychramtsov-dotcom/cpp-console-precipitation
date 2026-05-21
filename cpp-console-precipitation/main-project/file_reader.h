#pragma once
#include "precipitation.h"

int readData(const char* filename, Precipitation* data, int maxCount);
void printData(const Precipitation* data, int count);
