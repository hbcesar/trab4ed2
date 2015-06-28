struct job {
	int id;
	int tproc;
	int deadline;
	int multa;
};

typedef struct job Job;

struct permuta {
	Job** a_pos;
	Job** posicionados;
	int lowerbound;
	int upperbound;
	int tempoDecorrido;
	int qtdePosicionados;
	int qtdeNaoPosicionados;
	struct permuta* proximo;
};

typedef struct permuta Permuta;

Job* inicializarJob(int id, int tproc, int deadline, int multa);
Permuta* inicializaPermuta(int n);
Permuta* gerarRaiz(Job** entrada, int n);
Permuta* criarFilho(Permuta* p, int n, int k);
Permuta* inserir(Permuta* lista, Permuta* p);
int eFolha(Permuta* p);
void imprimirEntrada(Job** entrada, int n);
void imprimirResposta(Permuta* p, int n);
void imprimir(Permuta* p);