#include "main_vetor.h"

int main () {

    srand(time(NULL));
    int seed1 = rand();
    int size = 100000;
    int inicio_amostra = size/2;
    int fim_amostra = (size/2)+30;

    printf("Note a quantidade de tempo de cada algoritmo e pense como ele se comportaria em vetores muito maiores\n");
    printf("Todas as medidas de tempo estão em segundos\n");
    
    printf("Criando vetor com %d elementos\n", size);
    Vector *vetor_testes_searches = initialize_v(size);
    printf("Populando vetor com números aleatórios em ordem crescente\n");
    randomize_values_asc_v(vetor_testes_searches, seed1, size);

    printf("Posições %d a %d  para provar que o vetor realmente é aleatório e em ordem crescente : ", inicio_amostra, fim_amostra);
    show_portion_v(vetor_testes_searches, inicio_amostra, fim_amostra);

    //escolha dos números que serão buscados nos testes
    int qnt_testes = 15;
    int vet_testes_searches_procurados[qnt_testes];
    for (int numero_teste = 0; numero_teste < qnt_testes; numero_teste++) {
        vet_testes_searches_procurados[numero_teste] = vetor_testes_searches->v[rand() % size];
    }

    printf("\n");

    printf("Realizando %d buscas sequenciais por um elemento em uma posição aleatoria\n", qnt_testes);
    printf("Valores que serão buscados:\n");
     for (int i = 0; i < qnt_testes-1; i++) {
        printf("%d | ", vet_testes_searches_procurados[i]);
    }
    printf("%d\n", vet_testes_searches_procurados[qnt_testes-1]);    

    dados_estatisticos* tempos_search_sequencial = initialize_dados_estatisticos_e(qnt_testes);

    for(int i = 0; i < qnt_testes; i++) {
        
        clock_t inicio_ticks = clock();
        if (search_sequencial_v(vetor_testes_searches, vet_testes_searches_procurados[i])) {
            printf("Numero encontrado com sucesso no teste %d!\n", i+1);
        } else {
            printf("ERRO NO TESTE %d!\n", i);
        }
        clock_t fim_ticks = clock();
        insere_dado_e(tempos_search_sequencial, (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC);
    } 

    printf("Tempos de busca da busca sequencial: \n");
    for (int i = 0; i < qnt_testes; i++) {
        printf("Teste %d: %f\n", i+1, tempos_search_sequencial->valores[i]);
    }

    printf("--------------------\n");


    printf("Realizando %d buscas binárias pelas mesmos elementos procurados pelo teste anterior\n", qnt_testes);
    
    dados_estatisticos* tempos_search_binario = initialize_dados_estatisticos_e(qnt_testes);

    for(int i = 0; i < qnt_testes; i++) {
        
        clock_t inicio_ticks = clock();
        if (search_binario_v(vetor_testes_searches, vet_testes_searches_procurados[i])) {
            printf("Numero encontrado com sucesso no teste %d!\n", i+1);
        } else {
            printf("ERRO NO TESTE %d!\n", i);
        }
        clock_t fim_ticks = clock();
        insere_dado_e(tempos_search_binario, (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC);
    } 

    printf("Tempos de busca da busca binária: \n");
    for (int i = 0; i < qnt_testes; i++) {
        printf("Teste %d: %f\n", i+1, tempos_search_binario->valores[i]);
    }

    printf("Média de tempo da busca sequencial: %f\n", calcula_media_e(tempos_search_sequencial));
    printf("Desvio padrão da busca sequencial: %f\n", calcula_desvio_padrao_e(tempos_search_sequencial));
    printf("\n");
    printf("Média de tempo da busca binária: %f\n", calcula_media_e(tempos_search_binario));
    printf("Desvio padrão da busca binária: %f\n", calcula_desvio_padrao_e(tempos_search_binario));
    destroy_v(vetor_testes_searches); //liberar ram usada pelo vetor_testes_searches

    printf("\n");
    printf("====================\n");
    printf("INICIO DOS TESTES DOS SORTS\n");
    printf("====================\n\n");

    //criação das seeds que gerarão os mesmos vetores para o sorting
    //guardar as 5 num vetor e aplicar cada uma em cada tipo de algoritmo

    int qnt_seeds = 3;
    int vet_seeds[qnt_seeds];
    for (int i = 0; i < qnt_seeds; i++) {
        vet_seeds[i] = rand();
    }

    printf("Serão gerados %d vetores identicos e cada algoritmo resolverá todos eles\n", qnt_seeds);
    dados_estatisticos* tempos_bubble = initialize_dados_estatisticos_e(qnt_seeds);
    dados_estatisticos* tempos_insertion = initialize_dados_estatisticos_e(qnt_seeds);
    dados_estatisticos* tempos_selection = initialize_dados_estatisticos_e(qnt_seeds);
    dados_estatisticos* tempos_quick = initialize_dados_estatisticos_e(qnt_seeds);
    dados_estatisticos* tempos_merge = initialize_dados_estatisticos_e(qnt_seeds);

    //inicio dos testes
    for (int i = 0; i < qnt_seeds; i++) {
        printf("Testes com o vetor %d\n", i+1);
        printf("\n");
        printf("BUBBLE SORT:\n");
        Vector *vet_bubble_sort = initialize_v(size);

        printf("Populando o vetor com %d elementos aleatorios e únicos\n", size);
        randomize_values_v(vet_bubble_sort, vet_seeds[i], size);
        printf("Amostra de %d a %d:\n", inicio_amostra, fim_amostra);
        show_portion_v(vet_bubble_sort, inicio_amostra, fim_amostra);
        printf("\n");

        printf("Realizando o bubble sort\n");
        clock_t inicio_ticks = clock();
        bubble_sort_v(vet_bubble_sort);
        printf("Vetor ordenado com sucesso!\n");
        printf("Amostra do vetor ordenado:\n");
        show_portion_v(vet_bubble_sort, inicio_amostra, fim_amostra);
        clock_t fim_ticks = clock();
        printf("Tempo para ordenação: ");
        insere_dado_e(tempos_bubble, (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC);
        printf("%lf\n", tempos_bubble->valores[i]);
        destroy_v(vet_bubble_sort);

        printf("\n");

        printf("--------------------\n");


        printf("INSERTION SORT:\n");
        Vector *vet_insertion_sort = initialize_v(size);

        printf("Populando o vetor com %d elementos aleatorios\n", size);
        randomize_values_v(vet_insertion_sort, vet_seeds[i], size);

        printf("Realizando o insertion sort\n");
        inicio_ticks = clock();
        insertion_sort_v(vet_insertion_sort);
        printf("Vetor ordenado com sucesso!\n");
        printf("Amostra do vetor ordenado:\n");
        show_portion_v(vet_insertion_sort, inicio_amostra, fim_amostra);
        fim_ticks = clock();
        printf("Tempo para ordenação: ");
        insere_dado_e(tempos_insertion, (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC);
        printf("%lf\n", tempos_insertion->valores[i]);
        destroy_v(vet_insertion_sort);

        printf("\n");
    
        printf("--------------------\n");


        printf("SELECTION SORT:\n");
        Vector *vet_selection_sort = initialize_v(size);

        printf("Populando o vetor com %d elementos aleatorios\n", size);
        randomize_values_v(vet_selection_sort, vet_seeds[i], size);

        printf("Realizando o selection sort\n");
        inicio_ticks = clock();
        selection_sort_v(vet_selection_sort);
        printf("Vetor ordenado com sucesso!\n");
        printf("Amostra do vetor ordenado:\n");
        show_portion_v(vet_selection_sort, inicio_amostra, fim_amostra);
        fim_ticks = clock();
        printf("Tempo para ordenação: ");
        insere_dado_e(tempos_selection, (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC);
        printf("%lf\n", tempos_selection->valores[i]);
        destroy_v(vet_selection_sort);

        printf("\n");
    
        printf("--------------------\n");


        printf("QUICK SORT:\n");
        Vector *vet_quick_sort = initialize_v(size);

        printf("Populando o vetor com %d elementos aleatorios\n", size);
        randomize_values_v(vet_quick_sort, vet_seeds[i], size);

        printf("Realizando o quick sort\n");
        inicio_ticks = clock();
        quick_sort_v(vet_quick_sort);
        printf("Vetor ordenado com sucesso!\n");
        printf("Amostra do vetor ordenado:\n");
        show_portion_v(vet_quick_sort, inicio_amostra, fim_amostra);
        fim_ticks = clock();
        printf("Tempo para ordenação: ");
        insere_dado_e(tempos_quick, (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC);
        printf("%lf\n", tempos_quick->valores[i]);
        destroy_v(vet_quick_sort);

        printf("\n");

        printf("--------------------\n");


        printf("MERGE SORT:\n");
        Vector *vet_merge_sort = initialize_v(size);

        printf("Populando o vetor com %d elementos aleatorios\n", size);
        randomize_values_v(vet_merge_sort, vet_seeds[i], size);

        printf("Realizando o merge sort\n");
        inicio_ticks = clock();
        merge_sort_v(vet_merge_sort);
        printf("Vetor ordenado com sucesso!\n");
        printf("Amostra do vetor ordenado:\n");
        show_portion_v(vet_merge_sort, inicio_amostra, fim_amostra);
        fim_ticks = clock();
        printf("Tempo para ordenação: ");
        insere_dado_e(tempos_merge, (double)(fim_ticks - inicio_ticks) / CLOCKS_PER_SEC);
        printf("%lf\n", tempos_merge->valores[i]);
        destroy_v(vet_merge_sort);

        printf("\n");

        printf("FIM DOS TESTES COM O VETOR NUMERO %d\n", i+1);
        printf("********************\n\n");
    }

    printf("Resultados de tempos do bubble sort: \n");
    for (int i = 0; i < qnt_seeds; i++) {
        printf("Teste %d: %f\n", i+1, tempos_bubble->valores[i]);
    }
    printf("Média de tempo do bubble sort: %f\n", calcula_media_e(tempos_bubble));
    printf("Desvio padrão do bubble sort: %f\n", calcula_desvio_padrao_e(tempos_bubble));


    printf("Resultados de tempos do insertion sort: \n");
    for (int i = 0; i < qnt_seeds; i++) {
        printf("Teste %d: %f\n", i+1, tempos_insertion->valores[i]);
    }
    printf("Média de tempo do insertion sort: %f\n", calcula_media_e(tempos_insertion));
    printf("Desvio padrão do insertion sort: %f\n", calcula_desvio_padrao_e(tempos_insertion));


    printf("Resultados de tempos do selection sort: \n");
    for (int i = 0; i < qnt_seeds; i++) {
        printf("Teste %d: %f\n", i+1, tempos_selection->valores[i]);
    }
    printf("Média de tempo do selection sort: %f\n", calcula_media_e(tempos_selection));
    printf("Desvio padrão do selection sort: %f\n", calcula_desvio_padrao_e(tempos_selection));


    printf("Resultados de tempos do quick sort: \n");
    for (int i = 0; i < qnt_seeds; i++) {
        printf("Teste %d: %f\n", i+1, tempos_quick->valores[i]);
    }
    printf("Média de tempo do quick sort: %f\n", calcula_media_e(tempos_quick));
    printf("Desvio padrão do quick sort: %f\n", calcula_desvio_padrao_e(tempos_quick));


    printf("Resultados de tempos do merge sort: \n");
    for (int i = 0; i < qnt_seeds; i++) {
        printf("Teste %d: %f\n", i+1, tempos_merge->valores[i]);
    }
    printf("Média de tempo do selection sort: %f\n", calcula_media_e(tempos_merge));
    printf("Desvio padrão do selection sort: %f\n", calcula_desvio_padrao_e(tempos_merge));

}