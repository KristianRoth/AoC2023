#include "aoc8.h"
#include "../common.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

MapTree *find_name(MapTree *map, char* name) {
    while (strcmp(map->name, name) != 0) map = map->next;
    return map;
}

MapTree *find_ends_a(MapTree *map) {
    MapTree *found = NULL;
    while (map) {
        MapTree *next = map->next;
        if (map->name[2] == 'A') {
            map->next = found;
            found = map;
        }
        map = next;
    }
    return found;
}

MapTree *parse_map_tree(Node *head) {
    MapTree *map = NULL;
    do {
        MapTree *new = malloc(sizeof(MapTree));
        memcpy(new->name, head->value, 3);
        memcpy(new->left_name, head->value + 7, 3);
        memcpy(new->right_name, head->value + 12, 3);
        new->next = map;
        map = new;
    } while (head = head->next);
    MapTree *map_head = map;
    do {
        map->left  = find_name(map_head, map->left_name);
        map->right = find_name(map_head, map->right_name);
    } while (map = map->next);

    return map_head;
}

void Day8_solve() {
    Node *head = Common_readFile("AoC8/day8.txt");
    char *dirs = head->value;
    int dirs_len = strlen(dirs);
    MapTree *map = parse_map_tree(head->next->next);
    int count = 0;

    MapTree *walk = find_name(map, "AAA");
    while (strcmp(walk->name, "ZZZ") != 0) walk = dirs[count++%dirs_len] == 'L' ? walk->left : walk->right;

    MapTree *walks = find_ends_a(map);
    MapTree *w_len = walks;
    int STARTS_A_COUNT = 1;
    while (w_len = w_len->next) STARTS_A_COUNT++;


    MapTree *walks_array[STARTS_A_COUNT];
    for (int i = 0; i < STARTS_A_COUNT; i++) {
        walks_array[i] = walks;
        walks = walks->next;
    }

    int cycles[STARTS_A_COUNT];
    for (int i = 0; i < STARTS_A_COUNT; i++) {
        int count_w = 0;
        while (true) {
            walks_array[i] = dirs[count_w++%dirs_len] == 'L' ? walks_array[i]->left : walks_array[i]->right;
            if (walks_array[i]->name[2] == 'Z') {
                cycles[i] = count_w ;
                break;
            }
        }
    }

    long iterations = cycles[0];
    for (int i = 1; i < STARTS_A_COUNT; i++) {
        iterations = Common_lcm(iterations, cycles[i]);
    }

    printf("Answer 1st %ld\n", count);
    printf("Answer 2nd %ld\n", iterations);
}
