#ifndef AOC6_H
#define AOC6_H

typedef struct RaceNode RaceNode;
struct RaceNode {
    long time;
    long record;
    RaceNode *next;
};

void Day6_solve(void);

#endif // AOC6_H
