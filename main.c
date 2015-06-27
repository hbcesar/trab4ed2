#include <stdio.h>
#include <stdlib.h>

void lerEntrada(Job* entrada, int n){
	int i;
	int tempo, deadline, multa;

	for(i=0; i<n; i++){
		scanf("%d %d %d", &tempo, &deadline, &multa);
		entrada[i]=inicializarJob(i, tempo, deadline, multa);
	}
}

Permuta* geraPrimeira(Job* entrada, int n){
	int i;
	Permuta* primeira = inicializaPermuta(n);

	for(i=0; i < n; i++){
		novo->a_pos[i] = entrada[i];
		novo->upperbound += entrada[i]->multa;
	}

	free(entrada);

	return primeira;
}

Permuta* teste(Job* entrada, int n){
	int i;
	Permuta* teste = inicializaPermuta(n);

	free(teste->posicionados);

	teste->posicionados = entrada;

	for(i=0; i < n; i++){
		teste->upperbound = entrada[i]->multa;
		teste->tempoDecorrido += entrada[i]->tproc;

		if(teste->tempoDecorrido > entrada[i]->tproc)
			teste->lowerbound = entrada[i]->multa;
	}
}

int main(int argc, char* argv []){
	Permuta* p = NULL;
	Job* entrada = NULL;
	int n;

	n = atoi(argv[2]);

	entrada = (Job*) malloc(n * sizeof(Job));

	if (n <= 0){
		printf("Numero invalido de elementos!\n");
		exit(1);
	}

	lerEntrada(entrada, n);
	p = teste(entrada, n);
}