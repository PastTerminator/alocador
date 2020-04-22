#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lista.h"

LElement*createList(unsigned short int tamanho,char*memoria){
    LElement*novo =(struct element*) malloc(sizeof(LElement));
    novo->tamanhoBytes=tamanho;
    novo->ocupado=0;
    novo->posicaoVetor=memoria;
	novo->proximo = NULL;
	return novo;
}

LElement *createElement(unsigned short int tamanho){
	LElement*novo =(struct element*) malloc(sizeof(LElement));
    novo->tamanhoBytes=tamanho;
    novo->ocupado=1;
    novo->posicaoVetor=NULL;
	novo->proximo = NULL;
	return novo;
}

LElement*insertFirst(LElement*root, LElement*toInsert,char**whereToInsert){
    if((root->ocupado==0)&&(root->tamanhoBytes>toInsert->tamanhoBytes)){
        toInsert->proximo=root;
        toInsert->posicaoVetor=root->posicaoVetor;
        root->tamanhoBytes=root->tamanhoBytes-toInsert->tamanhoBytes;
        root->posicaoVetor=root->posicaoVetor+toInsert->tamanhoBytes;
        *whereToInsert=toInsert->posicaoVetor;
        return toInsert;
    }else if((root->ocupado==0)&&(root->tamanhoBytes==toInsert->tamanhoBytes)){
        toInsert->proximo=root->proximo;
        toInsert->posicaoVetor=root->posicaoVetor;
        free(root);
        *whereToInsert=toInsert->posicaoVetor;
        return toInsert;
    }else{
        root->proximo=insertFirst(root->proximo,toInsert,whereToInsert);
        return root;
    }
}
LElement*bestElement(LElement*root,int tamanho){
    LElement*AUX=root;
    LElement*retorno=NULL;
    int melhorAtual=9999999;
    while(AUX!=NULL){
        if((!AUX->ocupado)&&(AUX->tamanhoBytes>=tamanho)&&(AUX->tamanhoBytes<melhorAtual)){
            melhorAtual=AUX->tamanhoBytes;
            retorno=AUX;
        }
        AUX=AUX->proximo;
    }
    return retorno;
}
LElement*ondeInserir(LElement*root,LElement*toInsert,char*posicao){
    if(root->posicaoVetor==posicao){
        if(root->tamanhoBytes>toInsert->tamanhoBytes){
            toInsert->proximo=root;
            toInsert->posicaoVetor=root->posicaoVetor;
            root->tamanhoBytes=root->tamanhoBytes-toInsert->tamanhoBytes;
            root->posicaoVetor=root->posicaoVetor+toInsert->tamanhoBytes;
            return toInsert;
        }else if((root->ocupado==0)&&(root->tamanhoBytes==toInsert->tamanhoBytes)){
            toInsert->proximo=root->proximo;
            toInsert->posicaoVetor=root->posicaoVetor;
            free(root);
            return toInsert;
        }
    }
    root->proximo=ondeInserir(root->proximo,toInsert,posicao);
    return root;
    
}
LElement*insertBest(LElement*root, LElement*toInsert,char**whereToInsert){
    LElement*Best=bestElement(root,toInsert->tamanhoBytes);
    *whereToInsert=Best->posicaoVetor;
    return ondeInserir(root,toInsert,Best->posicaoVetor);
}
int liberarEspaco(LElement*raiz, char*ponteiro){
    if(raiz==NULL) return 0;
    if(raiz->posicaoVetor==ponteiro){
        raiz->ocupado=0;
        return 1;
    }else{
        return liberarEspaco(raiz->proximo, ponteiro);
    }

}
int checkSpace(LElement*raiz){
    LElement*proximo=raiz->proximo;
    if(proximo==NULL) return 0;
    if((raiz->ocupado==0)&&(proximo->ocupado==0)){
        raiz->proximo=proximo->proximo;
        raiz->tamanhoBytes=raiz->tamanhoBytes+proximo->tamanhoBytes;
        free(proximo);
        return 1;
    }
    return checkSpace(raiz->proximo);
}
int nElementVoid(LElement*root){
    if(root==NULL) return 0;
    if(root->ocupado==0){
        return 1+nElementVoid(root->proximo);
    }else{
        return nElementVoid(root->proximo);
    }
}
int Bigest(LElement*root,int bigest){
    if(root==NULL)return bigest;
    if(root->ocupado==0){
        if(root->tamanhoBytes>bigest){
            return Bigest(root->proximo,root->tamanhoBytes);
        }else{
            return Bigest(root->proximo,bigest);
        }
    }else{
        return Bigest(root->proximo,bigest);
    }
}
int totalFreeSpace(LElement*root){
    if(root==NULL) return 0;
    if(root->ocupado==0){
        return root->tamanhoBytes+totalFreeSpace(root->proximo);
    }else{
        return totalFreeSpace(root->proximo);
    }
}
void printlista(LElement*raiz){
    if(raiz==NULL) return;
    printf("%d %d %p\n",raiz->tamanhoBytes,raiz->ocupado,raiz->posicaoVetor);
    printlista(raiz->proximo);
    return;
}
int verificaNaLista(LElement*raiz,char*verifica){
    if(raiz==NULL) return 0;
    if((raiz->posicaoVetor==verifica)&&(raiz->ocupado)) return raiz->tamanhoBytes;
    return verificaNaLista(raiz->proximo,verifica);
}