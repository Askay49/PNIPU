#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int s, int *m);//функция вывода матрицы в консоль
void Input(int *size, int *autoFlag);//функция ввода данных (они обе в конце)

int main()
{
	int *matrix;//указатель - наша матрица
	int size = 0, autoFlag;//размер матрицы и режим ввода
	system("chcp 1251");//для русского языка
	system("cls");//длу русского
	srand(time(0));//точк аотсчета рандома

	Input(&size, &autoFlag);//вводим значения

	matrix = (int *)malloc(size * size * sizeof(int));//задаем размер матрицы

	if (autoFlag == 1)//если автоввод
	{
		for (int i = 0; i < size; i++)//цикл по строкам
		{
			for (int j = 0; j < size; j++)//цикл по столбцам
			{
				*(matrix + i * size + j) = rand() % 201 - 100;//случайное значение от -100 до 100
			}
		}
	}
	else if (autoFlag == 0)//ручной ввод
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

	printMatrix(size, matrix);//выводим матрицу

	for (int i = 0; i < size * 3; i++)//цикл повторяющий сортировку 
	{
		int k = 0;//сюда будем запоминать значение в ячейке
		for (int j = size - 1; j > 0; j--)//цикл по левой стороне
		{
			if (*(matrix + j * size) > *(matrix + (j - 1) * size))//если наше значение больше следующего
			{
				k = *(matrix + j * size);//запоминаем наше число
				*(matrix + j * size) = *(matrix + (j - 1) * size);//ставим на его место следующее
				*(matrix + (j - 1) * size) = k;//следующее число приравниваем к запомненому
			}
		}
		for (int j = 0; j < size - 1; j++)//цикл по верхней строке
		{
			if (*(matrix + j) > *(matrix + (j + 1)))
			{
				k = *(matrix + j);
				*(matrix + j) = *(matrix + (j + 1));
				*(matrix + (j + 1)) = k;
			}
		}

		for (int j = 0; j < size - 1; j++)//цикл по правой стороне
		{
			if (*(matrix + j * size + size - 1) > *(matrix + (j + 1) * size + size - 1))
			{
				k = *(matrix + j * size + size - 1);
				*(matrix + j * size + size - 1) = *(matrix + (j + 1) * size + size - 1);
				*(matrix + (j + 1) * size + size - 1) = k;
			}
		}
	}

	printf("\n");

	printMatrix(size, matrix);//выводи уже отсортированную матрицу

	int max = *(matrix + size + 1);//здесь буду макисмальное и минимальное число
	int min = *(matrix + size + 1);

	for (int i = 0; i < size; i++)//цикл по строкам
	{
		for (int j = 0; j < size; j++)//цикл по столбцам
		{
			if (j != 0 && j != size - 1 && i != 0)//если столбец не 0, если столбец не последний, если строка не 0
			{
				if (*(matrix + i * size + j) > max)//если значение больше нашего максимального
					max = *(matrix + i * size + j);//обновляем
				if (*(matrix + i * size + j) < min)//если значение меньше нашего минимального
					min = *(matrix + i * size + j);//обновляем
			}
		}
	}
	int flag = 0;//тут будем запоминать нашли максимальное или минимальное или нет

	for (int i = 0, j = 0; i < size; i++, j++)//цикл по диагонали
	{
		if (*(matrix + i * size + j) == max)//если число равно максимальному
		{
			printf("Главная диагональ содержит max: [%d][%d] = %d\n\n", i, j, max);//выводим
			flag = 1;//запоминаем
		}
		if (*(matrix + i * size + j) == min)//тоже самое с минимумом
		{
			printf("Главная диагональ содержит min: [%d][%d] = %d\n\n", i, j, min);
			flag = 1;
		}
	}
	if (flag == 0)//если не нашли макс или мин
		printf("Главная диагональ не содержит max или min");

	free(matrix);//освобождаем память от матрицы
	return 0;
}

void Input(int *size, int *autoFlag)//функция ввода
{
	while (1)
	{
		printf("Введите размер квадратной матрицы от 1 до 8: ");
		scanf("%d", &*size);//ввод
		if (*size <= 8 && *size >= 1)//если в нужных диапозонах идем дальше
		{
			printf("\n");
			break;
		}
		else//если же нет, заставляем заного ввести
			printf("Всё фигня, давай по новой \n\n");
	}
	while (1)
	{
		printf("Выберите режима ввода (1-случайные значения, 0-ручной ввод): ");
		scanf("%d", &*autoFlag);

		if (*autoFlag == 1 || *autoFlag == 0)//тоже самое с режимом ввода
		{
			printf("\n");
			break;
		}
		else
			printf("Всё фигня, давай по новой \n\n");
	}
}

void printMatrix(int s, int *m)//функция вывода матрицы
{
	for (int i = 0; i < s; i++)//цикл по строкам
	{
		printf("|");
		for (int j = 0; j < s; j++)//цикл по столбцам
		{
			printf("%4d ", *(m + i * s + j)); //выводим значение выделяя 4 знакоместа
		}
		printf("|\n");
	}
	printf("\n");
	return 0;
}