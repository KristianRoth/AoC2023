#include "aoc4.h"
#include "../common.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

CardNode *parse_cards(Node *head) {
    CardNode *cards = malloc(sizeof(CardNode));
    CardNode *tail = cards;
    do {
        char *value = head->value;
        Card *card = malloc(sizeof(Card));
        Common_strip_string(&value, "Card XXX: ");
        for (int i = 0; i < WINNING_AMOUNT; i++) {
            card->winning[i] = Common_get_number_lstrip(&value);
        }
        Common_strip_string(&value, " | ");
        for (int i = 0; i < NUMBERS_AMOUNT; i++) {
            card->numbers[i] = Common_get_number_lstrip(&value);
        }
        CardNode *new = malloc(sizeof(CardNode));
        new->card = card;
        tail->next = new;
        tail = new;
    } while (head = head->next);
    return cards->next;
}

int count_winners(Card *card) {
    int winners = 0;
    for (int i = 0; i < WINNING_AMOUNT; i++) {
        for (int j = 0; j < NUMBERS_AMOUNT; j++) {
            if (card->winning[i] == card->numbers[j]) {
                winners++;
                break;
            }
        }
    }
    return winners;
}

int sum_winners(CardNode *cards) {
    int sum = 0;
    do {
        sum += pow(2, count_winners(cards->card)-1);
    } while (cards = cards->next);
    return sum;
}

int sum_copy_winners(CardNode *cards) {
    int sum = 0;
    int cw = WINNING_AMOUNT+1;
    int copies[cw];
    memset(copies, 0, cw*sizeof(int));
    int start = 0;
    do {
        int winners = count_winners(cards->card);
        int card_copies = copies[start%cw] + 1;
        for (int i = 0; i < winners; i++) {
            copies[(start+i+1)%cw] += card_copies;
        }
        sum += card_copies;
        copies[start%cw] = 0;
        start++;
    } while (cards = cards->next);
    return sum;
}

void Day4_solve() {
    Node *head = Common_readFile("AoC4/day4.txt");
    CardNode *cards = parse_cards(head);
    int sum = sum_winners(cards);
    int sum_copy = sum_copy_winners(cards);
    printf("Answer 1st: %i\n", sum);
    printf("Answer 2nd: %i\n", sum_copy);
}
