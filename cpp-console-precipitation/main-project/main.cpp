#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "precipitation.h"
#include "file_reader.h"
#include "filter.h"
#include "sort.h"

// ============================================================
// Вывод меню и обработка выбора пользователя
// ============================================================

void printMenu() {
    printf("=== Меню ===\n");
    printf("1. Вывести все данные\n");
    printf("2. Фильтрация данных\n");
    printf("3. Сортировка данных\n");
    printf("0. Выход\n");
    printf("Ваш выбор: ");
}

void menuFilter(const Precipitation* data, int count) {
    printf("\n--- Выбор критерия фильтрации ---\n");
    printf("1. Дни, в которые шёл дождь\n");
    printf("2. Дни с количеством осадков меньше 1.5\n");
    printf("Ваш выбор: ");

    int choice = 0;
    scanf("%d", &choice);

    // Массив указателей на функции-селекторы
    bool (*selectors[])(const Precipitation*) = { isRain, isLowAmount };
    const char* descriptions[] = {
        "Дни, в которые шёл дождь",
        "Дни с количеством осадков < 1.5"
    };

    if (choice < 1 || choice > 2) {
        printf("Неверный выбор.\n");
        return;
    }

    Precipitation result[MAX_LINES];
    int resultCount = filterData(data, count, result, selectors[choice - 1]);

    printf("\nРезультат: %s\n", descriptions[choice - 1]);
    if (resultCount == 0) {
        printf("Нет данных, удовлетворяющих условию.\n\n");
    }
    else {
        printData(result, resultCount);
    }
}

void menuSort(Precipitation* data, int count) {
    printf("\n--- Выбор метода сортировки ---\n");
    printf("1. Шейкерная сортировка (Shaker sort)\n");
    printf("2. Быстрая сортировка (Quick sort)\n");
    printf("Ваш выбор: ");

    int sortChoice = 0;
    scanf("%d", &sortChoice);

    if (sortChoice < 1 || sortChoice > 2) {
        printf("Неверный выбор.\n");
        return;
    }

    printf("\n--- Выбор критерия сортировки ---\n");
    printf("1. По возрастанию количества осадков\n");
    printf("2. По возрастанию характеристики, затем месяца, затем дня\n");
    printf("Ваш выбор: ");

    int cmpChoice = 0;
    scanf("%d", &cmpChoice);

    if (cmpChoice < 1 || cmpChoice > 2) {
        printf("Неверный выбор.\n");
        return;
    }

    // Массивы указателей на функции сортировки и сравнения
    void (*sortFuncs[])(Precipitation*, int, CompareFunc) = { shakerSort, quickSort };
    CompareFunc cmpFuncs[] = { compareByAmount, compareByCharacteristicMonthDay };

    const char* sortNames[] = { "Шейкерная сортировка", "Быстрая сортировка" };
    const char* cmpNames[] = {
        "по возрастанию количества осадков",
        "по возрастанию характеристики / месяца / дня"
    };

    // Вызываем функцию сортировки через указатель, передавая указатель на функцию сравнения
    sortFuncs[sortChoice - 1](data, count, cmpFuncs[cmpChoice - 1]);

    printf("\nДанные отсортированы: %s, %s\n", sortNames[sortChoice - 1], cmpNames[cmpChoice - 1]);
    printData(data, count);
}

int main() {
    // Вариант 3: Осадки
    // Автор: Храмцов Андрей
    // Группа: 25ИСиТ-1д

    printf("Вариант 3: Осадки\n");
    printf("Автор: Храмцов Андрей\n");
    printf("Группа: 25ИСиТ-1д\n\n");

    Precipitation data[MAX_LINES];
    int count = readData(DATA_FILE, data, MAX_LINES);

    if (count == 0) {
        printf("Данные не загружены. Завершение работы.\n");
        return 1;
    }

    printf("Загружено записей: %d\n\n", count);

    int choice = -1;
    while (choice != 0) {
        printMenu();
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
        case 1:
            printData(data, count);
            break;
        case 2:
            menuFilter(data, count);
            break;
        case 3:
            menuSort(data, count);
            break;
        case 0:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n\n");
        }
    }

    return 0;
}
