#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256

int check_word(char *word)
{
	int mid = strlen(word) / 2;
	char mid_ch = word[mid];
	int count = 0;
	for (int i = 0; i < mid; i++)
		for (int j = mid; j < strlen(word); j++)
			if (word[i] == word[j])
				return 1;
	return 0;
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
		int len = strlen(token);

		if (len % 2 == 0 && check_word(token))
		{
			strcat(newstr, token);
			strcat(newstr, " ");
		}
		token = strtok(NULL, " \n");
	}

	printf("–езультат: %s\n", newstr);
	return 0;
}