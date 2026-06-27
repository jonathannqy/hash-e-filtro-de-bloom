#ifndef SCRIPT_H
#define SCRIPT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerar_nome_aleatorio(char *buffer);
void gerar_arquivo(char *nome_arquivo, int quantidade);
int arquivo_existe(const char *nome_arquivo);

#endif