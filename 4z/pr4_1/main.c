#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256

int check_word(char *word) //������� �������� ����� (���������� ������)
{
	for (int i = 0; i < (strlen(word) - 1); i++) //���� �� �����
	{
		if (word[i] > word[i + 1]) //���� ��������� ������� ������ ��������� �����
			return 0;			   //���������� ����
	}
	return 1; //���� ������� �� ���� �� ��������� �� �����, ���������� �������
}

int main(void)
{
	system("chcp 1251");		  //��� �������� �����
	system("cls");				  //��� �������� �����
	char str[SIZE], newstr[SIZE]; //������ ��������� � ���������������
	char *token = NULL;			  //���������, ������� ����� � ���� ������� �����

	printf("������� ������: ");

	fgets(str, SIZE, stdin);	//���� ������ � ������������ �� ����� (SIZE)
	newstr[0] = '\0';			//������ ����� ������ ������(�� ������ ������)
	token = strtok(str, " \n"); //������� strtok ���� � ��������� ������ ������� ��������� ������ ���������� (������ ��� ������� ������) � �� ��� ����� ���������� � ���������

	while (token) //���� ���� ��������� �� ������ ������, �.�. ���� � ����� ���� �����
	{
		int len;
		len = strlen(token); //����� �����

		if (check_word(token)) //��� �� �������� ������� �������� �����
		{
			strcat(newstr, token); //���� �������� ������ ��������� ����� � ����� ������
			strcat(newstr, " ");   //� ��������� ������ � ����� ������
		}
		token = strtok(NULL, " \n"); //����� � ���� ������� ������ �������� NULL, ����� ���������� � ������� ��� ���������� ����������, �.�. �� ��������� ����� ����
	}

	printf("���������: %s\n", newstr); //������� ���������
	return 0;
}
