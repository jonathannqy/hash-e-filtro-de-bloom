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
