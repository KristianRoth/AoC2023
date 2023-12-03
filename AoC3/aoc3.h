#ifndef AOC3_H
#define AOC3_H

#define ENGINE_HEIGHT 140
#define ENGINE_WIDTH 140

typedef struct Engine Engine;
struct Engine {
    char grid[ENGINE_HEIGHT][ENGINE_WIDTH];
};

typedef struct GearNode GearNode;
struct GearNode {
    GearNode *next;
    int hash;
    int first;
    int second;
};

void Day3_solve(void);

#endif // AOC3_H
