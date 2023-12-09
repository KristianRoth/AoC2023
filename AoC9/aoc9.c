#include "aoc9.h"
#include "../common.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

void parse_analysis(char *line, IntNode **firsts_ref, IntNode **lasts_ref) {
    Analysis *nums = NULL;
    IntNode *firsts;
    IntNode *lasts = NULL;
    while (*line != '\0') {
        Analysis *new = malloc(sizeof(Analysis));
        new->value = Common_get_number_lstrip(&line);
        if (lasts == NULL) {
            lasts = malloc(sizeof(IntNode));
            lasts->value = new->value;
        }
        new->next  = nums;
        nums = new;
    }
    firsts = malloc(sizeof(IntNode));
    firsts->value = nums->value;
    Analysis *prev = nums;
    while (true) {
        bool only_zeros = true;
        Analysis *layer = NULL;
        Analysis *prev_iter = prev;
        int last_value;
        while (prev_iter->next != NULL) {
            Analysis *new = malloc(sizeof(Analysis));
            new->value = prev_iter->value - prev_iter->next->value;
            if (new->value != 0) only_zeros = false;
            if (layer == NULL) {
                IntNode *new_first = malloc(sizeof(IntNode));
                new_first->next = firsts;
                new_first->value = new->value;
                firsts = new_first;
                layer = new;
            } else {
                Analysis *tmp = layer;
                while (tmp->next != NULL) tmp = tmp->next;
                tmp->next = new;
            }
            last_value = new->value;
            prev_iter = prev_iter->next;
        }
        IntNode *new_last = malloc(sizeof(IntNode));
        new_last->next = lasts;
        new_last->value = last_value;
        lasts = new_last;
        layer->layer = prev;
        if (only_zeros) {
            break;
        }
        prev = layer;
    }
    *firsts_ref = firsts;
    *lasts_ref = lasts;
}

int calculate_next(IntNode *a) {
    int sum = a->value;
    int count = 0;
    while (a->next) {
        sum = a->next->value + sum;
        a = a->next;
    };
    return sum;
}

int calculate_prev(IntNode *a) {
    int sum = a->value;
    int count = 0;
    while (a->next) {
        sum = a->next->value - sum;
        a = a->next;
    };
    return sum;
}

void Day9_solve() {
    Node *head = Common_readFile("AoC9/day9.txt");
    int sum = 0;
    int sum_lasts = 0;
    do {
        IntNode *firsts, *lasts;
        parse_analysis(head->value, &firsts, &lasts);
        sum += calculate_next(firsts);
        sum_lasts += calculate_prev(lasts);

    } while(head = head->next);
    printf("Answer 1st: %i\n", sum);
    printf("Answer 2nd: %i\n", sum_lasts);
}
