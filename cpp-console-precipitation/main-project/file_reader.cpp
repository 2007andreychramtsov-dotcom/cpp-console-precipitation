#include "file_reader.h"
#include <stdio.h>
#include <string.h>

// Читает данные из файла. Поля: день месяц количество характеристика
// Характеристика может содержать пробелы — читается до конца строки
int readData(const char* filename, Precipitation* data, int maxCount) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Ошибка: не удалось открыть файл '%s'\n", filename);
        return 0;
    }

    int count = 0;
    char line[MAX_LINE_LENGTH + 2];

    while (count < maxCount && fgets(line, sizeof(line), f)) {
        // Убираем символ новой строки
        int len = (int)strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[--len] = '\0';
        if (len > 0 && line[len - 1] == '\r') line[--len] = '\0';
        if (len == 0) continue;

        Precipitation& p = data[count];

        // Читаем день, месяц, количество
        int parsed = sscanf(line, "%d %d %lf", &p.day, &p.month, &p.amount);
        if (parsed != 3) continue;

        // Пропускаем три первых поля, характеристика — остаток строки
        const char* ptr = line;
        int spaces = 0;
        while (*ptr && spaces < 3) {
            if (*ptr == ' ') {
                spaces++;
                while (*ptr == ' ') ptr++;
            } else {
                ptr++;
            }
        }
        strncpy(p.characteristic, ptr, MAX_CHARACTERISTIC_LENGTH - 1);
        p.characteristic[MAX_CHARACTERISTIC_LENGTH - 1] = '\0';

        count++;
    }

    fclose(f);
    return count;
}

void printData(const Precipitation* data, int count) {
    printf("\n%-6s %-7s %-12s %s\n", "День", "Месяц", "Количество", "Характеристика");
    printf("%-6s %-7s %-12s %s\n", "------", "-------", "------------", "---------------");
    for (int i = 0; i < count; i++) {
        printf("%-6d %-7d %-12.2f %s\n",
            data[i].day, data[i].month, data[i].amount, data[i].characteristic);
    }
    printf("\n");
}
