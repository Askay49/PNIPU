#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int s, int *m);	  //������� ������ �������(�������� � �����)
void Input(int *size, int *autoFlag); //������� ����� ��������(�������� � �����)

int main()
{
	int *matrix;			//���� �������
	int size = 0, autoFlag; //������ ������� � ���������� ������ ������ �����
	srand(time(0));			//����� ������� �������

	Input(&size, &autoFlag); //����� ��������

	matrix = (int *)malloc(size * size * sizeof(int)); //���������� ������ �������
	//(�� ���� (int*) - ��� ������ �����)
	//size * size * sizeof(int) ��� ���������� ������ ������� ���� �������� (������ ������� * ������ ���������� ���� int)

	if (autoFlag == 1) //���� ���� ����
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				*(matrix + i * size + j) = rand() % 201 - 100; //��������� ���������� ����������
			}
		}
	}
	else if (autoFlag == 0) // ���� ������ ����
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				printf("a[%d][%d] = ", i, j);
				scanf("%d", (matrix + i * size + j)); //������ ����
			}
		}
		printf("\n");
	}

	printMatrix(size, matrix); //������� �������

	for (int t = 0; t < size * 3; t++) //���������� �����������
	{
		//� ����� ���� ������ ������� i - ��� ������, j - ��� �������
		//�� ���� ��� ������, � ������� i*size ��� �������� �� ������ ������� (�� ���� ������ ���������� �������)
		int k = 0; //���� ����� ���������� ��������, �� ���� �����

		for (int j = 0; j < size - 1; j++) //��������� ������� ������
		{
			if (*(matrix + j) > *(matrix + (j + 1)))
			{
				k = *(matrix + j);
				*(matrix + j) = *(matrix + (j + 1));
				*(matrix + (j + 1)) = k;
			}
		}
		for (int j = size - 1, i = 0; i < size - 1; i++, j--) //��������� �������� ���������
		{
			if (*(matrix + i * size + j) > *(matrix + (i + 1) * size + (j - 1)))
			{
				k = *(matrix + i * size + j);
				*(matrix + i * size + j) = *(matrix + (i + 1) * size + (j - 1));
				*(matrix + (i + 1) * size + (j - 1)) = k;
			}
		}
		for (int j = 0; j < size - 1; j++) //��������� ������ ������
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

	printMatrix(size, matrix);	   //������� �������
	int count = 0;				   //���������� ���� �� ���������� � ��������
	int flag = 0;				   //���� ������� ��� �������� ����� �� ������� ����� (����� 2 ���� �� ���������� ��������� � ����������)
	for (int j = 0; j < size; j++) //���� �� ��������
	{
		for (int t = 1; t < size - 1; t++) //���� ���� ����� ����� ���������� ��������
		{
			int replay = *(matrix + t * size + j);

			for (int i = 1; i < size - 1; i++) //���� �� �������
			{
				if (*(matrix + i * size + j) == replay && i != t && i + j != size - 1 && t + j != size - 1) //���� ����� ���������� � ��� �� ������������� �����
				{
					printf("���������� � ������� %d\n ", j + 1); //������� ��� ���� ����������
					count++;									 //���������� ��� ��� ����
					flag = 1;									 //���� � 1, ����� ����� �� ���������� �����
					break;										 //��������� ���� ����
				}
			}
			if (flag) //���� ���� ==1
			{
				flag = 0; //������������� ���� � 0
				break;	  //������� �� ����� �����
			}
		}
	}
	if (count == 0) //���� ���������� �� ����, ������� ��� �� �� ����
		printf("���������� ���");
	free(matrix); //����������� ������ �������
	return 0;
}

void Input(int *size, int *autoFlag) //������� ����� ��������
{
	while (1) //����������� ����
	{
		printf("������� ������ �� 1 �� 8: ");
		scanf("%d", &*size);
		if (*size <= 8 && *size >= 1) //���� ����� �� 1 �� 8
		{
			printf("\n");
			break; //������� �� �����
		}
		else //���� �� ������ ��������, ���������� �� ��������� ���� � ������� ��� ��� ������
			printf("������ \n\n");
	}
	while (1)
	{
		printf("�������� ����� ����� (1-����, 0-������): ");
		scanf("%d", &*autoFlag);

		if (*autoFlag == 1 || *autoFlag == 0) //���� 0 ��� 1 ������� �� �����
		{
			printf("\n");
			break;
		}
		else //���� �� ����� �������� ���������� �� ������
			printf("������ \n\n");
	}
}

void printMatrix(int s, int *m) //������� ������ �������
{
	for (int i = 0; i < s; i++) //���� �� �������
	{
		printf("|");
		for (int j = 0; j < s; j++) //���� �� ��������
		{
			printf("%4d ", *(m + i * s + j)); //����� �������� �������� 4 ����������
		}
		printf("|\n");
	}
	printf("\n");
	return 0;
}