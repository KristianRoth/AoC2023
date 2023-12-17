#include "aoc12.h"
#include "../common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

SpringMap *parse_spring_map(Node *head) {
    SpringMap *sm = NULL;
    do {
        char *line = head->value;
        SpringMap *new = malloc(sizeof(SpringMap));
        char *space = strchr(line, ' ');
        int len = (space-line);
        new->map = malloc(len+1);
        new->map_l = malloc(5*len+6);
        new->map_len = len;
        memcpy(new->map, line, len);
        new->map[len+1] = '\0';
        new->nums = Common_rec_get_int_node(space);
        memset(new->map_l, '?', 5*len+4);
        IntNode *tmp = NULL;
        for (int i = 0; i < 5; i++) {
            memcpy(new->map_l+(len+1)*i, line, len);
            IntNode *iter = new->nums;
            int nums_len = 0;
            do {
                IntNode *new_node = malloc(sizeof(IntNode));
                new_node->next = NULL;
                new_node->value = iter->value;
                if (tmp != NULL) {
                    tmp->next = new_node;
                } else {
                    new->nums_l = new_node;
                }
                tmp = new_node;
                nums_len++;
            } while (iter = iter->next);
            new->nums_len = nums_len;
        }
        new->map_l[5*len+5] = '\0';
        new->next = sm;
        sm = new;
    } while (head = head->next);
    return sm;
}

bool has_space(char *map, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (map[i] == '.') return false;
    }
    if (map[i] == '#') return false;
    return true;
}

long count_ways(long *cache, char *map, int map_len, IntNode *nums, int nums_len, int offset) {
    if (map_len == 0 || map_len < nums->value + 2*(nums_len-1)) return 0;
    long sum = 0;
    int cache_index = (map_len-1)*offset + nums_len;
    long cache_value = cache[cache_index] - 1;

    if (cache_value != -1) return cache_value;

    while (1) {
        while (*map == '.') {
            map++;
            map_len--;
        }
        if (map_len == 0 || map_len < nums->value || map_len < nums->value + 2*(nums_len-1)) {
            break;
        }
        if (has_space(map, nums->value)) {
            if (nums->next) {
                sum += count_ways(
                        cache,
                        map + nums->value + 1,
                        map_len - nums->value - 1,
                        nums->next,
                        nums_len - 1,
                        offset
                    );
            } else {
                if (strchr(map+nums->value, '#') == NULL) sum++;
            }
        }
        if (*map == '#') break;
        map++;
        map_len--;
    }
    cache[cache_index] = sum + 1;
    return sum;
}

void Day12_solve() {
    Node *head = Common_readFile("AoC12/day12.txt");
    SpringMap *sm = parse_spring_map(head);

    long sum = 0;
    long sum_l = 0;
    long *cache = malloc(0);
    long cache_len, last_cache_len;
    last_cache_len = 0;
    do {
        int len = sm->nums_len;
        int str_len = sm->map_len;
        int cache_len = len*5*(str_len*5+5)*sizeof(long);
        if (cache_len > last_cache_len) {
            free(cache);
            cache = malloc(cache_len);
        }
        memset(cache, 0, cache_len);

        sum   += count_ways(cache, sm->map,   str_len,       sm->nums,  len,    len*5);
        sum_l += count_ways(cache, sm->map_l, str_len*5 + 4, sm->nums_l, len*5, len*5);


    } while (sm = sm->next);
    printf("Answer 1st: %li\n", sum);
    printf("Answer 2nd: %li\n", sum_l);
}
