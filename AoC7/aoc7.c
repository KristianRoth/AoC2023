#include "aoc7.h"
#include "../common.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

void calc_ranks(Hand *a) {
    Rank *ranks = NULL;
    for (int i = 0; i < 5; i++) {
        Rank *tmp = ranks;
        while (tmp != NULL && tmp->rank != a->cards[i]) tmp = tmp->next;
        if (tmp == NULL) {
            Rank *new = malloc(sizeof(Rank));
            new->count = 1;
            new->rank = a->cards[i];
            new->next = ranks;
            ranks = new;
        } else {
            tmp->count++;
        }
    }
    Rank *sorted = NULL;
    int count = 0;
    while (ranks != NULL) {
        Rank *next = ranks->next;
        if (sorted == NULL || sorted->count < ranks->count) {
            ranks->next = sorted;
            sorted = ranks;
        } else {
            Rank *find = sorted;
            while (find->next != NULL && find->next->count > ranks->count) {
                find = find->next;
            }
            ranks->next = find->next;
            find->next = ranks;
        }
        count++;
        ranks = next;
    }
    a->rank_count = count;
    a->ranks = sorted;
}

Hand *parse_hands(Node *head) {
    Hand *hands = NULL;
    do {
        Hand *h = malloc(sizeof(Hand));
        memcpy(&h->cards, head->value, 5);
        Common_strip_string(&head->value, "XXXXX ");
        h->bid = Common_get_number_lstrip(&head->value);
        h->next = hands;
        calc_ranks(h);
        hands = h;
    } while (head = head->next);
    return hands;
}

int card_to_int(char c) {
    return  c == 'A' ? 14 :
            c == 'K' ? 13 :
            c == 'Q' ? 12 :
            c == 'J' ? 11 :
            c == 'T' ? 10 :
            c - 48;
}

bool compare_hands(Hand *a, Hand *b) {
    if (a->rank_count != b->rank_count) {
        return a->rank_count < b->rank_count;
    }
    if (a->ranks->count != b->ranks->count) {
        return a->ranks->count > b->ranks->count;
    }
    if (a->ranks->next->count != b->ranks->next->count) {
        return a->ranks->next->count > b->ranks->next->count;
    }
    for (int i = 0; i < 5; i++) {
        if (a->cards[i] != b->cards[i]) {
            return card_to_int(a->cards[i]) > card_to_int(b->cards[i]);
        }
    }
    return true;
}

void prepare_j(Hand *h) {
    do {
        Rank *r = h->ranks;
        if (r->rank == 'J') {
            h->ranks = r->next;
            h->rank_count = h->rank_count != 1 ? h->rank_count - 1 : 1;
            h->j_count = r->count;
        } else {
            while (r->next != NULL && r->next->rank != 'J') r = r->next;
            if (r->next != NULL) {
                h->j_count = r->next->count;
                r->next = r->next->next;
                h->rank_count = h->rank_count != 1 ? h->rank_count - 1 : 1;
            }
        }
    } while (h = h->next);
}

int card_to_int_j(char c) {
    return  c == 'A' ? 14 :
            c == 'K' ? 13 :
            c == 'Q' ? 12 :
            c == 'J' ? 1 :
            c == 'T' ? 10 :
            c - 48;
}

bool compare_hands_j(Hand *a, Hand *b) {
    if (a->rank_count != b->rank_count) {
        return a->rank_count < b->rank_count;
    }
    if (a->rank_count > 0 && a->j_count != 5 && (a->ranks->count + a->j_count != b->ranks->count + b->j_count)) {
        return a->ranks->count + a->j_count > b->ranks->count + b->j_count;
    }
    if (a->rank_count > 1 && (a->ranks->next->count != b->ranks->next->count)) {
        return a->ranks->next->count > b->ranks->next->count;
    }
    for (int i = 0; i < 5; i++) {
        if (a->cards[i] != b->cards[i]) {
            return card_to_int_j(a->cards[i]) > card_to_int_j(b->cards[i]);
        }
    }
    return true;
}


void Day7_solve() {
    Node *head = Common_readFile("AoC7/day7.txt");
    Hand *hands = parse_hands(head);

    Hand *sorted = NULL;
    while (hands != NULL) {
        Hand *next = hands->next;
        if (sorted == NULL || compare_hands(sorted, hands)) {
            hands->next = sorted;
            sorted = hands;
        } else {
            Hand *find = sorted;
            while (find->next != NULL && compare_hands(hands, find->next)) find = find->next;
            hands->next = find->next;
            find->next = hands;
        }
        hands = next;
    }
    hands = sorted;

    int sum = 0;
    int index = 1;
    do {
        sum += sorted->bid * (index++);
    } while (sorted = sorted->next);

    prepare_j(hands);

    sorted = NULL;
    while (hands != NULL) {
        Hand *next = hands->next;
        if (sorted == NULL || compare_hands_j(sorted, hands)) {
            hands->next = sorted;
            sorted = hands;
        } else {
            Hand *find = sorted;
            while (find->next != NULL && compare_hands_j(hands, find->next)) find = find->next;
            hands->next = find->next;
            find->next = hands;
        }
        hands = next;
    }
    hands = sorted;

    int sum_j = 0;
    int index_j = 1;
    do {
        sum_j += sorted->bid * (index_j++);
    } while (sorted = sorted->next);


    printf("Answer 1st %ld\n", sum);
    printf("Answer 2nd %ld\n", sum_j);

}
