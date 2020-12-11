#include<stdio.h>
#include<stdlib.h>

/* 
 * Sistema linear
 * Sistema => Ax=b
 */
typedef struct sistema {
	float **matriz; // Matriz A
	float *x; // Variaveis do sistema
	float *b; // Constantes do sistema
	int n;
}SISTEMA;

void imprimir_matriz(float **matriz, int n) {
	int i, j;

	printf("Matriz:");
	for (i = 0; i < n; i++) {
		printf("\n|");
		for (j = 0; j < n; j++) {
			printf(" %.2f,", matriz[i][j]);
		}
		printf("|");
	}

	printf("\n");
}

void imprimir_vetor(float *vetor, int n) {
	printf("|");
	for (int i = 0; i < n; i++) {
		printf(" %.2f", vetor[i]);
	}
	printf("|\n");
}

void imprimir_sistema(SISTEMA s) {
	printf("Imprimindo sistema\n");
	int i = 0;

	imprimir_matriz(s.matriz, s.n);

	printf("Imprimindo constantes:\n");
	imprimir_vetor(s.b, s.n);

	printf("Imprimindo variaveis:\n");
	imprimir_vetor(s.x, s.n);
	printf("\n");

}

/*
 * Alocar um vetor de float com tamanho n
 */
float* alocar_vetor(int tam) {
	return (float *) malloc(tam * sizeof(float));
}

/*
 * Alocar matriz de tamanho n e retornar
 */
float** alocar_matriz(int tam) {
	float **matriz = (float **) malloc(tam * sizeof(float *));

	for (int i = 0; i < tam; i++)
		matriz[i] = (float *) malloc(tam * sizeof(float));

	return matriz;
}

SISTEMA iniciar_sistema(int tam) {
	SISTEMA S;
	int i;

	S.n = tam;
	S.matriz = alocar_matriz(tam);
	//S.matriz = (float **) malloc(tam * sizeof(float *));
	//for (i = 0; i < tam; i++)
		//S.matriz[i] = (float *) malloc(tam * sizeof(float));

	// Alocar o vetor das constantes
	S.b = alocar_vetor(tam);

	// Alocar o vetor das variaveis 
	S.x = alocar_vetor(S.n);

	// Zerar o vetor das variaveis
	for (i = 0; i < S.n; i++) {
		S.x[i] = 0;
	}

	return S;
}

/*
 * Le as informações e retorna o sistema
 */
SISTEMA ler_sistema() {
	int k, j, tam;

	printf("Qual o tamanho do sistema?: ");
	scanf("%d", &tam);

	SISTEMA S = iniciar_sistema(tam);

	printf("Preencha a matriz: \n");
	for (k = 0; k < S.n; k++) {
		for (j = 0; j < S.n; j++) {
			scanf("%f", &S.matriz[k][j]);
		}
	}

	printf("Preencha o vetor b com suas constantes:\n");
	for (k = 0; k < S.n; k++) {
		printf("b[%d]: ", k);
		scanf("%f", &S.b[k]);
	}

	return S;
}
