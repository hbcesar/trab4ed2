struct job {
	int id;
	int tproc;
	int deadline;
	int multa;
};

typedef struct job Job;

Job* inicializarJob(int id, int tproc, int deadline, int multa);
