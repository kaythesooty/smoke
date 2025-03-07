#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "stringhlp.c"

void remove_game(char* cfgpath, char* input);
void add_game(int argc, char *argv[], char cfgpath[]);
void help();
void init(char path[]);
void list(char game[]);
void play(char game[]);

FILE *cfg;

int main(int argc, char *argv[])
{
  char path[128];
  char *pathend = "/.config/smoke.cfg";
  snprintf(path, 128, "%s%s", getenv("HOME"), pathend);

  cfg = fopen(path, "r");

  // if there were no cfg it would be necessary to create it
  if(cfg == NULL) {
    init(path);
    return 1;
  }

  if (argc >= 2 && argv[1][0] != '-') play(argv[1]);
  if (argc >= 2 && argv[1][0] == '-')
  {
    switch (argv[1][1])
    {
      case 'h':
        help();
        return 0;
      case 'l':
        list(argv[2]);
        return 0;
      case 'a':
        add_game(argc, argv, path);
        return 0;
      case 'r':
        remove_game(path, argv[2]);
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

void remove_game(char* cfgpath, char* input)
{
  char** cache = cache_file(cfg);
  int linec = line_count(cfg);

  cfg = fopen(cfgpath, "w");
  bool found = false;
  for (int i = 0; i < linec; i++) {
    size_t length = strlen(cache[i]);
    cache[i][length - 1] = '\0';

    printf("Comparing %s to %s... ", input, cache[i]);
    if (strcmp(cache[i], input) == 0) {
      printf("match found!\n");
      i += 3;
      found = true;
      continue;
    }

    printf("no match.\n");
    fprintf(cfg, "%s\n", cache[i]);
  }

  if (found) printf("\"%s\" removed\n", input);
  else printf("\"%s\" not found\n", input);
}

void add_game(int argc, char *argv[], char cfgpath[])
{
  char cmd[16];
  char name[100];
  char path[100];

  cfg = fopen(cfgpath, "a");

  fputc('\n', cfg);

  if (argc >= 3) {
    strcpy(cmd, argv[2]);
    fprintf(cfg, "%s", cmd);
    fputc('\n', cfg);
    } else {
    printf("Short name: ");
    fgets(cmd, 16, stdin);
    fprintf(cfg, "%s", cmd);
  }

  if (argc >= 4) {
    strcpy(name, argv[3]);
    fprintf(cfg, "%s", name);
    fputc('\n', cfg);
    } else {
    printf("Full name: ");
    fgets(name, 100, stdin);
    fprintf(cfg, "%s", name);
  }

  if (argc >= 5) {
    strcpy(path, argv[4]);
    fprintf(cfg, "%s", path);
    fputc('\n', cfg);
    } else {
    printf("Path to game: ");
    fgets(path, 100, stdin);
    fprintf(cfg, "%s", path);
  }


  printf("Okay, added %s\n", name);
}

void init(char path[])
{
  cfg = fopen(path, "w");
  fclose(cfg);

  printf("No cfg file found, new one created.\n");
}

void list(char game[])
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

void play(char game[])
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
