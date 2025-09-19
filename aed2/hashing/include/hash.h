#ifndef HASH_H
#define HASH_H

#define SIZE 1000

typedef struct Node_hash {
    int key;
    int index;
    struct Node_hash* next;
} Node_hash;

typedef struct hashtable {
    Node_hash* table[SIZE];
    int colisions_number;
} hashtable;

unsigned hash(int key);
Node_hash* create_node_hash(int key, int index);
void init_hashtable(hashtable* h);
void insert_hash(int key, int index, hashtable* h);
int search_hash(int key, hashtable* h);
Node_hash* get_hash_node(int key, hashtable* h);
int return_colisons (hashtable* h);

#endif // HASH_H