#ifndef AOC11_H
#define AOC11_H


typedef struct StarChart StarChart;
struct StarChart {
    int x;
    int y;
    int x_l;
    int y_l;
    StarChart *next;
};

void Day11_solve(void);

#endif // AOC11_H
