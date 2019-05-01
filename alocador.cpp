#include "aloca.h"
#include "iostream"
#include "string"
#include <bitset>
using namespace std;

//meualoc(int tamanhoMemoria, int politicaMem);
// the total size
// how to use bitmask operations using char?

int tamanhoMemoria1 = 100;
int politicaMem1 = 10;

meualoc::meualoc(int tamanhoMemoria, int politicaMem) {
    tamanhoMemoria1 = tamanhoMemoria;
    politicaMem1 = politicaMem;
}

char *memoria = (char*)malloc(sizeof(tamanhoMemoria1));

struct LinkedList {
    struct LinkedList *next;
    int tamanhoBytes; //bound 
    int base;
    int tamanho;
};

struct LinkedList* createList () {

    struct LinkedList *Nlist = (struct LinkedList*) malloc(sizeof(struct LinkedList*));

    Nlist->next = NULL;
    return Nlist;
} 

struct LinkedList* insertList(struct LinkedList *list, int tamanho) { // aloca um bloco de um tamanho qualquer

    struct LinkedList *aux, *aux2;
    struct LinkedList *temp = createList();
    int totalSize = 0;

    temp->tamanho = tamanho;

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

void printList(struct LinkedList *list1) {

    if (list1 == NULL)
        printf("Lista vazia\n");

    struct LinkedList *list = list1;
    while (list != NULL) {

        printf("base (%d) bound (%d) ",list->base, list->tamanhoBytes);

        list = list->next;
    }

    printf("\n");
}

struct LinkedList *blocoMemoria = NULL;

void printBits(unsigned int num)
{
   for(int bit=0;bit<(sizeof(unsigned int) * 8); bit++)
   {
      printf("%i ", num & 0x01);
      num = num >> 1;
   }
   printf("\n");
}

char *aloca(unsigned short int tamanho) {
    
    blocoMemoria = insertList(blocoMemoria, tamanho);
   
    printBits(tamanho);
}



int main() {

    aloca(100); 
    aloca(200);
    printList(blocoMemoria);

}



