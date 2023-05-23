#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256
#define SIZE_NAMEFILE 20

int file_processing(char *input, char *output); //���������� �������

int count = 1; //������� �����
int main(void)
{
	system("chcp 1251");
	system("cls");

	char nameFileInput[SIZE_NAMEFILE];	//��� �������� �����
	char nameFileOutput[SIZE_NAMEFILE]; //��� ��������� �����

	FILE *fileInput; //��������� �� ��� ����
	FILE *fileOutput;
	char str[SIZE], newstr[SIZE]; //������ �� ����� � ����������� ������
	newstr[0] = '\0';			  //��������� ������

	printf("������� �������� ��������� ����� (�� ������ %d ��������):", SIZE_NAMEFILE - 4);
	fgets(nameFileInput, SIZE_NAMEFILE - 4, stdin);	 //���� �������� �������� �����
	nameFileInput[strlen(nameFileInput) - 1] = '\0'; //������ ��������� ������, �� ��� \n
	strcat(nameFileInput, ".txt");					 //���� ������ ��� ��� ���� ������� ���������� ���������, ����� ���������� ��� ����
	fileInput = fopen(nameFileInput, "r");			 // ���������� �����, r - ��� ������
	if (fileInput == NULL)							 //���� �� �������� ������ ������ � �������� �����
	{
		printf("Error opening");
		return -1;
	}
	printf("������� �������� ����� ��� ������:"); //��� ���� �����
	fgets(nameFileOutput, SIZE_NAMEFILE - 4, stdin);
	nameFileOutput[strlen(nameFileOutput) - 1] = '\0';
	strcat(nameFileOutput, ".txt");
	fileOutput = fopen(nameFileOutput, "w"); // w - ��� ��������������
	if (fileOutput == NULL)
	{
		printf("Error opening");
		return -1;
	}

	//****************************************************************
	char *estr; //���������
	while (1)	//����������� ����
	{
		estr = fgets(str, SIZE, fileInput); //��������� � ���� ������������ �������� fgets

		if (estr == NULL) //���� ��� 0, �� ���� ������ �����������, ���� ������, ������� �� �����
			break;

		file_processing(str, newstr); //�������� � ������� ������(���� �����)
		fprintf(fileOutput, newstr);  //������ � �������� ���� ������������ ������
	}

	//****************************************************************
	fclose(fileInput); //��������� �����
	fclose(fileOutput);
}

int file_processing(char *input, char *output) //���� ������� ��������� �����
{

	int word_count = 0;
	// int skip = 0;
	int len = strlen(input); //����� ������

	output[0] = '\0'; //�������� ������

	if (count % 3 == 0) //������ 3 ������
	{
		char buffer[SIZE];			  //�����
		int max_len = 0;			  //���������� �������� ����� ����� ������ ��������
		char *token = NULL;			  //��������� ������� ����� ������� ����� �� ������
		token = strtok(input, " \n"); //�������� ������� ������ � ������ ��������, �� ������� ������ �����

		while (token) //���� ���� ���� �����
		{
			int len_word = strlen(token); //����� �����
			if (max_len < len_word)		  //���� ������� ����� ������
			{
				max_len = len_word;	   //������������ ���������� ��� �����
				buffer[0] = '\0';	   //������ �����
				strcat(buffer, token); //���������� � ����� ��� �����
			}

			token = strtok(NULL, " \n"); //����� ������ �������� 0, ������� �������� � ����� ��� ���������, �.�. ���� ����� �����
		}
		strcat(output, buffer); //������� � ����� ������ �����(����� ������� �����)
		strcat(output, "\n");	//� ������� ������
	}
	else
	{
		strcat(output, input); //���� ��� �� ������ 3 ������, �� ������ �������� ������
	}

	count++; //������� ������
}
