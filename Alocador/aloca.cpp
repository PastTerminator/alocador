#include "aloca.h"
#include "manibit.h"
#include "iostream"
#include "string"

meualoc::meualoc(int tamanhoMemoria,int politicaMem){
    memoria = (char*)malloc(sizeof(char)*tamanhoMemoria);
    politica=politicaMem;
    rootFree=createList(tamanhoMemoria,&memoria[0]);
    printf("memoria: %p\n",&memoria[0]);
}

char* meualoc::aloca(unsigned short int tamanho){
    char*toReturn=NULL;
    switch(politica)
    {
    case 0://BestFit
        rootFree=insertBest(rootFree,createElement(tamanho+4),&toReturn);
        colocarBitsMemoria(tamanho,toReturn);
        return toReturn;
        break;
    case 1://FirstFit
        rootFree=insertFirst(rootFree,createElement(tamanho+4),&toReturn);
        colocarBitsMemoria(tamanho,toReturn);
        return toReturn;
        break;
    }
}

int meualoc::libera(char*ponteiro){
    int retorno=liberarEspaco(rootFree,ponteiro);
    while(checkSpace(rootFree));
    return retorno;
}

int meualoc::verifica(char* ponteiro,int posicao){
    verificaNaLista(rootFree, &ponteiro[posicao]);
}

void meualoc::imprimeDados(){
    //printlista(rootFree);
    printf("Numero de Elementos na Lista dos Vazios: %d\n",nElementVoid(rootFree));
    printf("Maior espaço Livre: %d\n",Bigest(rootFree,0));
    printf("Média dos espaços livres: %d\n \n",totalFreeSpace(rootFree)/nElementVoid(rootFree));
    return;
}

meualoc::~meualoc(){
    free(memoria);
}
