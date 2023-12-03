#include "aoc3.h"
#include "../common.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

Engine *parse_input(Node *head) {
    Engine *e = malloc(sizeof(Engine));
    int count = 0;
    do {
        memcpy(&e->grid[count++], head->value, ENGINE_WIDTH);
    } while (head = head->next);
    return e;
}

bool is_symbol(char c) {
    return !(isdigit(c) || c == '.');
}

bool has_symbol(Engine *e, int id, int jd, int w, int num, GearNode *gears) {
    bool has_symbol = false;
    for (int i = id - 1; i < id + 2; i++) {
        for (int j = jd - 1; j < jd + w + 1; j++) {
            if (!(0 <= i && i < ENGINE_HEIGHT) || !(0 <= j && j < ENGINE_WIDTH)) {
                continue;
            }
            if (is_symbol(e->grid[i][j])) {
                has_symbol = true;
            }

            if (e->grid[i][j] == '*') {
                do {
                    if (gears->hash == i*ENGINE_WIDTH+j) {
                        gears->second = num;
                    }
                    if (gears->next == NULL) {
                        gears->next = (GearNode*)malloc(sizeof(GearNode));
                        gears = gears->next;
                        gears->first = num;
                        gears->hash = i*ENGINE_WIDTH+j;
                        break;
                    }
                } while (gears = gears->next);
            }

        }
    }
    return has_symbol;
}

int calculate_engine(Engine *e, GearNode *gears) {
    int sum = 0;
    for (int i = ENGINE_HEIGHT-1; i >= 0; i--) {
        for (int j = ENGINE_WIDTH-1; j >= 0; j--) {
            if (isdigit(e->grid[i][j])) {
                int num = 0;
                int k;
                for (k = 0; j-k >= 0 && isdigit(e->grid[i][j-k]); k++) {
                    num += pow(10, k)*(e->grid[i][j-k] - 48);
                }
                j -= k;
                if (has_symbol(e, i, j+1, k, num, gears)) {
                    sum += num;
                }
            }
        }
    }
    return sum;
}

int calculate_gears(GearNode *gears) {
    int sum = 0;
    do {
        sum += gears->first*gears->second;
    } while (gears = gears->next);
    return sum;
}

void Day3_solve() {
    Node *head = Common_readFile("AoC3/day3.txt");
    Engine *e = parse_input(head);
    GearNode *gears = malloc(sizeof(GearNode));
    int sum = calculate_engine(e, gears);
    int sum_gears = calculate_gears(gears);
    printf("Answer 1st: %i\n", sum);
    printf("Answer 2nd: %i\n", sum_gears);
}
