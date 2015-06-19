#include <stdio.h>
#include <stdlib.h>

void lerEntrada(Job* entrada, int n){
	int i;
	int tempo, deadline, multa;

	for(i=0; i<n; i++){
		scanf("%d %d %d", &tempo, &deadline, &multa);
		entrada[i]=inicializarJob(tempo, deadline, multa);
	}
}

int main(int argc, char* argv []){
	Job* entrada = NULL;
	int n;

	n = atoi(argv[2]);

	entrada = (Job*) malloc(n * sizeof(Job));

	if (n <= 0){
		printf("Numero invalido de elementos!\n");
		exit(1);
	}

	lerEntrada(entrada, n);
}