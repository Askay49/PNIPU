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

	for (int i = 0; i < size * 5; i++)
	{
		int k = 0;

		for (int j = 0; j < size - 1; j++)
		{
			if (*(matrix + j) > *(matrix + (j + 1)))
			{
				k = *(matrix + j);
				*(matrix + j) = *(matrix + (j + 1));
				*(matrix + (j + 1)) = k;
			}
		}

		for (int j = 0; j < size - 1; j++)
		{
			if (*(matrix + j * size + size - 1) > *(matrix + (j + 1) * size + size - 1))
			{
				k = *(matrix + j * size + size - 1);
				*(matrix + j * size + size - 1) = *(matrix + (j + 1) * size + size - 1);
				*(matrix + (j + 1) * size + size - 1) = k;
			}
		}

		for (int j = size - 1; j > 0; j--)
		{
			if (*(matrix + (size - 1) * size + j) > *(matrix + (size - 1) * size + (j - 1)))
			{
				k = *(matrix + (size - 1) * size + j);
				*(matrix + (size - 1) * size + j) = *(matrix + (size - 1) * size + (j - 1));
				*(matrix + (size - 1) * size + (j - 1)) = k;
			}
		}

		for (int j = size - 1; j > 1; j--)
		{
			if (*(matrix + j * size) > *(matrix + (j - 1) * size))
			{
				k = *(matrix + j * size);
				*(matrix + j * size) = *(matrix + (j - 1) * size);
				*(matrix + (j - 1) * size) = k;
			}
		}
	}

	printf("\n");

	printMatrix(size, matrix);
	int count = 0;
	int flag = 0;
	for (int j = 0; j < size; j++)
	{
		for (int t = 0; t < size; t++)
		{
			int replay = *(matrix + t * size + j);

			for (int i = 0; i < size; i++)
			{
				if (*(matrix + i * size + j) == replay && i != t)
				{
					printf("Повторяющиеся числа в столбце %d\n ", j + 1);
					count++;
					flag = 1;
					break;
				}
			}
			if (flag)
			{
				flag = 0;
				break;
			}
		}
	}
	if (count == 0)
		printf("Повторяющихся чисел в столбцах не найдено");
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