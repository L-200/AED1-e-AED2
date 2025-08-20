#ifndef DADOS_ESTATISTICOS_H
#define DADOS_ESTATISTICOS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct dados_estatisticos {
    double* valores; // Array de valores
    int tamanho; // Número de valores inseridos
    int capacidade; // Capacidade total do array
} dados_estatisticos;

dados_estatisticos* cria_dados_estatisticos_e(int tamanho);
void insere_dado_e(dados_estatisticos* dados, double valor);
double calcula_media_e(dados_estatisticos* dados);
double calcula_desvio_padrao_e(dados_estatisticos* dados);
void libera_dados_estatisticos_e(dados_estatisticos* dados);
#endif // DADOS_ESTATISTICOS_H