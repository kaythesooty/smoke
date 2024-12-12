#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool filter(char *str1, char *str2);

void addg(FILE *cfg, int argc, char *argv[], char cfgpath[]);
void help();
void init(FILE *cfg, char path[]);
void list(FILE *cfg, char game[]);
void play(FILE *cfg, char game[]);

int main(int argc, char *argv[])
{
    char *home = getenv("HOME");
    char *pathend = "/.config/smoke.cfg";

    char path[100];
    strcpy(path, home);
    strcat(path, pathend);

    FILE *cfg;
    cfg = fopen(path, "r");

    // if there were no cfg it would be necessary to create it
    if(cfg == NULL) {
        init(cfg, path);
        return 1;
    }

    if (argc >= 2 && argv[1][0] != '-') play(cfg, argv[1]);
    if (argc >= 2 && argv[1][0] == '-')
    {
        switch (argv[1][1])
        {
            case 'h':
                help();
                return 0;
            case 'l':
                list(cfg, argv[2]);
                return 0;
            case 'a':
                addg(cfg, argc, argv, path);
                return 0;
            case 'r':
                printf("todo: remove game\n");
                return 0;
            default:
                printf("\x1b[31mError: Invalid parameter\x1b[0m\n");
                help();
                return 0;
        }
    }
    if (argc == 1) help();

    fclose(cfg);
    return 0;
}

bool filter(char *str1, char *str2)
{
    if (!str2) return true;

    if (strspn(str1, str2) >= strlen(str2)) return true;

    return false;
}

void addg(FILE *cfg, int argc, char *argv[], char cfgpath[])
{
  char cmd[16];
  char name[100];
  char path[100];

  cfg = fopen(cfgpath, "a");

  fputc('\n', cfg);

  if (argc >= 3) {
    strcpy(cmd, argv[2]);
    fprintf(cfg, cmd);
    fputc('\n', cfg);
    } else {
    printf("Short name: ");
    fgets(cmd, 16, stdin);
    fprintf(cfg, cmd);
  }

  if (argc >= 4) {
    strcpy(name, argv[3]);
    fprintf(cfg, name);
    fputc('\n', cfg);
    } else {
    printf("Full name: ");
    fgets(name, 100, stdin);
    fprintf(cfg, name);
  }

  if (argc >= 5) {
    strcpy(path, argv[4]);
    fprintf(cfg, path);
    fputc('\n', cfg);
    } else {
    printf("Path to game: ");
    fgets(path, 100, stdin);
    fprintf(cfg, path);
  }


  printf("Okay, added %s\n", name);
}

void init(FILE *cfg, char path[])
{
    cfg = fopen(path, "w");
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

void help() {
  printf("smoke <gamename>\n  Runs the game specified. Must be exact match\n\n");
  printf(" -l [filter]\n  List games. [filter] takes a string and will only return results matchinig or beginning with it\n\n");
  printf(" -a [cmdname] [\"gamename\"] [path]\n  Adds a new game. If options are ommited, a prompt will allow input.\n\n");
  printf(" -r <cmdname>\n  Remove a game. Must be exact match\n\n");
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
