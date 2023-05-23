#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SIZE 30

int main()
{
	system("chcp 1251");
	system("cls");
	srand(time(0));

	int array[SIZE], autoFlag, min = 0;
	float number = 0;

	printf("Выберите режим работы (0 - ручной ввод, 1 - случайные числа) : ");
	scanf("%d", &autoFlag);
	printf("\n");

	if (autoFlag == 1)
	{
		for (int i = 0; i < SIZE; i++)
		{
			array[i] = rand() % 201 - 100;
		}
	}
	else if (autoFlag == 0)
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (i == 0)
				printf("Введите элементы массива:\n");
			scanf("%d", &array[i]);
		}
	}
	printf("Массив: ");
	for (int i = 0; i < SIZE; i++)
	{
		if (i == 0)
			printf("%d", array[i]);
		else
			printf(", %d", array[i]);
	}
	printf("\n\n");

	for (int i = 0; i < SIZE; i++)
	{
		number += array[i];
	}
	number = number / SIZE;
	printf("Среднее арифмитическое чисел: %f\n", number);

	float diff = fabs(number - array[0]);
	for (int t = 0; t <= SIZE - 1; t++)
	{
		if (fabs(number - array[t]) < diff)
		{
			diff = fabs(number - array[t]);
			min = array[t];
		}
	}
	printf("Бллижайшее число к среднему: %d\n", min);
}