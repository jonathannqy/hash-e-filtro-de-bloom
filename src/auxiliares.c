#include "auxiliares.h"
#include <stdlib.h>

void menu_principal() {
    printf("\n--- Sistema de Verificacao de Cadastro ---\n");
    printf("[1] Inserir novo usuário\n");
    printf("[2] Consultar usuário\n");
    printf("[3] Exibir estatísticas\n");
    printf("[4] Inserir lote\n");
    printf("[5] Gerar lote(Arquivo)\n");
    printf("[6] Quantidade de registros\n");
    printf("[7] Roda experimento de busca (sem bloom)\n");
    printf("[8] Roda experimento de busca (com bloom)\n");
    printf("[0] Sair\n");
    printf("Escolha uma opção: ");
}

int iniciar_cronometro(){
    //A função clock vai pegar o tempo de cpu e guardar em um int normal
    return clock();
}

int parar_cronometro(int inicio){
    int fim = clock();

    //Multiplica o resultado em 1.000.000 para sair em microssegundos.
    int tempo_gasto = ((fim - inicio) * 1000000) /CLOCKS_PER_SEC;

    return tempo_gasto;
}

void inserir_lote_completo(tabelaHash* h, Filtrodebloom* b, char* nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    
    if (arquivo == NULL) {
        printf("Erro: Não foi possível abrir o arquivo '%s'.\n", nome_arquivo);
        return;
    }

    char usuario[20];

    while (fscanf(arquivo, "%19s", usuario) == 1) {
        inserir_hash(h, usuario);
        inserir_bloom(b, usuario);
    }

    fclose(arquivo);
    printf("Lote carregado com sucesso no Hash e no Bloom!\n");
}
