#include "bloom.h"
#include "hash.h"



int verificar_bit(char *vetor, int pos){
    int byte_posicao = pos / 8;
    int bit_posicao = pos % 8;

    //Usando o operador (&) e desclocamento (<<), isso ignora o sinal negativo e foca apenas no bit fisico na memória
    if(vetor[byte_posicao] & (1 << bit_posicao)){
        return 1; //Aqui é verdadeiro. O bit está ligado

   }
   return 0; //Falso, o bit nao está ligado
}

    void marcar_bit(char *vetor, int pos){
    int byte_posicao = pos / 8;
    int bit_posicao = pos % 8;
    
    //Garante que o bit seja ligado sem desligar os bits vizinhos
    vetor[byte_posicao] |= (1 << bit_posicao);
    }

Filtrodebloom criar_filtro(int n){
    Filtrodebloom bloom;
    //10 bits para cada elemento inserido
    bloom.m = n * 10;
    // 7 funções hash
    bloom.k = 7;
   
    //Calloc vai zerar todos os bits automaticamente ao alocar a memória
    bloom.vetor = calloc((bloom.m / 8) + 1, sizeof(char));

    return bloom;
}

void liberar_filtro(Filtrodebloom *bloom){
    //Libera a memória
    free(bloom->vetor);
}

//Funçãao hash auxiliar para espalhar melhor os indices
int hash_auxiliar(int chave, int tamanho) {
    
    int resultado = (chave * 31) % tamanho;

    if (resultado < 0){
        resultado = (resultado * (-1));
    }

    return resultado;
}

void inserir_bloom(Filtrodebloom *bloom, char *item){

  //Funções para gerar o indice do número
  int h1 = hash_divisao(item);
  int h2 = hash_auxiliar(h1, bloom->m);

  int i;
  
  for(i = 0; i < bloom->k; i++){
    //Fórmula matemática do filtro de bloom
    int pos = (h1 + i * h2) % bloom->m;
     
    //Garante que não tenha indice negativo
    if(pos < 0){
        pos = -pos;
    }
        //Marca o bit no vetor
        marcar_bit(bloom->vetor, pos);
  }
}

int consultar_bloom(Filtrodebloom *bloom, char *item){

    //Calcula os dois hash usando métodos diferentes
    int h1 = hash_divisao(item); 
    int h2 = hash_auxiliar(h1, bloom->m);
    
    int i;
    for (i = 0; i < bloom->k; i++) {

        //Calcula a posição exata do bit
        int pos = (h1 + i * h2) % bloom->m;
        if (pos < 0) pos = -pos;
        
        //Se achou algum bit zero vai retornar que o item não existe de forma alguma
        if (verificar_bit(bloom->vetor, pos) == 0) {
            return 0; 
        }
    }

    //Vai retornar que possivelmente existe(e pode conter falsos positivos)
    return 1; 
}
