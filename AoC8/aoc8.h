#ifndef AOC8_H
#define AOC8_H

typedef struct MapTree MapTree;
struct MapTree {
    char name[3];
    MapTree *left;
    char left_name[3];
    MapTree *right;
    char right_name[3];
};

void Day8_solve(void);

#endif // AOC8_H
