#ifndef AOC9_H
#define AOC9_H

typedef struct Analysis Analysis;
struct Analysis {
    int value;
    Analysis *next;
    Analysis *layer;
};

void Day9_solve(void);

#endif // AOC9_H
