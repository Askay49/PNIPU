#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int s, int *m);	  //функция вывода матрицы
void Input(int *size, int *autoFlag); //функция ввода значений, они написаны в конце

int main()
{
	int *matrix; //сама матрица как указатель (чтобы можно было динамически менять размер)
	int size = 0, autoFlag;
	system("chcp 1251"); //для русского языка
	system("cls");		 //для русского языка
	srand(time(0));		 //точка отсчета рандома от времени

	Input(&size, &autoFlag); //вводим значения через функцию

	matrix = (int *)malloc(size * size * sizeof(int)); //задаем размер матрицы

	if (autoFlag == 1) //если автоматический ввод
	{
		for (int i = 0; i < size; i++) //цикл по строкам
		{
			for (int j = 0; j < size; j++) //цикл по столбцам
			{
				*(matrix + i * size + j) = rand() % 201 - 100; //значения от -100 до 100
			}
		}
	}
	else if (autoFlag == 0) //если ручной ввод заполняем сами
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				printf("a[%d][%d] = ", i, j);
				scanf("%d", (matrix + i * size + j)); //ввод значения
			}
		}
		printf("\n");
	}

	printMatrix(size, matrix); //выводим матрицу

	for (int c = 0; c < size; c++) //цикл повторяющий пузырьковую сортировку
	{
		int k = *(matrix); //сюда будем запоминать число
		int i = 0, j = 0;
		for (i = 0, j = 0; i < size - 1; i++, j++) //цикл по главной диагонали
		{
			if (*(matrix + i * size + j) > *(matrix + (i + 1) * size + (j + 1))) //если следующее в диагонали число больше предыдущего
			{
				k = *(matrix + i * size + j);									 //запоминаем наше число
				*(matrix + i * size + j) = *(matrix + (i + 1) * size + (j + 1)); //ставим на место нашего числа следующее (котоое было больше)
				*(matrix + (i + 1) * size + (j + 1)) = k;						 //ставим на место большего числа то которое запомнили
			}
		}
		for (j = 0; j < size - 2; j++) //цикл по столбцам (не трогает последние 2)
		{
			for (i = 1; i < size - 1; i++) //цикл по строкам
			{
				if (*(matrix + i * size + j) > *(matrix + (i + 1) * size + j) && j < i) //тот же принцип сортировки что и в диагонали
				{
					k = *(matrix + i * size + j);
					*(matrix + i * size + j) = *(matrix + (i + 1) * size + j);
					*(matrix + (i + 1) * size + j) = k;
				}
			}
		}
	}

	printMatrix(size, matrix); //выводим матрицу уже отсортированную

	int max = *(matrix);		   //сюда будем запоминать максимальное число
	for (int i = 0; i < size; i++) //цикл по строкам
	{
		for (int j = 0; j < size; j++) //цикл по столбцам
		{
			if (j <= i) //если число выше главной диагонали
			{
				if (*(matrix + i * size + j) > max) //проверяем больше ли оно чем прошлое максимальное
					max = *(matrix + i * size + j); //если больше запоминаем
			}
		}
	}
	printf("Максимальное среди сортированных: %d\n\n", max); //выводим максимальное

	free(matrix); //освобождаем память матрицы
	return 0;
}

void Input(int *size, int *autoFlag) //функция ввода значений
{
	while (1) //бесконечный цикл
	{
		printf("Выберите размер матрицы от 1 до 8: ");
		scanf("%d", &*size);		  //вводим размер матрицы
		if (*size <= 8 && *size >= 1) //если ввели от 1 до 8
		{
			printf("\n");
			break; //выходим из цикла
		}
		else
			printf("Ошибка \n\n"); //если ввели не от 1 до 8 выдаем ошибку и отправляем заного вводить значение
	}
	while (1) //бесконечный цикл
	{
		printf("Выберите режим ввода, 1-автоматический, 0-ручной): ");
		scanf("%d", &*autoFlag); //выодим режим ввода

		if (*autoFlag == 1 || *autoFlag == 0) //если это 0 или 1 выходим из цикла
		{
			printf("\n");
			break;
		}
		else
			printf("Ошибка \n\n"); //если не 0 или 1 выдаем ошибку и отправляем заного вводить значение
	}
}

void printMatrix(int s, int *m) //функция вывода матрицы
{
	for (int i = 0; i < s; i++) //цикл по строкам
	{
		printf("|");
		for (int j = 0; j < s; j++) //цикл по столбцам
		{
			printf("%4d ", *(m + i * s + j)); //выводим число выделяя 4 знакоместа
		}
		printf("|\n");
	}
	printf("\n");
}