#include "bloom.h"
#include "hash.h"

int potencias_de_dois[8] = {1, 2, 4, 8, 16, 32, 64, 128}; //Vetor de potências para ligar os bits

int verificar_bit(char *vetor, int pos){
    int byte_posicao = pos / 8;
    int bit_posicao = pos % 8;
    
    //Pega o valor decimal total armazenado no bloco de 8bits
    int estado_byte = vetor[byte_posicao];
     
    //Pega a potencia de 2 correspodente a posição do bit desejado
    int peso_bit = potencias_de_dois[bit_posicao];
     
    //Divisao do estado do byte pelo peso do bit desloca o valor desejado. Se o resto da divisao por 2 for ímpar, o bit é 1
    if((estado_byte / peso_bit) % 2 != 0){
        return 1; //Verdadeiro. O bit está ligado
    }
    return 0; //Falso. O bit não está ligado.
} 

    //Essa função vai ligar um bit especifico dentro do vetor
    void marcar_bit(char *vetor, int pos){
    int byte_posicao = pos / 8;
    int bit_posicao = pos % 8;

    //Garante que a soma so aconteça em bits desligados
    if(verificar_bit(vetor, pos) == 0){
        vetor[byte_posicao] = vetor[byte_posicao] + potencias_de_dois[bit_posicao];
    }
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
    if (resultado < 0) resultado = -resultado;
    return resultado;
}

void inserir_bloom(Filtrodebloom *bloom, char *item){
  int chave = texto_para_int(item);

  //Funções para gerar o indice do número
  int h1 = hash_divisao(item);
  int h2 = hash_auxiliar(chave, bloom->m);

  int i;
  
  for(i = 0; i < bloom->k; i++){
    //Fórmula matemática do filtro de bloom
    int pos = (h1 * i * h2) % bloom->m;
     
    //Garante que não tenha indice negativo
    if(pos < 0){
        pos = -pos;
    }
        //Marca o bit no vetor
        marcar_bit(bloom->vetor, pos);
  }
}

int consultar_bloom(Filtrodebloom *bloom, char *item){
    int chave = texto_para_int(item);

    //Calcula os dois hash usando métodos diferentes
    int h1 = hash_divisao(item); 
    int h2 = hash_auxiliar(chave, bloom->m);
    
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
