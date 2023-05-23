#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256

int check_word(char *str) //функция проверки слова
{
	int n = 0, m = strlen(str) - 1;

	while (n < m) //в цикле n - это буквы с начала слова, m - это с конца слова, идем до центра
		if (str[n++] != str[m--])
			return 0; //если нашли не совпадающие буквы, возвращаем 0

	return 1; //если все совпадает возвращаем один
}

int main(void)
{
	system("chcp 1251"); //для русского языка
	system("cls");
	char str[SIZE], newstr[SIZE]; //стрка начальная и отфильтрованная
	char *token = NULL;			  //сюда мы будем запоминать слова

	printf("Введите строку: ");

	fgets(str, SIZE, stdin);	//ввод строки
	newstr[0] = '\0';			//делаем новую строку пустой
	token = strtok(str, " \n"); //функция поиска слов, где 1 параметр строка в которой искать, второй символы разделители слов

	while (token) //цикл пока есть слова
	{
		if (check_word(token)) //если функция выше вернула 1, условие выполнится
		{
			strcat(newstr, token); //то добавляем к новой строке слово
			strcat(newstr, " ");   //и пробел
		}
		token = strtok(NULL, " \n"); //ищем новое слово
	}

	printf("Результат: %s\n", newstr); //выводим новую строку
	return 0;
}