#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#define SIZE 256		 //максимальный размер строки в файле
#define SIZE_NAMEFILE 20 //максимальный размер названия файлов

int file_processing(char *input, char *output); //функция обработки строк в файле

int main(void)
{
	char nameFileInput[SIZE_NAMEFILE]; //имена файлов
	char nameFileOutput[SIZE_NAMEFILE];

	FILE *fileInput; //указатели на сами файлы
	FILE *fileOutput;

	char str[SIZE], newstr[SIZE]; //строка из файла и отредактированная строка
	newstr[0] = '\0';			  //обнуляем новую строку на всякий случай

	printf("Введите название исходного файла (не больше %d символов):", SIZE_NAMEFILE);
	fgets(nameFileInput, SIZE_NAMEFILE, stdin);		 //вводим название файла (не забывать про расширение(.txt))
	nameFileInput[strlen(nameFileInput) - 1] = '\0'; //убираем последний символ(он там перевод строки(\n))
	fileInput = fopen(nameFileInput, "r");			 //открываем файл, r-для чтения
	if (fileInput == NULL)							 //если не смогли открыть выдаем ошибку
	{
		printf("Error opening");
		return -1;
	}
	printf("Введите название файла для записи:");
	fgets(nameFileOutput, SIZE_NAMEFILE, stdin);
	nameFileOutput[strlen(nameFileOutput) - 1] = '\0';
	fileOutput = fopen(nameFileOutput, "w"); //тут тоже самое но открыванием для редактирования - w
	if (fileOutput == NULL)
	{
		printf("Error opening");
		return -1;
	}

	//****************************************************************
	char *estr;
	while (1)
	{
		estr = fgets(str, SIZE, fileInput); //вводим строку из файла в нашу строку

		if (estr == NULL) //если закончился файл, прерываем цикл
			break;

		file_processing(str, newstr); //передаем функции наши строки
		fprintf(fileOutput, newstr);  //вводим отредактированную строку в новый файл
	}

	//****************************************************************
	fclose(fileInput); //закрываем файлы
	fclose(fileOutput);
}

int file_processing(char *input, char *output)
{
	output[0] = '\0';		 //на всякий случай обнуляем выходную строку
	int len = strlen(input); //длина входной строки
	int flag = 0;			 //запоминает, если слово начинается с цифры
	char *token = NULL;		 //указатель на слова в строке

	if (isdigit(input[0])) //если первый первый символ цифра
		flag = 1;		   //заопминаем это

	token = strtok(input, " \n"); //ищем первое слово в строке (оно ищется либо до пробела, либо до перевода строки(второй параметр))

	for (int i = 0; i < len; i++) //цикл по всей строке
	{

		if (input[i] == ' ')	 //если символ пробел
			strcat(output, " "); //просто вводим его в новую строку
		else					 //иначе
		{
			int len_word = strlen(token); //длина слова
			if (flag == 0)				  //если не с цифры была строка
			{
				strcat(output, token);		 //добавляем слово
				strcat(output, " ");		 //и пробел в новую строку
				i += len_word;				 //и смещаем цикл на длину этого слова
				token = strtok(NULL, " \n"); //а также обновляем слово в указателе
			}
			else //если же строка началась с цифры
			{
				strcat(output, "(");		 //добавляем скобку
				strcat(output, token);		 //потом слово
				strcat(output, ") ");		 //и снова скобку
				i += len_word;				 //также смещаем цикл на длину слова
				token = strtok(NULL, " \n"); //и обновляем указатель
			}
		}
	}
	strcat(output, "\n"); //в конце добавляем перевод строки
}
