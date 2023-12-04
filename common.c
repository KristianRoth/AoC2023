#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Node *Common_readFile(const char* path) {
    FILE *inputFile;
    inputFile = fopen(path, "rb");

    if (inputFile == NULL) {
        exit(EXIT_FAILURE);
    }

    Node *prev = malloc(sizeof(Node));
    Node *head = prev;
    Node *next;
    char buff[256];
    size_t len = 0;
    ssize_t read;

    while (fgets(buff, sizeof(buff), inputFile)) {
        next = (Node*)malloc(sizeof(Node));
        next->value = (char*)malloc(strlen(buff));
        strncpy(next->value, buff, strcspn(buff,"\n"));
        prev->next = next;
        prev = next;
    }
    fclose(inputFile);
    return head->next;
}

int Common_string_has_prefix(const char *str, const char *pre) {
    return strncmp(pre, str, strlen(pre)) == 0;
}

int Common_string_has_suffix(const char *str, const char *suf) {
    const char *a = str + strlen(str);
    const char *b = suf + strlen(suf);

    while (a != str && b != suf) {
        if (*--a != *--b) break;
    }
    return b == suf && *a == *b;
}

void Common_strip_string(char **str, char *suf) {
    *str = *str + strlen(suf);
}

int Common_get_number(char **str) {
    int num = atoi(*str);
    *str = *str + snprintf(NULL, 0, "%d", num);
    return num;
}

int Common_get_number_lstrip(char **str) {
    while (!isdigit(**str)) { (*str)++; }
    return Common_get_number(str);
}

int Common_count_occurances(const char *str, char c) {
    int occ = 0;
    for (int i = 0; str[i] != '\n'; i++) {
        if (str[i] == c) {
            occ++;
        }
    }
    return occ;
}
