#include "script.h"
#include "auxiliares.h"

typedef struct {
    int total_consultas;
    int consultas_evitadas;
    int falsos_positivos;
    int tempo_total_consultas; // Guarda a soma dos tempos em microssegundos
} Estatisticas;

int main() {

    // Inicializando a tabela hash
    tabelaHash hash;    
    inicializar_hash(&hash);
    //////////////////////////////

    // Inicializando o filtro de Bloom
    Filtrodebloom bloom = criar_filtro(100000);
    // O parâmetro 100000 representa a quantidade de usuários que iremos inserir, como os testes são mais perceptíveis com 100k, deixamos por padrão 100000 na função.
    //////////////////////////////

    // Inicializando as estatísticas
    Estatisticas status = {0, 0, 0, 0};
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
                scanf("%20s", identificador);

                inserir_hash(&hash, identificador);
                inserir_bloom(&bloom, identificador);
                

                printf("Usuário %s inserido com sucesso (Hash + Bloom).\n", identificador);
                break;
            }

            case 2: {
                printf("Digite o identificador para consulta: ");
                scanf("%20s", identificador);

                // Regista uma consulta
                status.total_consultas++;

                int tempo_inicial = iniciar_cronometro();

                if (consultar_bloom(&bloom, identificador) == 0) {
                    //Se retornar 0, o usuario com certeza não existe
                    printf("O usuário '%s' não existe\n", identificador);

                    // Regista uma consulta evitada
                    status.consultas_evitadas++;
                }

                else {
                //Se retornar 1, o usuário possivelmente existe
                printf("O usuário '%s' possivelmente existe. Verificando na tabela hash...\n", identificador);

                    //Verificando a tabela hash
                    if (buscar_hash(&hash, identificador) == 1) {
                        printf("Usuário '%s' encontrado na tabela hash!\n", identificador);
                    } 
                    else {
                        printf("O usuário '%s' não existe. É um falso positivo\n", identificador);

                        // Regista um falso positivo
                        status.falsos_positivos++;
                    }
                }

                // Regista o tempo de consulta
                status.tempo_total_consultas += parar_cronometro(tempo_inicial);

                break;
            }
            
            case 3: {
                printf("Digite o identificador para consulta direta na Hash: ");
                scanf("%20s", identificador);

                int tempo_inicial = iniciar_cronometro();

                // Ignora o bloom
                if (buscar_hash(&hash, identificador) == 1) {
                    printf("Usuário '%s' encontrado na tabela hash!\n", identificador);
                } 
                
                else {
                    printf("O usuário '%s' não existe.\n", identificador);
                }

                int tempo_gasto = parar_cronometro(tempo_inicial);
                printf("Tempo de busca na Hash: %d microssegundos.\n", tempo_gasto);
                
                break;
            }  

            case 4: {
                printf("\n--- Estatisticas do Sistema ---\n");
                
                printf("Quantidade de elementos armazenados: %d\n", quantidade_registros(&hash));
                printf("Quantidade de consultas realizadas: %d\n", status.total_consultas);
                printf("Consultas evitadas pela Bloom: %d\n", status.consultas_evitadas);
                printf("Número de falsos positivos: %d\n", status.falsos_positivos);

                if (status.total_consultas > 0) {
                    double taxa_fp = ((double)status.falsos_positivos / status.total_consultas) * 100.0;
                    double tempo_medio = (double)status.tempo_total_consultas / status.total_consultas;
                    
                    printf("Taxal de falsos positivos: %.2f%%\n", taxa_fp);
                    printf("Tempo médio de consulta: %.2f microssegundos\n", tempo_medio);
                }

                else {
                    printf("Taxa de falsos positivos: 0.00%%\n");
                    printf("Tempo médio de consulta: 0.00 microssegundos\n");
                }                

                break;
            }

            case 5: {
                int lote;

                printf("Lote que deseja inserir na Hash e no Bloom:\n");
                printf("[1] Lote 1k\n");
                printf("[2] Lote 10k\n");
                printf("[3] Lote 100k\n");  
                scanf("%d", &lote);

                if (lote == 1) {
                    inserir_lote_completo(&hash, &bloom, "data/usuarios1k.txt");
                } 
                
                else if (lote == 2) {
                    inserir_lote_completo(&hash, &bloom, "data/usuarios10k.txt");
                }
                
                else if (lote == 3) {
                    inserir_lote_completo(&hash, &bloom, "data/usuarios100k.txt");
                }

                break;
            }


            case 6: {
                int tamanho_lote;

                menu_lote();
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
                    
                    else if (tamanho_lote == 4) {
                        tamanho_lote = 1000;
                        gerar_arquivo_fake("data/usuarios1kfake.txt", tamanho_lote);
                    }

                    else if (tamanho_lote == 5) {
                        tamanho_lote = 10000;
                        gerar_arquivo_fake("data/usuarios10kfake.txt", tamanho_lote);
                    }
                    
                    else if (tamanho_lote == 6) {
                        tamanho_lote = 100000;
                        gerar_arquivo_fake("data/usuarios100kfake.txt", tamanho_lote);
                    }

                    else {
                        printf("Opção inválida!\n");
                        break;
                    }

                break;

            }

            case 7: {
                printf("Quantidade de registrados na Hash: %d\n", quantidade_registros(&hash));
                break;
            }

            case 8: {
                int lote;
                char nome_arquivo[50];

                menu_lote(); 
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

                else if (lote == 4) {
                    strcpy(nome_arquivo, "data/usuarios1kfake.txt");
                } 

                else if (lote == 5) {
                    strcpy(nome_arquivo, "data/usuarios10kfake.txt");
                } 

                else if (lote == 6) {
                    strcpy(nome_arquivo, "data/usuarios100kfake.txt");
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

                // Inicia o cronômetro
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
                resultados_sem_bloom(nome_arquivo, total_consultas, tempo_total);

                break;
            }

            case 9: {
                int lote;
                char nome_arquivo[50];

                menu_lote();
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

                else if (lote == 4) {
                    strcpy(nome_arquivo, "data/usuarios1kfake.txt");
                } 

                else if (lote == 5) {
                    strcpy(nome_arquivo, "data/usuarios10kfake.txt");
                } 

                else if (lote == 6) {
                    strcpy(nome_arquivo, "data/usuarios100kfake.txt");
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
                int consultas_evitadas = 0;
                int falsos_positivos = 0;

                printf("Buscando todos os registros do arquivo na Tabela Hash (com bloom)...\n");

                // Inicia o cronômetro
                int tempo_inicio = iniciar_cronometro();

                // Lê o arquivo linha por linha e realiza a busca usando Bloom + Hash
                while (fscanf(arquivo, "%19s", usuario) == 1) {
                    total_consultas++;
                    
                    // Verifica primeiro no filtro de bloom
                    if (consultar_bloom(&bloom, usuario) == 0) {
                        consultas_evitadas++;
                    } 
                    
                    else {
                        // Se o Bloom diz que possivelmente existe, verifica na Hash
                        if (buscar_hash(&hash, usuario) == 0) {
                            falsos_positivos++; // Se a Hash não achou, era um falso positivo do Bloom
                        }
                    }
                }

                // Para o cronômetro
                int tempo_total = parar_cronometro(tempo_inicio);

                fclose(arquivo);

                // Imprime os resultados
                resultados_com_bloom(nome_arquivo, total_consultas, consultas_evitadas, falsos_positivos, tempo_total);
                
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
