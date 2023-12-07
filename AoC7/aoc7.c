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
    return  c == 'A' ? 14+48 :
            c == 'K' ? 13+48 :
            c == 'Q' ? 12+48 :
            c == 'J' ? 11+48 :
            c == 'T' ? 10+48 :
            c;
}

int card_to_int_j(char c) {
    return  c == 'A' ? 14+48 :
            c == 'K' ? 13+48 :
            c == 'Q' ? 12+48 :
            c == 'J' ? 1+48 :
            c == 'T' ? 10+48 :
            c;
}

void count_scores(Hand *a) {
    do {
        long long score = 0;
        Rank *r = a->ranks;
        for (int i = 0; i < 5; i++) {
            score = Common_concatenate(score, r != NULL ? r->count : 0);
            r = r != NULL ? r->next : NULL;
        }
        for (int i = 0; i < 5; i++) {
            score = Common_concatenate(score, card_to_int(a->cards[i]));
        }

        a->score = score;
    } while (a = a->next);
}

void count_scores_j(Hand *a) {
    do {
        long long score = 0;
        Rank *r = a->ranks;

        bool first = true;
        for (int i = 0; i < 5; i++) {
            score = Common_concatenate(score, r != NULL ? r->count+a->j_count : a->j_count);
            a->j_count = 0;
            r = r != NULL ? r->next : NULL;
        }

        for (int i = 0; i < 5; i++) {
            score = Common_concatenate(score, card_to_int_j(a->cards[i]));
        }

        a->score = score;
    } while (a = a->next);
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

Hand *sorted_merge(Hand *a, Hand *b) {
    Hand *result = NULL;
    if (a == NULL) return b;
    if (b == NULL) return a;

    if (a->score <= b->score) {
        result = a;
        result->next = sorted_merge(a->next, b);
    } else {
        result = b;
        result->next = sorted_merge(a, b->next);
    }
    return result;
}

Hand *merge_sort(Hand *head) {
    if (head == NULL || head->next == NULL) return head;
    Hand *fast = head;
    Hand *slow = head;
    while (1) {
        if (fast->next == NULL) break;
        fast = fast->next;
        if (fast->next == NULL) break;
        fast = fast->next;
        slow = slow->next;
    }
    Hand *a = slow->next;
    slow->next = NULL;
    a = merge_sort(a);
    Hand *b = merge_sort(head);
    return sorted_merge(a, b);
}


void Day7_solve() {
    Node *head = Common_readFile("AoC7/day7.txt");
    Hand *hands = parse_hands(head);

    count_scores(hands);

    Hand *sorted = merge_sort(hands);
    hands = sorted;
    int sum = 0;
    int index = 1;
    do {
        sum += sorted->bid * (index++);
    } while (sorted = sorted->next);

    prepare_j(hands);
    count_scores_j(hands);

    sorted = merge_sort(hands);


    int sum_j = 0;
    int index_j = 1;
    do {
        sum_j += sorted->bid * (index_j++);
    } while (sorted = sorted->next);


    printf("Answer 1st %ld\n", sum);
    printf("Answer 2nd %ld\n", sum_j);

}
