#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256

int check_word(char *str)
{
	int n = 0, m;
	m = strlen(str) - 1;
	while (n < m)
		if (str[n++] != str[m--])
			return 0;

	return 1;
}

int main(void)
{
	system("chcp 1251");
	system("cls");
	char str[SIZE], newstr[SIZE];
	char *token = NULL;

	printf("¬ведите строку: ");

	fgets(str, SIZE, stdin);
	newstr[0] = '\0';
	token = strtok(str, " \n");

	while (token)
	{
		int len;
		len = strlen(token);

		if (check_word(token))
		{
			strcat(newstr, token);
			strcat(newstr, " ");
		}
		token = strtok(NULL, " \n");
	}

	printf("–езультат: %s\n", newstr);
	return 0;
}
