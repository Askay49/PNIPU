#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256		 //������������ ������ ������
#define SIZE_NAMEFILE 20 //������������ ������ ����� ������

int file_processing(char *input, char *output); //������� ��������� ����

int count = 1; //������� �����

int main(void)
{
	system("chcp 1251"); //��� �������� �����
	system("cls");

	char nameFileInput[SIZE_NAMEFILE]; //����� ������
	char nameFileOutput[SIZE_NAMEFILE];

	FILE *fileInput; //��������� �� ���� �����
	FILE *fileOutput;
	char str[SIZE], newstr[SIZE]; //������ �� ����� � ����������������� ������
	newstr[0] = '\0';			  //�� ������ ������ �������� �������� ������

	printf("������� �������� ��������� ����� (�� ������ %d ��������):", SIZE_NAMEFILE); //������ ��� ����� (�� �������� ��� ���������� (.txt))
	fgets(nameFileInput, SIZE_NAMEFILE, stdin);											//��� ����
	nameFileInput[strlen(nameFileInput) - 1] = '\0';									//������� ��������� ������, �� ��� ������� ������(\n)
	fileInput = fopen(nameFileInput, "r");												//��������� ���� r - ��� ������
	if (fileInput == NULL)																//���� �� �������� ������ ������
	{
		printf("Error opening");
		return -1;
	}
	printf("������� �������� ����� ��� ������:"); //���� ����� ��� ��������� �����
	fgets(nameFileOutput, SIZE_NAMEFILE, stdin);
	nameFileOutput[strlen(nameFileOutput) - 1] = '\0';
	fileOutput = fopen(nameFileOutput, "w"); //w - ��� ��������������
	if (fileOutput == NULL)
	{
		printf("Error opening");
		return -1;
	}

	//****************************************************************
	char *estr;
	while (1) //����������� ����
	{
		estr = fgets(str, SIZE, fileInput); //����� ������ �� �����

		if (estr == NULL) //���� ������ ����������� ������� �� �����
			break;

		file_processing(str, newstr); //�������� ������� ������
		fprintf(fileOutput, newstr);  //������ ����� ������ � �������� ����
	}

	//****************************************************************
	fclose(fileInput); //��������� �����
	fclose(fileOutput);
}

int file_processing(char *input, char *output)
{
	int word_count = 1;		 //������� ����
	int len = strlen(input); //����� ������

	output[0] = '\0'; //�� ������ ������ ������� �������� ������

	if (count % 2 == 0) //���� ������ ������
	{
		char *token = NULL;			  //��������� �� �����
		token = strtok(input, " \n"); //����� ������ �����
		for (int i = 0; i < len; i++) //���� �� ������
		{
			int len_word = strlen(token);				 //����� �����
			if (input[i] == ' ')						 //���� ������ ������
				strcat(output, " ");					 //������ ��� � ����� ������
			else if (input[i] != ' ' && word_count != 3) //���� �� ������ � ��� �� ������ �����
			{
				if (word_count != 1)		 //���� �� ������ �����
					strcat(output, " ");	 //��������� ������
				strcat(output, token);		 //������ ����� � ������
				i += len_word;				 //������� ���� �� ����� �����
				word_count++;				 //��������� ������� ����
				token = strtok(NULL, " \n"); //����� ��������� �����
			}
			else if (word_count == 3) //���� ��� 3 �����
			{
				i += len_word;				 //������� ���� �� ��� �����
				word_count++;				 //��������� �������
				token = strtok(NULL, " \n"); //����� ��������� �����
			}
		}
		strcat(output, "\n"); //��������� ������� ������
	}
	else
	{
		strcat(output, input); //���� ��� �������� ������ ������ ������ ��
	}

	count++; //��������� ������� �����
}
