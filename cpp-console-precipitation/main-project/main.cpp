#include <stdio.h>
#include "constants.h"
#include "precipitation.h"
#include "file_reader.h"
#include "Windows.h"

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    printf("Laboratory work #8. GIT\n");
    printf("Variant #3. Precipitation\n");
    printf("Author: Andrey Khramtsov\n");

    Precipitation data[MAX_LINES];
    int count = readData(DATA_FILE, data, MAX_LINES);

    if (count == 0) {
        printf("Данные не загружены.\n");
        return 1;
    }

    printf("Загружено записей: %d\n\n", count);
    printData(data, count);

    return 0;
}