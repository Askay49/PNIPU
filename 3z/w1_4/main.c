#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int s, int *m);	  //функция вывода матрицы
void Input(int *size, int *autoFlag); //функция ввода значений (они описаны в конце)

int main()
{
	int *matrix;			//сама матрица (указатель)
	int size = 0, autoFlag; //размер и режим ввода
	system("chcp 1251");	//эти две строки для русского языка, если в код блоксе, то можно убрать их
	system("cls");			//, если в код блоксе, то можно убрать их
	srand(time(0));			//точка отсчета рандома

	Input(&size, &autoFlag); //ввод значений

	matrix = (int *)malloc(size * size * sizeof(int)); //задаем размер матрицы, по сути это строка размера size*size*на размер значения типа int

	if (autoFlag == 1) //в зависимости от выбраного режима заполняем матрицу
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				*(matrix + i * size + j) = rand() % 201 - 100; //случайные числа
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
				scanf("%d", (matrix + i * size + j)); //вводим сами
			}
		}
		printf("\n");
	}

	printMatrix(size, matrix); //выводим матрицу

	for (int t = 0; t < size * size + size; t++) //цикл для повторения сортировки
	{
		int k = 0;					   //буфер
		for (int j = 0; j < size; j++) //цикл по столбцам
		{
			if (j % 2 == 0) //если это столбец четный(они идут от 0)
			{
				for (int i = 0; i < size - 1; i++) //сортируем вниз
				{
					if (*(matrix + i * size + j) > *(matrix + (i + 1) * size + j))
					{
						k = *(matrix + i * size + j);
						*(matrix + i * size + j) = *(matrix + (i + 1) * size + j);
						*(matrix + (i + 1) * size + j) = k;
					}
					if (j != size - 1)																	 //кроме последнего столбца
						if (*(matrix + (size - 1) * size + j) > *(matrix + (size - 1) * size + (j + 1))) //сортируем значения между столбцами
						{
							k = *(matrix + (size - 1) * size + j);
							*(matrix + (size - 1) * size + j) = *(matrix + (size - 1) * size + (j + 1));
							*(matrix + (size - 1) * size + (j + 1)) = k;
						}
				}
			}
			else //для нечетных стобцов
			{
				for (int i = size - 1; i > 0; i--) //сортируем вверх
				{
					if (*(matrix + i * size + j) > *(matrix + (i - 1) * size + j))
					{
						k = *(matrix + i * size + j);
						*(matrix + i * size + j) = *(matrix + (i - 1) * size + j);
						*(matrix + (i - 1) * size + j) = k;
					}
					if (j != size - 1) //если не последний столбец соортируем между столбцами
						if (*(matrix + j) > *(matrix + (j + 1)))
						{
							k = *(matrix + j);
							*(matrix + j) = *(matrix + (j + 1));
							*(matrix + (j + 1)) = k;
						}
				}
			}
		}
	}

	printf("\n");

	printMatrix(size, matrix);	 //вывод матрицы
	int flag = 0;				 //переменная запоминающая что надо вывести
	int replay1[2] = {200, 200}; //два массива запоминающие положение пар
	int replay2[2] = {200, 200};
	for (int i = 0, j = 0; i < size; i++, j++) //цикл по главной диагонали
	{
		for (int t = 0, c = 0; t < size; t++, c++) //также по диагонали
		{
			if (i != t && j != c)										  //если циклы не на одном числе
				if (*(matrix + i * size + j) == *(matrix + t * size + c)) //если нашли равные числа в диагонали
				{
					if (flag == 0) //и у нас еще не было пар
					{
						flag = 1;		//запоминаем что есть пара
						replay1[0] = i; //запоминаем позиции чисел
						replay1[1] = j;
						replay2[0] = t;
						replay2[1] = c;
					}
					else if (i != replay1[0] && j != replay1[1] && t != replay1[0] && c != replay1[1] && i != replay2[0] && j != replay2[1] && t != replay2[0] && c != replay2[1]) //исключаем числа которые мы уже нашли
					{
						flag = 2; //если мы нашли еще одну пару, запоминаем
					}
				}
		}
	}

	if (flag == 1) //если нашли одну пару
		printf("Главная диагональ содержит одну пару одинаковых чисел\n");
	if (flag == 0) //если не нашли пар
		printf("Главная диагональ не содержит пару одинаковых чисел\n");
	if (flag == 2) //если нашли больше 1 пары
		printf("Главная диагональ содержит больше одной пары одинаковых чисел\n");
	free(matrix); //освобождаем место матрицы
}

void Input(int *size, int *autoFlag)
{
	while (1) //бесконечный цикл
	{
		printf("Введите размер квадратной матрицы от 1 до 8: ");
		scanf("%d", &*size);		  //вводим значение
		if (*size <= 8 && *size >= 1) //если ввели правильно, выходим из цикла
		{
			printf("\n");
			break;
		}
		else //если не правильно выдаем ошибку и все заного
			printf("Ошибка \n\n");
	}
	while (1) //также для режима ввода
	{
		printf("Выберите режима ввода (1-случайные значения, 0-ручной ввод): ");
		scanf("%d", &*autoFlag);

		if (*autoFlag == 1 || *autoFlag == 0)
		{
			printf("\n");
			break;
		}
		else
			printf("Ошибка \n\n");
	}
}

void printMatrix(int s, int *m) //вывод матрицы
{
	for (int i = 0; i < s; i++) //цикл по строкам
	{
		printf("|");
		for (int j = 0; j < s; j++) //цикл по столбцам
		{
			printf("%4d ", *(m + i * s + j)); //выводим значение, выделяем 4 знакоместа
		}
		printf("|\n");
	}
	printf("\n");
	return 0;
}