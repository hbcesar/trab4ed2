#include <stdio.h>
#include <stdlib.h>

struct job {
	int id;
	int tproc;
	int deadline;
	int multa;
	struct job* proximo;
}

typedef struct job Job;

Job* inicializarJob(int id, int tproc, int deadline, int multa){
	Job* novo = (Job*)malloc(sizeof(Job));

	novo->id = id;
	novo->tproc = tproc;
	novo->deadline = deadline;
	novo->multa = multa;

	return novo;
}

Job* copiarJob(Job* origem){
	return inicializarJob(origem->id, origem->tproc, origem->deadline, origem->multa);
}

