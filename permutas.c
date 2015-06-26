#include <stdio.h>
#include <stdlib.h>

struct permuta {
	Job* a_pos;
	Job* posicionados;
	float lowerbound;
	float upperbound;
	int tempoDecorrido;
	int qtdePosicionados;
	int qtdeNaoPosicionados;
}

typedef struct permuta Permuta;

Permuta* inicializaPermuta(Job* entrada, int n){
	Permuta* novo = (Permuta*)malloc(sizeof(Permuta));

	novo->a_pos = entrada;
	novo->posicionados = (Job*)malloc(n*sizeof(Job*));
	novo->lowerbound = 0.0;
	novo->upperbound = 0.0;
	novo->tempoDecorrido = 0.0;
	novo->qtdePosicionados = 0;
	novo->qtdeNaoPosicionados = 0;

	return novo;
}

void adicionaPosicionado(Permuta* p, Job* job){
	p->posicionados[p->qtdePosicionados++]= job;

	p->tempoDecorrido += job->tproc;

	if(p->tempoDecorrido > job->deadline){
		p->lowerbound += job->multa;
	}
}

void adicionaNaoPosicionado(Permuta* p, Job* job){
	p->a_pos[p->qtdeNaoPosicionados++] = job;

	p->upperbound += job->multa;

	if(p->tempoDecorrido > job->deadline){
		p->lowerbound += job->multa;
	}


}



