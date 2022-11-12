#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

// estruturas
typedef struct nodo {
	int conteudo;
	struct nodo * filhoEsq;
	struct nodo * filhoDir;
} Nodo;
typedef int BOOLEAN; //para retorno das funções

//protótipos
void opcao1(void);
void opcao2(void);
BOOLEAN inserirNodo(Nodo ** nodoAtual, int valor);
BOOLEAN removerNodo(Nodo ** nodoAtual, int valor);
Nodo * procuraMaior(Nodo * nodoAtual);
Nodo * pesquisarNodo(Nodo * nodoAtual, int valor);
BOOLEAN balancear(Nodo ** nodoRaiz);
int calcularFatorBalanc(Nodo * nodoRaiz);
int alturaArvore(Nodo * nodoAtual);
BOOLEAN balancearEsq(Nodo ** nodoRaiz);
BOOLEAN balancearDir(Nodo ** nodoRaiz);
void rotarEsq(Nodo ** raizAtual);
void rotarDir(Nodo ** raizAtual);
void imprimirArvore(Nodo * nodoAtual, int nivel);
BOOLEAN verificaArvoreAVL(Nodo * raizAtual);
void liberarNodo(Nodo * nodoAtual);

int main() {
	opcao1();	
}
void opcao1() {
	
	Nodo *raiz = NULL;
	int nos;
	printf("Quantos nodos voce deseja criar?\n ");
	scanf("%d", &nos);

	//srand(time(0));
	//printf("Nodos gerados: ");
  int valor;
	for (int i = 0; i < nos; i++) {
    printf("Valor do %do Nodo: ",i+1);
    scanf("%d", &valor);        
		
		BOOLEAN lixo = inserirNodo(&raiz, valor); 	//inserindo nodo na árvore
		//printf("%d ", valor);
	}
	printf("\nPressione ENTER para continuar...\n");
	getchar();

	printf("# IMPRIMINDO ARVORE #\n");
	imprimirArvore(raiz, 0);	

	
  
	getchar();

	liberarNodo(raiz);
}
void rotarDir(Nodo **raizAtual) {
	Nodo *novaRaiz;
	novaRaiz = (*raizAtual)->filhoEsq;					 //novaRaiz - filho a esquerda
	(*raizAtual)->filhoEsq = novaRaiz->filhoDir; //filho da direita da raiz = null
	novaRaiz->filhoDir = (*raizAtual);					 //filho direito de novaRaiz = raiz
	*raizAtual = novaRaiz;											 //o endereço da raiz = novaRaiz
}
void rotarEsq(Nodo **raizAtual) {
	Nodo *novaRaiz;
	novaRaiz = (*raizAtual)->filhoDir;					 //novaRaiz = filho a direita
	(*raizAtual)->filhoDir = novaRaiz->filhoEsq; //filho da direita da raiz = NULL
	novaRaiz->filhoEsq = (*raizAtual);					 //filho esquerdo de novaRaiz = raiz
	*raizAtual = novaRaiz;											 //o endereço da raiz = novaRaiz
}

BOOLEAN inserirNodo(Nodo **nodoAtual, int valor) {
	if (*nodoAtual == NULL) {
		*nodoAtual = (Nodo *)malloc(sizeof(Nodo)); //criando nodo
		(*nodoAtual)->filhoEsq = NULL;
		(*nodoAtual)->filhoDir = NULL;
		(*nodoAtual)->conteudo = valor;
		return TRUE;
	}

	else if (valor < (*nodoAtual)->conteudo) { 						//permite valores repetidos
		if (inserirNodo(&(*nodoAtual)->filhoEsq, valor)) {  //if inserirNodo == TRUE{
			if (balancear(nodoAtual)) 												//if Balanceamento == TRUE
				return FALSE;
			else
				return TRUE;
		}
	}
	else if (valor >= (*nodoAtual)->conteudo) {
		if (inserirNodo(&(*nodoAtual)->filhoDir, valor)) {
			if (balancear(nodoAtual)) 
				return FALSE;
			else 
				return TRUE;
		}
		else 
			return FALSE;
	}
}
Nodo *procuraMaior(Nodo *nodoAtual) {
	Nodo *nodoRetorno = nodoAtual;
	Nodo *nodoDir = nodoAtual->filhoDir;
	while (nodoDir != NULL) {
		nodoRetorno = nodoDir;
		nodoDir = nodoDir->filhoDir;
	}
	return nodoRetorno;
}

Nodo *pesquisarNodo(Nodo *nodoAtual, int valor) {
	while (nodoAtual != NULL && valor != nodoAtual->conteudo) {
		if (valor > nodoAtual->conteudo)
			nodoAtual = nodoAtual->filhoDir;
		else if (valor < nodoAtual->conteudo)
			nodoAtual = nodoAtual->filhoEsq;
	}
	return nodoAtual;
}

BOOLEAN balancear(Nodo **nodoAtual) {
	int fatorBalanc = calcularFatorBalanc(*nodoAtual);
	if (fatorBalanc > 1)
		return balancearEsq(nodoAtual);
	else if (fatorBalanc < -1)
		return balancearDir(nodoAtual);
	else
		return FALSE;
}

int calcularFatorBalanc(Nodo *nodoRaiz) {
	if (nodoRaiz == NULL) 
		return 0;

	int altEsq = alturaArvore(nodoRaiz->filhoEsq);
	int altDir = alturaArvore(nodoRaiz->filhoDir);
	return altEsq - altDir;
}

int alturaArvore(Nodo *nodoAtual) {
	if (!nodoAtual) 
		return 0;

	int alturaEsq = alturaArvore(nodoAtual->filhoEsq);
	int alturaDir = alturaArvore(nodoAtual->filhoDir);
	if (alturaEsq > alturaDir)
		return alturaEsq + 1;
	else
		return alturaDir + 1;
}

BOOLEAN balancearEsq(Nodo **nodoRaiz) {
	int fbEsq = calcularFatorBalanc((*nodoRaiz)->filhoEsq);
	if (fbEsq > 0)
	{ //rotação simples
		rotarDir(nodoRaiz);
		return TRUE;
	}
	else if (fbEsq < 0)
	{ //rotação dupla direita
		rotarEsq(&((*nodoRaiz)->filhoEsq));
		rotarDir(nodoRaiz);
		return TRUE;
	}
	return FALSE;
}

BOOLEAN balancearDir(Nodo **nodoRaiz) {
	int fbDir = calcularFatorBalanc((*nodoRaiz)->filhoDir);
	if (fbDir < 0) { //rotação simples
		rotarEsq(nodoRaiz);
		return TRUE;
	}
	else if (fbDir > 0) { //rotação dupla esquerda
		rotarDir(&((*nodoRaiz)->filhoDir));
		rotarEsq(nodoRaiz);
		return TRUE;
	}
	return FALSE;
}
void imprimirArvore(Nodo *nodoAtual, int nivel) {
	if (nodoAtual == NULL)
		return;

	for (int i = 0; i < nivel; i++) //imprimindo nivel da arvore; 2 espaços a mais por nivel
		printf("  ");
	printf("%d\n", nodoAtual->conteudo); //imprimindo conteudo do nodo

	imprimirArvore(nodoAtual->filhoEsq, nivel + 1);
	imprimirArvore(nodoAtual->filhoDir, nivel + 1);
}
void liberarNodo(Nodo *nodoAtual) {
	if (nodoAtual == NULL)
		return;

	liberarNodo(nodoAtual->filhoDir);
	liberarNodo(nodoAtual->filhoEsq);
	free(nodoAtual);
}
