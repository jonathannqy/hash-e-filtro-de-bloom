#include "script.h"

void gerar_nome_aleatorio(char *buffer){
    // Gera 8 letras minúsculas aleatórias (de 'a' até 'z')
    for (int i = 0; i < 8; i++) {
        buffer[i] = 'a' + (rand() % 26);
    }
    
    // Gera 3 números aleatórios (de '0' até '9')
    for (int i = 8; i < 11; i++) {
        buffer[i] = '0' + (rand() % 10);
    }
    
    buffer[11] = '\0';
}

void gerar_nome_fake(char *buffer){
    // 1. Coloca o prefixo obrigatório "fake" (4 caracteres)
    buffer[0] = 'f';
    buffer[1] = 'a';
    buffer[2] = 'k';
    buffer[3] = 'e';

    // 2. Gera 4 letras minúsculas aleatórias (posições 4 a 7)
    for (int i = 4; i < 8; i++) {
        buffer[i] = 'a' + (rand() % 26);
    }
    
    // 3. Gera 3 números aleatórios (posições 8 a 10)
    for (int i = 8; i < 11; i++) {
        buffer[i] = '0' + (rand() % 10);
    }
    
    // 4. Finaliza a string de forma segura
    buffer[11] = '\0';
}

void gerar_arquivo(char *nome_arquivo, int quantidade){
    FILE *arquivo = fopen(nome_arquivo, "w");
    
    if (arquivo == NULL) {
        printf("Erro: Não foi possível criar o arquivo '%s'.\n", nome_arquivo);
        return;
    }

    char buffer[12]; 
    
    for (int i = 0; i < quantidade; i++) {
        gerar_nome_aleatorio(buffer);
        fprintf(arquivo, "%s\n", buffer);
    }

    fclose(arquivo);
    printf("Arquivo '%s' gerado com %d registros normais.\n", nome_arquivo, quantidade);
}

void gerar_arquivo_fake(char *nome_arquivo, int quantidade){
    FILE *arquivo = fopen(nome_arquivo, "w");
    
    if (arquivo == NULL) {
        printf("Erro: Não foi possível criar o arquivo '%s'.\n", nome_arquivo);
        return;
    }

    char buffer[12]; 
    
    for (int i = 0; i < quantidade; i++) {
        gerar_nome_fake(buffer);
        fprintf(arquivo, "%s\n", buffer);
    }

    fclose(arquivo);
    printf("Arquivo '%s' gerado com %d registros FAKE.\n", nome_arquivo, quantidade);
}

// Retorna 1 se o arquivo existe, 0 se não existe
int arquivo_existe(const char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo != NULL) {
        fclose(arquivo); 
        return 1;
    }
    return 0; 
}