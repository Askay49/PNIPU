#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256
#define SIZE_NAMEFILE 20

int file_processing(char *input, char *output);

int main(void)
{
	system("chcp 1251");
	system("cls");

	char nameFileInput[SIZE_NAMEFILE]; //����� ������
	char nameFileOutput[SIZE_NAMEFILE];

	FILE *fileInput; //��������� �� ���� �����
	FILE *fileOutput;
	char str[SIZE], newstr[SIZE]; //������ �� ����� � ����� ������������
	newstr[0] = '\0';			  //������ ������ ������

	printf("������� �������� ��������� ����� (�� ������ %d ��������):", SIZE_NAMEFILE);
	fgets(nameFileInput, SIZE_NAMEFILE, stdin);		 //���� �������� �������� �����
	nameFileInput[strlen(nameFileInput) - 1] = '\0'; //������ ��������� ������, �� ��� \n
	fileInput = fopen(nameFileInput, "r");			 // ���������� �����, r - ��� ������
	if (fileInput == NULL)							 //���� �� �������� ������ ������ � �������� �����
	{
		printf("Error opening");
		return -1;
	}
	printf("������� �������� ����� ��� ������:"); //��� ���� �����
	fgets(nameFileOutput, SIZE_NAMEFILE, stdin);
	nameFileOutput[strlen(nameFileOutput) - 1] = '\0';
	fileOutput = fopen(nameFileOutput, "w"); // w - ��� ��������������
	if (fileOutput == NULL)
	{
		printf("Error opening");
		return -1;
	}

	//****************************************************************
	char *estr;
	while (1)
	{
		estr = fgets(str, SIZE, fileInput); //���� ������ �� ����� � ���� ������

		if (estr == NULL) //���� ����������� ������ ��������� ����
			break;
		file_processing(str, newstr); //��������� ���� ������� �� ��������� �����
		fprintf(fileOutput, newstr);  //� ��������� � ����� ����
	}

	//****************************************************************
	fclose(fileInput); //��������� �����
	fclose(fileOutput);
}

int file_processing(char *input, char *output)
{
	char buffer[SIZE]; //�����
	buffer[0] = '\0';
	strcat(buffer, input); //��������� � ����� ������� ������

	int count = 0, count2 = 0;			//������ ������� ������� �����, ������ ������� ���� ������ �����
	char *token = strtok(input, " \n"); //������ ������ ����

	int len = strlen(token); //����� ����� �������
	output[0] = '\0';
	while (token) //���� ���� � ��� ���� �����
	{
		int lenWord = strlen(token); //����� �����
		count++;
		if (lenWord == len) //���� ����� ����� ����� ����� ������� �����, ��������� ������ �������
			count2++;
		token = strtok(NULL, " \n"); //��������� �����
	}

	if (count2 == count) //���� �������� �����, ��������� !
	{
		strcat(output, "!");
	}
	strcat(output, buffer); //� ��������� ����� � ����� ������
}
