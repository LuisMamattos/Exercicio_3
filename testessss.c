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
Nodo * pesquisarNodo(Nodo * nodoAtual, int valor);
void rotarEsq(Nodo ** raizAtual);
void rotarDir(Nodo * raizAtual);
void imprimirArvore(Nodo * nodoAtual, int nivel);
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

	//pesquisa
	//int valor;
	printf("\nInsira valor que deseja rotacionar a esquerda: ");
	scanf("%d", &valor);
	Nodo *nodoBusca = pesquisarNodo(raiz, valor);
	if (nodoBusca == NULL){
		printf("Valor nao esta presente nesta arvore.\n");
  }
	else{    
		printf("Valor presente na arvore: %d\n", nodoBusca->conteudo);
    rotarEsq(&nodoBusca);
  }

  printf("# IMPRIMINDO ARVORE #\n");
	imprimirArvore(raiz, 0);
  
	getchar();

	liberarNodo(raiz);
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
		return (inserirNodo(&(*nodoAtual)->filhoEsq, valor));		
	}
	else if (valor >= (*nodoAtual)->conteudo) {		
		return (inserirNodo(&(*nodoAtual)->filhoDir, valor));		
	}
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
