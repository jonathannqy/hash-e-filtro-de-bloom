#ifndef BLOOM_H
#define BLOOM_H

#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int m; //Tamanho de bits
    int k; //Funcões hash
    unsigned char *vetor; //Aponta para a memória
}Filtrodebloom;

//funções filtro de bloom de (criar, liberar(free), inserir e de consultar o filtro)
Filtrodebloom criar_filtro(int n);
unsigned int hash_djb2(char *chave);
void liberar_filtro(Filtrodebloom *bloom);
void inserir_bloom(Filtrodebloom *bloom, char *item);
int consultar_bloom(Filtrodebloom *bloom, char *item);

#endif
