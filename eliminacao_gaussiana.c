#include<stdio.h>
#define LEN 10

// Sistema linear
// Sistema => Ax=b
typedef struct sistema {
	float matriz[LEN][LEN]; // Matriz A
	float x[LEN]; // Variaveis do sistema
	float b[LEN]; // Constantes do sistema
	int n;
}SISTEMA;

void imprimir_matriz(float matriz[LEN][LEN], int n) {
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

void imprimir_vetor(float vetor[LEN], int n) {
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
 * Recebe um sistema e transforma sua matriz em uma matriz triangular superior
 */
void transformar_matriz_triangular_superior(SISTEMA *S) {
	int i, k, j;
	float m = 0;
	
	for (k = 0; k < S->n -1; k++) { // Linha/coluna do pivo
		for (i = k +1; i < S->n; i++) { // Linha sendo eliminada
			// Dividir a linha a ser eleminada pelo pivo
			m = S->matriz[i][k] / S->matriz[k][k];
			S->matriz[i][k] = 0; // Zera elemento abaixo do pivo

			// Faz o calculo pro resto dos termos da linha
			for (j = k +1; j < S->n; j++) {
				// Para cada elemento da linha a ser eleminada subtraia pelos elementos
				// da linha que está sendo utilizada para a eliminação vs o multiplicador
				S->matriz[i][j] = S->matriz[i][j] - (m * S->matriz[k][j]);
			}
			
			// Necessário realizar a mesma operação para o elemento b
			S->b[i] = S->b[i] - (m * S->b[k]);
		}
	}
}

/*
 * Recebe o ponteiro para um SISTEMA, calcula em matriz triangular e por fim
 * realiza a  eliminação gaussiana
 */
void elimnacao_gaussiana(SISTEMA *S) {
	transformar_matriz_triangular_superior(S);	

	// Calcular primeiro Xn
	// Esta sendo sobrescrito pela matriz
	S->x[S->n -1] = S->b[S->n -1] / S->matriz[S->n -1][S->n -1];

	int k, j;
	float s;

	for (k = S->n -1; k >= 0; k--) {
		s = 0;
		for (j = k +1; j < S->n; j++) {
			s = s + S->matriz[k][j] * S->x[j];
		}
		S->x[k] = (S->b[k] - s) / S->matriz[k][k];
	} 
}

/*
 * Le as informações e armazenar em uma estrutura
 */
SISTEMA lerSistema() {
	SISTEMA S;
	int k, j;

	printf("Qual o tamanho do sistema?: ");
	scanf("%d", &S.n);

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

	for (k = 0; k < S.n; k++) {
		S.x[k] = 0;
	}

	return S;
}

int main() {
	SISTEMA sistema;

	/*printf("Por enquanto so suporta sistemas quadraticos!\n");*/
	sistema = lerSistema();
	imprimir_sistema(sistema);
	
	printf("Calculando eliminacao gaussiana\n");
	elimnacao_gaussiana(&sistema);

	imprimir_sistema(sistema);

	return 0;
}
