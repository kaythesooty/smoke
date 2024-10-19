#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool filter(char *str1, char *str2);

void init();
void list(FILE *cfg, char game[]);
// void play();

int main(int argc, char *argv[])
{
    FILE *cfg;
    cfg = fopen("smoke.cfg", "r");

    // if there were no cfg it would be necessary to create it
    if(cfg == NULL) {
        init(cfg);
    }


    list(cfg, argv[1]);

    fclose(cfg);
    return 0;
}

bool filter(char *str1, char *str2)
{
    if (!str2) return true;

    if (strspn(str1, str2) >= strlen(str2)) return true;

    return false;
}

void init(FILE *cfg)
{
    cfg = fopen("smoke.cfg", "w");
    fclose(cfg);

    printf("No cfg file found, new one created.\n");
}

void list(FILE *cfg, char game[])
{
    char buffer[128];
    bool found = true;

    printf("----------\n");

    while (fgets(buffer, 128, cfg)) {

        if (filter(buffer, game) && buffer[0] != '#' && buffer[0] != '\n') {
            printf("%s", buffer);
            fgets(buffer, 128, cfg);
            printf("Name: %s", buffer);
            fgets(buffer, 128, cfg);
            printf("Path: %s\n", buffer);
            found = true;

        }

    }

    if (!found) printf("No games match");

}
