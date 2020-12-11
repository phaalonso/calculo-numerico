#include <stdio.h>
#include <math.h>

//Consegui arrumar o anterior mas agora esse nao ta funfando kk

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

float err_abs(float *a, float *b, int n) {
	int i;
	float diff, sum = 0;

	for (i = 0; i < n; i++){
		diff = fabs(a[i] - b[i]);

		if (diff > sum)
			sum = diff;
	}

	return sum;
}

float err_relativo(float *a, float *b, int n) {
	int i;
	float err_a, diff, sum = 0;

	// Dessa forma ele economiza uma iteração
	err_a = fabs(a[0]);
	i = n;
	while (i > 0) {
		if (fabsf(a[i]) > err_a) {
			err_a = fabs(a[i]);
		}
		/*i--;*/
	}

	for (i = 0; i < n; i++){
		diff = fabs(a[i]) - fabs(b[i]); // Utilizando fabs para pegar o valor absoluto de um numero float
		// Guardando a maior diferença
		if (diff > sum)
			sum = diff;
	}

	return sum / err_a;
}

void gauss_seidel(SISTEMA *s, float *x, float tol) {
	int i, j;
	float sum;
	float y[s->n];

	do {
		for (j = 0; j < s->n; j++) 
			y[j] = x[j];

		for (i = 0; i < s->n; i++) {
			sum = 0;
			for (j = 0; j < i; j++) {
				sum += s->matriz[i][j] * y[j];
			}
			for (j = i +1; j < s->n; j++) {
				sum += s->matriz[i][j] * y[j];
			}
			//x[i] = (s->b[i] - sum) / s->matriz[i][i];
			x[i] = s->b[i] - sum;
		}

		imprimir_vetor(x, s->n);
	} while (err_abs(x, y, s->n) > tol);  // ||x - y || > ε 
}

void lerVetor(float *x, int tam) {

	printf("Insira os dados de x:");
	for (int i = 0; i < tam; i++) {
		scanf("%f", &x[i]);
	}
}

void dividir_termo_diagonal(SISTEMA *s) {
	int j, k;
	float pivo = 0;

	for (j = 0; j < s->n; j++) {
		pivo = s->matriz[j][j];
		for (k = 0; k < s->n; k++) {
			s->matriz[j][k] /= pivo;
		}

		s->b[j] /= pivo;
	}
}

int main() {
	SISTEMA s;

	// Le o sistema
	s = ler_sistema();
	float x[s.n];

	// Le o vetor x
	lerVetor(x, s.n);

	dividir_termo_diagonal(&s);
	// imprimir_sistema(s);
	
	gauss_seidel(&s, x, 0.001);

	// imprimir_sistema(s);

	printf("Imprimindo elementos de x");
	imprimir_vetor(x, s.n);

}
