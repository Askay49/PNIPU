#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int s, int *m);
void Input(int *size, int *autoFlag);

int main()
{
	int *matrix;
	int size = 0, autoFlag;
	system("chcp 1251");
	system("cls");
	srand(time(0));

	Input(&size, &autoFlag);

	matrix = (int *)malloc(size * size * sizeof(int));

	if (autoFlag == 1)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				*(matrix + i * size + j) = rand() % 201 - 100;
			}
		}
	}
	else if (autoFlag == 0)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				printf("a[%d][%d] = ", i, j);
				scanf("%d", (matrix + i * size + j));
			}
		}
		printf("\n");
	}

	printMatrix(size, matrix);

	for (int c = 0; c < size * 2; c++)
	{
		int k = 0;
		int j = 0;
		for (int i = 0; i < size - 1; i++)
		{
			if (*(matrix + i * size + j) > *(matrix + i * size + (j + 1)))
			{
				k = *(matrix + i * size + j);
				*(matrix + i * size + j) = *(matrix + i * size + (j + 1));
				*(matrix + i * size + (j + 1)) = k;
			}
			if (*(matrix + i * size + (j + 1)) > *(matrix + (i + 1) * size + (j + 1)))
			{
				k = *(matrix + i * size + (j + 1));
				*(matrix + i * size + (j + 1)) = *(matrix + (i + 1) * size + (j + 1));
				*(matrix + (i + 1) * size + (j + 1)) = k;
			}
			j++;
		}
	}

	int max = *(matrix + 1 * size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (j != i && j != (i + 1))
			{
				if (*(matrix + i * size + j) > max)
					max = *(matrix + i * size + j);
			}
		}
	}

	printMatrix(size, matrix);

	if (size != 1)
		printf("Максимальное число среди несортированных: %d\n\n", max);
	else
		printf("Несортированных чисел нет");

	free(matrix);
	return 0;
}

void Input(int *size, int *autoFlag)
{
	while (1)
	{
		printf("Введите размер квадратной матрицы от 1 до 8: ");
		scanf("%d", &*size);
		if (*size <= 8 && *size >= 1)
		{
			printf("\n");
			break;
		}
		else
			printf("Всё фигня, давай по новой \n\n");
	}
	while (1)
	{
		printf("Выберите режима ввода (1-случайные значения, 0-ручной ввод): ");
		scanf("%d", &*autoFlag);

		if (*autoFlag == 1 || *autoFlag == 0)
		{
			printf("\n");
			break;
		}
		else
			printf("Всё фигня, давай по новой \n\n");
	}
}

void printMatrix(int s, int *m)
{
	for (int i = 0; i < s; i++)
	{
		printf("|");
		for (int j = 0; j < s; j++)
		{
			printf("%4d ", *(m + i * s + j)); //*(m + i * s + j));
		}
		printf("|\n");
	}
	printf("\n");
	return 0;
}