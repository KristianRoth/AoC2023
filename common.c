#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
