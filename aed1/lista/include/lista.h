#ifndef LISTAHEADER_H
#define LISTAHEADER_H

typedef struct Node {
    int value;
    struct Node* prox;
} Node;

typedef struct Int_Linked_List {
    Node* prim;
} Int_Linked_List;

/* Construtor da lista encadeada */
Int_Linked_List* initialize_l();

/* Adiciona elemento ao final da lista encadeada */
void append_l(Int_Linked_List* l, int value);

/* Adiciona elementos ao final da lista encadeada */
void append_values_l(Int_Linked_List* l, int n, int values[]);

/*Adiciona elementos na ordem inversa do vetor dado*/
void append_values_reverse_l(Int_Linked_List* l, int n, long values[]);

/* Método get elemento da lista encadeada */
int get_l(Int_Linked_List* l, int i);

/*Método get tamanho da lista encadeada*/
int get_size_l(Int_Linked_List* l);

/* Remove último elemento da lista e retorna */
int pop_l(Int_Linked_List* l);

/* Remove toda a lista usando a função anterior*/
void destroy_l(Int_Linked_List* l);

/* Randomiza valores em uma lista de forma aleatória */
void randomize_values_l(Int_Linked_List* l, int seed, int size);

/* Randomiza valores em uma lista de forma aleatória, mas ordenada em ascendencia */
void randomize_values_asc_l(Int_Linked_List* l, int seed, int size);

/* Método set elemento da lista encadeada */
void set_l(Int_Linked_List* l, int i, int value);

/* Busca sequencialmente por um valor na lista*/
int search_sequencial_l(Int_Linked_List* l, int value);

#endif // LISTAHEADER_H