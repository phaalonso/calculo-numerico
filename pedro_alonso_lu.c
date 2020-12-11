#include<stdio.h>
#define LEN 3 

/*
 * Aluno: Pedro Alonso
 * Prontuario: PE3001059
 */

void imprimir_matriz(float matriz[][LEN], int n) {
	int i, j;

	for (i = 0; i < n; i++) {
		printf("\n|");
		for (j = 0; j < n; j++) {
			printf(" %.2f,", matriz[i][j]);
		}
		printf("|");
	}

	printf("\n");
}

float decomposicao_lu(float matriz[][LEN], float b[LEN], int n) {
	float L[LEN][LEN] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

	int i, j, k;

	float m, Xn;

	for(k = 0; k < (n - 1); k++) {
		for(i = k +1; i < n; i++) {
			m = matriz[i][k] / matriz[k][k];
			L[i][k] = m;
			matriz[i][k] = 0;

			for(j = (k + 1); j < n; j++) {
				matriz[i][j] = matriz[i][j] - m * matriz[k][j];
			}
			b[i] = b[i] - m * b[k];
		}
	}

	Xn = b[n -1] / matriz[n -1][n -1];

	printf("Matriz L");
	imprimir_matriz(L, n);

	printf("Matriz U");
	imprimir_matriz(matriz, n);

	return Xn;
}

int main() {
	float matriz[LEN][LEN] = {
		{ 1, 1,  0},
		{ 1, 2, -1},
		{ 0,-1,  3}
	};

	float b[LEN] = { 2, 1, 5 }; 

	printf("Matriz A");
	imprimir_matriz(matriz, 3);

	float m = decomposicao_lu(matriz, b, 3);
	printf("%.2f\n", m);
	
	return 0;
}
