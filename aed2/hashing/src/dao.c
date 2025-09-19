#include <stdio.h>
#include <dao.h>
#include <stdlib.h>
#include <string.h>


// Função para inicializar o arquivo (cria se não existir)
void dao_inicializar() {
    FILE *file = fopen(FILENAME, "wb");; // Abre em modo de escrita binária (sobrescreve se existe)
    if (file == NULL) {
        perror("Erro ao inicializar o arquivo");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

void dao_inserir_aluno(Aluno aluno) {
    FILE *file = fopen(FILENAME, "ab"); // Abre para adicionar (append binary)
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    fwrite(&aluno, sizeof(Aluno), 1, file);
    fclose(file);
    printf("Aluno %s %s (Matrícula: %d) inserido com sucesso.\n", aluno.nome, aluno.sobrenome, aluno.matricula);
}


Aluno dao_buscar_aluno(int position) {
    FILE *file = fopen(FILENAME, "rb");
    Aluno aluno = {0}; // Initialize with zeros

    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return aluno;
    }

    // Move to the desired position
    if (fseek(file, position * sizeof(Aluno), SEEK_SET) != 0) {
        perror("Erro ao posicionar no arquivo");
        fclose(file);
        return aluno;
    }

    // Read the Aluno at that position
    if (fread(&aluno, sizeof(Aluno), 1, file) != 1) {
        perror("Erro ao ler aluno do arquivo");
    }

    fclose(file);
    return aluno;
}

void dao_print_btree(int inutil, int index) {

    Aluno aluno = dao_buscar_aluno(int position);

    printf("Matricula: %d | Nome: %s | Idade: %d\n", aluno.matricula, aluno.nome, aluno.idade);
    
}

void visitarAlunos(const char *arquivo, void (*visitante)(Aluno *)) { //mais util para passar o aluno e montar as estruturas
    FILE *fp = fopen(arquivo, "rb");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Aluno aluno;
    while (fread(&aluno, sizeof(Aluno), 1, fp) == 1) {
        visitante(&aluno);
    }

    fclose(fp);
}


int busca_sequencial_alunos(int chave) { //mais util para simular melhor a busca sequencial
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }
    Aluno aluno;
        while (fread(&aluno, sizeof(Aluno), 1, fp) == 1) {
            if (aluno.matricula == chave) {
                fclose(fp);
                return 1;
            }
        }
    return 0;
}

void save_answer(const char *answer_filename, long long content[], int tam_content) {
    FILE *file = fopen(answer_filename, "w");
    if (file == NULL) {
        perror("Erro ao abrir arquivo de resposta");
        return;
    }

    for (int i = 0; i < tam_content; i++) {
        fprintf(file, "%lld\n", content[i]);
    }

    fclose(file);
}