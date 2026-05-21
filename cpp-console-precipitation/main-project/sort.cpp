#include "sort.h"
#include <string.h>

// ============================================================
// Шейкерная сортировка (Shaker sort / Cocktail sort)
// ============================================================
void shakerSort(Precipitation* data, int count, CompareFunc cmp) {
    int left = 0;
    int right = count - 1;
    while (left < right) {
        // Проход слева направо — выталкиваем максимум вправо
        for (int i = left; i < right; i++) {
            if (cmp(&data[i], &data[i + 1]) > 0) {
                Precipitation tmp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = tmp;
            }
        }
        right--;
        // Проход справа налево — выталкиваем минимум влево
        for (int i = right; i > left; i--) {
            if (cmp(&data[i - 1], &data[i]) > 0) {
                Precipitation tmp = data[i - 1];
                data[i - 1] = data[i];
                data[i] = tmp;
            }
        }
        left++;
    }
}

// ============================================================
// Быстрая сортировка (Quick sort)
// ============================================================
static void quickSortHelper(Precipitation* data, int lo, int hi, CompareFunc cmp) {
    if (lo >= hi) return;
    Precipitation pivot = data[(lo + hi) / 2];
    int i = lo, j = hi;
    while (i <= j) {
        while (cmp(&data[i], &pivot) < 0) i++;
        while (cmp(&data[j], &pivot) > 0) j--;
        if (i <= j) {
            Precipitation tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
            i++; j--;
        }
    }
    quickSortHelper(data, lo, j, cmp);
    quickSortHelper(data, i, hi, cmp);
}

void quickSort(Precipitation* data, int count, CompareFunc cmp) {
    if (count > 1)
        quickSortHelper(data, 0, count - 1, cmp);
}

// ============================================================
// Критерий 1: по возрастанию количества осадков
// ============================================================
int compareByAmount(const Precipitation* a, const Precipitation* b) {
    if (a->amount < b->amount) return -1;
    if (a->amount > b->amount) return 1;
    return 0;
}

// ============================================================
// Критерий 2: по возрастанию характеристики;
//             в рамках одной характеристики — по месяцу;
//             в рамках одного месяца — по дню
// ============================================================
int compareByCharacteristicMonthDay(const Precipitation* a, const Precipitation* b) {
    int cmpChar = strcmp(a->characteristic, b->characteristic);
    if (cmpChar != 0) return cmpChar;
    if (a->month != b->month) return a->month - b->month;
    return a->day - b->day;
}
