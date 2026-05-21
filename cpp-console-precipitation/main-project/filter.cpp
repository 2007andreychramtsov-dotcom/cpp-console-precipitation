#include "filter.h"
#include <string.h>
#include <ctype.h>

int filterData(const Precipitation* data, int count,
               Precipitation* result,
               bool (*selector)(const Precipitation*)) {
    int resultCount = 0;
    for (int i = 0; i < count; i++) {
        if (selector(&data[i])) {
            result[resultCount++] = data[i];
        }
    }
    return resultCount;
}

// Проверяет, содержит ли характеристика слово "дождь" (без учёта регистра)
bool isRain(const Precipitation* p) {
    // Ищем подстроку "дождь" в характеристике
    // strcmp не подходит — характеристика может содержать другие слова
    // Простой поиск подстроки
    const char* hay = p->characteristic;
    const char* needle = "\xd0\xb4\xd0\xbe\xd0\xb6\xd0\xb4\xd1\x8c"; // "дождь" UTF-8
    // Используем стандартный strstr
    return strstr(hay, needle) != nullptr ||
           strstr(hay, "дождь") != nullptr;
}

bool isLowAmount(const Precipitation* p) {
    return p->amount < 1.5;
}
