#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include <time.h>
#include <math.h>

double calcula_media(double vet[], int quant_testes) {
    double soma_val_testes =  0.0;
    for(int i = 0; i< quant_testes; i++) {
        soma_val_testes += vet[i];
    }
    return soma_val_testes/quant_testes;
}

#include <math.h> // Para usar a função sqrt()

double calcula_desvio_padrao(double vet[], int quant_testes, double media) {
    if (quant_testes <= 1) {
        return 0.0;
    }

    double soma_quadrados_diferencas = 0.0;
    for (int i = 0; i < quant_testes; i++) {
        double diff = vet[i] - media;
        soma_quadrados_diferencas += diff * diff;
    }

    double variancia = soma_quadrados_diferencas / (quant_testes - 1);

    return sqrt(variancia);
}

int main () {

    srand(time(NULL));
    int seed = rand();
    int size = 10000000;
    
    printf("Criando vetor com 10.000.000 de elementos\n");
    Vector *vetor_testes = initialize_v(size);
    printf("Populando vetor com números aleatórios em ordem crescente\n");
    randomize_values_asc_v(vetor_testes, seed, size);

    printf("Posições 5.000.000 a 5.000.030  para provar que o vetor realmente é aleatório e em ordem crescente : ");
    for(int i = 5000000; i< 5000030; i++) {
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

    for(int i = 0; i < qnt_testes; i++) {
        
        clock_t inicio_ticks = clock();
        if (search_sequencial_v(vetor_testes, vet_testes_buscas[i])) {
            printf("Numero encontrado com sucesso no teste %d!\n", i+1);
        } else {
            printf("ERRO NO TESTE %d!\n", i);
        }
        clock_t fim_ticks = clock();
        tempos_search_sequencial[i] = (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC;
    } 

    printf("Tempos de busca da busca sequencial: \n");
    for (int i = 0; i < qnt_testes; i++) {
        printf("Teste %d: %f\n", i+1, tempos_search_sequencial[i]);
    }
    double media = calcula_media(tempos_search_sequencial, qnt_testes);
    printf("Média de tempo: %f\n", media);
    double desvio_padrao = calcula_desvio_padrao(tempos_search_sequencial, qnt_testes, media);
    printf("Desvio padrão: %f\n", desvio_padrao);

}