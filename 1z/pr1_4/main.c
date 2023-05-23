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

    if (x==1)
    {
      if (y>=0)
      {
        f = 1.0 / sqrtf(y);
        printf("1u\n");
      }
    }
    else if (y==1)
    {
      if (x>=0)
      {
        f = 1.0 / sqrtf(x);
        printf("2u\n");
      }
    }
    else
    {
      f = 1.0 / (sqrtf(x+y)+(22.0/7));
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
