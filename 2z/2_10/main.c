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

	int array[SIZE], autoFlag, count = 0, max = 0;
	float number = 0;

	printf("�������� ����� ������ (0 - ������ ����, 1 - ��������� �����) : ");
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
				printf("������� �������� �������:\n");
			scanf("%d", &array[i]);
		}
	}
	printf("������: ");
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
	printf("������� �������������� �����: %f\n", number);

	int number2;
	if (fabs(number - (int)number) > 0.5)
	{
		if (number > 0)
			number2 = (int)number + 1;
		else
			number2 = (int)number;
	}

	else if (fabs(number - (int)number) < 0.5)
	{
		if (number < 0)
			number2 = (int)number;
		else
			number2 = (int)number - 1;
	}

	for (int i = 0; i < SIZE; i++)
	{
		if (array[i] % number2 == 0)
		{
			count++;
		}
	}
	printf("���������: %d\n", count);
}