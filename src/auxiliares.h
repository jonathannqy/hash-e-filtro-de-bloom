#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"
#include "bloom.h"

void menu_principal();
int iniciar_cronometro();
int parar_cronometro(int inicio);
void inserir_lote_completo(tabelaHash* h, Filtrodebloom* b, char* nome_arquivo);

#endif