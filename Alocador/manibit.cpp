#include "iostream"
#include "string"
#include <bitset>

using namespace std;

void converterBit(unsigned short int tamanho, char *byteFirst, char *byteLast) {

    unsigned short int first = 0, last = 0;
    first = tamanho, last = tamanho;
                            //0000000000000011
    first = (first & 0xFF00); // FF00 = 1111111100000000
    first = (first >> 8);
 

    *byteFirst = (char)first;

    last = (last & 0xFF); // FF = 0000000011111111
    *byteLast = (char)last;

}

void colocarBitsMemoria(int tamanho,char*memoria) {
    unsigned short int numeroMagico = 50;
    char begin, end, magicoBegin, magicoEnd; 
    converterBit(tamanho, &begin, &end);
    converterBit(numeroMagico, &magicoBegin, &magicoEnd);

    memoria[0] = begin;
    memoria[1] = end;
    memoria[2] = magicoBegin;
    memoria[3] = magicoEnd;

    return;
}

unsigned int getBits(char s1, char s2) {

    unsigned int first = (s1 & 0xFF);
    first=first<<8;
    unsigned int last = (s2 & 0xFF);
    unsigned int finalBits = (first | last);
    return finalBits;
}

int printBitChar(char value) {
    
    for (int i = 0; i < 8; i++) {
        printf("%d", !!((value << i) & 0x80));
    }
    printf("\n");
    return 0;
}

void printBits(char*memoria) { // tem mto print só pra tu entender como funciona, pode retirar dps
    printf("tamanho (%d)\n", getBits(memoria[0], memoria[1]));
    printf("primeira parte em bits ");
    printBitChar(memoria[0]);
    printf("segunda parte em bits ");
    printBitChar(memoria[1]);
    printf("\n");
}