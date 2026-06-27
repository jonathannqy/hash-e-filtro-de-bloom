#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hash.h"
#include "script.h"


void menu_principal();

int main() {

    // Inicializando a tabela hash
    tabelaHash hash;    
    inicializar_hash(&hash);
    //////////////////////////////

    // Inicializando o filtro de Bloom
    //////////////////////////////

    int opcao;
    char identificador[50];

    do {
        menu_principal();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida!\n");
            while(getchar() != '\n'); // Limpa o buffer
        }

        switch (opcao) {
            case 1: {
                printf("Digite o identificador do usuário: ");
                scanf("%49s", identificador);

                inserir_hash(&hash, identificador);
                // Inserir no bloom depois

                printf("Usuário %s inserido com sucesso (Hash).\n", identificador);
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
                int lote;

                printf("Qual lote deseja inserir:\n");
                printf("[1] Lote 1k\n");
                printf("[2] Lote 10k\n");
                printf("[3] Lote 100k\n");  
                scanf("%d", &lote);

                if (lote == 1) {
                    inserir_lote_hash(&hash, "data/usuarios1k.txt");
                } 
                
                else if (lote == 2) {
                    inserir_lote_hash(&hash, "data/usuarios10k.txt");
                }
                
                else if (lote == 3) {
                    inserir_lote_hash(&hash, "data/usuarios100k.txt");
                }


                break;
            }


            case 5: {
                int tamanho_lote;

                printf("Qual o tamanho do lote: \n");
                printf("[1] Lote 1k\n");
                printf("[2] Lote 10k\n");
                printf("[3] Lote 100k\n");
                scanf("%d", &tamanho_lote);

                    if (tamanho_lote == 1) {
                        tamanho_lote = 1000;
                        gerar_arquivo("data/usuarios1k.txt", tamanho_lote);
                    } 

                    else if (tamanho_lote == 2) {
                        tamanho_lote = 10000;
                        gerar_arquivo("data/usuarios10k.txt", tamanho_lote);
                    } 
                    
                    else if (tamanho_lote == 3) {
                        tamanho_lote = 100000;
                        gerar_arquivo("data/usuarios100k.txt", tamanho_lote);
                    } 
                    
                    else {
                        printf("Opção inválida!\n");
                        break;
                    }

                break;

            }

            case 6: {
                printf("Quantidade de registros: %d\n", quantidade_registros(&hash));
                break;
            }

            case 0: {
                printf("Limpando tabela hash..\n");
                liberar_hash(&hash);

                /*
                printf("Limpando filtro de Bloom..\n");
                liberar_filtro(&meu_filtro);
                */

                printf("Encerrando o sistema...\n");
                break;
           }


            default: {
                printf("Opção inválida! Tente novamente.\n");
                break;
            }
        }

    } while (opcao != 0);

    return 0;
}

void menu_principal() {
    printf("\n--- Sistema de Verificacao de Cadastro ---\n");
    printf("[1] Inserir novo usuário\n");
    printf("[2] Consultar usuário\n");
    printf("[3] Exibir estatísticas\n");
    printf("[4] Inserir lote\n");
    printf("[5] Gerar lote(Arquivo)\n");
    printf("[6] Quantidade de registros\n");
    printf("[0] Sair\n");
    printf("Escolha uma opção: ");
}