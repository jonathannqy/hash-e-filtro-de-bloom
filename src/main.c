#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "bloom.h"


void menu_principal();

int main() {
    int opcao;
    char identificador[50];
    char nome_arquivo[50];

    do {
        menu_principal();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida!\n");
            while(getchar() != '\n'); // Limpa o buffer
            continue;
        }

        switch (opcao) {
            case 1: {
                printf("Digite o identificador do usuário: ");
                scanf("%49s", identificador);
                
                printf("Usuário %s inserido com sucesso.\n", identificador);
                break;
            }


            case 2: {
                printf("Digite o identificador para consulta: ");
                scanf("%49s", identificador);

                // Fluxo obrigatorio:
                // 1. Consultar Filtro de Bloom
                // 2. Se nao existe no Bloom -> "definitivamente nao existe" 
                // 3. Se possivelmente existe -> Consultar Tabela Hash 
                break;

            }

            case 3: {
                printf("\n--- Estatisticas do Sistema ---\n");
                break;
            }


            case 4: {
                printf("Digite o nome do arquivo texto (ex: usuarios.txt [cite: 55]): ");
                scanf("%49s", nome_arquivo);
                
                FILE *arquivo = fopen(nome_arquivo, "r");
                if (arquivo == NULL) {
                    printf("Erro na hora de abrir o arquivo '%s'!\n", nome_arquivo);
                } 
                
                else {
                    
                    printf("Lote carregado com sucesso!\n");
                    fclose(arquivo);
                }

                break;

            }

            case 0: {
                printf("Encerrando o sistema...\n");
                break;
           }


            default: {
                printf("Opção inválida! Tente novamente.\n");
                break;
            }
        }

    } while (opcao != 0);

    // TODO: Liberar memoria alocada para a Hash e para o vetor de bits do Bloom (se houver)

    return 0;
}

void menu_principal() {
    printf("\n--- Sistema de Verificacao de Cadastro ---\n");
    printf("[1] Inserir novo usuario\n");
    printf("[2] Consultar usuario\n");
    printf("[3] Exibir estatisticas\n");
    printf("[4] Inserir em lote (Arquivo)\n");
    printf("[0] Sair\n");
    printf("Escolha uma opção: ");
}