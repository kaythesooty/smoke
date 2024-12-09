#include <stdio.h>
#include <string.h>

int main()
{
  char buffer[32];
  char idx[4][32];

  printf("Enter string (max 32 characters): ");
  scanf("%s", &buffer);

  strcpy(idx[0], buffer);

  printf("%s\n", idx[0]);
}
