#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256
#define SIZE_NAMEFILE 20

int file_processing(char *input, char *output);

int flag = 0;
int count = 0;

int main(void)
{
	system("chcp 1251");
	system("cls");

	char nameFileInput[SIZE_NAMEFILE];
	char nameFileOutput[SIZE_NAMEFILE];

	FILE *fileInput;
	FILE *fileOutput;
	char str[SIZE], newstr[SIZE];
	newstr[0] = '\0';

	printf("¬ведите название исходного файла (не больше %d символов):", SIZE_NAMEFILE);
	fgets(nameFileInput, SIZE_NAMEFILE, stdin);
	nameFileInput[strlen(nameFileInput) - 1] = '\0';
	fileInput = fopen(nameFileInput, "r");
	if (fileInput == NULL)
	{
		printf("Error opening");
		return -1;
	}
	printf("¬ведите название файла дл€ записи:");
	fgets(nameFileOutput, SIZE_NAMEFILE, stdin);
	nameFileOutput[strlen(nameFileOutput) - 1] = '\0';
	fileOutput = fopen(nameFileOutput, "w");
	if (fileOutput == NULL)
	{
		printf("Error opening");
		return -1;
	}

	//****************************************************************
	char *estr;
	while (1)
	{
		estr = fgets(str, SIZE, fileInput);

		if (estr == NULL)
			break;

		file_processing(str, newstr);
		fprintf(fileOutput, newstr);
	}

	//****************************************************************
	fclose(fileInput);
	fclose(fileOutput);
}

int file_processing(char *input, char *output)
{
	output[0] = '\0';
	int len = strlen(input);
	char buffer[2];

	buffer[1] = '\0';

	if (flag == 0)
		count = 0;

	for (int i = 0; i < len; i++)
	{
		if (input[i] != ' ')
			count++;
		else
			count = 0;
		if (count <= 8)
		{
			buffer[0] = input[i];
			strcat(output, buffer);
		}
	}
	if (output[strlen(output) - 1] != '\n' && input[strlen(input) - 1] == '\n')
		strcat(output, "\n");

	if (output[strlen(output) - 1] != '\n' && output[strlen(output) - 1] != ' ')
		flag = 1;
	else
		flag = 0;
}
