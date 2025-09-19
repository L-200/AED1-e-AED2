#ifndef DAO_H
#define DAO_H

#include "aluno.h"
#define FILENAME "aluno_db"

void dao_inicializar();

void dao_inserir_aluno(Aluno aluno);

/*
 Busca um aluno pelo seu índice na lista.
 */
Aluno dao_buscar_aluno(int position);

void dao_print_btree(int inutil, int index);

void aplicarFuncaoNosAlunos(const char *arquivo, int (*funcao)(int));

int busca_sequencial_alunos(int chave);

void save_answer(const char *answer_filename, long long content[], int tam_content);

#endif // DAO_H