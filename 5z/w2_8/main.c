#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256
#define SIZE_NAMEFILE 20

int file_processing(char *input, char *output); //объ€вление функции

int count = 1; //счетчик строк
int main(void)
{
	system("chcp 1251");
	system("cls");

	char nameFileInput[SIZE_NAMEFILE];	//им€ входного файла
	char nameFileOutput[SIZE_NAMEFILE]; //им€ выходного файла

	FILE *fileInput; //указатели на сам файл
	FILE *fileOutput;
	char str[SIZE], newstr[SIZE]; //строка из файла и обработана€ строка
	newstr[0] = '\0';			  //обнуление строки

	printf("¬ведите название исходного файла (не больше %d символов):", SIZE_NAMEFILE - 4);
	fgets(nameFileInput, SIZE_NAMEFILE - 4, stdin);	 //ввод названи€ входного файла
	nameFileInput[strlen(nameFileInput) - 1] = '\0'; //убрать последний символ, он там \n
	strcat(nameFileInput, ".txt");					 //тупо потому что мне лень вводить расширение посто€нно, можно переделать без него
	fileInput = fopen(nameFileInput, "r");			 // открывание файла, r - дл€ чтени€
	if (fileInput == NULL)							 //если не открылс€ выдать ошибку и вырубить прогу
	{
		printf("Error opening");
		return -1;
	}
	printf("¬ведите название файла дл€ записи:"); //все тоже самое
	fgets(nameFileOutput, SIZE_NAMEFILE - 4, stdin);
	nameFileOutput[strlen(nameFileOutput) - 1] = '\0';
	strcat(nameFileOutput, ".txt");
	fileOutput = fopen(nameFileOutput, "w"); // w - дл€ редактировани€
	if (fileOutput == NULL)
	{
		printf("Error opening");
		return -1;
	}

	//****************************************************************
	char *estr; //указатель
	while (1)	//бесконечный цикл
	{
		estr = fgets(str, SIZE, fileInput); //принимает в себ€ возвращаемое значение fgets

		if (estr == NULL) //если оно 0, то либо строки закончились, либо ошибка, выходим из цикла
			break;

		file_processing(str, newstr); //передаем в функцию строки(вход выход)
		fprintf(fileOutput, newstr);  //вводим в выходной файл обработанную строку
	}

	//****************************************************************
	fclose(fileInput); //закрываем файлы
	fclose(fileOutput);
}

int file_processing(char *input, char *output) //сама функци€ обработки строк
{

	int word_count = 0;
	// int skip = 0;
	int len = strlen(input); //длина строки

	output[0] = '\0'; //занул€ем строку

	if (count % 3 == 0) //каждую 3 строку
	{
		char buffer[SIZE];			  //буфер
		int max_len = 0;			  //переменна€ хран€ща€ длину слова самого длинного
		char *token = NULL;			  //указатель который будет хранить слова из строки
		token = strtok(input, " \n"); //передаем функции строку и массив символов, до которых искать слова

		while (token) //цикл пока есть слова
		{
			int len_word = strlen(token); //длина слова
			if (max_len < len_word)		  //если нашлось слово длинее
			{
				max_len = len_word;	   //приравниваем переменной эту длину
				buffer[0] = '\0';	   //чистим буфер
				strcat(buffer, token); //записываем в буфер это слово
			}

			token = strtok(NULL, " \n"); //когда первый аргумент 0, функци€ начинает с места где закончила, т.е. ищем новое слово
		}
		strcat(output, buffer); //вписать в новую строку буфер(самое длинное слово)
		strcat(output, "\n");	//и перевод строки
	}
	else
	{
		strcat(output, input); //если это не кажда€ 3 строка, то просто копируем строку
	}

	count++; //считаем строки
}
