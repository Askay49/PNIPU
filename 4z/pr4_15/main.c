#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256

int check_word(char *word)//������� �������� �����
{
	int mid = strlen(word) / 2;//����� �����
	char mid_ch = word[mid];//������ � ������ �����
	int count = 0;//�������
	for (int i = 0; i < strlen(word); i++)//���� �� �����
	{
		if (word[i] == mid_ch)//���� ������ ����� ������������
		{
			count++;//���������� �������
		}
	}
	if (count == 3)//���� �� ����� 3 (��� �����������+��� 2 ����)
		return 1;//������� ������ 1
	return 0;//����� 0
}

int main(void)
{
	system("chcp 1251");//��� �������� �����
	system("cls");
	char str[SIZE], newstr[SIZE];//������
	char *token = NULL;//��������� �� �����

	printf("������� ������: ");

	fgets(str, SIZE, stdin);//���� ������
	newstr[0] = '\0';//�� ������ ������ ������ ������
	token = strtok(str, " \n");//������� strtok ���� ����� ������ �� �������� ��������� ������ ���������� � ����������

	while (token)//���� ���� ��������� �� ����� 0
	{
		int len = strlen(token);//����� �����

		if (len % 2 == 1 && check_word(token))//���� ����� �������� ����� � ������� ������� 1
		{
			strcat(newstr, token);//��������� � ����� ������ �����
			strcat(newstr, " ");//� ������
		}
		token = strtok(NULL, " \n");//��������� � ������� ������ ���������� NULL �� �� ��������� � ����� ��� ��� ���������
	}

	printf("���������: %s\n", newstr);//�������
	return 0;
}