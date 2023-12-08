#include "aoc1.h"
#include "../common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_number(char* value) {
    int sum = 0;
    for (int i = 0; i < strlen(value); i++) {
        if (isdigit(value[i])) {
            sum += 10*(value[i] - 48);
            break;
        }
    }
    for (int i = strlen(value)-1; i >= 0; i--) {
        if (isdigit(value[i])) {
            sum += (value[i] - 48);
            break;
        }
    }
    return sum;
}

char numbers[9][6] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

int get_digit(char* value) {
    if (isdigit(value[0])) {
        return value[0] - 48;
    }
    for (int i = 0; i < 9; i++) {
        if (Common_string_has_prefix(value, numbers[i])) {
            return i + 1;
        }
    }
    return 0;
}

int get_number_spelled(char* value) {
    int sum = 0;
    int num;

    for (int i = 0; i < strlen(value); i++) {
        if (num = get_digit(&value[i])) {
            sum += 10*num;
            break;
        }
    }

    char *str_end = value + strlen(value);
    for (int i = 0; i < strlen(value); i++) {
        if (num = get_digit(str_end - i - 1)) {
            sum += num;
            break;
        }
    }
    return sum;
}

void Day1_solve() {
    Node *head = Common_readFile("AoC1/day1.txt");
    int sum = 0;
    int sumSpelled = 0;
    do {
        sum += get_number(head->value);
        sumSpelled += get_number_spelled(head->value);
    } while (head = head->next);

    printf("Answer 1st: %i\n", sum);
    printf("Answer 2nd: %i\n", sumSpelled);
}

