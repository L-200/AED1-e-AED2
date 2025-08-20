#include <dados_estatisticos.h>

dados_estatisticos* cria_dados_estatisticos_e(int tamanho) {

    dados_estatisticos* dados = (dados_estatisticos*) malloc(sizeof(dados_estatisticos));
    dados->valores = (double*) malloc(tamanho * sizeof(double));
    dados->tamanho = 0;
    dados->capacidade = tamanho;
    return dados;
}

void insere_dado_e(dados_estatisticos* dados, double valor) {
    if (dados->tamanho < dados->capacidade) {
        dados->valores[dados->tamanho++] = valor;
    } else {
        printf("Erro: vetor de dados estatísticos cheio!\n");
    }
}

double calcula_media_e(dados_estatisticos* dados) {

    double soma = 0.0;
    for (int i = 0; i < dados->tamanho; i++) {
        soma += dados->valores[i];
    }
    return soma / dados->tamanho;

}

double calcula_desvio_padrao_e(dados_estatisticos* dados) {
    if (dados->tamanho <= 1) {
        return 0.0;
    }

    double media = calcula_media_e(dados);
    double soma_quadrados_diferencas = 0.0;

    for (int i = 0; i < dados->tamanho; i++) {
        double diff = dados->valores[i] - media;
        soma_quadrados_diferencas += diff * diff;
    }

    double variancia = soma_quadrados_diferencas / (dados->tamanho - 1);

    return sqrt(variancia);
}

void libera_dados_estatisticos_e(dados_estatisticos* dados) {
    if (dados) {
        free(dados->valores);
        free(dados);
    }
}