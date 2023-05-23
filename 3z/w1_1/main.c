#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int s, int *m);	  //������� ������ �������
void Input(int *size, int *autoFlag); //������� ����� ��������, ��� �������� � �����

int main()
{
	int *matrix; //���� ������� ��� ��������� (����� ����� ���� ����������� ������ ������)
	int size = 0, autoFlag;
	system("chcp 1251"); //��� �������� �����
	system("cls");		 //��� �������� �����
	srand(time(0));		 //����� ������� ������� �� �������

	Input(&size, &autoFlag); //������ �������� ����� �������

	matrix = (int *)malloc(size * size * sizeof(int)); //������ ������ �������

	if (autoFlag == 1) //���� �������������� ����
	{
		for (int i = 0; i < size; i++) //���� �� �������
		{
			for (int j = 0; j < size; j++) //���� �� ��������
			{
				*(matrix + i * size + j) = rand() % 201 - 100; //�������� �� -100 �� 100
			}
		}
	}
	else if (autoFlag == 0) //���� ������ ���� ��������� ����
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				printf("a[%d][%d] = ", i, j);
				scanf("%d", (matrix + i * size + j)); //���� ��������
			}
		}
		printf("\n");
	}

	printMatrix(size, matrix); //������� �������

	for (int c = 0; c < size; c++) //���� ����������� ����������� ����������
	{
		int k = *(matrix); //���� ����� ���������� �����
		int i = 0, j = 0;
		for (i = 0, j = 0; i < size - 1; i++, j++) //���� �� ������� ���������
		{
			if (*(matrix + i * size + j) > *(matrix + (i + 1) * size + (j + 1))) //���� ��������� � ��������� ����� ������ �����������
			{
				k = *(matrix + i * size + j);									 //���������� ���� �����
				*(matrix + i * size + j) = *(matrix + (i + 1) * size + (j + 1)); //������ �� ����� ������ ����� ��������� (������ ���� ������)
				*(matrix + (i + 1) * size + (j + 1)) = k;						 //������ �� ����� �������� ����� �� ������� ���������
			}
		}
		for (j = 0; j < size - 2; j++) //���� �� �������� (�� ������� ��������� 2)
		{
			for (i = 1; i < size - 1; i++) //���� �� �������
			{
				if (*(matrix + i * size + j) > *(matrix + (i + 1) * size + j) && j < i) //��� �� ������� ���������� ��� � � ���������
				{
					k = *(matrix + i * size + j);
					*(matrix + i * size + j) = *(matrix + (i + 1) * size + j);
					*(matrix + (i + 1) * size + j) = k;
				}
			}
		}
	}

	printMatrix(size, matrix); //������� ������� ��� ���������������

	int max = *(matrix);		   //���� ����� ���������� ������������ �����
	for (int i = 0; i < size; i++) //���� �� �������
	{
		for (int j = 0; j < size; j++) //���� �� ��������
		{
			if (j <= i) //���� ����� ���� ������� ���������
			{
				if (*(matrix + i * size + j) > max) //��������� ������ �� ��� ��� ������� ������������
					max = *(matrix + i * size + j); //���� ������ ����������
			}
		}
	}
	printf("������������ ����� �������������: %d\n\n", max); //������� ������������

	free(matrix); //����������� ������ �������
	return 0;
}

void Input(int *size, int *autoFlag) //������� ����� ��������
{
	while (1) //����������� ����
	{
		printf("�������� ������ ������� �� 1 �� 8: ");
		scanf("%d", &*size);		  //������ ������ �������
		if (*size <= 8 && *size >= 1) //���� ����� �� 1 �� 8
		{
			printf("\n");
			break; //������� �� �����
		}
		else
			printf("������ \n\n"); //���� ����� �� �� 1 �� 8 ������ ������ � ���������� ������ ������� ��������
	}
	while (1) //����������� ����
	{
		printf("�������� ����� �����, 1-��������������, 0-������): ");
		scanf("%d", &*autoFlag); //������ ����� �����

		if (*autoFlag == 1 || *autoFlag == 0) //���� ��� 0 ��� 1 ������� �� �����
		{
			printf("\n");
			break;
		}
		else
			printf("������ \n\n"); //���� �� 0 ��� 1 ������ ������ � ���������� ������ ������� ��������
	}
}

void printMatrix(int s, int *m) //������� ������ �������
{
	for (int i = 0; i < s; i++) //���� �� �������
	{
		printf("|");
		for (int j = 0; j < s; j++) //���� �� ��������
		{
			printf("%4d ", *(m + i * s + j)); //������� ����� ������� 4 ����������
		}
		printf("|\n");
	}
	printf("\n");
}