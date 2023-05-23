#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

void printMatrix(int s, int *m);	  //������� ������ �������
void Input(int *size, int *autoFlag); //������� ����� �������� (��� ������� � �����)

int main()
{
	int *matrix;			//���� ������� (���������)
	int size = 0, autoFlag; //������ � ����� �����
	system("chcp 1251");	//��� ��� ������ ��� �������� �����, ���� � ��� ������, �� ����� ������ ��
	system("cls");			//, ���� � ��� ������, �� ����� ������ ��
	srand(time(0));			//����� ������� �������

	Input(&size, &autoFlag); //���� ��������

	matrix = (int *)malloc(size * size * sizeof(int)); //������ ������ �������, �� ���� ��� ������ ������� size*size*�� ������ �������� ���� int

	if (autoFlag == 1) //� ����������� �� ��������� ������ ��������� �������
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				*(matrix + i * size + j) = rand() % 201 - 100; //��������� �����
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
				scanf("%d", (matrix + i * size + j)); //������ ����
			}
		}
		printf("\n");
	}

	printMatrix(size, matrix); //������� �������

	for (int t = 0; t < size * size + size; t++) //���� ��� ���������� ����������
	{
		int k = 0;					   //�����
		for (int j = 0; j < size; j++) //���� �� ��������
		{
			if (j % 2 == 0) //���� ��� ������� ������(��� ���� �� 0)
			{
				for (int i = 0; i < size - 1; i++) //��������� ����
				{
					if (*(matrix + i * size + j) > *(matrix + (i + 1) * size + j))
					{
						k = *(matrix + i * size + j);
						*(matrix + i * size + j) = *(matrix + (i + 1) * size + j);
						*(matrix + (i + 1) * size + j) = k;
					}
					if (j != size - 1)																	 //����� ���������� �������
						if (*(matrix + (size - 1) * size + j) > *(matrix + (size - 1) * size + (j + 1))) //��������� �������� ����� ���������
						{
							k = *(matrix + (size - 1) * size + j);
							*(matrix + (size - 1) * size + j) = *(matrix + (size - 1) * size + (j + 1));
							*(matrix + (size - 1) * size + (j + 1)) = k;
						}
				}
			}
			else //��� �������� �������
			{
				for (int i = size - 1; i > 0; i--) //��������� �����
				{
					if (*(matrix + i * size + j) > *(matrix + (i - 1) * size + j))
					{
						k = *(matrix + i * size + j);
						*(matrix + i * size + j) = *(matrix + (i - 1) * size + j);
						*(matrix + (i - 1) * size + j) = k;
					}
					if (j != size - 1) //���� �� ��������� ������� ���������� ����� ���������
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

	printMatrix(size, matrix);	 //����� �������
	int flag = 0;				 //���������� ������������ ��� ���� �������
	int replay1[2] = {200, 200}; //��� ������� ������������ ��������� ���
	int replay2[2] = {200, 200};
	for (int i = 0, j = 0; i < size; i++, j++) //���� �� ������� ���������
	{
		for (int t = 0, c = 0; t < size; t++, c++) //����� �� ���������
		{
			if (i != t && j != c)										  //���� ����� �� �� ����� �����
				if (*(matrix + i * size + j) == *(matrix + t * size + c)) //���� ����� ������ ����� � ���������
				{
					if (flag == 0) //� � ��� ��� �� ���� ���
					{
						flag = 1;		//���������� ��� ���� ����
						replay1[0] = i; //���������� ������� �����
						replay1[1] = j;
						replay2[0] = t;
						replay2[1] = c;
					}
					else if (i != replay1[0] && j != replay1[1] && t != replay1[0] && c != replay1[1] && i != replay2[0] && j != replay2[1] && t != replay2[0] && c != replay2[1]) //��������� ����� ������� �� ��� �����
					{
						flag = 2; //���� �� ����� ��� ���� ����, ����������
					}
				}
		}
	}

	if (flag == 1) //���� ����� ���� ����
		printf("������� ��������� �������� ���� ���� ���������� �����\n");
	if (flag == 0) //���� �� ����� ���
		printf("������� ��������� �� �������� ���� ���������� �����\n");
	if (flag == 2) //���� ����� ������ 1 ����
		printf("������� ��������� �������� ������ ����� ���� ���������� �����\n");
	free(matrix); //����������� ����� �������
}

void Input(int *size, int *autoFlag)
{
	while (1) //����������� ����
	{
		printf("������� ������ ���������� ������� �� 1 �� 8: ");
		scanf("%d", &*size);		  //������ ��������
		if (*size <= 8 && *size >= 1) //���� ����� ���������, ������� �� �����
		{
			printf("\n");
			break;
		}
		else //���� �� ��������� ������ ������ � ��� ������
			printf("������ \n\n");
	}
	while (1) //����� ��� ������ �����
	{
		printf("�������� ������ ����� (1-��������� ��������, 0-������ ����): ");
		scanf("%d", &*autoFlag);

		if (*autoFlag == 1 || *autoFlag == 0)
		{
			printf("\n");
			break;
		}
		else
			printf("������ \n\n");
	}
}

void printMatrix(int s, int *m) //����� �������
{
	for (int i = 0; i < s; i++) //���� �� �������
	{
		printf("|");
		for (int j = 0; j < s; j++) //���� �� ��������
		{
			printf("%4d ", *(m + i * s + j)); //������� ��������, �������� 4 ����������
		}
		printf("|\n");
	}
	printf("\n");
	return 0;
}