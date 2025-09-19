#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dao.h"
#include "test_cases.h"
//
// Created by luizg on 12/06/25.
//

#define POPULATE_NUM 1000

const char *first_names[] = {
    "Jose", "Maria", "Joao", "Ana", "Pedro", "Paulo", "Carlos", "Sandra",
    "Antonio", "Fernanda", "Lucas", "Julia", "Rafael", "Mariana", "Bruno",
    "Camila", "Felipe", "Amanda", "Gabriel", "Patricia"
};

const char *last_names[] = {
    "Silva", "Santos", "Oliveira", "Souza", "Rodrigues", "Ferreira", "Alves",
    "Pereira", "Lima", "Gomes", "Costa", "Ribeiro", "Martins", "Carvalho",
    "Almeida", "Lopes", "Soares", "Fernandes", "Vieira", "Barbosa"
};


int main() {
    srand(time(NULL));

    char op;
    printf("Quer excluir os dados anteriores (y/n)?\n");

    scanf("%c", &op);

    switch (op) {
        case 'y':
            printf("Inicializando a DAO...\n");
            dao_inicializar();
            printf("DAO finalizada.\n\n");

            printf("Populando db com %d alunos...\n", POPULATE_NUM);
            int *order = malloc(POPULATE_NUM * sizeof(int));
            int acc = 0;
            for (int i = 0; i < POPULATE_NUM; i++) {
                acc += rand() % 10 + 1;
                order[i] = acc;
            }

            for (int i = POPULATE_NUM - 1; i > 0; i--) {
                int j = rand() % (i + 1);
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }

            for (int i = 0; i < POPULATE_NUM; ++i) {
                Aluno aluno = {
                    .altura = 1.5 + ((float) rand() / RAND_MAX) * 0.5,
                    .matricula = order[i],
                    .idade = 12 + (rand() % 20),
                    .nota1 = 5.0 + ((float) rand() / RAND_MAX) * 5.0,
                    .nota2 = 5.0 + ((float) rand() / RAND_MAX) * 5.0,
                    .nota3 = 5.0 + ((float) rand() / RAND_MAX) * 5.0
                };

                strncpy(aluno.nome, first_names[rand() % 20], MAX_NOME_SIZE);
                strncpy(aluno.sobrenome, last_names[rand() % 20], MAX_NOME_SIZE);
                aluno.nome[MAX_NOME_SIZE - 1] = '\0';
                aluno.sobrenome[MAX_NOME_SIZE - 1] = '\0';
                dao_inserir_aluno(aluno);
            }

            free(order);
            printf("Populado com sucesso.\n\n");
            break;
        case 'n':
            break;
        default:
            printf("Opção inválida. Sem remover.\n\n");
            break;
    }

    printf("First Task:\n");
    first_task(POPULATE_NUM);
    printf("------------\n\n");

    printf("Second Task:\n");
    second_task(POPULATE_NUM);
    printf("------------\n\n");

    printf("Terceira Task:\n");
    third_task(POPULATE_NUM);
    printf("------------\n\n");

    printf("Quarta Task:\n");
    fourth_task(POPULATE_NUM, 25, '>');
    printf("------------\n");

    printf("Quinta Task:\n");
    fifth_task(POPULATE_NUM, 25, '>');
    printf("------------\n");
}
