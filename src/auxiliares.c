#include "auxiliares.h"
#include <stdlib.h>

void menu_principal() {
    printf("\n--- Sistema de Verificação de Cadastro ---\n");
    printf("[1] Inserir novo usuário no hash e no bloom\n");
    printf("[2] Consultar usuário (com bloom)\n"); // <- Nome atualizado para clareza
    printf("[3] Consultar usuário (sem bloom)\n");   // <- NOVA OPÇÃO AQUI
    printf("[4] Exibir estatísticas\n");
    printf("[5] Inserir lote na tabela hash e no bloom\n");
    printf("[6] Gerar lote (Arquivo)\n");
    printf("[7] Quantidade de registrados na tabela hash\n");
    printf("[8] Teste de busca cronometrado (sem bloom)\n");
    printf("[9] Teste de busca cronometrado (com bloom)\n");
    printf("[0] Sair\n");
    printf("Escolha uma opção: ");
}

void menu_lote() {
    printf("Escolha o lote que deseja testar: \n");
    printf("[1] Lote 1k\n");
    printf("[2] Lote 10k\n");
    printf("[3] Lote 100k\n");  
}

void resultados_sem_bloom(char* nome_arquivo, int total_consultas, int tempo_total){
    printf("\n--- RESULTADOS DO EXPERIMENTO ---\n");
    printf("Arquivo testado: %s\n", nome_arquivo);
    printf("Quantidade de buscas: %d\n", total_consultas);
    printf("Tempo total gasto: %d microssegundos.\n", tempo_total);
    printf("Tamanho da tabela Hash: %d\n", tamanho_tabela()); 
    
    if (total_consultas > 0) {
        printf("Tempo médio por busca: %.4f microssegundos.\n", (double)tempo_total / total_consultas);
    }
}


void resultados_com_bloom(char* nome_arquivo, int total_consultas, int consultas_evitadas, int falsos_positivos, int tempo_total){
    printf("\n--- RESULTADOS DO EXPERIMENTO ---\n");
    printf("Arquivo testado: %s\n", nome_arquivo);
    printf("Quantidade de buscas: %d\n", total_consultas);
    printf("Consultas pesadas (Hash) evitadas: %d\n", consultas_evitadas);
    printf("Falsos positivos do Bloom: %d\n", falsos_positivos);
    printf("Tempo total gasto: %d microssegundos.\n", tempo_total);
    printf("Tamanho da tabela Hash: %d\n", tamanho_tabela()); 

    if (total_consultas > 0) {
        printf("Tempo médio por busca: %.4f microssegundos.\n", (double)tempo_total / total_consultas);
        printf("Taxa de Falsos Positivos neste lote: %.2f%%\n", ((double)falsos_positivos / total_consultas) * 100.0);
    }
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
