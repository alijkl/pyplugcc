#include <stdio.h>
#include <stdlib.h>

int test123 (const char *x) {
  return printf ("%s\n", x);
}

int main(void)
{
  test123((char*)"test");
  printf("Hello, World!\n");
  return EXIT_SUCCESS;
}
