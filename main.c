#include <stdio.h>
#include <stdlib.h>
#include "permuta.h"
//#include "job.h"
#include "bb.h"

void lerEntrada(Job** entrada, int n){
	int i;
	int tempo, deadline, multa;

	for(i=0; i<n; i++){
		scanf("%d %d %d", &tempo, &deadline, &multa);
		entrada[i] = inicializarJob(i, tempo, deadline, multa);
	}
}

Permuta* teste(Job** entrada, int n){
	int i;
	Permuta* teste = inicializaPermuta(n);

	free(teste->posicionados);

	teste->posicionados = entrada;
	teste->qtdePosicionados = n;

	for(i=0; i < n; i++){
		teste->upperbound += entrada[i]->multa;
		teste->tempoDecorrido += entrada[i]->tproc;

		if(teste->tempoDecorrido > entrada[i]->deadline)
			teste->lowerbound += entrada[i]->multa;
	}

	return teste;
}

int main(int argc, char* argv []){
	Permuta* p = NULL;
	Job** entrada = NULL;
	int n;

	n = atoi(argv[2]);

	entrada = (Job**) malloc(n * sizeof(Job*));

	if (n <= 0){
		printf("Numero invalido de elementos!\n");
		exit(1);
	}

	lerEntrada(entrada, n);
	imprimirEntrada(entrada, n);

	p = teste(entrada, n);
	
	p = branchAndBound(entrada, p->lowerbound, n);
	imprimirResposta(p, n);

	return 0;
}