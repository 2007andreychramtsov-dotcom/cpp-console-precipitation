#include "pch.h"
#include "CppUnitTest.h"
#include "../main-project/precipitation.h"
#include "../main-project/processing.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittestproject
{
    TEST_CLASS(unittestproject)
    {
    public:
        // Тест 1: январь — осадки 0.5 + 1.2 + 2.3 = 4.0
        TEST_METHOD(TestMonth1)
        {
            Precipitation data[3];
            data[0] = { 1, 1, 0.5, "снег" };
            data[1] = { 3, 1, 1.2, "мокрый снег" };
            data[2] = { 5, 1, 2.3, "дождь" };
            double result = process(data, 3, 1);
            Assert::AreEqual(4.0, result, 0.001);
        }

        // Тест 2: февраль — осадки 0.8 + 1.7 + 0.3 = 2.8
        TEST_METHOD(TestMonth2)
        {
            Precipitation data[3];
            data[0] = { 10, 2, 0.8, "снег" };
            data[1] = { 14, 2, 1.7, "дождь" };
            data[2] = { 20, 2, 0.3, "снег" };
            double result = process(data, 3, 2);
            Assert::AreEqual(2.8, result, 0.001);
        }

        // Тест 3: месяц без осадков — должен вернуть 0.0
        TEST_METHOD(TestMonthEmpty)
        {
            Precipitation data[2];
            data[0] = { 1, 1, 0.5, "снег" };
            data[1] = { 3, 3, 1.2, "дождь" };
            double result = process(data, 2, 2);
            Assert::AreEqual(0.0, result, 0.001);
        }
    };
}