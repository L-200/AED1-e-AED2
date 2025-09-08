#include <main_arvores.h>

int main() {
    int size_testes = 100000;
    int qnt_testes = 5;
    srand(time(NULL));
    dados_estatisticos *tempos_criacao_btree = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *tempos_search_btree = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *tempos_liberacao_btree = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *alturas_btree = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *tempos_criacao_avl = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *tempos_search_avl = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *tempos_liberacao_avl = initialize_dados_estatisticos_e(qnt_testes);
    dados_estatisticos *alturas_avl = initialize_dados_estatisticos_e(qnt_testes);

    for (int i = 0; i <qnt_testes; i++) {

        int seed = rand();
        printf("Iniciado teste numero %d\n", i+1);
        
        printf("Gerando vetor de tamanho %d\n", size_testes);
        Vector* vet_testes = initialize_v(size_testes);
        randomize_values_asc_v(vet_testes, seed, size_testes);
        // para testes show_portion_v(vet_testes, 0, 10);
        int pos_valor_encontrado = rand() % size_testes;
        int valor_procurado = vet_testes->v[pos_valor_encontrado];
        //printf("Valor a ser procurado: %d (posição %d do vetor)\n", valor_procurado, pos_valor_encontrado);
        printf("--------------------------------\n");
        
        printf("Criando BTree com %d elementos\n", size_testes);
        clock_t inicio = clock();
        BTree* btree = initialize_btree();
        append_from_vector_btree(&btree, vet_testes->v, vet_testes->tam);
        clock_t fim = clock();
        double tempo_criacao_btree = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Tempo de criacao da BTree: %f segundos\n", tempo_criacao_btree);
        insere_dado_e(tempos_criacao_btree, tempo_criacao_btree);
        printf("--------------------------------\n");

        int altura_btree = get_height_btree(btree);
        printf("Altura da BTree: %d\n", altura_btree);
        insere_dado_e(alturas_btree, altura_btree);
        printf("--------------------------------\n");

        clock_t inicio_search = clock();
        printf("Procurando o valor %d\n", valor_procurado);
        int encontrado_btree = search_first_btree(btree, valor_procurado);
        if (encontrado_btree) {
            printf("Valor encontrado na BTree!\n");
        } else {
            printf("ERRO: VALOR NÃO ENCONTRADO\n");
        }
        clock_t fim_search = clock();
        double tempo_search_btree = (double)(fim_search - inicio_search) / CLOCKS_PER_SEC;
        printf("Tempo de busca na BTree: %f segundos\n", tempo_search_btree);
        insere_dado_e(tempos_search_btree, tempo_search_btree);
        printf("--------------------------------\n");

        clock_t inicio_liberacao = clock();
        clear_btree(&btree);
        clock_t fim_liberacao = clock();
        double tempo_liberacao_btree = (double)(fim_liberacao - inicio_liberacao) / CLOCKS_PER_SEC;
        printf("Tempo de liberação da BTree: %f segundos\n", tempo_liberacao_btree);
        insere_dado_e(tempos_liberacao_btree, tempo_liberacao_btree);
        printf("================================\n\n");

    }

}