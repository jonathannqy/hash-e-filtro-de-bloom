#include "bloom.h"
#include "hash.h"

unsigned int hash_djb2(char *chave) {
    unsigned int hash = 5381; 
    //Percorre cada caractere da string até encontrar o caractere nulo que marca o fim do texto
    for (int i = 0; chave[i] != '\0'; i++) {
        hash = (hash * 33) + chave[i]; 
        //Garante que a ordem das lestras eo valor delas criem um número único
    }
    return hash;
}

int verificar_bit(unsigned char *vetor, int pos){
    int byte_posicao = pos / 8;
    int bit_posicao = pos % 8;

    //Vetor de potências de 2 para ativação e verificação de bits
    int potencia[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    
    //Divisão, como tem unsigned nunca fica negativo
    return (vetor[byte_posicao] / potencia[bit_posicao]) % 2;

}

void marcar_bit(unsigned char *vetor, int pos){
    int byte_posicao = pos / 8;
    int bit_posicao = pos % 8;
    int potencia[8] = {1, 2, 4, 8, 16, 32, 64, 128};
    
    //Só soma a potencia se o bit estiver desligado
    if(verificar_bit(vetor, pos) == 0){
        vetor[byte_posicao] += potencia[bit_posicao];
    }
}

Filtrodebloom criar_filtro(int n){
    Filtrodebloom bloom;
    //10 bits para cada elemento inserido
    bloom.m = n * 10;
    // 7 funções hash
    bloom.k = 7;
   
    //Calloc vai zerar todos os bits automaticamente ao alocar a memória
    bloom.vetor = calloc((bloom.m / 8) + 1, sizeof(unsigned char));

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

   unsigned int chave_base = hash_djb2(item);
  //Funções para gerar o indice do número
  int h1 = chave_base % bloom->m;
  int h2 = hash_auxiliar(chave_base / 10, bloom->m);

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
    unsigned int chave_base = hash_djb2(item);
    //Calcula os dois hash usando métodos diferentes
    int h1 = chave_base % bloom->m;
    int h2 = hash_auxiliar(chave_base / 10, bloom->m);
    
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
