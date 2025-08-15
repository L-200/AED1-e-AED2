#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include <time.h>
#include <math.h>

//funções auxiliares para os testes 


double calcula_media(double vet[], int quant_testes) {
    double soma_val_testes =  0.0;
    for(int i = 0; i< quant_testes; i++) {
        soma_val_testes += vet[i];
    }
    return soma_val_testes/quant_testes;
}


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
    int seed1 = rand();
    int size = 10000000;
    
    printf("Criando vetor com 10.000.000 de elementos\n");
    Vector *vetor_testes_searches = initialize_v(size);
    printf("Populando vetor com números aleatórios em ordem crescente\n");
    randomize_values_asc_v(vetor_testes_searches, seed1, size);

    printf("Posições 5.000.000 a 5.000.030  para provar que o vetor realmente é aleatório e em ordem crescente : ");
    show_portion_v(vetor_testes_searches, 5000000, 5000030);
    printf("\n");

    //escolha dos números que serão buscados nos testes
    int qnt_testes = 30;
    int vet_testes_searches_procurados[qnt_testes];
    for (int numero_teste = 0; numero_teste < qnt_testes; numero_teste++) {
        vet_testes_searches_procurados[numero_teste] = vetor_testes_searches->v[rand() % size];
    }

    printf("\n");

    printf("Realizando %d buscas sequenciais por um elemento em uma posição aleatoria\n", qnt_testes);
    printf("Valores que serão buscados:\n");
     for (int i = 0; i < qnt_testes; i++) {
        printf("%d |", vet_testes_searches_procurados[i]);
    }
    printf("\n");    

    double tempos_search_sequencial[qnt_testes];

    for(int i = 0; i < qnt_testes; i++) {
        
        clock_t inicio_ticks = clock();
        if (search_sequencial_v(vetor_testes_searches, vet_testes_searches_procurados[i])) {
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
    printf("Média de tempo da busca sequencial: %f\n", media);
    double desvio_padrao = calcula_desvio_padrao(tempos_search_sequencial, qnt_testes, media);
    printf("Desvio padrão da busca sequencial: %f\n", desvio_padrao);


    printf("-----------------------------\n");


    printf("Realizando %d buscas binárias pelas mesmos elementos procurados pelo teste anterior\n", qnt_testes);
    for (int i = 0; i < qnt_testes; i++) {
        printf("%d |", vet_testes_searches_procurados[i]);
    }
    printf("\n");
    
    double tempos_search_binario[qnt_testes];

    for(int i = 0; i < qnt_testes; i++) {
        
        clock_t inicio_ticks = clock();
        if (search_binario_v(vetor_testes_searches, vet_testes_searches_procurados[i])) {
            printf("Numero encontrado com sucesso no teste %d!\n", i+1);
        } else {
            printf("ERRO NO TESTE %d!\n", i);
        }
        clock_t fim_ticks = clock();
        tempos_search_binario[i] = (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC;
    } 

    printf("Tempos de busca da busca binária: \n");
    for (int i = 0; i < qnt_testes; i++) {
        printf("Teste %d: %f\n", i+1, tempos_search_binario[i]);
    }
    media = calcula_media(tempos_search_binario, qnt_testes);
    printf("Média de tempo da busca binária: %f\n", media);
    desvio_padrao = calcula_desvio_padrao(tempos_search_binario, qnt_testes, media);
    printf("Desvio padrão da busca binária: %f\n", desvio_padrao);

    destroy_v(vetor_testes_searches); //liberar ram usada pelo vetor_testes_searches

    printf("-------------\n");
    printf("INICIO DOS TESTES DOS SORTS\n");
    printf("-------------\n");

    //criação das seeds que gerarão os mesmos vetores para o sorting
    int seed2 = rand();
    int seed3 = rand();
    int seed4 = rand();
    int seed5 = rand();
    int seed6 = rand();
    printf("Serão gerados 5 vetores identicos e cada algoritmo resolverá os 5\n");


    printf("BUBBLE SORT:\n");
    Vector *bubble_sort1 = initialize_v(size);
    printf("Populando o primeiro vetor com 10.000.000 de elementos aleatorios\n");
    
}