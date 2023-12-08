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

HashMap *parse_map_tree(Node *head, Node **starts_a) {
    HashMap *hm = Common_hash_create(1000, &Common_hash_string);
    Node *names = NULL;
    Node *as = NULL;
    do {
        MapTree *new = malloc(sizeof(MapTree));
        Node *list = malloc(sizeof(Node));
        memcpy(new->name, head->value, 3);
        memcpy(new->left_name, head->value + 7, 3);
        memcpy(new->right_name, head->value + 12, 3);
        Common_hash_put(hm, new->name, new);
        list->value = new->name;
        list->next = names;
        names = list;
        if (new->name[2] == 'A') {
            Node *a = malloc(sizeof(Node));
            a->next = as;
            a->value = new->name;
            as = a;
        }
    } while (head = head->next);
    *starts_a = as;
    do {
        MapTree *map = Common_hash_get(hm, names->value);
        map->left  = (MapTree*)Common_hash_get(hm, map->left_name);
        map->right = (MapTree*)Common_hash_get(hm, map->right_name);
    } while (names = names->next);

    return hm;
}

void Day8_solve() {
    Node *head = Common_readFile("AoC8/day8.txt");
    char *dirs = head->value;
    int dirs_len = strlen(dirs);
    Node *starts_a;
    HashMap *hm = parse_map_tree(head->next->next, &starts_a);

    int count = 0;
    MapTree *walk = Common_hash_get(hm, "AAA");
    while (strcmp(walk->name, "ZZZ") != 0) walk = dirs[count++%dirs_len] == 'L' ? walk->left : walk->right;

    Node *starts_a_len = starts_a;
    int STARTS_A_COUNT = 1;
    while (starts_a_len = starts_a_len->next) STARTS_A_COUNT++;

    MapTree *walks_array[STARTS_A_COUNT];
    for (int i = 0; i < STARTS_A_COUNT; i++) {
        walks_array[i] = Common_hash_get(hm, starts_a->value);
        starts_a = starts_a->next;
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
