#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include <time.h>
#include <math.h>

int main () {

    srand(time(NULL));
    int seed = rand();
    int size = 1000000;
    
    printf("Criando vetor com 2.000.000 de elementos\n");
    Vector *vetor_testes = initialize_v(size);
    printf("Populando vetor com números aleatórios em ordem crescente\n");
    randomize_values_asc_v(vetor_testes, seed, size);

    printf("Posições 1.000.000 a 1.000.030  para provar que o vetor realmente é aleatório e em ordem crescente : ");
    for(int i = 1000000; i< 1000030; i++) {
        printf("%d ||", vetor_testes->v[i]);
    }

    //escolha dos números que serão buscados nos testes
    int qnt_testes = 30;
    int vet_testes_buscas[qnt_testes];
    for (int numero_teste = 0; numero_teste < qnt_testes; numero_teste++) {
        vet_testes_buscas[numero_teste] = vetor_testes->v[rand() % size];
    }

    printf("Realizando %d buscas sequenciais por um elemento em uma posição aleatoria\n", qnt_testes);

    double tempos_search_sequencial[qnt_testes];
    double somatorio_tempos = 0;

    for(int i = 0; i < qnt_testes; i++) {
        
        clock_t inicio_ticks = clock();
        if (search_sequencial_v(vetor_testes, vet_testes_buscas[i])) {
            printf("Numero encontrado com sucesso no teste %d!\n", i+1);
        } else {
            printf("ERRO NO TESTE %d!\n", i);
        }
        clock_t fim_ticks = clock();
        tempos_search_sequencial[i] = (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC;
        somatorio_tempos += tempos_search_sequencial[i];
    } 

    printf("Tempos de busca da busca sequencial: \n");
    for (int i = 0; i < qnt_testes; i++) {
        printf("Teste %d: %f\n", i+1, tempos_search_sequencial[i]);
    }

    double media = somatorio_tempos / qnt_testes;
    printf("Média de tempo: %f\n", media);

    //calculo do desvio padrao
    double soma_quadrados = 0.0;
    for (int i = 0; i < qnt_testes; i++) {
        double diff = tempos_search_sequencial[i] - media;
        soma_quadrados += diff * diff; // mais rápido que pow()
    }
    // dividir por (n - 1) e tirar a raiz
    double desvio_padrao = sqrt(soma_quadrados / (qnt_testes - 1));
    printf("Desvio padrão: %f\n", desvio_padrao);

}