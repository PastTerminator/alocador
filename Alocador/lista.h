#include<stdlib.h>

typedef struct element{
	struct element*proximo;
    unsigned short int tamanhoBytes;
    short ocupado;
    char*posicaoVetor;
}LElement;

LElement*createList(unsigned short int tamanho,char*memoria);
LElement *createElement(unsigned short int tamanho);
LElement*insertFirst(LElement*root, LElement*toInsert,char**whereToInsert);
LElement*insertBest(LElement*root, LElement*toInsert,char**whereToInsert);
void printlista(LElement*raiz);
int liberarEspaco(LElement*raiz, char*ponteiro);
int checkSpace(LElement*raiz);
int nElementVoid(LElement*root);
int Bigest(LElement*root,int bigest);
int totalFreeSpace(LElement*root);
int verificaNaLista(LElement*raiz, char*verifica);