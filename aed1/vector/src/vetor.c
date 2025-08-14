#include "../include/vetor.h"
#include <stdlib.h>
#include <stdio.h>
#include <error.h>

Vector* initialize_v(int tamanho) {
    Vector* vet = (Vector*) malloc(sizeof(Vector));
    vet->tam = tamanho;
    vet->v = malloc(sizeof(int)*tamanho);
    return vet;
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
    int j;
    srand(seed);
    for(j = 0; j < size; j++) {
        v->v[j] = (rand() % size / 2) + 1;
    }

}

void randomize_values_asc_v(Vector* v, int seed, int size) {
    int a = 1, j;
    srand(seed);
    for(j = 0; j < size; j++) {
        a = a + (rand() % size / 2) + 1;
        set_v(v, j, a);
    }
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
        int meio = (inicio + fim) /2;
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
    int i, j, aux;
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
    if(vet == NULL || vet->tam <= 1) {
        return;
    }
    int i, j, aux;
    for(i=0; i < vet->tam; i++) {
        aux = vet->v[i];
        j = i-1;
        while (j >= 0 && vet->v[j] > aux) {
            vet->v[j+1] = vet->v[j];
            j--;
        }
        vet->v[j+1] = aux;
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

void recursive_quick_sort_v(Vector* vet, int inicio, int fim) {
    int i = inicio;
    int j = fim;
    int aux;
    int pivo = vet->v[(inicio+fim)/2];
    while(i <= j) {
        while ( i <= fim && vet->v[i] < pivo) {i++;}
        while ( j >= inicio && vet->v[j] > pivo) {j--;}
        if(i <= j) {
            aux = vet->v[i];
            vet->v[i] = vet->v[j];
            vet->v[j] = aux;
            i++;
            j--;
        }
    }
    if ( i < fim) {recursive_quick_sort_v(vet, i, fim);}
    if ( j > inicio) {recursive_quick_sort_v(vet, inicio, j);}
}

void quick_sort_v(Vector* vet) {
    if (vet == NULL || vet->tam <= 1) {
        return;
    }
    int fim = vet->tam -1;
    recursive_quick_sort_v(vet, 0, fim);
}

void merge_v(Vector* vet, int inicio, int meio, int fim) {
    int i = inicio;
    int j = meio+1;
    int k = 0;
    int* temp = (int*) malloc(sizeof(int) * (fim - inicio + 1));
    while(i <= meio && j <= fim) {
        if(vet->v[i] <= vet->v[j]) {
            temp[k] = vet->v[i];
            k++;
            i++;
        } else {
            temp[k] = vet->v[j];
            k++;
            j++;
        }
    }
    while(i <= meio) {
        temp[k] = vet->v[i];
        k++;
        i++;
    }
    while(j <= fim) {
        temp[k] = vet->v[j];
        k++;
        j++;
    }
    k = 0;
    for(i = inicio; i <= fim; i++) {
        vet->v[i] = temp[k];
        k++;
    }
    free(temp);
}

void recursive_merge_sort_v(Vector* vet, int inicio, int fim) {
    if (inicio >= fim) {
        return;
    }
    int meio = (inicio + fim)/2;
    recursive_merge_sort_v(vet, inicio, meio);
    recursive_merge_sort_v(vet, meio+1, fim);
    merge_v(vet, inicio, meio, fim);
}

void merge_sort_v(Vector* vet) {
    if(vet == NULL || vet->tam <= 1) {
        return;
    }
    recursive_merge_sort_v(vet, 0, vet->tam - 1);
}