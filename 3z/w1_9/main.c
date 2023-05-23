#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int s, int *m);
void Input(int *size, int *autoFlag);

int main()
{
	int *matrix;			//сама матрица
	int size = 0, autoFlag; //размер матрицы и переменная режима ввода
	system("chcp 1251");	//эти две строки меняют кодировку на русскую
	system("cls");			//если не надо, можешь удалить
	srand(time(0));

	Input(&size, &autoFlag); //функция ввода, она в конце прописана

	matrix = (int *)malloc(size * size * sizeof(int)); //создание матрицы, в ней i - это строка, j - это столбец

	if (autoFlag == 1) //способ заполнения матрицы 1-случайные числа
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				*(matrix + i * size + j) = rand() % 201 - 100;
			}
		}
	}
	else if (autoFlag == 0) // 0 - вручную
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

	printMatrix(size, matrix); //вывод матрицы

	for (int c = 0; c < size * 3; c++) //сортировка
	{
		int k = 0;

		for (int i = 0, j = 0; i < size; i++, j++) //этот цикл идет по диагонали
		{
			if (*(matrix + i * size + j) > *(matrix + (i + 1) * size + (j + 1)))
			{
				k = *(matrix + i * size + j);
				*(matrix + i * size + j) = *(matrix + (i + 1) * size + (j + 1));
				*(matrix + (i + 1) * size + (j + 1)) = k;
			}
		}
		for (int j = size - 1; j > 0; j--) //этот по нижней стороне
		{
			if (*(matrix + (size - 1) * size + j) > *(matrix + (size - 1) * size + (j - 1)))
			{
				k = *(matrix + (size - 1) * size + j);
				*(matrix + (size - 1) * size + j) = *(matrix + (size - 1) * size + (j - 1));
				*(matrix + (size - 1) * size + (j - 1)) = k;
			}
		}

		for (int j = size - 1; j > 1; j--) //этот по левой стороне
		{
			if (*(matrix + j * size) > *(matrix + (j - 1) * size))
			{
				k = *(matrix + j * size);
				*(matrix + j * size) = *(matrix + (j - 1) * size);
				*(matrix + (j - 1) * size) = k;
			}
		}
	}

	printMatrix(size, matrix); //вывод матрицы

	int min = *(matrix + size);	   //переменная хранящая минимальное значение
	for (int i = 0; i < size; i++) //поиск минимального значения
	{
		for (int j = 0; j < size; j++)
		{
			if (j != i && j != 0 && i != size - 1) //условие исключающее сортированные цисла
			{
				if (*(matrix + i * size + j) < min) //если нашли меньше, присваиваем
					min = *(matrix + i * size + j);
			}
		}
	}

	if (size != 1) //если матрица 1х1 несортированных не будет
		printf("минимальное среди не сортированных: %d\n\n", min);
	else
		printf("нет минимального");

	free(matrix);
	return 0;
}

void Input(int *size, int *autoFlag) //функция ввода
{
	while (1)
	{
		printf("введи от 1 до 8: ");
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
		printf("способ ввода, 1-автомат, 0-ручной): ");
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

void printMatrix(int s, int *m) //вывод матрицы
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