#include <stdio.h>

void init();

int main(int argc, char* argv) {

    init();


    printf("Running game\n");

    return 0;
}

void init() {
    FILE *cfg;

    cfg = fopen("smoke.cfg", "w");
    fclose(cfg);
}
