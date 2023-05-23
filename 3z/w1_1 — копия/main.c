#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
//-----------------------Вариант 10----------------------------
//-------------------------Этап 1------------------------------
    system("chcp 1251");
	system("cls");
	srand(time(0));

	int size, Flag, i, j;
    printf("Введите размер квадратной матрицы от 1 до 8: ");
    scanf("%d", &size);
    printf("\n");
    int m[size][size];

    printf("Выберите режима ввода (1-случайные значения, 0-ручной ввод): ");
    scanf("%d", &Flag);
    printf("\n");
//-------------------------Этап 2------------------------------

    if (Flag == 1)
	{
        for (int i = 0; i < size; i++)
        {
            printf("|");
            for (int j = 0; j < size; j++)
            {
                m[i][j]=i+ rand()% (20 - 10 + 1);       //i * size + j
                printf("%3d ", m[i][j]);
            }
            printf("|\n");
        }
        printf("\n");
}
	else if (Flag == 0)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				printf("a[%d][%d] = ", i, j);
				scanf("%d", (&m[i][j]));
			}
		}
		printf("\n");
	}
//-------------------------Этап 3------------------------------

    int mm[size*2+(size-2)];
    for (int j = 0; j < size; ++j)
        {
            mm[j] = m[0][j];
        }
    for (int i = 1, j = size-2; i < size-1; ++i)
        {
            mm[size-1+i] = m[i][j];
            j=j-1;

        }
    for (int k = 0; k < size; ++k)
        {
            mm[size*2-2+k] = m[size-1][k];
        }
//-------------------------Этап 4------------------------------

    for (int i = size*2+(size-2)-1; i >= 1; i--)
        for (int j = 0; j < i; j++)
        {
            if (mm[j] > mm[j + 1])
            {
                int f = mm[j];
                mm[j] = mm[j + 1];
                mm[j + 1] = f;
            }
        }
//-------------------------Этап 5------------------------------

    for (int j = 0; j < size; ++j)
        {
            m[0][j] = mm[j];
        }
    for (int i = 1, j = size-2; i < size-1; ++i)
        {
            m[i][j] = mm[size-1+i];
            j=j-1;

        }
    for (int k = 0; k < size; ++k)
        {
            m[size-1][k] = mm[size*2-2+k];
        }
//-------------------------Этап 6------------------------------

    for (int i = 0; i < size; i++)
        {
            printf("|");
            for (int j = 0; j < size; j++)
            {
                printf("%3d ", m[i][j]);
            }
            printf("|\n");
        }
//-------------------------Этап 7------------------------------

    int f[size-2], fl, r;
    r=0;
    for (int j = 0; j < size; j++)
        {
            fl=0;
            for (int i = 1; i < size-1; i++)
                {
                    if (i != size-1-j)
                    {
                        f[i-1] = m[i][j];
            //           printf("%3d ", f[i-1]);
                    }
                }
             //   printf("\n ");
            for (int n = 0; n < size-2; n++)
                {
                    for (int p = 0; p < size-2; ++p)
                    {
                       if ((f[n] == f[p]) && (n != p) && (fl == 0))
                       {
                           printf("В стобце %3d есть повторения\n", j+1);
                           fl = 1;
                           r = 1;
                       }
                    }
                }
            for (int i = 0; i < size-2; i++)
                {
                    f[i] = 99;
                }
        }
    if (r == 0)
    {
        printf("\nНет столбцов с повтрениями!\n");
    }

}
