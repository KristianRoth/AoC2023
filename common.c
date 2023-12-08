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
    char buff[512];
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

unsigned long Common_get_number_ul(char **str) {
    char *end;
    unsigned long num = strtoul(*str, &end, 10);
    *str = end;
    return num;
}

unsigned long Common_get_number_lstrip_ul(char **str) {
    while (!isdigit(**str)) { (*str)++; }
    return Common_get_number_ul(str);
}

int Common_count_occurances(const char *str, char c) {
    int occ = 0;
    while (*str != '\0') {
        if (*str == c) {
            occ++;
        }
        str++;
    }
    return occ;
}

long Common_concatenate(long x, long y) {
    long pow = 10;
    while(y >= pow) {
        pow *= 10;
    }
    return x * pow + y;
}

long Common_lcm(long x, long y) {
    return x*y/Common_gcd(x, y);
}

long Common_gcd(long x, long y) {
    while (y != 0) {
        int t = y;
        y = x%y;
        x = t;
    }
    return x;
}

HashMap *Common_hash_create(int bucket_count, int (*hash_fn)(char*)) {
    HashMap *hm = malloc(sizeof(int) + sizeof(void*) + sizeof(void*)*bucket_count);
    hm->bucket_count = bucket_count;
    hm->hash_fn = hash_fn;
    memset(&hm->buckets, 0, sizeof(void*)*bucket_count);
    return hm;
}

void Common_hash_put(HashMap *hm, char *key, void *data) {
    int hash = hm->hash_fn(key)%hm->bucket_count;
    HashNode *new = malloc(sizeof(HashNode));
    new->key  = key;
    new->data = data;
    new->next = hm->buckets[hash];
    hm->buckets[hash] = new;
}

void *Common_hash_get(HashMap *hm, char *key) {
    int hash = hm->hash_fn(key)%hm->bucket_count;
    HashNode *bucket = hm->buckets[hash];
    while (bucket != NULL && strcmp(bucket->key, key)) bucket = bucket->next;
    return bucket != NULL ? bucket->data : NULL;
}

int Common_hash_string(char *str) {
    int a = 112241;
    while (str != str + strlen(str)) a += (a << 5) + a + *(str++);
    return a;
}
