#include "../include/vetor.h"
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <time.h>

Vector* initialize_v(int tamanho) {
    Vector* vet = (Vector*) malloc(sizeof(Vector));
    vet->tam = tamanho;
    vet->v = malloc(sizeof(int)*tamanho);
    return vet;
}

void copy_v(Vector* antigo, Vector* novo) {
    
    for(int i = 0; i < antigo->tam; i++) {
        novo->v[i] = antigo->v[i];
    }
}

void destroy_v(Vector* v) {
    if (v) {
        free(v->v);
        free(v);
    }
}

int get_v(Vector* vet, int i) {
    if(i> vet->tam) {
        error(EXIT_FAILURE, 0, "Index fora dos limites");
    }
    return vet->v[i];
}

void set_v(Vector* vet, int i, int value) {
    if(i> vet->tam) {
        error(EXIT_FAILURE, 0, "Index fora dos limites");
    }
    vet->v[i] = value;
}


void randomize_values_v(Vector* v, int seed, int size) {
   srand(seed);
    for (int i = 0; i < size; i++) {
        v->v[i] = i + 1;
    }
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = v->v[i];
        v->v[i] = v->v[j];
        v->v[j] = tmp;
    }
}

void randomize_values_asc_v(Vector* v, int seed, int size) {
    int a = 1, j;
    srand(seed);
    for(j = 0; j < size; j++) {
        a = a + (rand() % 10) + 1;
        set_v(v, j, a);
    }
}

void show_portion_v(Vector *v, int inicio, int fim) {
    for (int i = inicio; i < fim-1; i++) {
        printf("%d | ", v->v[i]);
    }
    printf("%d", v->v[fim-1]);
    printf("\n");
}

void swap_v(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int search_sequencial_v(Vector* vet, int value) {
    int i;
    for(i=0 ; i < vet->tam; i++) {
        if(vet->v[i] == value) {
            return 1;
        }
    }
    return 0;
}

int search_binario_v(Vector* vet, int value) {
    int inicio = 0;
    int fim = vet->tam - 1;
    while(inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        if(vet->v[meio] > value) {
            fim = meio-1;
        }
        else if (vet->v[meio] < value) {
            inicio = meio+1;
        }
        else {
            return 1;
        }
    }
    return 0;
}

void bubble_sort_v(Vector* vet) {
    if(vet == NULL || vet->tam <= 1) {
        return;
    }
    int i, j;
    int aux;
    for(i = 0; i < vet->tam - 1; i++) {
        for(j = 0; j < vet->tam - 1 - i; j++) {
            if(vet->v[j] > vet->v[j+1]) {
                aux = vet->v[j+1];
                vet->v[j+1] = vet->v[j];
                vet->v[j] = aux;
            }
        }
    }
}

void insertion_sort_v(Vector* vet) {
    for (int i = 1; i < vet->tam; i++) {
        int key = vet->v[i];
        int j = i - 1;

        while (j >= 0 && vet->v[j] > key) {
            vet->v[j + 1] = vet->v[j];
            j = j - 1;
        }
        vet->v[j + 1] = key;
    }
}

void selection_sort_v(Vector* vet){
    if(vet == NULL || vet->tam <= 1) {
            return;
        }
    int i, j, menor, aux;
    for(i=0; i < vet->tam; i++) {
        menor = i;
        for(j = i+1; j < vet->tam; j++) {
            if(vet->v[j] < vet->v[menor]) {
                menor = j;
            }
        }
        if(menor != i) {
            aux = vet->v[i];
            vet->v[i] = vet->v[menor];
            vet->v[menor] = aux; 
        }
    }
}

int partition_v(Vector *vet, int low, int high) {
    
    int pivot = vet->v[high];
    int menor_pivo = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (vet->v[j] < pivot) {
            menor_pivo++;
            swap_v(&vet->v[menor_pivo], &vet->v[j]);
        }
    }
    
    swap_v(&vet->v[menor_pivo + 1], &vet->v[high]);  
    return menor_pivo + 1;
}

void recursive_quick_sort_v(Vector *vet, int low, int high) {
    if (low < high) {
        
        int particao = partition_v(vet, low, high);

        recursive_quick_sort_v(vet, low, particao - 1);
        recursive_quick_sort_v(vet, particao + 1, high);
    }
}

void quick_sort_v(Vector *v) {
    recursive_quick_sort_v(v, 0, v->tam - 1);
}

void merge_v(Vector* vet, int inicio, int meio, int fim, int* temp) {
    int i = inicio;
    int j = meio+1;
    int k = inicio;

    while(i <= meio && j <= fim) {
        if(vet->v[i] <= vet->v[j]) {
            temp[k++] = vet->v[i++];
        } else {
            temp[k++] = vet->v[j++];
        }
    }
    while(i <= meio) {
        temp[k++] = vet->v[i++];
    }
    while(j <= fim) {
        temp[k++] = vet->v[j++];
    }

    for(i = inicio; i <= fim; i++) {
        vet->v[i] = temp[i];
    }
}

void recursive_merge_sort_v(Vector* vet, int inicio, int fim, int* temp) {
    if (inicio >= fim) return;

    int meio = (inicio + fim)/2;
    recursive_merge_sort_v(vet, inicio, meio, temp);
    recursive_merge_sort_v(vet, meio+1, fim, temp);
    merge_v(vet, inicio, meio, fim, temp);
}

void merge_sort_v(Vector* vet) {
    if(vet == NULL || vet->tam <= 1) return;

    int* temp = (int*) malloc(sizeof(int) * vet->tam);
    recursive_merge_sort_v(vet, 0, vet->tam - 1, temp);
    free(temp);
}