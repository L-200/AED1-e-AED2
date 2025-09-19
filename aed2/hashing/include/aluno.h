//
// Created by luizg on 12/06/25.
//
#ifndef ALUNO_H
#define ALUNO_H

#define MAX_NOME_SIZE 100

typedef struct Aluno {
    int matricula;
    char nome[MAX_NOME_SIZE];
    char sobrenome[MAX_NOME_SIZE];
    int idade;
    float altura;
    float nota1;
    float nota2;
    float nota3;
} Aluno;

void print_aluno(Aluno a);

#endif //ALUNO_H
