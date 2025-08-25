#include "../include/lista.h"
#include <stdlib.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#define MAX_STRING_SIZE 1000000

Int_Linked_List* initialize_l() {
    Int_Linked_List* list = (Int_Linked_List*) malloc(sizeof(Int_Linked_List));
    list->prim = NULL;

    return list;
}

/* Função para colocar no final da lista */
void append_l(Int_Linked_List* l, int value) {
    Node *i = l->prim;
    Node *new_node = (Node*) malloc(sizeof(Node));

    new_node->value = value;
    new_node->prox = NULL;

    if(i == NULL) {
        l->prim = new_node;
        return;
    }

    while(i->prox != NULL) i = i->prox;

    i->prox = new_node;
}

void append_values_l(Int_Linked_List* l, int n, int values[]) {
    int j;
    for(j = 0; j < n; j++) {
        append_l(l, values[j]);
    }
}

void append_values_reverse_l(Int_Linked_List* l, int n, int values[]) {
    int j;
    for(j = n - 1; j >= 0; j--) {
        append_l(l, values[j]);
    }
}


int get_l(Int_Linked_List* l, int i) {
    Node* n;

    for(n = l->prim; n != NULL; n = n->prox) {
        if(i == 0) {
            return n->value;
        }
        i--;
    }

    error(EXIT_FAILURE, 0, "Index fora dos limites");
    return -1;
}

int get_size_l(Int_Linked_List* l) {
    if (l->prim == NULL) {
        return 0;
    }
    Node* n = l->prim;
    int i = 1;
    for(;n->prox != NULL;i++) {
        n = n->prox;
    }
    return i;
}

int pop_l(Int_Linked_List* l) {
    Node* n = l->prim;
    int value;

    if(n == NULL) {
        error(EXIT_FAILURE, 0, "Lista está vazia");
    }
    
    /* Caso seja o primeiro elemento */
    if(n->prox == NULL) {
        value = n->value;
        l->prim = NULL;
        free(n);
        return value;
    }

    while(n->prox->prox != NULL) n = n->prox;

    value = n->prox->value;
    free(n->prox);
    n->prox = NULL;

    return value;
}

void destroy_l(Int_Linked_List* l) {
    while(l->prim != NULL) {
        pop_l(l);
    }
    free(l);
}

void randomize_values_l(Int_Linked_List* l, int seed, int size) {
    int j;
    srand(seed);
    for(j = 0; j < size; j++) {
        append_l(l, (rand() % size / 2) + 1);
    }

}

void randomize_values_asc_l(Int_Linked_List* l, int seed, int size) {
    int a = 1, j;
    srand(seed);
    for(j = 0; j < size; j++) {
        a = a + (rand() % size / 2) + 1;
        append_l(l, a);
    }
}

void set_l(Int_Linked_List* l, int i, int value) {
    Node* n;

    for(n = l->prim; n != NULL; n = n->prox) {
        if(i == 0) {
            n->value = value;
            return;
        }
        i--;
    }

    error(EXIT_FAILURE, 0, "Index fora dos limites");
}


int search_sequencial_l(Int_Linked_List* l, int value) {
    Node* n;
    for(n = l->prim; n != NULL; n = n->prox) {
        if (n->value == value) {
            return 1;
        }
    }
    return 0;
}
