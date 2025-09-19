#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

unsigned hash(int key) {
    return (unsigned)key % SIZE;
}

Node_hash* create_node_hash(int key, int index) {
    Node_hash* new_node = (Node_hash*)malloc(sizeof(Node_hash));
    new_node->key = key;
    new_node->index = index;
    new_node->next = NULL;
    return new_node;
}

void init_hashtable(hashtable* h) {
    for (int i = 0; i < SIZE; i++) {
        h->table[i] = NULL;
    }
    h->colisions_number = 0;
}

void insert_hash(int key, int index, hashtable* h) {
    unsigned idx = hash(key);
    Node_hash* new_node = create_node_hash(key, index);
    if (h->table[idx] == NULL) {
        h->table[idx] = new_node;
    } else {
        h->colisions_number++;
        Node_hash* current = h->table[idx];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

Node_hash* get_hash_node(int key, hashtable* h) {
    unsigned idx = hash(key);
    Node_hash* current = h->table[idx];
    while (current != NULL) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int search_hash(int key, hashtable* h) {
    return get_hash_node(key, h) != NULL;
}

int return_colisons (hashtable* h) {
    return h->colisions_number;
}