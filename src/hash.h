#ifndef HASH_H
#define HASH_H

// O tamanho da tabela deve ser um numero primo longe de uma potência de 2 para diminuir colisões com o método da divisão.

// Estrutura para armazenar o dado do usuário
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
void inicializarHash(tabelaHash* h);
void liberarHash(tabelaHash* h);

// Funções do nosso metodo hash
int hash_divisao(char* chave);
int inserir_hash(tabelaHash* h, char* chave);
int buscar_hash(tabelaHash* h, char* chave);
int inserir_lote_hash(tabelaHash* h, char* nome_arquivo);

// Funções auxiliares
int quantidade_registros(tabelaHash* h);

#endif