#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    float x, y, function, Number_Pi;
    Number_Pi = 3.14f;
    printf("������ ����� x: ");
    scanf("%f", &x);
    printf("������ ����� y: ");
    scanf("%f", &y);

    if ((fabs(x) == Number_Pi) && (y != -(1 / 7)))
    {
        function = (10.2 / (y + 1 / 7));
    }
    else if (fabs(x) < Number_Pi)
    {
        function = sin(x);
    }
    else
    {
        function = exp(x + y);
    }
    printf("\n�������� �������: %f", function);

    return 0;
}