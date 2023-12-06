#include "aoc6.h"
#include "../common.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

RaceNode *parse_races(Node *head) {
    char *time = head->value;
    char *distance = head->next->value;
    Common_strip_string(&time, "Time:");
    Common_strip_string(&distance, "Distance:");
    RaceNode *r = NULL;
    while (*time != '\0') {
        RaceNode *new = malloc(sizeof(RaceNode));
        new->time   = Common_get_number_lstrip(&time);
        new->record = Common_get_number_lstrip(&distance);
        new->next   = r;
        r = new;
    }
    return r;
}

long concatenate(long x, long y) {
    long pow = 10;
    while(y >= pow) {
        pow *= 10;
    }
    return x * pow + y;
}

int ceil_cust(float f) {
    int c = (int)ceilf(f);
    return c == f ? c + 1: c;
}

int calculate_ways_to_win(RaceNode *r) {
    int sum = 1;
    do {
        sum *= 1 + r->time - 2*(int)ceil_cust(((float)r->time-sqrtf(r->time*r->time-4*r->record))/2);
    } while (r = r->next);
    return sum;
}

void Day6_solve() {
    Node *head = Common_readFile("AoC6/day6.txt");
    RaceNode *r = parse_races(head);
    long sol = calculate_ways_to_win(r);

    while (r->next) {
        r->time = concatenate(r->next->time, r->time);
        r->record = concatenate(r->next->record, r->record);
        r->next = r->next->next;
    }
    long sol_ker = calculate_ways_to_win(r);

    printf("Answer 1st: %ld\n", sol);
    printf("Answer 2nd: %ld\n", sol_ker);
}
