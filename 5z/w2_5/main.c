#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define SIZE 256//макс размер строки
#define SIZE_NAMEFILE 20//макс размер названия файла

int file_processing(char *input, char *output);//функция обработки строки

int main(void)
{
	system("chcp 1251");
	system("cls");

	char nameFileInput[SIZE_NAMEFILE];//имена файлов
	char nameFileOutput[SIZE_NAMEFILE];

	FILE *fileInput;//указатели на файлы
	FILE *fileOutput;
	char str[SIZE], newstr[SIZE];//строки
	newstr[0] = '\0';

	printf("Введите название исходного файла (не больше %d символов):", SIZE_NAMEFILE);
	fgets(nameFileInput, SIZE_NAMEFILE, stdin);//вводим название файла
	nameFileInput[strlen(nameFileInput) - 1] = '\0';//убираем перевод строки последним символом
	fileInput = fopen(nameFileInput, "r");//открываем файл для чтения
	if (fileInput == NULL)//в непонятнйо ситуации выдаем ошибку
	{
		printf("Error opening");
		return -1;
	}
	printf("Введите название файла для записи:");
	fgets(nameFileOutput, SIZE_NAMEFILE, stdin);
	nameFileOutput[strlen(nameFileOutput) - 1] = '\0';
	fileOutput = fopen(nameFileOutput, "w");//тоже самое но этот файл открываем с возможностью редактирования
	if (fileOutput == NULL)
	{
		printf("Error opening");
		return -1;
	}

	//****************************************************************
	char *estr;
	while (1)
	{
		estr = fgets(str, SIZE, fileInput);//берем строку из файла

		if (estr == NULL)//если слова закончились выходим из цикла
			break;

		file_processing(str, newstr);//передаем в функцию строки
		fprintf(fileOutput, newstr);//вбиваем новую строку в новый файл
	}

	//****************************************************************
	fclose(fileInput);//освобождаем память
	fclose(fileOutput);
}

int file_processing(char *input, char *output)
{
	output[0] = '\0';
	char buffer[SIZE];//буффер
	buffer[0] = '\0';
	strcat(buffer, input);//запоминаем в буффер входную строку
	int flag = 0;
	char *token = NULL;//указатель на слова

	token = strtok(input, " \n");

	while (token)
	{
		int len_word = strlen(token);//длина слова
		if (token[0] == token[len_word - 1])//если 1 символ равен последнему
		{
			flag = 1;//запоминаем
			break;
		}
		token = strtok(NULL, " \n");
	}
	if (flag)//если условие в цикле хоть раз выполнилось
		strcat(output, "!");//добавляем в начале строки !
	strcat(output, buffer);
}
