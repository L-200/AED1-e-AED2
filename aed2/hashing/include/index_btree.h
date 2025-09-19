#ifndef BTREE_H
#define BTREE_H

typedef struct BTree {
    struct BTree *l, *r;
    int v, index;
} BTree;

BTree* initialize_btree();

char is_empty_btree(BTree *t);

BTree* append_btree(BTree **t, int v, int index);

BTree* append_btree_no_repeat(BTree **t, int v);

BTree* find_greater_subtree(BTree *t, int value);

BTree* find_greater_equal_subtree(BTree *t, int value);

BTree* find_less_subtree(BTree *t, int value);

BTree* find_less_equal_subtree(BTree *t, int value);

int check_greater_btree(BTree *t, int v);

int check_less_btree(BTree *t, int v);

int* append_random_values_btree(BTree **t, int tam);

BTree* search_first_btree(BTree *t, int v);

void walk_tree_pre_order_btree(BTree *t, void (*func)(int v));

void walk_tree_in_order_btree(BTree *t, void (*func)(int v, int index));

void walk_tree_post_order_btree(BTree *t, void (*func)(int v));

int get_height_btree(BTree *t);

BTree* remove_value_btree(BTree *t, int v);

void clear_btree(BTree **t);

#endif // BTREE_H