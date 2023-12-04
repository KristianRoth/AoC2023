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
void Common_strip_string(char **str, char *suf);
int Common_get_number(char **str);
int Common_get_number_lstrip(char **str);
int Common_count_occurances(const char *str, char c);

#endif // COMMON_H
