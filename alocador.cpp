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

struct LinkedList {
    struct LinkedList *next;
    int tamanhoBytes; //bound 
    int base;
    int tamanho;
    int tamanhoLista;
    int resto;
    int ocupado;
    char *posicaoVetor;
};

struct LinkedList* createList () {

    struct LinkedList *Nlist = (struct LinkedList*) malloc(sizeof(struct LinkedList*));
    Nlist->tamanhoLista = 0;
    Nlist->next = NULL;
    return Nlist;
} 

struct LinkedList* insertList(struct LinkedList *list, int tamanho, char *posicaoPagina) { // aloca um bloco de um tamanho qualquer

    struct LinkedList *aux, *aux2;
    struct LinkedList *temp = createList();
    int totalSize = 0;
    int flag = 0;
    temp->tamanho = tamanho;
    temp->posicaoVetor = posicaoPagina;
    if (list == NULL) {
        temp->tamanhoBytes = (tamanho - 1);
        temp->base = 0;
        totalSize += tamanho;
        list = temp;
    } else {
        
        aux = list;
        aux2 = list;
        while (aux->next != NULL) { 
            aux = aux->next;
        }
        aux->next = temp;
        while (aux2 != NULL) {
            totalSize += aux2->tamanho;
            aux2->tamanhoBytes = (totalSize - 1);
            aux2->base = (totalSize - aux2->tamanho);
            aux2 = aux2->next;  
        }
    }
    
    return list;
}

int sizeList(struct LinkedList *list) {
    int size = 0;

    while (list != NULL) {
        size++;
        list = list->next;
    }

    return size;
}

void printList(struct LinkedList *list1) {

    if (list1 == NULL)
        printf("Lista vazia\n");

    struct LinkedList *list = list1;
    while (list != NULL) {

        printf("base (%d) bound (%d) tamanhoLista(%d)\n",list->base, list->tamanhoBytes, list->tamanhoLista);

        list = list->next;
    }

    printf("\n");
}



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

void bit_set(char bit, char *byte) {
    bit = 1 << bit;
    *byte = *byte | bit;
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

struct LinkedList *blocoMemoria = NULL;

char *aloca(unsigned short int tamanho) {
    unsigned short int numeroMagico = 100;
    char magicoBegin, magicoEnd;
    converterBit(numeroMagico, &magicoBegin, &magicoEnd);

    char begin, end;
    converterBit(tamanho, &begin, &end);
    int size = sizeList(blocoMemoria);
    int i = 0;
    char *posicaoPagina;
    for (i = 0; i < (size); i++) { 
    }
    if (!i) {
        memoria[0] = begin;
        memoria[1] = end;
        memoria[2] = magicoBegin;
        memoria[3] = magicoEnd;
        posicaoPagina = &memoria[0];
        printf("s1 (%d) s2 (%d) magico1 (%d) magico2 (%d) posicaoPagina (%p)\n", memoria[0], memoria[1],
         memoria[2], memoria[3], posicaoPagina);
    }
    if (i > 0) {
        i *= 4;
        memoria[i] = begin;
        printf("s1 (%d) ", memoria[i]);
        posicaoPagina = &memoria[i];
        i += 1;
        memoria[i] = end;
        printf("s2 (%d) ", memoria[i]);
        i += 1;
        memoria[i] = magicoBegin;
        printf("magico1 (%d) ", memoria[i]);
        i += 1;
        memoria[i] = magicoEnd;
        printf("magico2 (%d) ", memoria[i]);

        printf("posicaoPagina (%p)\n", posicaoPagina);

    }
    
    blocoMemoria = insertList(blocoMemoria, tamanho, posicaoPagina);
}


int main() {

    aloca(100);
    aloca(200);
    aloca(600);

}
