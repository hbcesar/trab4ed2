#include <stdio.h>
#include <stdlib.h>
#include "permuta.h"

Lista* inicializaLista(Job** entrada, int n){
	Lista* lista = alocaLista();
	lista->primeiro = gerarRaiz(entrada, n);
	lista->ultimo = lista->primeiro;

	return lista;
}

Permuta* branchAndBound(Job** entrada, int limite, int n){
	Lista* lista = inicializaLista(entrada, n);
	Permuta* item = NULL;
	Permuta* melhor = NULL;
	Permuta* filho = NULL;
	int limiteUB = limite;
	int i;

	while(lista->primeiro != NULL){
		//retira o primeiro elemento da lista para gerar seus filhos
		item = lista->primeiro;
		lista->primeiro = lista->primeiro->proximo;

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
				liberarPermuta(item);
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

	return melhor;
}