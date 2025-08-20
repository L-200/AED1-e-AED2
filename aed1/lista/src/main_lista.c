#include <main_lista.h>

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
    printf("Para demonstrar o uso de listas, vamos criar uma lista encadeada simples e comparar o seu tempo de busca com o de um vetor.\n");
    srand(time(NULL));
    int size = 100000;
    int inicio_amostra = size/2;
    int fim_amostra = (size/2)+30;
    printf("Criando vetor com %d elementos\n", size);
}