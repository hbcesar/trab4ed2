#include <stdio.h>
#include <stdlib.h>
#include "permuta.h"


Permuta* inicializaPermuta(int n){
	Permuta* novo = (Permuta*)malloc(sizeof(Permuta));

	novo->a_pos = (Job**)malloc(n*sizeof(Job*));
	novo->posicionados = (Job**)malloc(n*sizeof(Job*));
	novo->lowerbound = 0;
	novo->upperbound = 0;
	novo->tempoDecorrido = 0;
	novo->qtdePosicionados = 0;
	novo->qtdeNaoPosicionados = 0;
	novo->proximo = NULL;

	return novo;
}

Job* inicializarJob(int id, int tproc, int deadline, int multa){
	Job* novo = (Job*)malloc(sizeof(Job));

	novo->id = id;
	novo->tproc = tproc;
	novo->deadline = deadline;
	novo->multa = multa;

	return novo;
}

Permuta* gerarRaiz(Job** entrada, int n){
	int i;
	Permuta* primeira = inicializaPermuta(n);
	primeira->qtdeNaoPosicionados = n;

	for(i=0; i < n; i++){
		primeira->a_pos[i] = entrada[i];
		primeira->upperbound += entrada[i]->multa;
	}

	free(entrada);

	return primeira;
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

void copiarPermuta(Permuta* origem, Permuta* destino, int k){
	int i, j;

	//copia todos os campos da estrutura
	//nesse caso vemos que upper bound tb copia o lower bound,
	//pois este ainda será incrementado.
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
	//e atualizando os LB e UP.
	for(i=0, j=0; i < origem->qtdeNaoPosicionados; i++, j++){
		if(i == k){
			j--;
		} else {
			destino->a_pos[j] = origem->a_pos[i];
			destino->upperbound += destino->a_pos[j]->multa;
			if(destino->a_pos[j]->deadline < destino->tempoDecorrido){
				destino->lowerbound += destino->a_pos[j]->multa;
			}
		}
	}

}

//recebe a permuta de origem (p), o numero de jobs(n) e o índice do
//job que sairá do vetor de não posicionados e irá para o lindo vetor de posicionados
Permuta* criarFilho(Permuta* p, int n, int k){
	int i;
	Permuta* nova = inicializaPermuta(n);

	copiarPermuta(p, nova, k);

	//copia o menino que vai ser posicionado pro lugarzinho dele
	adicionarPosicionado(nova, p->a_pos[k]);

	return nova;
}

//insere lista de permutas ordenada pelo upper bound
Permuta* inserir(Permuta* lista, Permuta* p){
	Permuta* frente = NULL;
	Permuta* tras = NULL;

	if(lista == NULL){
		lista = p;
	} else {
		frente = lista;

		while((frente != NULL) && (frente->lowerbound < p->lowerbound)){
			tras = frente;
			frente = frente->proximo;
		}

		if(tras == NULL){
			p->proximo = lista;
			lista = p;
		} else if (frente == NULL){
			tras->proximo = p;
		} else {
			tras->proximo = p;
			p->proximo = frente;
		}
	}

	return lista;
}

int eFolha(Permuta* p){
	if(p->qtdeNaoPosicionados == 0){
		return 1;
	} else {
		return 0;
	}
}

void imprimirEntrada(Job** entrada, int n){
	int i;

	for(i=0; i < n; i++){
		printf("%d %d %d\n", entrada[i]->tproc, entrada[i]->deadline, entrada[i]->multa);
	}
}

void imprimirResposta(Permuta* p, int n){
	int i;

	printf("%d:", p->lowerbound);

	for(i=0; i < p->qtdePosicionados; i++){
		printf(" %d", p->posicionados[i]->id);
	}

	printf("\n");
}

void imprimir(Permuta* p){
	int i;

	printf("UB e LB: %d %d\n", p->upperbound, p->lowerbound);
	printf("qtdePosicionados e qtdeNaoPosicionados: %d %d\nPosicionados: ", p->qtdePosicionados, p->qtdeNaoPosicionados);

	for(i=0; i < p->qtdePosicionados; i++){
		printf(" %d", p->posicionados[i]->id);
	}

	printf("\nA posicionar:");

	for(i=0; i < p->qtdeNaoPosicionados; i++){
		printf(" %d", p->a_pos[i]->id);
	}

	printf("\n");
}

void liberarPermuta(Permuta* p){
	if(p!=NULL){
		free(p->a_pos);
		free(p->posicionados);
		free(p);
	}
}

