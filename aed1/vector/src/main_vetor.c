#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include <time.h>

int main () {

    srand(time(NULL));
    int seed = rand();
    int size = 1000000;
    
    printf("Criando vetor com 1.000.000 de elementos\n");
    Vector *vetor_testes = initialize_v(size);
    printf("Populando vetor com números aleatórios em ordem crescente\n");
    randomize_values_asc_v(vetor_testes, seed, size);

    printf("Posições 500.000 a 500.050  para provar que o vetor realmente é aleatório e em ordem crescente : ");
    for(int i = 500000; i< 500050; i++) {
        printf("%d ||", vetor_testes->v[i]);
    }

}