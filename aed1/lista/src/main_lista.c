#include <main_lista.h>

int main () {

    //preparando os testes
    int qnt_testes = 5;
    int size_testes = 100000;
    srand(time(NULL));
    dados_estatisticos *tempos_criacao_lista = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *tempos_criacao_vetor = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *tempos_search_lista = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *tempos_search_vetor = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *tempos_liberacao_lista = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *tempos_liberacao_vetor = initialize_dados_estatisticos_e(qnt_testes);
    printf("Tempo em segundos\n");

    //realizando os testes

    for (int i = 0; i < qnt_testes; i++) {
        printf("=====================================\n");
        printf("Teste %d\n", i+1);
        //testes de tempo de criação
        int seed = rand();
        printf("Criando vetor que será copiado para popular a lista e um novo vetor\n");
        Vector *vet_original_testes = initialize_v(size_testes);
        randomize_values_v(vet_original_testes, seed, vet_original_testes->tam);

        printf("TESTES DE CRIAÇÃO\n");
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

        printf("===============================\n");
        printf("TESTES DE BUSCA\n");

        int valor_procurado = vet_original_testes->v[rand() % size_testes];
        printf("Procurando o valor %d na lista\n", valor_procurado);
        inicio_ticks = clock();
        int encontrado_lista = search_sequencial_l(lista, valor_procurado);
        fim_ticks = clock();
        if (encontrado_lista) {
            printf("Valor encontrado na lista\n");
        } else {
            printf("ERRO: VALOR NÃO ENCONTRADO\n");
        }
        insere_dado_e(tempos_search_lista, (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC);
        printf("Tempo para busca na lista: %lf\n", tempos_search_lista->valores[i]);

        printf("Procurando o valor %d no vetor\n", valor_procurado);
        inicio_ticks = clock();
        int encontrado_vetor = search_sequencial_v(vet_novo, valor_procurado);
        fim_ticks = clock();
        if (encontrado_vetor) {
            printf("Valor encontrado no vetor\n");
        } else {
            printf("ERRO: VALOR NÃO ENCONTRADO\n");
        } 
        insere_dado_e(tempos_search_vetor, (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC);
        printf("Tempo para busca no vetor: %lf\n", tempos_search_vetor->valores[i]);

        destroy_v(vet_original_testes);
        //testes de liberação da memória
        printf("===============================\n");
        printf("TESTES DE LIBERAÇÃO DE MEMÓRIA\n");
        inicio_ticks = clock();
        destroy_l(lista);
        fim_ticks = clock();
        printf("Memória da lista liberada\n");
        insere_dado_e(tempos_liberacao_lista, (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC);
        printf("Tempo para liberação da lista: %lf\n", tempos_liberacao_lista->valores[i]);
        
        printf("Liberando a memória do vetor\n");
        inicio_ticks = clock();
        destroy_v(vet_novo);
        fim_ticks = clock();
        printf("Memória do vetor liberada\n");
        insere_dado_e(tempos_liberacao_vetor, (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC);
        printf("Tempo para liberação do vetor: %lf\n", tempos_liberacao_vetor->valores[i]);

    }

    //mostrando os resultados
    printf("=====================================\n");
    printf("RESULTADOS FINAIS\n");
    printf("======================================\n");

    printf("Tempos de criação da lista:\n");
    for (int i = 0; i < tempos_criacao_lista->tamanho; i++) {
        printf("Tempo de criação da lista numero %d: %lf \n", i, tempos_criacao_lista->valores[i]);
    }
    printf("Média: %lf\n", calcula_media_e(tempos_criacao_lista));
    printf("Desvio Padrão: %lf\n", calcula_desvio_padrao_e(tempos_criacao_lista));

    printf("--------------------------------\n");
    printf("Tempos de criação do vetor:\n");
    for (int i = 0; i < tempos_criacao_vetor->tamanho; i++) {
        printf("Tempo de criação do vetor numero %d: %lf \n", i, tempos_criacao_vetor->valores[i]);
    }
    printf("Média: %lf\n", calcula_media_e(tempos_criacao_vetor));
    printf("Desvio Padrão: %lf\n", calcula_desvio_padrao_e(tempos_criacao_vetor));  

    printf("--------------------------------\n");
    printf("Tempos de busca na lista:\n");
    for (int i = 0; i < tempos_search_lista->tamanho; i++) {
        printf("Tempo de busca na lista numero %d: %lf \n", i, tempos_search_lista->valores[i]);
    }
    printf("Média: %lf\n", calcula_media_e(tempos_search_lista));
    printf("Desvio Padrão: %lf\n", calcula_desvio_padrao_e(tempos_search_lista));

    printf("--------------------------------\n");
    printf("Tempos de busca no vetor:\n");
    for (int i = 0; i < tempos_search_vetor->tamanho; i++) {
        printf("Tempo de busca no vetor numero %d: %lf \n", i, tempos_search_vetor->valores[i]);
    }
    printf("Média: %lf\n", calcula_media_e(tempos_search_vetor));
    printf("Desvio Padrão: %lf\n", calcula_desvio_padrao_e(tempos_search_vetor));

    printf("--------------------------------\n");
    printf("Tempos de liberação da lista:\n");
    for (int i = 0; i < tempos_liberacao_lista->tamanho; i++) {
        printf("Tempo de liberação da lista numero %d: %lf \n", i, tempos_liberacao_lista->valores[i]);
    }   
    printf("Média: %lf\n", calcula_media_e(tempos_liberacao_lista));
    printf("Desvio Padrão: %lf\n", calcula_desvio_padrao_e(tempos_liberacao_lista));

    printf("--------------------------------\n");
    printf("Tempos de liberação do vetor:\n");
    for (int i = 0; i < tempos_liberacao_vetor->tamanho; i++) {
        printf("Tempo de liberação do vetor numero %d: %lf \n", i, tempos_liberacao_vetor->valores[i]);
    }   
    printf("Média: %lf\n", calcula_media_e(tempos_liberacao_vetor));
    printf("Desvio Padrão: %lf\n", calcula_desvio_padrao_e(tempos_liberacao_vetor));
}