#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#define SIZE 256 //����� ������

int check_word(char *str,int len) // ������� �������� ����� �� ��������
{
	int count = 0; //�������
	for (int i = 0; i < len/2;i++)//���� �� ������ �������� �����
		for (int j = len/2; j < len;j++)//���� �� ������ �������� �����
    		if (str[i] == str[j]) {//���� ������� ����������
      			count++;//���������� �������
      			break; //� ������� �� ����� �� ������ ��������
    		}
 	if (count!=len/2)//���� ������� �� ����� �������� ����� �����
    	return 0;//���������� 0, �.�. �� ��������� �������
	return 1;//���� �� ��� ��������� ���������� 1
}

int main(void)
{
	system("chcp 1251");//��� �������� �����, �������� ����� �������
	system("cls");//��� �������� �����, �������� ����� �������
	char str[SIZE], newstr[SIZE];// ������ ����������� � ���������������
	char *token = NULL;//���������, ������� ����� ������� ����� �� ������
	
	printf("������� ������: ");

	fgets(str, SIZE, stdin);//������ ������ � ������������ �� �����
	newstr[0] = '\0';//�� ������ ������ �������� ������
	token = strtok(str, " \n");//����� �������� � ����� ��� ������ ������� strtok, ������ ���������� ��������� �� ����� � ������ �� ������� ����������� �� ������� �� ������ ���������

	while (token)//���� ���� �� ���������� ����� � ������
	{
		int len = strlen(token);//����� �����

		if (len%2==0 && check_word(token,len))//���� ������ ����� � ������� �����������
		{
			strcat(newstr, token);//��������� � ����� ������ ��� �����
			strcat(newstr, " ");//� ������
		}
		token = strtok(NULL, " \n");//��������� ��������� �� ��������� �����
	}

	printf("���������: %s\n", newstr);//������� ����� ������
	return 0;
}
