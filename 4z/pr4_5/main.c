#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256

int check_word(char *word)
{
	for (int i = 0; i < strlen(word); i++)
	{
		for (int j = 0; j < strlen(word); j++)
			if (word[i] == word[j] && i != j)
				return 1;
	}
	return 0;
}

int main(void)
{
	//system("chcp 1251");
	//system("cls");
	char str[SIZE], newstr[SIZE];
	char *token = NULL;

	printf("������� ������: ");

	fgets(str, SIZE, stdin);
	newstr[0] = '\0';
	token = strtok(str, " \n");

	while (token)
	{
		int len = strlen(token);

		if (check_word(token))
		{
			strcat(newstr, token);
			strcat(newstr, " ");
		}
		token = strtok(NULL, " \n");
	}

	printf("���������: %s\n", newstr);
	return 0;
}