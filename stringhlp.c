/* -------------------------
 * String Helper functions
 * ------------------------*/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRLENG 128

// Returns number of lines in text file
int line_count(FILE* file)
{
  if (file == NULL) return 0;

  char ch;
  int lines = 0;

  while(!feof(file)) {
    ch = fgetc(file);
    if (ch == '\n') lines++;
  }

  rewind(file);

  return lines;
}

// Compares two strings and returns true if str1 contains or is str2
// Also returns true if there is nothing in string 2
bool filter(char *str1, char *str2)
{
  if (!str2) return true;

  if (strspn(str1, str2) >= strlen(str2)) return true;

  return false;
}

// Caches a file into string pointers
char** cache_file(FILE* file)
{
  int ln = line_count(file);
  int i,j;
  char** pntr;

  //Allocate memory for pointer pointer
  pntr = (char**)malloc(ln * sizeof(char*));
  if (pntr == NULL) {
    fprintf(stderr, "malloc fail (step 1)\n");
    return pntr;
  }

  for (i = 0; i < ln; i++) {
    pntr[i] = (char*)malloc(MAX_STRLENG * sizeof(char));
    if (pntr[i] == NULL) {
      fprintf(stderr, "malloc fail (step 2.%d)", i);
      return pntr;
    }
    fgets(pntr[i], MAX_STRLENG, file);
  }

  rewind(file);
  
  return pntr;
}
