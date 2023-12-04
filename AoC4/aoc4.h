#ifndef AOC4_H
#define AOC4_H

#define WINNING_AMOUNT 10
#define NUMBERS_AMOUNT 25

typedef struct Card Card;
struct Card {
    int winning[WINNING_AMOUNT];
    int numbers[NUMBERS_AMOUNT];
};

typedef struct CardNode CardNode;
struct CardNode {
    CardNode *next;
    Card *card;
};

typedef struct WinnerNode WinnerNode;
struct WinnerNode {
    WinnerNode *next;
    int *amount;
};

void Day4_solve(void);

#endif // AOC4_H

