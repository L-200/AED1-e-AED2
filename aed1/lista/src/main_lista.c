#include <main_lista.h>

int main () {

    //preparando os testes
    int qnt_testes = 3;
    int size_testes = 100000;
    srand(time(NULL));
    dados_estatisticos *tempos_criacao_lista = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *tempos_criacao_vetor = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *tempos_search_lista = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *tempos_search_vetor = initialize_dados_estatisticos_e(qnt_testes);
    printf("Tempo em segundos\n");

    //realizando os testes

    for (int i = 0; i < qnt_testes; i++) {
        printf("Teste %d\n", i+1);
        int seed = rand();
        printf("Criando vetor que será copiado para popular a lista e um novo vetor\n");
        Vector *vet_original_testes = initialize_v(size_testes);
        randomize_values_v(vet_original_testes, seed, vet_original_testes->tam);

        printf("Criando a lista\n");
        clock_t inicio_ticks = clock();
        Int_Linked_List *lista = initialize_l();
        append_values_reverse_l(lista, size_testes, vet_original_testes->v);
        clock_t fim_ticks = clock();
        printf("Lista criada\n");
        insere_dado_e(tempos_criacao_lista, (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC);
        printf("Tempo para criação: %lf\n", tempos_criacao_lista->valores[i]);

        printf("Criando novo vetor para comparação\n");
        inicio_ticks = clock();
        Vector *vet_novo = initialize_v(size_testes);
        copy_v(vet_original_testes, vet_novo);
        fim_ticks = clock();
        printf("Vetor criado\n");
        insere_dado_e(tempos_criacao_vetor, (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC);
        printf("Tempo para criação: %lf\n", tempos_criacao_vetor->valores[i]);
    }
}