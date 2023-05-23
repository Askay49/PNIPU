#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#define SIZE 256		 //������������ ������ ������ � �����
#define SIZE_NAMEFILE 20 //������������ ������ �������� ������

int file_processing(char *input, char *output); //������� ��������� ����� � �����

int main(void)
{
	char nameFileInput[SIZE_NAMEFILE]; //����� ������
	char nameFileOutput[SIZE_NAMEFILE];

	FILE *fileInput; //��������� �� ���� �����
	FILE *fileOutput;

	char str[SIZE], newstr[SIZE]; //������ �� ����� � ����������������� ������
	newstr[0] = '\0';			  //�������� ����� ������ �� ������ ������

	printf("������� �������� ��������� ����� (�� ������ %d ��������):", SIZE_NAMEFILE);
	fgets(nameFileInput, SIZE_NAMEFILE, stdin);		 //������ �������� ����� (�� �������� ��� ����������(.txt))
	nameFileInput[strlen(nameFileInput) - 1] = '\0'; //������� ��������� ������(�� ��� ������� ������(\n))
	fileInput = fopen(nameFileInput, "r");			 //��������� ����, r-��� ������
	if (fileInput == NULL)							 //���� �� ������ ������� ������ ������
	{
		printf("Error opening");
		return -1;
	}
	printf("������� �������� ����� ��� ������:");
	fgets(nameFileOutput, SIZE_NAMEFILE, stdin);
	nameFileOutput[strlen(nameFileOutput) - 1] = '\0';
	fileOutput = fopen(nameFileOutput, "w"); //��� ���� ����� �� ����������� ��� �������������� - w
	if (fileOutput == NULL)
	{
		printf("Error opening");
		return -1;
	}

	//****************************************************************
	char *estr;
	while (1)
	{
		estr = fgets(str, SIZE, fileInput); //������ ������ �� ����� � ���� ������

		if (estr == NULL) //���� ���������� ����, ��������� ����
			break;

		file_processing(str, newstr); //�������� ������� ���� ������
		fprintf(fileOutput, newstr);  //������ ����������������� ������ � ����� ����
	}

	//****************************************************************
	fclose(fileInput); //��������� �����
	fclose(fileOutput);
}

int file_processing(char *input, char *output)
{
	output[0] = '\0';		 //�� ������ ������ �������� �������� ������
	int len = strlen(input); //����� ������� ������
	int flag = 0;			 //����������, ���� ����� ���������� � �����
	char *token = NULL;		 //��������� �� ����� � ������

	if (isdigit(input[0])) //���� ������ ������ ������ �����
		flag = 1;		   //���������� ���

	token = strtok(input, " \n"); //���� ������ ����� � ������ (��� ������ ���� �� �������, ���� �� �������� ������(������ ��������))

	for (int i = 0; i < len; i++) //���� �� ���� ������
	{

		if (input[i] == ' ')	 //���� ������ ������
			strcat(output, " "); //������ ������ ��� � ����� ������
		else					 //�����
		{
			int len_word = strlen(token); //����� �����
			if (flag == 0)				  //���� �� � ����� ���� ������
			{
				strcat(output, token);		 //��������� �����
				strcat(output, " ");		 //� ������ � ����� ������
				i += len_word;				 //� ������� ���� �� ����� ����� �����
				token = strtok(NULL, " \n"); //� ����� ��������� ����� � ���������
			}
			else //���� �� ������ �������� � �����
			{
				strcat(output, "(");		 //��������� ������
				strcat(output, token);		 //����� �����
				strcat(output, ") ");		 //� ����� ������
				i += len_word;				 //����� ������� ���� �� ����� �����
				token = strtok(NULL, " \n"); //� ��������� ���������
			}
		}
	}
	strcat(output, "\n"); //� ����� ��������� ������� ������
}
