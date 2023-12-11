#include "aoc11.h"
#include "../common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void Day11_solve() {
    Node *head = Common_readFile("AoC11/day11.txt");
    int stars_x[STARS];
    int stars_y[STARS];
    memset(stars_x, 0, sizeof(stars_x));
    memset(stars_y, 0, sizeof(stars_y));

    int count_y = 0;
    int no_stars_count = 0;
    do {
        char *line = head->value;
        int count_x = 0;
        while (*line != '\0') {
            if (*line == '#') {
                stars_x[count_x]++;
                stars_y[count_y]++;
            }
            line++;
            count_x++;
        }
        count_y++;
    } while (head = head -> next);

    int offset_x[STARS];
    int offset_y[STARS];
    offset_x[0] = 0;
    offset_y[0] = 0;
    for (int i = 1; i < STARS; i++) {
        offset_x[i] = (stars_x[i] == 0 ? 1 : 0) + offset_x[i-1];
        offset_y[i] = (stars_y[i] == 0 ? 1 : 0) + offset_y[i-1];
    }

    long sum = 0;
    long sum2 = 0;
    for (int i = 0; i < STARS; i++) {
        for (int j = i+1; j < STARS; j++) {
            sum +=  (stars_x[i]*stars_x[j])*(j - i + (offset_x[j] - offset_x[i]));
            sum +=  (stars_y[i]*stars_y[j])*(j - i + (offset_y[j] - offset_y[i]));

            sum2 += (stars_x[i]*stars_x[j])*(j - i + (offset_x[j] - offset_x[i])*999999);
            sum2 += (stars_y[i]*stars_y[j])*(j - i + (offset_y[j] - offset_y[i])*999999);

        }
    }
    printf("Answer 1st: %li\n", sum);
    printf("Answer 2nd: %li\n", sum2);
}
