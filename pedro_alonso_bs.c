#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define E 2.7182818284590452353602874

/*
 * Formula a ser calculada
 */
float f(float x) {
	float res = powf(E, x) + x;
	//printf("res: %f\n", res);
	return res;
}

float bissecacao(float a, float b, float e, int maxInteracao) {
	int k = 1;
	float c;

	while (k <= maxInteracao) {
		c = (a + b) / 2;
		printf("%d A: %f B: %f C: %f\n", k, a, b, c);

		if (((b - a) / 2 < e) || (fabsf(f(c)) < e)) 
			return c;
		if (f(a) * f(c) < 0) {
			b = c;
		} else {
			a = c;
		}
		k++;
	}
	printf("O metodo nao obteve uma solucao em %d iteracoes", maxInteracao);
	exit(1);

}

int main() {
	int maxInteracao;
	float e, a, b, c;

	a = -1;
	b = 0;
	maxInteracao = 100;
	e = 0.001;

	if (f(a) * f(b) < 0) {
		c = bissecacao(a, b, e, maxInteracao);
		printf("x= %f\n", c);
		printf("f(x)= %f\n", f(c));
	} else {
		printf("Nao foi encontrada uma raiz");
	}


	return 0;
}
