#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SIZE 100

int main()
{
	system("chcp 1251");
	system("cls");

	int array[SIZE], autoFlag, i = 0;

	printf("�������� ����� ������ (0 - ������ ����, 1 - ��������� �����) : ");
	scanf("%d", &autoFlag);
	printf("\n");

	if (autoFlag == 1)
	{
		while (i < SIZE)
		{
			array[i] = rand() % 201 - 100;
			i++;
		}
	}
	else if (autoFlag == 0)
	{
		while (i < SIZE)
		{
			if (i == 0)
				printf("������� �������� �������:\n");
			scanf("%d", &array[i]);
			i++;
		}
	}
	printf("������: ");
	for (int t = 0; t <= SIZE - 1; t++)
	{
		if (t == 0)
			printf("%d", array[t]);
		else
			printf(", %d", array[t]);
	}
	printf("\n\n");
	int count = 0, number = 0;
	for (int t = 0; t < SIZE; t++)
	{
		number += array[t];
		count++;
	}
	number = number / count;
	printf("������� �������������� �����: %d\n", number);
	int check = 0;
	for (int t = 0; t <= SIZE - 1; t++)
	{
		if (array[t] == number)
			check = 1;
	}
	if (check == 1)
		printf("���������: ����� �������\n");
	else
		printf("���������: ����� �� �������\n");
}