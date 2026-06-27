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

void gerar_arquivo(char *nome_arquivo, int quantidade){
    // ("w") Significa modo de escrita
    FILE *arquivo = fopen(nome_arquivo, "w");
    
    if (arquivo == NULL) {
        // Boa prática
        printf("Erro: Não foi possível criar o arquivo '%s'.\n", nome_arquivo);
        return;
    }

    char buffer[12]; // 11 caracteres + 1 para o '\0'
    
    for (int i = 0; i < quantidade; i++) {
        gerar_nome_aleatorio(buffer);
        fprintf(arquivo, "%s\n", buffer);
    }

    fclose(arquivo);

    printf("Arquivo '%s' gerado com %d registros.\n", nome_arquivo, quantidade);
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