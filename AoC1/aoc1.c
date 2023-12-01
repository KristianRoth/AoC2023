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

int get_digit_end(char* value) {
    if (isdigit(*(value + strlen(value) - 1))) {
        return *(value + strlen(value) - 1) - 48;
    }
    for (int i = 0; i < 9; i++) {
        if (Common_string_has_suffix(value, numbers[i])) {
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
    char *substr = malloc(sizeof(value));
    strcpy(substr, value);
    for (int i = strlen(value); i >= 0; i--) {
        substr[i] = '\0';
        if (num = get_digit_end(substr)) {
            sum += num;
            break;
        }
    }
    free(substr);
    return sum;
}

void Day1_solve() {
    Node *head = Common_readFile("AoC1/day1.txt");
    Node *input = head;
    int sum = 0;
    int sumSpelled = 0;
    while (input != NULL) {
        sum += get_number(input->value);
        sumSpelled += get_number_spelled(input->value);
        input = input->next;
    }
    printf("Answer 1st: %d\n", sum);
    printf("Answer 2nd: %d\n", sumSpelled);
}

