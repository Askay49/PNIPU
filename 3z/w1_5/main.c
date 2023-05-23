#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int s, int *m);//������� ������ ������� � �������
void Input(int *size, int *autoFlag);//������� ����� ������ (��� ��� � �����)

int main()
{
	int *matrix;//��������� - ���� �������
	int size = 0, autoFlag;//������ ������� � ����� �����
	system("chcp 1251");//��� �������� �����
	system("cls");//��� ��������
	srand(time(0));//���� �������� �������

	Input(&size, &autoFlag);//������ ��������

	matrix = (int *)malloc(size * size * sizeof(int));//������ ������ �������

	if (autoFlag == 1)//���� ��������
	{
		for (int i = 0; i < size; i++)//���� �� �������
		{
			for (int j = 0; j < size; j++)//���� �� ��������
			{
				*(matrix + i * size + j) = rand() % 201 - 100;//��������� �������� �� -100 �� 100
			}
		}
	}
	else if (autoFlag == 0)//������ ����
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

	printMatrix(size, matrix);//������� �������

	for (int i = 0; i < size * 3; i++)//���� ����������� ���������� 
	{
		int k = 0;//���� ����� ���������� �������� � ������
		for (int j = size - 1; j > 0; j--)//���� �� ����� �������
		{
			if (*(matrix + j * size) > *(matrix + (j - 1) * size))//���� ���� �������� ������ ����������
			{
				k = *(matrix + j * size);//���������� ���� �����
				*(matrix + j * size) = *(matrix + (j - 1) * size);//������ �� ��� ����� ���������
				*(matrix + (j - 1) * size) = k;//��������� ����� ������������ � �����������
			}
		}
		for (int j = 0; j < size - 1; j++)//���� �� ������� ������
		{
			if (*(matrix + j) > *(matrix + (j + 1)))
			{
				k = *(matrix + j);
				*(matrix + j) = *(matrix + (j + 1));
				*(matrix + (j + 1)) = k;
			}
		}

		for (int j = 0; j < size - 1; j++)//���� �� ������ �������
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

	printMatrix(size, matrix);//������ ��� ��������������� �������

	int max = *(matrix + size + 1);//����� ���� ������������ � ����������� �����
	int min = *(matrix + size + 1);

	for (int i = 0; i < size; i++)//���� �� �������
	{
		for (int j = 0; j < size; j++)//���� �� ��������
		{
			if (j != 0 && j != size - 1 && i != 0)//���� ������� �� 0, ���� ������� �� ���������, ���� ������ �� 0
			{
				if (*(matrix + i * size + j) > max)//���� �������� ������ ������ �������������
					max = *(matrix + i * size + j);//���������
				if (*(matrix + i * size + j) < min)//���� �������� ������ ������ ������������
					min = *(matrix + i * size + j);//���������
			}
		}
	}
	int flag = 0;//��� ����� ���������� ����� ������������ ��� ����������� ��� ���

	for (int i = 0, j = 0; i < size; i++, j++)//���� �� ���������
	{
		if (*(matrix + i * size + j) == max)//���� ����� ����� �������������
		{
			printf("������� ��������� �������� max: [%d][%d] = %d\n\n", i, j, max);//�������
			flag = 1;//����������
		}
		if (*(matrix + i * size + j) == min)//���� ����� � ���������
		{
			printf("������� ��������� �������� min: [%d][%d] = %d\n\n", i, j, min);
			flag = 1;
		}
	}
	if (flag == 0)//���� �� ����� ���� ��� ���
		printf("������� ��������� �� �������� max ��� min");

	free(matrix);//����������� ������ �� �������
	return 0;
}

void Input(int *size, int *autoFlag)//������� �����
{
	while (1)
	{
		printf("������� ������ ���������� ������� �� 1 �� 8: ");
		scanf("%d", &*size);//����
		if (*size <= 8 && *size >= 1)//���� � ������ ���������� ���� ������
		{
			printf("\n");
			break;
		}
		else//���� �� ���, ���������� ������ ������
			printf("�� �����, ����� �� ����� \n\n");
	}
	while (1)
	{
		printf("�������� ������ ����� (1-��������� ��������, 0-������ ����): ");
		scanf("%d", &*autoFlag);

		if (*autoFlag == 1 || *autoFlag == 0)//���� ����� � ������� �����
		{
			printf("\n");
			break;
		}
		else
			printf("�� �����, ����� �� ����� \n\n");
	}
}

void printMatrix(int s, int *m)//������� ������ �������
{
	for (int i = 0; i < s; i++)//���� �� �������
	{
		printf("|");
		for (int j = 0; j < s; j++)//���� �� ��������
		{
			printf("%4d ", *(m + i * s + j)); //������� �������� ������� 4 ����������
		}
		printf("|\n");
	}
	printf("\n");
	return 0;
}