#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
 
// 100003 é um número primo adequado para evitar colisões com até 100000 entradas.
#define TAMANHO_TABELA 100003 

// Tamanhos ideais para um lote de 1000:
// #define TAMANHO_TABELA 4001 // FC = 25%.
// #define TAMANHO_TABELA 1999 // FC = 50%.
// #define TAMANHO_TABELA 1361 // FC = 75%.

// Tamanhos ideais para um lote de 10.000:
//#define TAMANHO_TABELA 40009 // FC = 0.25 = 25%.
// #define TAMANHO_TABELA 20011 // FC = 50%.
// #define TAMANHO_TABELA  13337 // FC = 75%.

// Tamanhos ideais para um lote de 100.000:
//#define TAMANHO_TABELA 400009 // FC = 0.25 = 25%. 
// #define TAMANHO_TABELA  200003 // FC = 50%.
// #define TAMANHO_TABELA  133379 // FC = 75%.

// Funções principais
void inicializar_hash(tabelaHash* h) {
    // Aloca o vetor de elementos com base no tamanho definido
    h->tabela = (elementoHash*)malloc(TAMANHO_TABELA * sizeof(elementoHash));
    h->quantidade = 0;

    // Inicializa todos os slots como vazios
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        h->tabela[i].ocupado = 0;
    }
}

void liberar_hash(tabelaHash* h) {
    if (h->tabela != NULL) {
        free(h->tabela);
        h->tabela = NULL;
    }
    h->quantidade = 0;
}
////////////////////////////////////////////////////////////////////////////////////


// Funções do nosso método hash

// Método da divisão
int hash_divisao(char* chave) {
    unsigned int soma = 0;
    
    // Soma os valores ASCII da string 
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += (unsigned char)chave[i];
    }

    return soma % TAMANHO_TABELA;
}

// Função da sondagem linear
int sondagem_linear(int indice_atual) {
    return (indice_atual + 1) % TAMANHO_TABELA;
}

// Inserção na tabela hash 
int inserir_hash(tabelaHash* h, char* chave) {
    // Proteção contra tabela cheia (fator de carga = 1)
    if (h->quantidade >= TAMANHO_TABELA) {
        printf("Erro: Tabela Hash esta cheia!\n");
        return 0; // Falha na inserção
    }

    int indice_inicial = hash_divisao(chave);
    int indice = indice_inicial;

    // Sondagem Linear: Procura o próximo espaço vazio
    while (h->tabela[indice].ocupado == 1) {
        // Evita inserir usuários duplicados
        if (strcmp(h->tabela[indice].identificador, chave) == 0) {
            return 0; 
        }
        
        // Chama a sondagem linear
        indice = sondagem_linear(indice);
    }

    // Insere o dado se achar uma posição livre
    strncpy(h->tabela[indice].identificador, chave, 19);
    h->tabela[indice].identificador[19] = '\0'; // Garante o fim da string
    h->tabela[indice].ocupado = 1;
    h->quantidade++;

    return 1; // Inserção feita com sucesso
}

// Busca com sondagem linear
int buscar_hash(tabelaHash* h, char* chave) {
    if (h->tabela == NULL) return 0;

    int indice_inicial = hash_divisao(chave);
    int indice = indice_inicial;

    // Percorre enquanto houver elementos na sequência de colisão
    while (h->tabela[indice].ocupado == 1) {
        
        // Quando encontra o usuário, retorna verdadeiro
        if (strcmp(h->tabela[indice].identificador, chave) == 0) {
            return 1; 
        }
        
        // Chama a sondagem linear
        indice = sondagem_linear(indice);
        
        // Condição de parada de segurança: se deu uma volta inteira no vetor
        if (indice == indice_inicial) {
            break; 
        }
    }

    // Se encontrou um slot vazio (ocupado == 0) antes de achar a chave, ou se deu a volta inteira, significa que o usuário não existe.
    return 0; 
}

// inserção em lote a partir de um arquivo
void inserir_lote_hash(tabelaHash* h, char* nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    
    if (arquivo == NULL) {
        printf("Erro: Não foi possível abrir o arquivo '%s'.\n", nome_arquivo);
        return;
    }

    char usuario[20];

    // Lê até o fim do arquivo (usando limite de 19 chars para não estourar o buffer)
    while (fscanf(arquivo, "%19s", usuario) == 1) {
        inserir_hash(h, usuario);
    }

    fclose(arquivo);
    return;
}
////////////////////////////////////////////////////////////////////////////////////



// Função auxiliar
int quantidade_registros(tabelaHash* h) {
    return h->quantidade;
}
////////////////////////////////////////////////////////////////////////////////////
