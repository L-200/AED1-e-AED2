#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "avltree.h"

AVLTree* initialize_avltree() {
    return NULL;
};

char is_empty_avltree(AVLTree *t) {
    return t == NULL;
}

int height (AVLTree* t) {
    if ( t == NULL) {
        return 0;
    }
    return t->h;
}

int get_height_avltree(AVLTree *t) {
    if(t == NULL) {
        return 0;
    }

    int l = get_height_avltree(t->l);
    int r = get_height_avltree(t->r);

    return 1 + (l > r ? l : r);
}

int balance (AVLTree* t) {
    if ( t == NULL ) {
        return 0;
    }
    return height(t->l) - height(t->r);
}

int max (int h1, int h2) {
    if (h1 > h2) {
        return h1;
    } else {
        return h2;
    }
}

AVLTree* rotate_left_avltree (AVLTree *A) {
    AVLTree* B = A->r;
    AVLTree* C = B->l;

    B->l = A;
    A->r = C;

    A->h = max(height(A->l), height(A->r)) + 1;
    B->h = max(height(B->l), height(B->r)) + 1;

    return B;
}

AVLTree* rotate_right_avltree (AVLTree* A) {
    AVLTree* B = A->l;
    AVLTree* C = B->r;

    B->r = A;
    A->l = C;

    A->h = max(height(A->l), height(A->r)) + 1;
    B->h = max(height(B->l), height(B->r)) + 1;

    return B;
}

AVLTree* append_avltree(AVLTree **t, int value) {
    if (*t == NULL) {
        *t = malloc(sizeof(AVLTree));
        (*t)->v = value;
        (*t)->l = NULL;
        (*t)->r = NULL;
        (*t)->h = 1;
        return *t;
    } 
    if(value < (*t)->v) {
        (*t)->l = append_avltree(&(*t)->l, value);
    } else if(value > (*t)->v) {
        (*t)->r = append_avltree(&(*t)->r, value);
    } else {
        return *t;
    }

    (*t)->h = 1 + max(height((*t)->r), height((*t)->l));
    int balanco = balance(*t);

    if(balanco > 1) {
        if(value > (*t)->l->v) 
            (*t)->l = rotate_left_avltree((*t)->l);
        return rotate_right_avltree(*t);
    } 
    else if (balanco < -1) {
        if(value < (*t)->r->v) 
            (*t)->r = rotate_right_avltree((*t)->r);
        return rotate_left_avltree(*t);
    }

    return *t;
}

void _append_from_vector_avltree(AVLTree **t, int v[], int i, int j) {
    if (i <= j) {
        int m = i + (j - i) / 2;
        
        *t = append_avltree(t, v[m]);

        _append_from_vector_avltree(t, v, i, m - 1);
        _append_from_vector_avltree(t, v, m + 1, j);
    }
}

void append_random_values_avtree(AVLTree **t, int tam) {
    clock_t clocker = clock();

    int i, init;
    int v[tam];

    srand(clocker);
    init = rand() % tam;
    v[0] = init;

    for(i = 1; i < tam; i++) {
        v[i] = v[i-1] + rand() % tam;
    }

    _append_from_vector_avltree(t, v, 0, tam - 1);
}

AVLTree* search_first_avltree(AVLTree *t, int v) {
    if(t == NULL || t->v == v) {
        return t;
    }
    if(v < t->v) {
        return search_first_avltree(t->l, v);
    } else {
        return search_first_avltree(t->r, v);
    }
}

void walk_tree_pre_order_avltree(AVLTree *t, void (*func)(int v)) {
    if(is_empty_avltree(t)) {
        return;
    }
    func(t->v);
    walk_tree_pre_order_avltree(t->l, func);
    walk_tree_pre_order_avltree(t->r, func);
}

void walk_tree_in_order_avltree(AVLTree *t, void (*func)(int v)) {
    if(is_empty_avltree(t)) {
        return;
    }
    walk_tree_in_order_avltree(t->l, func);
    func(t->v);
    walk_tree_in_order_avltree(t->r, func);
}

void walk_tree_post_order_avltree(AVLTree *t, void (*func)(int v)) {
    if(is_empty_avltree(t)) {
        return;
    }
    walk_tree_post_order_avltree(t->l, func);
    walk_tree_post_order_avltree(t->r, func);
    func(t->v);
}

char has_only_child_avltree(AVLTree *t) {
    return (!t->l && t->r) || (t->l && !t->r);
}

char no_child_avltree(AVLTree *t) {
    return !t->r && !t->l; 
}

void foo_avltree(AVLTree *t, AVLTree *b, AVLTree *s) {
    if(b->r == t) {
        b->r = s;
    } else {
        b->l = s;
    }
}

void clear_avltree (AVLTree **t) {
    if(*t != NULL) {
        clear_avltree(&((*t)->l));
        clear_avltree(&((*t)->r));
    } else {
        free(*t);
    }
    *t = NULL;
}
