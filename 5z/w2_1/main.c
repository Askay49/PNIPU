#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256		 //максимальный размер строки
#define SIZE_NAMEFILE 20 //максимальный размер имени файлов

int file_processing(char *input, char *output); //функция обработки слов

int count = 1; //счетчик строк

int main(void)
{
	system("chcp 1251"); //для русского языка
	system("cls");

	char nameFileInput[SIZE_NAMEFILE]; //имена файлов
	char nameFileOutput[SIZE_NAMEFILE];

	FILE *fileInput; //указатели на сами файлы
	FILE *fileOutput;
	char str[SIZE], newstr[SIZE]; //строка из файла и отредактированная строка
	newstr[0] = '\0';			  //на всякий случай обнуляем выходную строку

	printf("Введите название исходного файла (не больше %d символов):", SIZE_NAMEFILE); //вводим имя файла (не забывать про расширение (.txt))
	fgets(nameFileInput, SIZE_NAMEFILE, stdin);											//сам ввод
	nameFileInput[strlen(nameFileInput) - 1] = '\0';									//удаляем последний символ, он там перевод строки(\n)
	fileInput = fopen(nameFileInput, "r");												//открываем файл r - для чтения
	if (fileInput == NULL)																//если не открылся выдаем ошибку
	{
		printf("Error opening");
		return -1;
	}
	printf("Введите название файла для записи:"); //тоже самое для выходного файла
	fgets(nameFileOutput, SIZE_NAMEFILE, stdin);
	nameFileOutput[strlen(nameFileOutput) - 1] = '\0';
	fileOutput = fopen(nameFileOutput, "w"); //w - для редактирования
	if (fileOutput == NULL)
	{
		printf("Error opening");
		return -1;
	}

	//****************************************************************
	char *estr;
	while (1) //бесконечный цикл
	{
		estr = fgets(str, SIZE, fileInput); //берем строку из файла

		if (estr == NULL) //если строки закончились выходим из цикла
			break;

		file_processing(str, newstr); //передаем функции строки
		fprintf(fileOutput, newstr);  //вводим новую строку в выходной файл
	}

	//****************************************************************
	fclose(fileInput); //закрываем файлы
	fclose(fileOutput);
}

int file_processing(char *input, char *output)
{
	int word_count = 1;		 //счетчик слов
	int len = strlen(input); //длина строки

	output[0] = '\0'; //на всякий случай очищаем выходную строку

	if (count % 2 == 0) //если строка четная
	{
		char *token = NULL;			  //указатель на слово
		token = strtok(input, " \n"); //берем первое слово
		for (int i = 0; i < len; i++) //цикл по строке
		{
			int len_word = strlen(token);				 //длина слова
			if (input[i] == ' ')						 //если символ пробел
				strcat(output, " ");					 //вводим его в новую строку
			else if (input[i] != ' ' && word_count != 3) //если не пробел и это не третье слово
			{
				if (word_count != 1)		 //если не первое слово
					strcat(output, " ");	 //добавляем пробел
				strcat(output, token);		 //вводим слово в строку
				i += len_word;				 //смещаем цикл на длину слова
				word_count++;				 //добавляем счетчик слов
				token = strtok(NULL, " \n"); //берем следующее слово
			}
			else if (word_count == 3) //если это 3 слово
			{
				i += len_word;				 //смещаем цикл на его длину
				word_count++;				 //добавляем счетчик
				token = strtok(NULL, " \n"); //берем следующее слово
			}
		}
		strcat(output, "\n"); //добавляем перевод строки
	}
	else
	{
		strcat(output, input); //если это нечетная строка просто вводим ее
	}

	count++; //добавляем счетчик строк
}
