#ifndef VETORHEADER_H

#define VETORHEADER_H

typedef struct Vector {
    int tam;
    long* v;
} Vector;

Vector* initialize_v(int tam);

int get_v(Vector* v, int i);

void set_v(Vector* v, int i, long value);

int search_sequencial_v(Vector* v, long i);

int search_binario_v(Vector* v, long i);

void bubble_sort_v(Vector* v);

void insertion_sort_v(Vector*v);

void selection_sort_v(Vector* v);

void recursive_quick_sort_v(Vector* vet, int inicio, int fim);

void quick_sort_v(Vector* v);

void merge_v(Vector* vet, int inicio, int meio, int fim);

void recursive_merge_sort_v(Vector* vet, int inicio, int fim);

void merge_sort_v(Vector* v);

void randomize_values_v(Vector* v, int seed, int size);

void randomize_values_asc_v(Vector* v, int seed, int size);

#endif