#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool filter(char *str1, char *str2);

void init();
void list(FILE *cfg, char game[]);
void play(FILE *cfg, char game[]);

int main(int argc, char *argv[])
{
    FILE *cfg;
    cfg = fopen("smoke.cfg", "r");

    // if there were no cfg it would be necessary to create it
    if(cfg == NULL) {
        init(cfg);
        return 1;
    }

    if (argc == 2 && argv[1][0] != '-') play(cfg, argv[1]);
    if (argc >= 2 && argv[1][0] == '-') list(cfg, argv[2]);
    if (argc == 1) printf("Smoke!\n");

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
    bool found = false;

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

    if (!found) printf("No games match\n");

}

void play(FILE *cfg, char game[])
{
    char buffer[128];

    while(fgets(buffer, 128, cfg))
    {
        buffer[strcspn(buffer, "\n")] = 0;
        if (strcmp(buffer, game) == 0 && buffer[0] != '#' && buffer[0] != '\n')
        {
            fgets(buffer, 128, cfg);
            printf("Running %s", buffer);
            fgets(buffer, 128, cfg);
            printf("from %s", buffer);

            return;
        }
    }

    printf("%s not found\n", game);
}
