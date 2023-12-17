#ifndef AOC12_H
#define AOC12_H

#include "../common.h"

typedef struct SpringMap SpringMap;
struct SpringMap {
    char *map;
    char *map_l;
    int map_len;
    int nums_len;
    IntNode *nums;
    IntNode *nums_l;
    SpringMap *next;
};

void Day12_solve(void);

#endif // AOC12_H
