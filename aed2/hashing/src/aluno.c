#include "aluno.h"
#include <stdio.h>
//
// Created by luizg on 12/06/25.
//
void print_aluno(Aluno a) {
    printf("Matricula: %d\n", a.matricula);
    printf("Nome: %s\n", a.nome);
    printf("Sobrenome: %s\n", a.sobrenome);
    printf("Idade: %d\n", a.idade);
    printf("Altura: %.2f\n", a.altura);
    printf("Nota 1: %.2f\n", a.nota1);
    printf("Nota 2: %.2f\n", a.nota2);
    printf("Nota 3: %.2f\n", a.nota3);
}