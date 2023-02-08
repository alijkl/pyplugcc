#include <stdio.h>
#include <stdlib.h>

enum days {Sunday=7, Monday=1, Tuesday, Wednesday, Thursday, Friday, Saturday};

enum months
  {
    January = 1, February, March, April,
    May, June, July, August,
    September, October, November, December,
  };

enum color {red, green, blue, white};
enum days d;
int i;
int *a;

int main(void)
{
  i = 1;
  a = (int*)3; 
  
  printf("i %i\n", i);
  printf ("a %ls\n", a);  
  return EXIT_SUCCESS;
}
