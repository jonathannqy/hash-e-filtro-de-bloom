#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hash.h"
#include "script.h"
#include "bloom.h"


void menu_principal();
int iniciar_cronometro();
int parar_cronometro(int inicio);

int main() {

    // Inicializando a tabela hash
    tabelaHash hash;    
    inicializar_hash(&hash);
    //////////////////////////////

    // Inicializando o filtro de Bloom
    Filtrodebloom bloom = criar_filtro(100000);
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
                inserir_bloom(&bloom, identificador);
                

                printf("Usuário %s inserido com sucesso (Hash + Bloom).\n", identificador);
                break;
            }


            case 2: {
                printf("Digite o identificador para consulta: ");
                scanf("%49s", identificador);

                if (consultar_bloom(&bloom, identificador) == 0) {
                    //Se retornar 0, o usuario com certeza não existe
                    printf("O usuario '%s' não existe\n", identificador);
                }

                else {
                //Se retornar 1, o usuário possivelmente existe
                printf("O usuario '%s' possivelmente existe. Verificando na tabela hash...\n", identificador);

                    //Verificando a tabela hash
                    if (buscar_hash(&hash, identificador) == 1) {
                        printf("Usuario '%s' encontrado na tabela hash!\n", identificador);
                    } 
                    else {
                        printf("O usuario '%s' não existe. É um falso positivo\n", identificador);
                    }
                }

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

            case 7: {
                int lote;
                char nome_arquivo[50];

                printf("Qual lote deseja usar para o experimento de busca:\n");
                printf("[1] Lote 1k\n");
                printf("[2] Lote 10k\n");
                printf("[3] Lote 100k\n");  
                scanf("%d", &lote);

                if (lote == 1) {
                    strcpy(nome_arquivo, "data/usuarios1k.txt");
                }

                else if (lote == 2) {
                    strcpy(nome_arquivo, "data/usuarios10k.txt");
                } 
                
                else if (lote == 3) {
                    strcpy(nome_arquivo, "data/usuarios100k.txt");
                } 
                
                else {
                    printf("Opção inválida!\n");
                    break;
                }

                // Abre o arquivo para leitura
                FILE *arquivo = fopen(nome_arquivo, "r");
                if (arquivo == NULL) {
                    printf("Erro: Arquivo '%s' não encontrado. Gere o lote primeiro.\n", nome_arquivo);
                    break;
                }

                char usuario[20];
                int total_consultas = 0;

                printf("Buscando todos os registros do arquivo na Tabela Hash (sem bloom)...\n");

                // 1. Inicia o cronômetro
                int tempo_inicio = iniciar_cronometro();

                // Lê o arquivo linha por linha e realiza a busca na Hash
                while (fscanf(arquivo, "%19s", usuario) == 1) {
                    buscar_hash(&hash, usuario);
                    total_consultas++;
                }

                // Para o cronômetro
                int tempo_total = parar_cronometro(tempo_inicio);

                fclose(arquivo);

                // Imprime os resultados
                printf("\n--- RESULTADOS DO EXPERIMENTO (SEM BLOOM) ---\n");
                printf("Arquivo testado: %s\n", nome_arquivo);
                printf("Quantidade de buscas: %d\n", total_consultas);
                printf("Tempo total gasto: %d microssegundos.\n", tempo_total);
                printf("Tamanho da tabela Hash: %d\n", tamanho_tabela()); 
                
                if (total_consultas > 0) {
                    printf("Tempo médio por busca: %.4f microssegundos.\n", (double)tempo_total / total_consultas);
                }
                
                break;
            }

            case 0: {
                printf("Limpando tabela hash..\n");
                liberar_hash(&hash);

                printf("Limpando filtro de Bloom..\n");
                liberar_filtro(&bloom);

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
    printf("[7] Roda experimento de busca (sem bloom)\n");
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