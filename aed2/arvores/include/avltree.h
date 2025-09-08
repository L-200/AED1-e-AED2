#ifndef AVLTREE_H
#define AVLTREE_H

typedef struct AVLTree {
    struct AVLTree *l, *r;
    int h, v;
} AVLTree;

AVLTree* initialize_avltree();

char is_empty_avltree(AVLTree *t);

AVLTree* append_avltree(AVLTree **t, int v);

void append_from_vector_avltree(AVLTree **t, int v[], int tam);

int height (AVLTree* t);

int balance (AVLTree* t);

int max (int h1, int h2);

AVLTree* rotate_left_avltree (AVLTree* t);

AVLTree* rotate_right_avltree (AVLTree* t);

int search_avltree(AVLTree *t, int v);

void walk_tree_pre_order_avltree(AVLTree *t, void (*func)(int v));

void walk_tree_in_order_avltree(AVLTree *t, void (*func)(int v));

void walk_tree_post_order_avltree(AVLTree *t, void (*func)(int v));

AVLTree* remove_value_avltree(AVLTree *t, int v);

int get_height_avltree(AVLTree *t);

void clear_avltree(AVLTree **t);

#endif // AVLTREE_H