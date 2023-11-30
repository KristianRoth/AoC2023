#include <stdio.h>
#include "common.h"
#include <stdlib.h>
#include "AoC1/aoc1.h"

void (*day_simple_solves[])(void) = {
    Day1_solve_simple
};

void (*day_solves[])(void) = {
    Day1_solve
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Give day number to run");
        return 0;
    }
    int day = atoi(argv[1]) - 1;
    (day_simple_solves[day])();
    (day_solves[day])();
    return 0;
}
