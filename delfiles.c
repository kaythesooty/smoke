#include <stdio.h>
#include <stdlib.h>

int lineCount(FILE* file);
int cacheFile(FILE* file);

int main()
{
    FILE* file;
    file = fopen("testdoc.txt", "r");

    int res = cacheFile(file);
    printf("Exit with code %d\n", res);

    return 0;
}

int lineCount(FILE* file)
{
    if (file == NULL) return 0;

    char ch;
    int lines = 0;

    while(!feof(file)) {
        ch = fgetc(file);
        if (ch == '\n') lines++;
    }

    return lines;
}

int cacheFile(FILE* file) {
    // No file? return -1
    if (file == NULL) return -1;

    // Variable setup
    int ln = lineCount(file);
    printf("%d\n", ln);
    char* ptr;

    // Attempt memory allocation, return -2 if fails
    ptr = (char*)calloc(ln + 1, sizeof(char));
    if (ptr == NULL) return -2;

    // Add an 'A' to each array element
    for (int i = 0; i < ln; i++) {
        ptr[i] = 'A';
    }
    ptr[ln] = '\0';

    printf("%sH!\n", ptr);

    return 0; // Return 0 on successful cache
}
