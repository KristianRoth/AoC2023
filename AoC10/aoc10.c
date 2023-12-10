#include "aoc10.h"
#include "../common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void print_pipe_map(PipeMap *map) {
    for (int i = 0; i < PIPE_N; i++) {
        for (int j = 0; j < PIPE_N; j++) {
            printf("%c", map->pipe[pipe_index(i, j)]);
        }
        printf("\n");
    }
    printf("\n");
}

PipeMap *parse_pipe_map(Node *head) {
    PipeMap *map = malloc(sizeof(PipeMap));
    int count = 0;
    do {
        memcpy(map->pipe + count++*PIPE_N, head->value, PIPE_N);
    } while (head = head->next);
    return map;
}

Step find_next(PipeMap *map, Step s) {
    if (s.x == -1 && map->pipe[s.i] == 'F') { map->pipe[s.i] = s.u ? 'Y' : ' '; return  (Step){ s.i + PIPE_N,  0,  1,   0}; }
    if (s.x == -1 && map->pipe[s.i] == '-') { map->pipe[s.i] = s.u ? ' ' : ' '; return  (Step){ s.i - 1,      -1,  0, s.u}; }
    if (s.x == -1 && map->pipe[s.i] == 'L') { map->pipe[s.i] = s.u ? ' ' : 'Y'; return  (Step){ s.i - PIPE_N,  0, -1,   0}; }

    if (s.x ==  1 && map->pipe[s.i] == 'J') { map->pipe[s.i] = s.u ? ' ' : 'Y'; return  (Step){ s.i - PIPE_N,  0, -1,   1}; }
    if (s.x ==  1 && map->pipe[s.i] == '-') { map->pipe[s.i] = s.u ? ' ' : ' '; return  (Step){ s.i + 1,      +1,  0, s.u}; }
    if (s.x ==  1 && map->pipe[s.i] == '7') { map->pipe[s.i] = s.u ? 'Y' : ' '; return  (Step){ s.i + PIPE_N,  0,  1,   1}; }

    if (s.y == -1 && map->pipe[s.i] == '7') { map->pipe[s.i] = s.u ? ' ' : ' '; return  (Step){ s.i - 1,      -1,  0,   0}; }
    if (s.y == -1 && map->pipe[s.i] == '|') { map->pipe[s.i] = s.u ? 'Y' : 'Y'; return  (Step){ s.i - PIPE_N,  0, -1, s.u}; }
    if (s.y == -1 && map->pipe[s.i] == 'F') { map->pipe[s.i] = s.u ? ' ' : ' '; return  (Step){ s.i + 1,       1,  0,   0}; }

    if (s.y ==  1 && map->pipe[s.i] == 'J') { map->pipe[s.i] = s.u ? ' ' : ' '; return  (Step){ s.i - 1,      -1,  0,   1}; }
    if (s.y ==  1 && map->pipe[s.i] == '|') { map->pipe[s.i] = s.u ? 'Y' : 'Y'; return  (Step){ s.i + PIPE_N,  0, +1, s.u}; }
    if (s.y ==  1 && map->pipe[s.i] == 'L') { map->pipe[s.i] = s.u ? ' ' : ' '; return  (Step){ s.i + 1,       1,  0,   1}; }
    printf("BAD %c x:%i y:%i\n", map->pipe[s.i], s.x, s.y);
    exit(0);
}

int find_s(PipeMap *map) {
    for (int i = 0; i < PIPE_N*PIPE_N; i++) {
        if (map->pipe[i] == 'S') return i;
    }
}

void Day10_solve() {
    Node *head = Common_readFile("AoC10/day10.txt");
    PipeMap *map = parse_pipe_map(head);

    int s = find_s(map);

    Step step = (Step){s-1, -1, 0, 1};

    int step_count = 0;
    while (map->pipe[step.i] != 'S') {
        step = find_next(map, step);
        step_count++;
    }

    map->pipe[step.i] = ' ';

    bool outside = true;
    int inside_count = 0;
    for (int i = 0; i < PIPE_N*PIPE_N; i++) {
        if (map->pipe[i] == 'Y') outside = !outside;
        if (!outside && map->pipe[i] != 'Y' && map->pipe[i] != ' ' && map->pipe[i] != 'S') inside_count++;
    }

    printf("Answer 1st: %i\n", step_count/2 + 1);
    printf("Answer 2nd: %i\n", inside_count);
}


