#ifndef AOC9_H
#define AOC9_H

#define ANA_NUM 21
#define ana_index(k, n) ((k)*ANA_NUM+(n))

typedef struct Analysis Analysis;
struct Analysis {
    int values[ANA_NUM*ANA_NUM];
};

void Day9_solve(void);

#endif // AOC9_H
