struct permuta {
	Job* a_pos;
	Job* posicionados;
	float lowerbound;
	float upperbound;
	int tempoDecorrido;
	int qtdePosicionados;
	int qtdeNaoPosicionados;
	struct permuta* proximo;
};

typedef struct permuta Permuta;

void adicionarPosicionado(Permuta* p, Job* job);
void copiarPermuta(Permuta* origem, Permuta* destino, int k);
Permuta* criarFilho(Permuta* p, int n, int k);
Permuta* inserir(Permuta* lista, Permuta* p);
float obterCusto(Permuta* p);
int eFolha(Permuta* p);
