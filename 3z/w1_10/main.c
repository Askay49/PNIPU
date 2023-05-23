#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int s, int *m);	  //функция вывода матрицы(написана в конце)
void Input(int *size, int *autoFlag); //функция ввода значений(написана в конце)

int main()
{
	int *matrix;			//сама матрица
	int size = 0, autoFlag; //размер матрицы и переменная выбора режима ввода
	srand(time(0));			//точка отсчета рандома

	Input(&size, &autoFlag); //водим значения

	matrix = (int *)malloc(size * size * sizeof(int)); //определяем размер матрицы
	//(по сути (int*) - это размер ячеек)
	//size * size * sizeof(int) это количество памяти которое надо выделить (размер матрицы * размер переменной типа int)

	if (autoFlag == 1) //если авто ввод
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				*(matrix + i * size + j) = rand() % 201 - 100; //заполняем случайными значениями
			}
		}
	}
	else if (autoFlag == 0) // если ручной ввод
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

	for (int t = 0; t < size * 3; t++) //сортировка пузырьковая
	{
		//в таком виде записи матрицы i - это строка, j - это столбец
		//по сути это строка, в которой i*size это смещение на размер матрицы (на одну строку квадратной матрицы)
		int k = 0; //сюда будем запоминать значение, по сути буфер

		for (int j = 0; j < size - 1; j++) //сортируем верхнюю строку
		{
			if (*(matrix + j) > *(matrix + (j + 1)))
			{
				k = *(matrix + j);
				*(matrix + j) = *(matrix + (j + 1));
				*(matrix + (j + 1)) = k;
			}
		}
		for (int j = size - 1, i = 0; i < size - 1; i++, j--) //сортируем побочную диагональ
		{
			if (*(matrix + i * size + j) > *(matrix + (i + 1) * size + (j - 1)))
			{
				k = *(matrix + i * size + j);
				*(matrix + i * size + j) = *(matrix + (i + 1) * size + (j - 1));
				*(matrix + (i + 1) * size + (j - 1)) = k;
			}
		}
		for (int j = 0; j < size - 1; j++) //сортируем нижнюю строку
		{
			if (*(matrix + (size - 1) * size + j) > *(matrix + (size - 1) * size + (j + 1)))
			{
				k = *(matrix + (size - 1) * size + j);
				*(matrix + (size - 1) * size + j) = *(matrix + (size - 1) * size + (j + 1));
				*(matrix + (size - 1) * size + (j + 1)) = k;
			}
		}
	}

	printf("\n");

	printMatrix(size, matrix);	   //выводим матрциу
	int count = 0;				   //запоминаем были ли повторения в столбцах
	int flag = 0;				   //флаг который нам позволит выйти из второго цикла (чтобы 2 раза не выводилось сообщение о повторении)
	for (int j = 0; j < size; j++) //цикл по столбцам
	{
		for (int t = 1; t < size - 1; t++) //этот цикл нужен чтобы запоминать значение
		{
			int replay = *(matrix + t * size + j);

			for (int i = 1; i < size - 1; i++) //цикл по строкам
			{
				if (*(matrix + i * size + j) == replay && i != t && i + j != size - 1 && t + j != size - 1) //если нашли повторение и это не сортированное число
				{
					printf("Повторение в столбце %d\n ", j + 1); //выводим что есть повторение
					count++;									 //запоминаем что оно было
					flag = 1;									 //флаг в 1, чтобы выйти из следующего цикла
					break;										 //прерываем этот цикл
				}
			}
			if (flag) //если флаг ==1
			{
				flag = 0; //устанавливаем флаг в 0
				break;	  //выходим из этого цикла
			}
		}
	}
	if (count == 0) //если повторений не было, выводим что их не было
		printf("Повторений нет");
	free(matrix); //освобождаем память матрицы
	return 0;
}

void Input(int *size, int *autoFlag) //функция ввода значений
{
	while (1) //бесконечный цикл
	{
		printf("Введите размер от 1 до 8: ");
		scanf("%d", &*size);
		if (*size <= 8 && *size >= 1) //если ввели от 1 до 8
		{
			printf("\n");
			break; //выходим из цикла
		}
		else //если же другое значение, отправляем на повторный ввод и говорим что так нельзя
			printf("Ошибка \n\n");
	}
	while (1)
	{
		printf("Выберите режим ввода (1-Авто, 0-Ручной): ");
		scanf("%d", &*autoFlag);

		if (*autoFlag == 1 || *autoFlag == 0) //если 0 или 1 выходим из цикла
		{
			printf("\n");
			break;
		}
		else //если же левое значение отправляем на повтор
			printf("Ошибка \n\n");
	}
}

void printMatrix(int s, int *m) //функция вывода матрицы
{
	for (int i = 0; i < s; i++) //цикл по строкам
	{
		printf("|");
		for (int j = 0; j < s; j++) //цикл по столбцам
		{
			printf("%4d ", *(m + i * s + j)); //вывод значения выделяем 4 знакоместа
		}
		printf("|\n");
	}
	printf("\n");
	return 0;
}