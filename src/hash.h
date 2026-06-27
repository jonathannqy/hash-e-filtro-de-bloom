#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char identificador[20];
    int ocupado; 
} elementoHash;

// Tabela Hash
typedef struct {
    elementoHash* tabela;
    int quantidade; // Para saber o fator de carga 
} tabelaHash;

// Funções principais 
void inicializar_hash(tabelaHash* h);
void liberar_hash(tabelaHash* h);

// Funções do nosso metodo hash
int hash_divisao(char* chave);
int sondagem_linear(int indice_atual);
int inserir_hash(tabelaHash* h, char* chave);
int buscar_hash(tabelaHash* h, char* chave);
void inserir_lote_hash(tabelaHash* h, char* nome_arquivo);

// Funções auxiliares
int quantidade_registros(tabelaHash* h);
int tamanho_tabela();

#endif