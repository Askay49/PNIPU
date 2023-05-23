#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{

  while (1)
  {
    float x, y, absX, absY;
    float f, pi;
    int flag;

    printf("Write x and y:\n");
    scanf("%f", &x);
    scanf("%f", &y);

    absX = fabs(x);
    absY = fabs(y);
    pi = 22.0 / 7;

    if ((absX < pi))
    {
      if (cos(x * y) != 0)
      {
        f = tan((x * y) * pi / 180);
        printf("1u\n");
      }
      else
        printf("Error\n");
    }
    else if (absY < pi)
    {
      f = 1 / tan((x * y) * pi / 180);
      printf("2u\n");
    }
    else
    {
      f = exp(x + y);
      printf("3u\n");
    }
    printf("f(x,y)= %.3f\n", f);
    printf("continue? (1-Yes, 0 - No):\n");
    scanf("%d", &flag);
    if (flag == 0)
      break;
  }

  return 0;
}
