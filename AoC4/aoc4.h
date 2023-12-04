#ifndef AOC4_H
#define AOC4_H

#define WINNING_AMOUNT 10
#define NUMBERS_AMOUNT 25

typedef struct CardNode CardNode;
struct CardNode {
    CardNode *next;
    int winners;
};

void Day4_solve(void);

#endif // AOC4_H

