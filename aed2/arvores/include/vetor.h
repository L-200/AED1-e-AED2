#ifndef VETORHEADER_H
#define VETORHEADER_H

typedef struct Vector {
    int tam;
    int* v;
} Vector;

Vector* initialize_v(int tam);

void copy_v(Vector* antigo, Vector* novo);

void destroy_v(Vector* v);

int get_v(Vector* v, int i);

void set_v(Vector* v, int i, int value);

void randomize_values_v(Vector* v, int seed, int size);

void randomize_values_asc_v(Vector* v, int seed, int size);

void show_portion_v(Vector* v, int inicio, int);

void swap_v(int* a, int* b);

int search_sequencial_v(Vector* v, int i);

int search_binario_v(Vector* v, int i);

void bubble_sort_v(Vector* v);

void insertion_sort_v(Vector*v);

void selection_sort_v(Vector* v);

int partition_v(Vector *vet, int low, int high);

void recursive_quick_sort_v(Vector *vet, int low, int high);

void quick_sort_v(Vector* vet);

void merge_v(Vector* vet, int inicio, int meio, int fim, int* temp);

void recursive_merge_sort_v(Vector* vet, int inicio, int fim, int* temp);

void merge_sort_v(Vector* vet);

#endif // VETORHEADER_H