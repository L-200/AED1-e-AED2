#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "index_btree.h"

BTree* initialize_btree() {
    return NULL;
};

char is_empty_btree(BTree *t) {
    return t == NULL;
}

BTree* find_greater_subtree(BTree *t, int value) {
    if (t == NULL) return NULL;

    if (t->v > value) {
        return t;
    }

    return find_greater_subtree(t->r, value);
}

BTree* find_greater_equal_subtree(BTree *t, int value) {
    if (t == NULL) return NULL;

    if (t->v >= value) {
        return t;
    }

    return find_greater_equal_subtree(t->r, value);
}

BTree* find_less_subtree(BTree *t, int value) {
    if (t == NULL) return NULL;

    if (t->v < value) {
        return t;
    }

    return find_less_subtree(t->l, value);
}

BTree* find_less_equal_subtree(BTree *t, int value) {
    if (t == NULL) return NULL;

    if (t->v <= value) {
        return t;
    }

    return find_less_equal_subtree(t->l, value);
}


BTree* append_btree(BTree **t, int v, int index) {
    if(*t == NULL) {
        *t = malloc(sizeof(BTree));
        (*t)->v = v;
        (*t)->index = index;
        (*t)->l = NULL;
        (*t)->r = NULL;
        return *t;
    } else {
        if((*t)->v >= v) {
            return append_btree(&(*t)->l, v, index);
        } else {
            return append_btree(&(*t)->r, v, index);
        }
    }
}

BTree* append_btree_no_repeat(BTree **t, int v) {
    if(*t == NULL) {
        *t = malloc(sizeof(BTree));
        (*t)->v = v;
        (*t)->l = NULL;
        (*t)->r = NULL;
        return *t;
    } else {
        if((*t)->v > v) {
            return append_btree_no_repeat(&(*t)->l, v);
        } else if((*t)->v < v) {
            return append_btree_no_repeat(&(*t)->r, v);
        } else {
            printf("Valor %d repetido, descartando...\n", v);
            return NULL;
        }
    }
}

#define print_vec(v, n) for(int ppp = 0; ppp < n; ppp++) printf("%d ", v[ppp])

void _append_from_vector_btree(BTree **t, int v[], int i, int j) {
    if (i <= j) {
        int m = i + (j - i) / 2;
        
        append_btree(t, v[m], v[m]);

        _append_from_vector_btree(t, v, i, m - 1);
        _append_from_vector_btree(t, v, m + 1, j);
    }
}

int* append_random_values_btree(BTree **t, int tam) {
    clock_t clocker = clock();

    int i, init;
    int * v = malloc(sizeof(int) * tam);

    srand(clocker);
    init = rand() % 100;
    v[0] = init;

    for(i = 1; i < tam; i++) {
        v[i] = v[i-1] + rand() % 100;
    }

    _append_from_vector_btree(t, v, 0, tam - 1);
    return v;
}

BTree* search_first_btree(BTree *t, int v) {
    if(t == NULL || t->v == v)
        return t;
    if(v < t->v) {
        return search_first_btree(t->l, v);
    } else {
        return search_first_btree(t->r, v);
    }
}

void walk_tree_pre_order_btree(BTree *t, void (*func)(int v)) {
    if(is_empty_btree(t)) {
        return;
    }
    func(t->v);
    walk_tree_pre_order_btree(t->l, func);
    walk_tree_pre_order_btree(t->r, func);
}

void walk_tree_in_order_btree(BTree *t, void (*func)(int v, int index)) {
    if(is_empty_btree(t)) {
        return;
    }
    walk_tree_in_order_btree(t->l, func);
    func(t->v, t->index);
    walk_tree_in_order_btree(t->r, func);
}

int check_greater_btree(BTree *t, int v) {
    if(t == NULL) {
        return 0;
    }
    if(t->v > v) {
        return check_greater_btree(t->r, v) + check_greater_btree(t->l, v) + 1;
    }
    return check_greater_btree(t->r, v) + check_greater_btree(t->l, v);
}

int check_less_btree(BTree *t, int v) {
    if(t == NULL) {
        return 0;
    }
    if(t->v < v) {
        return check_greater_btree(t->r, v) + check_greater_btree(t->l, v) + 1;
    }
    return check_greater_btree(t->r, v) + check_greater_btree(t->l, v);
}

void walk_tree_post_order_btree(BTree *t, void (*func)(int v)) {
    if(is_empty_btree(t)) {
        return;
    }
    walk_tree_post_order_btree(t->l, func);
    walk_tree_post_order_btree(t->r, func);
    func(t->v);
}

char has_only_child_btree(BTree *t) {
    return (!t->l && t->r) || (t->l && !t->r);
}

char no_child_btree(BTree *t) {
    return !t->r && !t->l; 
}

void foo_btree(BTree *t, BTree *b, BTree *s) {
    if(b->r == t) {
        b->r = s;
    } else {
        b->l = s;
    }
}

BTree* _remove_value_btree(BTree *t, BTree *b, int v) {
    BTree *tmp1, *tmp2;
    if(is_empty_btree(t)) {
        return NULL;
    }
    if(t->v == v) {
        if(!(has_only_child_btree(t) || no_child_btree(t))) {
            tmp1 = t->l, tmp2 = tmp1;
            while(tmp1->r) {
                tmp2 = tmp1;
                tmp1 = tmp1->r;               
            }

            BTree* tmp_l = t->l;
            BTree* tmp_r = t->r;
            t->l = tmp1->l;
            t->r = tmp1->r;

            if(tmp_l == tmp1->l) {
                tmp1->l = t;
            } else {
                tmp1->l = tmp_l;
            }

            tmp1->r = tmp_r;
            if(b) {
                foo_btree(tmp1, b, tmp1);                
            }

            b = tmp2;
        }
        if(b) {
            if(t->l) {
                foo_btree(t, b, t->l);
            } else {
                foo_btree(t, b, t->r);
            }
        }

        t = NULL;

        if(b == NULL) {
            return tmp1;
        } else {
            return t;
        }
    }
    if(t->v > v) {
        return _remove_value_btree(t->l, t, v);
    } else {
        return _remove_value_btree(t->r, t, v);
    }
}

BTree* remove_value_btree(BTree *t, int v) {
    return _remove_value_btree(t, NULL, v);
}

int get_height_btree(BTree *t) {
    if(t == NULL) {
        return 0;
    }

    int l = get_height_btree(t->l);
    int r = get_height_btree(t->r);

    return 1 + (l > r ? l : r);
}

void clear_btree(BTree **t) {
    if(*t != NULL) {
        clear_btree(&((*t)->l));
        clear_btree(&((*t)->r));
    } else {
        free(*t);
    }
    *t = NULL;
}