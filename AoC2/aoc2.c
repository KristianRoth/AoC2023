#include "aoc2.h"
#include "../common.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

Game *parse_game(char *game) {
    int sets = Common_count_occurances(game, ';') + 1;
    Game *g = malloc(sizeof(int) + sets*sizeof(Set));
    Common_strip_string(&game, "Game ");
    g->index = Common_get_number(&game);
    Common_strip_string(&game, ": ");
    int i = 0;
    while (*game != '\0') {
        Set *s = malloc(sizeof(Set));
        while (true) {
            int amount = Common_get_number(&game);
            Common_strip_string(&game, " ");
            if (Common_string_has_prefix(game, "red")) {
                s->red += amount;
                Common_strip_string(&game, "red");
            }
            if (Common_string_has_prefix(game, "blue")) {
                s->blue += amount;
                Common_strip_string(&game, "blue");
            }
            if (Common_string_has_prefix(game, "green")) {
                s->green += amount;
                Common_strip_string(&game, "green");
            }
            if (*game == ';') {
                Common_strip_string(&game, "; ");
                break;
            }
            if (*game == '\0') {
                break;
            }
            Common_strip_string(&game, ", ");
        }
        g->sets[i++] = *s;
        free(s);
    }
    g->set_count = i;
    return g;
}

bool is_valid_game(Game *game) {
    for (int i = 0; i < game->set_count; i++) {
        Set s = game->sets[i];
        if (s.red > 12 || s.green > 13 || s.blue > 14) {
            return false;
        }
    }
    return true;
}

int calculate_power(Game *game) {
    int mr = 0;
    int mg = 0;
    int mb = 0;
    for (int i = 0; i < game->set_count; i++) {
        Set s = game->sets[i];
        if (mr < s.red) {
            mr = s.red;
        }
        if (mg < s.green) {
            mg = s.green;
        }
        if (mb < s.blue) {
            mb = s.blue;
        }
    }
    return mr * mg * mb;
}

void Day2_solve() {
    Node *head = Common_readFile("AoC2/day2.txt");
    int sum = 0;
    int sum_power = 0;
    do {
        Game *g = parse_game(head->value);
        sum_power += calculate_power(g);
        if (is_valid_game(g)) {
            sum += g->index;
        }
    } while (head = head->next);
    printf("Answer 1st: %i\n", sum);
    printf("Answer 2nd: %i\n", sum_power);
}
