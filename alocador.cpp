#include "aloca.h"
#include "iostream"
#include "string"
#include <bitset>
using namespace std;

//meualoc(int tamanhoMemoria, int politicaMem);
// the total size
// how to use bitmask operations using char?

int tamanhoMemoria1 = 1000;
int politicaMem1 = 10;

meualoc::meualoc(int tamanhoMemoria, int politicaMem) {
    tamanhoMemoria1 = tamanhoMemoria;
    politicaMem1 = politicaMem;
}

char *memoria = (char*)malloc(sizeof(char)*tamanhoMemoria1);

void printBits(unsigned int num) {
    int vector[16];

    for(int bit = 0; bit < 16; bit++)
    {
        vector[bit] = (num&0x01);
        num = num >> 1;
    }

    for (int i = 15; i >= 0; i--) {
        printf("%d", vector[i]);
    }

    printf("\n");
}

int printBitChar(char value) {
    
    for (int i = 0; i < 8; i++) {
        printf("%d", !!((value << i) & 0x80));
    }
    printf("\n");
    return 0;
}

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

unsigned int getBits(char s1, char s2) {

    unsigned int first = (s1 & 0xFF);
    unsigned int last = (s2 & 0xFF);
    unsigned int finalBits = (first | last);
    
    return finalBits;
}


char* colocarBitsMemoria(int tamanho) {
    unsigned short int numeroMagico = 50;
    char begin, end, magicoBegin, magicoEnd; 
    converterBit(tamanho, &begin, &end);
    converterBit(numeroMagico, &magicoBegin, &magicoEnd);

    memoria[0] = begin;
    memoria[1] = end;
    memoria[2] = magicoBegin;
    memoria[3] = magicoEnd;

    return &memoria[0];
}

void printBits() { // tem mto print só pra tu entender como funciona, pode retirar dps

    printf("Isto é o tamanho\n");
    printf("total (%d)\n", getBits(memoria[0], memoria[1]));
    printf("primeira parte (%d) segunda parte (%d)\n", memoria[0], memoria[1]);
    

    unsigned int bits = getBits(memoria[0], memoria[1]);

    printf("total em bits ");
    printBits(bits);
    printf("primeira parte em bits ");
    printBitChar(memoria[0]);
    printf("segunda parte em bits ");
    printBitChar(memoria[1]);

    printf("\n");

    printf("Isto é o número mágico\n");

    printf("total (%d)\n", getBits(memoria[2], memoria[3]));
    printf("primeira parte (%d) segunda parte (%d)\n", memoria[2], memoria[3]);


    bits = getBits(memoria[2], memoria[3]);

    printf("total em bits ");
    printBits(bits);
    printf("primeira parte em bits ");
    printBitChar(memoria[2]);
    printf("segunda parte em bits ");
    printBitChar(memoria[3]);

    printf("\n");


}

char *aloca(unsigned short int tamanho) {
    colocarBitsMemoria(tamanho);
    printBits();
}


int main() {

    aloca(100);


}
