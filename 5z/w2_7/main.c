#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define SIZE 256//���� ������ ������
#define SIZE_NAMEFILE 20//���� ������ �������� �����

int file_processing(char *input, char *output);//������� ��������� ������

int main(void)
{
	system("chcp 1251");
	system("cls");

	char nameFileInput[SIZE_NAMEFILE];//����� ������
	char nameFileOutput[SIZE_NAMEFILE];

	FILE *fileInput;//��������� �� �����
	FILE *fileOutput;
	char str[SIZE], newstr[SIZE];//������
	newstr[0] = '\0';

	printf("������� �������� ��������� ����� (�� ������ %d ��������):", SIZE_NAMEFILE);
	fgets(nameFileInput, SIZE_NAMEFILE, stdin);//������ �������� �����
	nameFileInput[strlen(nameFileInput) - 1] = '\0';//������� ������� ������ ��������� ��������
	fileInput = fopen(nameFileInput, "r");//��������� ���� ��� ������
	if (fileInput == NULL)//� ���������� �������� ������ ������
	{
		printf("Error opening");
		return -1;
	}
	printf("������� �������� ����� ��� ������:");
	fgets(nameFileOutput, SIZE_NAMEFILE, stdin);
	nameFileOutput[strlen(nameFileOutput) - 1] = '\0';
	fileOutput = fopen(nameFileOutput, "w");//���� ����� �� ���� ���� ��������� � ������������ ��������������
	if (fileOutput == NULL)
	{
		printf("Error opening");
		return -1;
	}

	//****************************************************************
	char *estr;
	while (1)
	{
		estr = fgets(str, SIZE, fileInput);//����� ������ �� �����

		if (estr == NULL)//���� ����� ����������� ������� �� �����
			break;

		file_processing(str, newstr);//�������� � ������� ������
		fprintf(fileOutput, newstr);//������� ����� ������ � ����� ����
	}

	//****************************************************************
	fclose(fileInput);//����������� ������
	fclose(fileOutput);
}

int file_processing(char *input, char *output)
{
	output[0] = '\0';
	char buffer[SIZE];//������
	char number[5];
	buffer[0] = '\0';
	strcat(buffer, input);//���������� � ������ ������� ������
	int flag = 0;
	char *token = NULL;//��������� �� �����

	token = strtok(input, " \n");
	int count = 0;
	while (token)
	{
		int len_word = strlen(token);//����� �����
		if (len_word>count)
		{
			count = len_word;
		}
		token = strtok(NULL, " \n");
	}
	sprintf(number, " %i", count);
	buffer[strlen(buffer)-1]= '\0';
	number[strlen(number)]= '\n';
	number[4]= '\0';
	strcat(output, buffer);
	strcat(output, number);
}
	