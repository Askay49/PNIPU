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

	for (int c = 0; c < size+1; c++)
	{
		int k = 0;
		int i = 0, j = 0;
		for (int t = 0; t < size - 1; t++)
		{
			for (i = t, j = 0; i < size; i++, j++)
			{
				if (*(matrix + i * size + j) > *(matrix + (i + 1) * size + (j + 1)))
				{
					k = *(matrix + i * size + j);
					*(matrix + i * size + j) = *(matrix + (i + 1) * size + (j + 1));
					*(matrix + (i + 1) * size + (j + 1)) = k;
				}
			}
		}
	}

	printMatrix(size, matrix);

	int min = *(matrix + size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (j <= i)
			{
				if (*(matrix + i * size + j) < min)
					min = *(matrix + i * size + j);
			}
		}
	}

	if (size != 1)
		printf("минимальное среди сортирвоанных: %d\n\n", min);
	else
		printf("нет сортированных значений");

	free(matrix);
	return 0;
}

void Input(int *size, int *autoFlag)
{
	while (1)
	{
		printf("введите размер матрицы от 1 до 8: ");
		scanf("%d", &*size);
		if (*size <= 8 && *size >= 1)
		{
			printf("\n");
			break;
		}
		else
			printf("ошибка \n\n");
	}
	while (1)
	{
		printf("выберите метод ввода, 1-авто, 0-ручной): ");
		scanf("%d", &*autoFlag);

		if (*autoFlag == 1 || *autoFlag == 0)
		{
			printf("\n");
			break;
		}
		else
			printf("ошибка \n\n");
	}
}

void printMatrix(int s, int *m)
{
	for (int i = 0; i < s; i++)
	{
		printf("|");
		for (int j = 0; j < s; j++)
		{
			printf("%4d ", *(m + i * s + j));
		}
		printf("|\n");
	}
	printf("\n");
	return 0;
}