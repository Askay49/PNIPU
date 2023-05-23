#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SIZE 10

int main()
{
	system("chcp 1251");
	system("cls");
	srand(time(0));

	int array[SIZE], autoFlag, i = 0, count = 0, max = 0;
	float number = 0;

	printf("Выберите режим работы (0 - ручной ввод, 1 - случайные числа) : ");
	scanf("%d", &autoFlag);
	printf("\n");

	if (autoFlag == 1)
	{
		while (i < SIZE)
		{
			array[i] = rand() % 201 - 100;
			i++;
		}
	}
	else if (autoFlag == 0)
	{
		while (i < SIZE)
		{
			if (i == 0)
				printf("Введите элементы массива:\n");
			scanf("%d", &array[i]);
			i++;
		}
	}
	printf("Массив: ");
	for (int t = 0; t <= SIZE - 1; t++)
	{
		if (t == 0)
			printf("%d", array[t]);
		else
			printf(", %d", array[t]);
	}
	printf("\n\n");

	for (int t = 0; t <= SIZE - 1; t++)
	{
		number += array[t];
		count++;
	}
	number = number / count;
	printf("Среднее арифмитическое чисел: %f\n", number);

	float diff = fabs(number - array[0]);
	for (int t = 0; t <= SIZE - 1; t++)
	{
		if (fabs(number - array[t]) > diff)
		{
			diff = fabs(number - array[t]);
			max = array[t];
		}
	}
	printf("Результат: %d\n", max);
}