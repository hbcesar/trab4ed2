#include <stdio.h>
#include <stdlib.h>
#include "permuta.h"

Permuta* branchAndBound(Job** entrada, int limite, int n){
	Permuta* lista = gerarRaiz(entrada, n);
	Permuta* item = lista;
	Permuta* melhor = NULL;
	Permuta* filho = NULL;
	int limiteUB = limite;
	int i;

	if(lista == NULL){
		return NULL;
	} else {
		while(lista != NULL){
			//retira o primeiro elemento da lista para gerar seus filhos
			item = lista;
			lista = lista->proximo;
	
			if(!eFolha(item)){
				if(item->lowerbound > limiteUB){
					liberarPermuta(item);
				} else {
			 		//gera os filhos de item e (se for o caso) os insere na lista
					for(i=0; i < item->qtdeNaoPosicionados; i++){
						filho = criarFilho(item, n, i);
						if(filho->lowerbound >= limiteUB){
						 	liberarPermuta(filho);
						} else {
						 	lista = inserir(lista, filho);
						}
					}
			 	}
			} else {
				if(item->lowerbound >= limiteUB){
					liberarPermuta(item);
				} else {
					if(item->upperbound < limiteUB){
						melhor = item;
						limiteUB = item->upperbound;
					}
				}
			}
		}
		liberarPermuta(item);
		return melhor;
	}
}