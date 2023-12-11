#include "aoc11.h"
#include "../common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void insert_star(StarChart **c_ref, int x, int y, int no_stars_count) {
    StarChart *c = *c_ref;
    StarChart *new = malloc(sizeof(StarChart));
    new->x = x;
    new->y = y + no_stars_count;
    new->x_l = x;
    new->y_l = y + 999999*no_stars_count;
    if (c == NULL || c->x >= x) {
        new->next = c;
        c = new;
    } else {
        StarChart *iter = c;
        while (iter->next != NULL && iter->next->x < x) iter = iter->next;
        new->next = iter->next;
        iter->next = new;
    }
    *c_ref = c;
}

StarChart *parse_stars(Node *head) {
    StarChart *c = NULL;
    int count_y = 0;
    int no_stars_count = 0;
    do {
        char *line = head->value;
        int count_x = 0;
        bool no_stars = true;
        while (*line != '\0') {
            if (*line == '#') {
                no_stars = false;
                insert_star(&c, count_x, count_y, no_stars_count);
            }
            line++;
            count_x++;
        }
        no_stars_count += no_stars;
        count_y++;
    } while (head = head -> next);

    StarChart *iter = c;
    int empty_xs = 0;
    int index = 0;
    while (iter != NULL) {
        if (iter->x != index) {
            empty_xs++;
            index++;
            continue;
        }
        do {
            iter->x += empty_xs;
            iter->x_l += 999999*empty_xs;
            iter = iter->next;
        } while (iter != NULL && iter->x == index);
        index++;
    }
    return c;
}

void Day11_solve() {
    Node *head = Common_readFile("AoC11/day11.txt");
    StarChart *c = parse_stars(head);
    long sum = 0;
    long sum_l = 0;
    do {
        StarChart *iter = c->next;
        while (iter) {
            sum += iter->x - c->x + abs(iter->y - c->y);
            sum_l += iter->x_l - c->x_l + abs(iter->y_l - c->y_l);
            iter = iter->next;
        }
    } while(c = c->next);

    printf("Answer 1st: %li\n", sum);
    printf("Answer 2nd: %li\n", sum_l);
}


// 833166416
// 832678904
// 832324192
// 832323778
// 635412704

// 842645913794


