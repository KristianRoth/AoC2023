#ifndef AOC10_H
#define AOC10_H

#include <stdbool.h>

#define PIPE_N 140
#define pipe_index(x, y) ((x)*PIPE_N + (y))

typedef struct PipeMap PipeMap;
struct PipeMap {
    char pipe[PIPE_N*PIPE_N];
};

typedef struct Step Step;
struct Step {
    int i;
    int x;
    int y;
    bool u;
};

void Day10_solve(void);

#endif // AOC10_H
