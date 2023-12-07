#include "main.h"
#include <stdio.h>
#include "common.h"
#include <stdlib.h>
#include <time.h>
#include "AoC1/aoc1.h"
#include "AoC2/aoc2.h"
#include "AoC3/aoc3.h"
#include "AoC4/aoc4.h"
#include "AoC5/aoc5.h"
#include "AoC6/aoc6.h"
#include "AoC7/aoc7.h"

void (*day_solves[])(void) = {
    Day1_solve,
    Day2_solve,
    Day3_solve,
    Day4_solve,
    Day5_solve,
    Day6_solve,
    Day7_solve,
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Give day number to run\n");
        return 0;
    }
    int day = atoi(argv[1]) - 1;
    if (argc == 3) {
        int amount = atoi(argv[2]);
        run_performance(day, amount);
        return 0;
    }

    (day_solves[day])();
    return 0;
}


void run_performance(int day, int amount) {
    int old_stdout = dup(1);
    freopen ("/dev/null", "w", stdout);

    clock_t begin = clock();
    for (int i = 0; i < amount; i++) {
        (day_solves[day])();
    }
    clock_t end = clock();

    fclose(stdout);
    stdout = fdopen(old_stdout, "w");

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC / amount;
    printf("%f\n", time_spent);
}
