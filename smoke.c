#include <stdio.h>
#include <string.h>

void init();
void list(FILE *cfg);
void find(FILE *cfg, char game[]);

int main(int argc, char *argv[])
{
    FILE *cfg;
    cfg = fopen("smoke.cfg", "r");

    // if there were no cfg it would be necessary to create it
    if(cfg == NULL) {
        init(cfg);
    }

    if (argc > 1) {
        find(cfg, argv[1]);
    } else {
        list(cfg);
    }

    return 0;
}

void init(FILE *cfg)
{
    cfg = fopen("smoke.cfg", "w");
    fclose(cfg);

    printf("No cfg file found, new one created.\n");
}

void list(FILE *cfg)
{
    char buffer[128];

    printf("----------\n");

    while (fgets(buffer, 128, cfg)) {

        if (buffer[0] != '#' && buffer[0] != '\n') {
            printf("%s", buffer);
            fgets(buffer, 128, cfg);
            printf("Name: %s", buffer);
            fgets(buffer, 128, cfg);
            printf("Path: %s\n", buffer);

        }

    }

}

void find(FILE *cfg, char game[])
{
    char buffer[128];

    printf("----------\n");

    while (fgets(buffer, 128, cfg)) {

        if (strspn(buffer, game) >= strlen(game) && buffer[0] != '#') {
            printf("%s", buffer);
            fgets(buffer, 128, cfg);
            printf("Name: %s", buffer);
            fgets(buffer, 128, cfg);
            printf("Path: %s\n", buffer);

        }

    }

}
