#include <stdio.h>
#include <string.h>

void init();

int main(int argc, char **argv) {
    // init();

    FILE *cfg;
    cfg = fopen("smoke.cfg", "r");

    if (argc > 1) {
        char game[24];
        fscanf(cfg, "%24s", &game);
        if (strcmp(game, argv[1]) == 0) {
            printf("Found %s vs %s\n", argv[1], game);
        } else {
            printf("Couldn't find %s vs %s\n", argv[1], game);
            // return 1;
        }
    }

    // printf("%c\n", argv[1][0]);

    return 0;
}

void init() {
    FILE *cfg;

    cfg = fopen("smoke.cfg", "w");
    fclose(cfg);
}
