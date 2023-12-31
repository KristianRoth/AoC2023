#ifndef COMMON_H
#define COMMON_H

typedef struct Node Node;
struct Node {
    char *value;
    Node *next;
};


typedef struct IntNode IntNode;
struct IntNode {
    int value;
    IntNode *next;
};

typedef struct HashNode HashNode;
struct HashNode {
    char* key;
    void* data;
    HashNode* next;
};

typedef struct HashMap HashMap;
struct HashMap {
    int bucket_count;
    unsigned int (*hash_fn)(char*);
    HashNode* buckets[];
};

Node *Common_readFile(const char *path);
int Common_string_has_suffix(const char *str, const char *suf);
int Common_string_has_prefix(const char *str, const char *pre);
void Common_strip_string(char **str, char *suf);
int Common_get_number(char **str);
int Common_get_number_lstrip(char **str);
int Common_count_occurances(const char *str, char c);
unsigned long Common_get_number_ul(char **str);
unsigned long Common_get_number_lstrip_ul(char **str);
long Common_concatenate(long x, long y);
long Common_lcm(long x, long y);
long Common_gcd(long x, long y);
HashMap *Common_hash_create(int bucket_count, unsigned int (*hash_fn)(char*));
void Common_hash_put(HashMap *hm, char *key, void *data);
void *Common_hash_get(HashMap *hm, char *key);
unsigned int Common_hash_string(char *str);
void Common_hash_print(HashMap *hm);
void Common_hash_free(HashMap *hm);
void Common_int_node_print(IntNode *head, char *prefix);
IntNode *Common_rec_get_int_node(char *str);


#endif // COMMON_H
