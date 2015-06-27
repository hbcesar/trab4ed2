#include <stdio.h>
#include <stdlib.h>
#include "permuta.h"
#include "job.h"
#include "bb.h"

Permuta* branchAndBound(Permuta* lista, int n){
	int limiteUB = lista->upperbound;
	Permuta* melhor = NULL;
	Permuta* item = lista;
	Permuta* filho = NULL;
	int i;

	if(lista == NULL){
		return NULL;
	} else {
		while(lista != NULL){
			//retira o primeiro elemento da lista para gerar seus filhos
			item = lista;
			lista = lista->proximo;
	
			if(!eFolha(lista)){
				if(item->lowerbound >= limiteUB){
					free(item);
				} else {
					//gera os filhos de item e (se for o caso) os insere na lista
					for(i=0; i < item->qtdeNaoPosicionados; i++){
						filho = criarFilho(item, n, i);

						if(filho->lowerbound >= limiteUB){
							free(filho);
						} else {
							lista = inserir(lista, filho);
							//limiteUB = filho->lowerbound;
						}
					}
				}
			} else {
				if(item->lowerbound >= limiteUB){
					free(item);
				} else {
					if(item->upperbound < limiteUB){
						limiteUB = item->upperbound;
					}
				}
			}
		}
		return item;
	}
}