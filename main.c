#include <stdio.h>
#include "common.h"
#include <stdlib.h>
#include "AoC1/aoc1.h"
#include "AoC2/aoc2.h"

void (*day_solves[])(void) = {
    Day1_solve,
    Day2_solve,
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Give day number to run");
        return 0;
    }
    int day = atoi(argv[1]) - 1;
    (day_solves[day])();
    return 0;
}
