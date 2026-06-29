#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"
#include "bloom.h"

void menu_principal();
void menu_lote();

int iniciar_cronometro();
int parar_cronometro(int inicio);

void inserir_lote_completo(tabelaHash* h, Filtrodebloom* b, char* nome_arquivo);

void resultados_sem_bloom(char* nome_arquivo, int total_consultas, int tempo_total);
void resultados_com_bloom(char* nome_arquivo, int total_consultas, int consultas_evitadas, int falsos_positivos, int tempo_total);

#endif