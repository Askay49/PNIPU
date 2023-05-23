#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{

  while (1)
  {
    int flag;
    float f, pi, x, y;

    printf("Write x and y:\n");
    scanf("%f", &x);
    scanf("%f", &y);

    pi = 3.14f;

    if (abs(x + y) - pi > 0.0001 || abs(x + y) - pi < 0.0001)
    {
      if (sqrt(x + y) != 0)
      {
        f = 3.2 / sqrtf(x + y);
        printf("1u\n");
      }
      else
        printf("Error\n");
    }
    else if (abs(x + y) < pi)
    {
      f = (22 / 7.0) + cos(x * pi / 180);
      printf("2u\n");
    }
    else
    {
      f = exp(sqrt(x + y));
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
