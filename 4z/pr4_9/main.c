#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256

int check_word(char *str) //������� �������� �����
{
	int n = 0, m = strlen(str) - 1;

	while (n < m) //� ����� n - ��� ����� � ������ �����, m - ��� � ����� �����, ���� �� ������
		if (str[n++] != str[m--])
			return 0; //���� ����� �� ����������� �����, ���������� 0

	return 1; //���� ��� ��������� ���������� ����
}

int main(void)
{
	system("chcp 1251"); //��� �������� �����
	system("cls");
	char str[SIZE], newstr[SIZE]; //����� ��������� � ���������������
	char *token = NULL;			  //���� �� ����� ���������� �����

	printf("������� ������: ");

	fgets(str, SIZE, stdin);	//���� ������
	newstr[0] = '\0';			//������ ����� ������ ������
	token = strtok(str, " \n"); //������� ������ ����, ��� 1 �������� ������ � ������� ������, ������ ������� ����������� ����

	while (token) //���� ���� ���� �����
	{
		if (check_word(token)) //���� ������� ���� ������� 1, ������� ����������
		{
			strcat(newstr, token); //�� ��������� � ����� ������ �����
			strcat(newstr, " ");   //� ������
		}
		token = strtok(NULL, " \n"); //���� ����� �����
	}

	printf("���������: %s\n", newstr); //������� ����� ������
	return 0;
}