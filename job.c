#include <stdio.h>
#include <stdlib.h>

struct job {
	int tproc;
	int deadline;
	int multa;
	struct job* proximo;
}

typedef struct job Job;

Job* inicializarJob(int tproc, int deadline, int multa){
	Job* novo = (Job*)malloc(sizeof(Job));

	novo->tproc = tproc;
	novo->deadline = deadline;
	novo->multa = multa;

	return novo;
}