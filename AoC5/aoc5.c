#include "aoc5.h"
#include "../common.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

void parse_seeds(char *str, unsigned long seeds[], int seed_count) {
    Common_strip_string(&str, "seeds: ");
    for (int i = 0; i < seed_count; i++) {
        seeds[i] = Common_get_number_lstrip_ul(&str);
    }
}

MapNode *parse_map(Node **head_ptr) {
    Node *head = *head_ptr;
    head = head->next;
    MapNode *map = NULL;

    do {
        if (*(head->value) == '\0') {
            break;
        }

        char *line = head->value;
        MapNode *new = malloc(sizeof(MapNode));
        new->dest = Common_get_number_lstrip_ul(&line);
        new->source = Common_get_number_lstrip_ul(&line);
        new->range = Common_get_number_lstrip_ul(&line);

        if (map == NULL || map->source > new->source) {
            new->next = map;
            map = new;
            continue;
        }

        MapNode *find, *prev;
        find = map;
        while (find != NULL && find->source <= new->source) {
            prev = find;
            find = find->next;
        }
        new->next = find;
        prev->next = new;
    } while (head = head->next);

    *head_ptr = head;
    return map;
}

unsigned long map(MapNode *map, unsigned long val) {
    do {
        if (val < map->source) {
            return val;
        }

        if (val < map->source + map->range) {
            return map->dest + val - map->source;
        }

    } while (map = map->next);
    return val;
}

Range *map_range(MapNode *map, Range *r) {
    MapNode *map_head = map;
    Range *mapped = malloc(sizeof(Range));
    Range *head = mapped;
    do {
        printf("\nSTART %lu <-> %lu has next -> %p\n", r->start, r->end, r->next);
        do {
            printf("loop %lu <-> %lu mapr %lu <-> %lu\n", r->start, r->end, map->source, map->source + map->range);
            if (r->start < map->source) {
                Range *new = malloc(sizeof(Range));
                new->start = r->start;
                if (r->end <= map->source) {
                    printf("strait %lu <-> %lu\n", r->start, r->end);

                    new->end = r->end;
                    mapped->next = new;
                    mapped = mapped->next;
                    break;
                } else {
                    new->end = map->source - 1;
                    Range *next = malloc(sizeof(Range));
                    next->start = map->source;
                    next->end = r->end;
                    printf("split %lu <-> %lu, %lu <-> %lu\n", new->start, new->end, next->start, next->end);
                    new->next = map_range(map_head, next);
                    mapped->next = new;
                    while (mapped->next) { mapped = mapped->next; };
                    break;
                }
            }
            if (r->start < map->source + map->range) {
                Range *new = malloc(sizeof(Range));
                new->start = map->dest + r->start - map->source;
                if (r->end <= map->source + map->range) {
                    new->end = map->dest + r->end - map->source;
                    printf("map %lu <-> %lu to %lu <-> %lu\n", r->start, r->end, new->start, new->end);
                    mapped->next = new;
                    mapped = mapped->next;
                    break;
                } else {
                    new->end = map->dest + map->range - 1;
                    Range *next = malloc(sizeof(Range));
                    next->start = map->source + map->range;
                    next->end = r->end;
                    printf("map split %lu <-> %lu, %lu <-> %lu\n", new->start, new->end, next->start, next->end);
                    new->next = map_range(map_head, next);
                    mapped->next = new;
                    while (mapped->next) { mapped = mapped->next; };
                    break;
                }
            }
            if (map->next == NULL) {
                printf("end %lu <-> %lu, %p\n", r->start, r->end, map->next);
                Range *new = malloc(sizeof(Range));
                new->start = r->start;
                new->end = r->end;
                mapped->next = new;
                mapped = mapped->next;
            }
        } while (map = map->next);
        map = map_head;
    } while (r = r->next);
    printf("END\n");
    return head->next;
}

unsigned long get_min(Range *r) {
    unsigned long min = ULONG_MAX;
    do {
        if (r->start < min) {
            min = r->start;
        }
    } while (r = r->next);
    return min;
}

void Day5_solve() {
    Node *head = Common_readFile("AoC5/day5.txt");
    int seed_count = Common_count_occurances(head->value, ' ');

    unsigned long seeds[seed_count];
    parse_seeds(head->value, seeds, seed_count);

    head = head->next->next;

    MapNode *seed_to_soil = parse_map(&head);
    MapNode *soil_to_fert = parse_map(&head);
    MapNode *fert_to_water = parse_map(&head);
    MapNode *water_to_light = parse_map(&head);
    MapNode *light_to_temp = parse_map(&head);
    MapNode *temp_to_humi = parse_map(&head);
    MapNode *humi_to_loc = parse_map(&head);

    unsigned long min_loc = ULONG_MAX;
    for (int i = 0; i < seed_count; i++) {
        unsigned long soil = map(seed_to_soil, seeds[i]);
        unsigned long fert = map(soil_to_fert, soil);
        unsigned long water = map(fert_to_water, fert);
        unsigned long light = map(water_to_light, water);
        unsigned long temp = map(light_to_temp, light);
        unsigned long humi = map(temp_to_humi, temp);
        unsigned long loc = map(humi_to_loc, humi);

        if (loc < min_loc) {
            min_loc = loc;
        }
    }

    Range *seeds_ranges = NULL;
    for (int i = 0; i < seed_count; i += 2) {
        Range *new = malloc(sizeof(Range));
        new->start = seeds[i];
        new->end = seeds[i] + seeds[i+1] - 1;
        new->next = seeds_ranges;
        seeds_ranges = new;
    }

    Range *soils = map_range(seed_to_soil, seeds_ranges);
    Range *ferts = map_range(soil_to_fert, soils);
    Range *waters = map_range(fert_to_water, ferts);
    Range *lights = map_range(water_to_light, waters);
    Range *temps = map_range(light_to_temp, lights);
    Range *humis = map_range(temp_to_humi, temps);
    Range *locs = map_range(humi_to_loc, humis);


    unsigned long min_loc_range = get_min(locs);

    printf("Answer 1st: %lu\n", min_loc);
    printf("Answer 2nd: %lu\n", min_loc_range);
}
