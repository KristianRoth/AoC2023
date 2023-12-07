#ifndef AOC7_H
#define AOC7_H

typedef struct Rank Rank;
struct Rank {
    char rank;
    int count;
    Rank *next;
};

typedef struct Hand Hand;
struct Hand {
    char cards[5];
    int bid;
    int rank_count;
    int j_count;
    long score;
    Rank *ranks;
    Hand *next;
};

void Day7_solve(void);

#endif // AOC7_H
