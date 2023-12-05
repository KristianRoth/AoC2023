#ifndef AOC5_H
#define AOC5_H

typedef struct MapNode MapNode;
struct MapNode {
    unsigned long source;
    unsigned long dest;
    unsigned long range;
    MapNode *next;
};

typedef struct Range Range;
struct Range {
    unsigned long start;
    unsigned long end;
    Range *next;
};


void Day5_solve(void);

#endif // AOC5_H
