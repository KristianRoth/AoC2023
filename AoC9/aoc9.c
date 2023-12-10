#include "aoc9.h"
#include "../common.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

Analysis *parse_analysis(char *line) {
    Analysis *nums = malloc(sizeof(Analysis));
    int count = 0;
    while (*line != '\0') {
        nums->values[ana_index(0, count++)] = Common_get_number_lstrip(&line);
    }
    for (int k = 1; k < ANA_NUM; k++) {
        for (int n = 0; n < ANA_NUM-k; n++) {
            nums->values[ana_index(k, n)] = nums->values[ana_index(k-1, n+1)] - nums->values[ana_index(k-1, n)];
        }
    }
    return nums;
}

int calculate_next(Analysis *a) {
    int sum = 0;
    for (int i = 0; i < ANA_NUM; i++) {
        sum += a->values[ana_index(i, ANA_NUM-i-1)];
    }
    return sum;
}

int calculate_prev(Analysis *a) {
    int sum = 0;
    for (int i = ANA_NUM-1; i >= 0; i--) {
        sum = a->values[ana_index(i, 0)] - sum;
    }
    return sum;
}

void Day9_solve() {
    Node *head = Common_readFile("AoC9/day9.txt");
    int sum = 0;
    int sum_lasts = 0;
    do {
        Analysis *a = parse_analysis(head->value);
        sum += calculate_next(a);
        sum_lasts += calculate_prev(a);
    } while(head = head->next);
    printf("Answer 1st: %i\n", sum);
    printf("Answer 2nd: %i\n", sum_lasts);
}
