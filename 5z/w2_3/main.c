#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256
#define SIZE_NAMEFILE 20

int file_processing(char *input, char *output);//объ€вл€етс€ функци€

int main(void)
{
	system("chcp 1251");//руский €зык
	system("cls");

	char nameFileInput[SIZE_NAMEFILE];//название файлов входного и выходного
	char nameFileOutput[SIZE_NAMEFILE];

	FILE *fileInput;//указатель на файл входной
	FILE *fileOutput;//и выходной
	char str[SIZE], newstr[SIZE];//строка куда будет записыватс€ строка из файла и строка котора€ будет вписыватс€ в новый файл
	newstr[0] = '\0';//на вс€кий случай очищаем строку

	printf("¬ведите название исходного файла (не больше %d символов):", SIZE_NAMEFILE);
	fgets(nameFileInput, SIZE_NAMEFILE, stdin);//вводим название с ограничением длины строки
	nameFileInput[strlen(nameFileInput) - 1] = '\0';//убираем символ перевода строки из конца названи€
	strcat(nameFileInput, ".txt");//добавл€ем к названию расширение .txt
	fileInput = fopen(nameFileInput, "r");//открываем файл дл€ чтени€
	if (fileInput == NULL)//если не открылс€ выдаем ошибку
	{
		printf("Error opening");
		return -1;
	}
	printf("¬ведите название файла дл€ записи:");
	fgets(nameFileOutput, SIZE_NAMEFILE, stdin);
	nameFileOutput[strlen(nameFileOutput) - 1] = '\0';
	strcat(nameFileOutput, ".txt");
	fileOutput = fopen(nameFileOutput, "w");//все тоже самое дл€ выходного файла только открываем дл€ записи 
	if (fileOutput == NULL)
	{
		printf("Error opening");
		return -1;
	}

	//****************************************************************
	char *estr;//указатель на строки в файле
	while (1)//бесконечный цикл
	{
		estr = fgets(str, SIZE, fileInput);//берем строку из файла

		if (estr == NULL)//если нет строки или кака€ то ошибка прерываем цикл
			break;

		file_processing(str, newstr);//вызываем функцию котора€ в конце кода
		fprintf(fileOutput, newstr);//записываем в выходной файл новую строку
	}

	//****************************************************************
	fclose(fileInput);//закрываем оба файла
	fclose(fileOutput);
}

int file_processing(char *input, char *output)
{
	output[0] = '\0';//на вс€кий случай чистим строку
	int len = strlen(input);//длина строки
	char *token = NULL;//указатель на слова в строке (пока что пустой)

	token = strtok(input, " \n");//берем первое слово из строки

	for (int i = 0; i < len; i++)//цикл по строке посимвольно
	{

		if (input[i] == ' ')//если символ пробел
			strcat(output, " ");//добавл€ем в новую строку пробел
		else//иначе
		{
			int len_word = strlen(token);//длина слова
			if (len_word > 2)//если она больше 2
			{
				strcat(output, token);//добавл€ем слово в новую строку
				strcat(output, " ");//и пробел
				i += len_word;//добавл€ем к i длину слова (перескакиваем слово в цикле)
				token = strtok(NULL, " \n");//обновл€ем слово в указателе на следующее
			}
			else//если же длина слова меньше 2
			{
				strcat(output, " ");//добавл€ем пробел
				i += len_word;//перескакиваем слово в цикле
				token = strtok(NULL, " \n");//обновл€ем слово в указателе
			}
		}
	}
	strcat(output, "\n");//добавл€ем перевод строки в строку
}
