#include <stdio.h>
#include <stdlib.h>

struct permuta {
	Job* a_pos;
	Job* posicionados;
	float lowerbound;
	float upperbound;
}

typedef struct permuta Permuta;

Permuta* inicializaPermuta(int n){
	Permuta* novo = (Permuta*)malloc(sizeof(Permuta));

	novo->a_pos = NULL;
	novo->posicionados = NULL;
	novo->lowerbound = 0.0;
	novo->upperbound = 0.0;

	return novo;
}

Permuta* setaLowerBound(Permuta* p){

}

Permuta* setaUpperBound(Permuta* p){
	
}