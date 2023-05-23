#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256

int check_word(char *word)//функция проверки слова
{
	int mid = strlen(word) / 2;//центр слова
	char mid_ch = word[mid];//символ в центре слова
	int count = 0;//счетчик
	for (int i = 0; i < strlen(word); i++)//цикл по слову
	{
		if (word[i] == mid_ch)//если символ равен центральному
		{
			count++;//прибавляем счетчик
		}
	}
	if (count == 3)//если он равен 3 (сам центральный+еще 2 раза)
		return 1;//функция вернет 1
	return 0;//иначе 0
}

int main(void)
{
	system("chcp 1251");//для русского языка
	system("cls");
	char str[SIZE], newstr[SIZE];//строки
	char *token = NULL;//указатель на слова

	printf("Введите строку: ");

	fgets(str, SIZE, stdin);//ввод строки
	newstr[0] = '\0';//на всякий случай чистим строку
	token = strtok(str, " \n");//функция strtok ищет часть строки до символов указанных вторым параметром и запоминает

	while (token)//цикл пока указатель не будет 0
	{
		int len = strlen(token);//длина слова

		if (len % 2 == 1 && check_word(token))//если слово нечетной длины и функция вернула 1
		{
			strcat(newstr, token);//добавляем в новую строку слово
			strcat(newstr, " ");//и пробел
		}
		token = strtok(NULL, " \n");//передавая в функция первым параметром NULL мы ее запускаем с места где она закончила
	}

	printf("Результат: %s\n", newstr);//выводим
	return 0;
}