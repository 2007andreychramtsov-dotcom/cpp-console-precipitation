#include <stdio.h>
#include "constants.h"
#include "precipitation.h"
#include "file_reader.h"
#include "filter.h"
#include "Windows.h"

void printMenu() {
    printf("=== Меню ===\n");
    printf("1. Вывести все данные\n");
    printf("2. Фильтрация данных\n");
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

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    printf("Laboratory work #8. GIT\n");
    printf("Variant #3. Precipitation\n");
    printf("Author: Andrey Khramtsov\n");
    printf("Группа: 25ИСиТ-1д\n\n");

    Precipitation data[MAX_LINES];
    int count = readData(DATA_FILE, data, MAX_LINES);

    if (count == 0) {
        printf("Данные не загружены.\n");
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
        case 0:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор.\n\n");
        }
    }

    return 0;
}