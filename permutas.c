#include <stdio.h>
#include <stdlib.h>
#include "permuta.h"

Permuta* inicializaPermuta(int n){
	Permuta* novo = (Permuta*)malloc(sizeof(Permuta));

	novo->a_pos = (Job*)malloc(n*sizeof(Job*));
	novo->posicionados = (Job*)malloc(n*sizeof(Job*));
	novo->lowerbound = 0.0;
	novo->upperbound = 0.0;
	novo->tempoDecorrido = 0.0;
	novo->qtdePosicionados = 0;
	novo->qtdeNaoPosicionados = 0;
	novo->proximo = NULL;

	return novo;
}

void adicionarPosicionado(Permuta* p, Job* job){
	p->posicionados[p->qtdePosicionados++]= job;
	p->qtdeNaoPosicionados--;

	p->tempoDecorrido += job->tproc;

	if(p->tempoDecorrido > job->deadline){
		p->lowerbound += job->multa;
		p->upperbound += job->multa;
	}
}

// void adicionaNaoPosicionado(Permuta* p, Job* job){
// 	p->a_pos[p->qtdeNaoPosicionados++] = job;

// 	p->upperbound += job->multa;

// 	// if(p->tempoDecorrido + job->tproc > job->deadline){
// 	// 	p->lowerbound += job->multa;
// 	// }
// }

void copiarPermuta(Permuta* origem, Permuta* destino, int k){
	int i, j;

	//copia todos os campos da estrutura
	destino->lowerbound = origem->lowerbound;
	destino->upperbound = origem->lowerbound;
	destino->tempoDecorrido = origem->tempoDecorrido;
	destino->qtdePosicionados = origem->qtdePosicionados;
	destino->qtdeNaoPosicionados = origem->qtdeNaoPosicionados;

	//copia o vetor de jobs posicionados
	for(i = 0; i < origem->qtdePosicionados; i++){
		destino->posicionados[i] = origem->posicionados[i];
	}

	//copia o vetor de não posicionados, pulando o infeliz que vai ser posicionado
	for(i=0, j=0; i < origem->qtdeNaoPosicionados; i++, j++){
		if(i == k){
			j--;
		} else {
			destino->a_pos[j] = origem->a_pos[i];
			destino->upperbound += destino->a_pos[j]->multa;
			if(destino->a_pos[j]->deadline < destino->tempoDecorrido){
				destino->lowerbound = destino->a_pos[j]->multa;
			}
		}
	}

}

//recebe a permuta de origem (p), o numero de jobs(n) e o índice do
//job que saíram do vetor de não posicionados e irá para o lindo vetor de posicionados
Permuta* criarFilho(Permuta* p, int n, int k){
	int i;
	Permuta* nova = inicializaPermuta(n);

	copiarPermuta(p, nova, k)

	//copia o menino que vai ser posicionado pro lugarzinho dele
	adicionarPosicionado(nova, p->a_pos[k]);

	calcularBounds(nova);

	return nova;
}

//insere lista de permutas ordenada pelo upper bound
Permuta* inserir(Permuta* lista, Permuta* p){
	Permuta* frente, tras;

	if(lista == NULL){
		lista = p;
	} else {
		frente = lista;

		while((frente->lowerbound < p->lowerbound) && (frente != NULL)){
			tras = frente;
			frente = frente->proximo;
		}

		if(tras == NULL){
			p->proximo = lista;
		} else if (frente == NULL){
			tras->proximo = p;
		} else {
			tras->proximo = p;
			p->proximo = frente;
		}
	}
}

float obterCusto(Permuta* p){
	if(p->qtdeNaoPosicionados != 0){
		printf("Não é possivel obter custo final, não é folha.\n");
		exit(1);
	}

	return p->lowerbound;
}

int eFolha(Permuta* p){
	if(p->qtdeNaoPosicionados == 0){
		return 1;
	} else {
		return 0;
	}
}

