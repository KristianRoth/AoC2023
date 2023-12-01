#ifndef COMMON_H
#define COMMON_H

typedef struct Node Node;
struct Node {
    char *value;
    Node *next;
};

Node *Common_readFile(const char *path);
int Common_string_has_suffix(const char *str, const char *suf);
int Common_string_has_prefix(const char *str, const char *pre);


#endif // COMMON_H
