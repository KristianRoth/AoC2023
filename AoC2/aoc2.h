#ifndef AOC2_H
#define AOC2_H

typedef struct Set Set;
struct Set {
    int blue;
    int red;
    int green;
};

typedef struct Game Game;
struct Game {
    int index;
    int set_count;
    Set sets[];
};

void Day2_solve(void);

#endif // AOC2_H
