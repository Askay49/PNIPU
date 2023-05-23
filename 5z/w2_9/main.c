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

	char nameFileInput[SIZE_NAMEFILE]; //имена файлов
	char nameFileOutput[SIZE_NAMEFILE];

	FILE *fileInput; //указатели на сами файлы
	FILE *fileOutput;
	char str[SIZE], newstr[SIZE]; //строка из файла и новая обработанная
	newstr[0] = '\0';			  //делаем строку пустой

	printf("Введите название исходного файла (не больше %d символов):", SIZE_NAMEFILE);
	fgets(nameFileInput, SIZE_NAMEFILE, stdin);		 //ввод названия входного файла
	nameFileInput[strlen(nameFileInput) - 1] = '\0'; //убрать последний символ, он там \n
	fileInput = fopen(nameFileInput, "r");			 // открывание файла, r - для чтения
	if (fileInput == NULL)							 //если не открылся выдать ошибку и вырубить прогу
	{
		printf("Error opening");
		return -1;
	}
	printf("Введите название файла для записи:"); //все тоже самое
	fgets(nameFileOutput, SIZE_NAMEFILE, stdin);
	nameFileOutput[strlen(nameFileOutput) - 1] = '\0';
	fileOutput = fopen(nameFileOutput, "w"); // w - для редактирования
	if (fileOutput == NULL)
	{
		printf("Error opening");
		return -1;
	}

	//****************************************************************
	char *estr;
	while (1)
	{
		estr = fgets(str, SIZE, fileInput); //ввод строки из файла в ношу строку

		if (estr == NULL) //если закончились строки прерываем цикл
			break;
		file_processing(str, newstr); //выполняем нашу функцию по обработке строк
		fprintf(fileOutput, newstr);  //и вписываем в новый файл
	}

	//****************************************************************
	fclose(fileInput); //закрываем файлы
	fclose(fileOutput);
}

int file_processing(char *input, char *output)
{
	char buffer[SIZE]; //буфер
	buffer[0] = '\0';
	strcat(buffer, input); //вписываем в буфер входную строку

	int count = 0, count2 = 0;			//первый счетчик считает слова, сторой сколько слов равной длины
	char *token = strtok(input, " \n"); //фунция поиска слов

	int len = strlen(token); //длина слова первого
	output[0] = '\0';
	while (token) //цикл пока у нас есть слова
	{
		int lenWord = strlen(token); //длина слова
		count++;
		if (lenWord == len) //если длина слова равна длине первого слова, добавляем второй счетчик
			count2++;
		token = strtok(NULL, " \n"); //обновляем слово
	}

	if (count2 == count) //если счетчики равны, добавляем !
	{
		strcat(output, "!");
	}
	strcat(output, buffer); //и добавляем буфер в новую строку
}
