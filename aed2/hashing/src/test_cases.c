#include "test_cases.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#include "index_btree.h"
#include "dao.h"
#include "hash.h"
#include "vetor.h"
#define SEC2NANOSEC 1000000000

struct timespec t1, t2;
long long time_spent;

void print_int(int i, int index) {
    printf("%d -> %d\n", i, index);
}

void print_node_callback(int value, int index) {
    Aluno aluno = dao_buscar_aluno(index);
    print_aluno(aluno);
}

void first_task(int N) {
    int total_iter = 30;

    long long tempos[total_iter];
    int list_matr[N];

    printf("Criando a arvore de indexes.\n");
    BTree *index_tree = initialize_btree();

    for (int i = 0; i < N; ++i) {
        Aluno a = dao_buscar_aluno(i);
        list_matr[i] = a.matricula;
        append_btree(&index_tree, a.matricula, i);
    }

    for (int i = 0; i < total_iter; i++) {
        int matr_search = list_matr[rand() % N];
        clock_gettime(CLOCK_MONOTONIC, &t1);
        BTree *node = search_first_btree(index_tree, matr_search);
        Aluno a = dao_buscar_aluno(node->index);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        time_spent = ((long long) t2.tv_sec * SEC2NANOSEC + t2.tv_nsec) - (
                         (long long) t1.tv_sec * SEC2NANOSEC + t1.tv_nsec);

        tempos[i] = time_spent;
    }

    save_answer("first_task_ans.txt", tempos, total_iter);
}

void second_task(int N) {
    int total_iter = 30;

    long long tempos[total_iter];

    printf("Criando a tabela hash dos índices com tamanho %d.\n", SIZE);

    hashtable index_table;
    init_hashtable(&index_table);

    int list_matr[N];

    for (int i = 0; i < N; ++i) {
        Aluno a = dao_buscar_aluno(i);
        list_matr[i] = a.matricula;
        insert_hash(a.matricula, i, &index_table);
    }

    printf("Numero de colisoes: %d\n", return_colisons(&index_table));

    for (int i = 0; i < total_iter; i++) {
        int matr_search = list_matr[rand() % N];
        clock_gettime(CLOCK_MONOTONIC, &t1);
        Node_hash *node = get_hash_node(matr_search, &index_table);
        Aluno a = dao_buscar_aluno(node->index);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        time_spent = ((long long) t2.tv_sec * SEC2NANOSEC + t2.tv_nsec) - (
                         (long long) t1.tv_sec * SEC2NANOSEC + t1.tv_nsec);
        tempos[i] = time_spent;
    }

    save_answer("second_task_ans.txt", tempos, total_iter);
}

void third_task(int N) {
    int total_iter = 30;

    struct timespec t1, t2;
    long long time_spent;
    long long tempos[total_iter];

    int soma = 0;

    for (int i = 0; i < total_iter; i++) {
        int value_searched = rand() % N;

        clock_gettime(CLOCK_MONOTONIC, &t1);
        busca_sequencial_alunos(value_searched);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        time_spent = ((double)t2.tv_sec*SEC2NANOSEC + (double)t2.tv_nsec) - ((double)t1.tv_sec*SEC2NANOSEC + (double)t1.tv_nsec);

        tempos[i] = time_spent;
        soma += time_spent;
    }

    save_answer("third_task_ans.txt", tempos, total_iter);

}

void fourth_task(int N, int idade_search, char operator) {
    int total_iter = 30;
    int qtd_fourth_task = 0;


    long long tempos[total_iter];
    printf("Criando a árvore binária para o atributo 'idade'.\n");

    BTree *index_tree = initialize_btree();

    for (int i = 0; i < N; ++i) {
        Aluno a = dao_buscar_aluno(i);
        append_btree(&index_tree, a.idade, i);
    }

    for (int i = 0; i < total_iter; i++) {
        qtd_fourth_task = 0;

        switch (operator) {
            case '>':
                // printf("Listando alunos com idade > %d:\n", idade_search);

                clock_gettime(CLOCK_MONOTONIC, &t1);
                BTree *greater_root = find_greater_subtree(index_tree, idade_search);
                qtd_fourth_task += check_greater_btree(greater_root, idade_search);
                clock_gettime(CLOCK_MONOTONIC, &t2);
                time_spent = ((double)t2.tv_sec*SEC2NANOSEC + (double)t2.tv_nsec) - ((double)t1.tv_sec*SEC2NANOSEC + (double)t1.tv_nsec);

                //impressao dos dados de cada um:
                walk_tree_in_order_btree(greater_root, dao_print_btree);

                break;
            case '<':
                // printf("Listando alunos com idade < %d:\n", idade_search);

                clock_gettime(CLOCK_MONOTONIC, &t1);
                BTree *less_root = find_less_subtree(index_tree, idade_search);
                qtd_fourth_task += check_less_btree(less_root, idade_search);
                clock_gettime(CLOCK_MONOTONIC, &t2);
                time_spent = ((double)t2.tv_sec*SEC2NANOSEC + (double)t2.tv_nsec) - ((double)t1.tv_sec*SEC2NANOSEC + (double)t1.tv_nsec);

                walk_tree_in_order_btree(less_root, dao_print_btree);

                break;
            default:
                printf("Operador inválido! Use > ou <.\n");
                break;
        }


        tempos[i] = time_spent;
    }
    clear_btree(&index_tree);

    save_answer("fourth_task_ans.txt", tempos, total_iter);

    printf("Quantidade de alunos: %d\n", qtd_fourth_task);


}

void fifth_task(int N, int idade_search, char operator) {
    int total_iter = 30;

    long long tempos[30];
    long long soma = 0;

    for (int i = 0; i < total_iter; i++) {
        Vector* resultados = initialize_v(N);

        int qtd_fith_task = 0;

        clock_gettime(CLOCK_MONOTONIC, &t1);
        for (int j = 0; j < N; j++) {
            Aluno a = dao_buscar_aluno(j);
            int atende = 0;

            switch (operator) {
                case '>': 
                    atende = (a.idade > idade_search);
                    break;
                case '<': 
                    atende = (a.idade < idade_search );
                    break;
                default:
                    printf("Operador inválido! Use > ou <.\n");
                    destroy_v(resultados);
                    return;
            }

            if (atende) {
                set_v(resultados, qtd_fith_task, j); //guarda a posicao 
                qtd_fith_task++;
            }

        }//ciclo de cada registro

        clock_gettime(CLOCK_MONOTONIC, &t2);

        time_spent = ((long long)t2.tv_sec * SEC2NANOSEC + t2.tv_nsec) -
                     ((long long)t1.tv_sec * SEC2NANOSEC + t1.tv_nsec);
        tempos[i] = time_spent;
        soma += time_spent;

        printf("\n Iteração numero %d: %d alunos encontrados\n", i + 1, qtd_fith_task);
        printf("Lista de alunos:\n");
        for (int k = 0; k < qtd_fith_task; k++) {
            int numero_aluno = get_v(resultados, k);
            Aluno a = dao_buscar_aluno(numero_aluno);
            printf("Matricula: %d | Nome: %s | Idade: %d\n", a.matricula, a.nome, a.idade);
        }

        destroy_v(resultados); //liberar memoria

    }//ciclo das 30 vezes 

    save_answer("fifth_task_ans.txt", tempos, total_iter);

}