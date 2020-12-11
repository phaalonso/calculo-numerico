#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*
 * Calcule o erro absoluto -> EA = |x[k] - x[k-1]|
 */
float err_abs(float x1, float x2) {
	return fabsf(x1 - x2);
}

/*
 * Calcule o erro relativo -> ER = EA / |x[k]|
 */
float err_rel(float x1, float x2) {
	return err_abs(x1, x2) / fabsf(x1);
}

/*
 * Formula a ser calculada
 */
float f(float x) {
	//return powf(x, 3) - 4 * powf(x, 2) - 10;
	return cosf(x) - x;
}

float fgeral(float x) {
	//return sqrtf(10 / (4 + x));
	return cosf(x);
}

float ponto_fixo(float inicial, float e, int maxInteracao) {
	int k = 1;
	float x[maxInteracao];
	x[0] = inicial;

	printf("k = %d \t|%f\n", 0, x[0]);
	while (k <= maxInteracao) {
		x[k] = fgeral(x[k-1]);
		printf("k = %d \t|%f\n", k, x[k]);

		// Se |xk - xk-1| < e ou |xk-xk-1|/|xk| < e ou |f(xk)| < e
		if (err_abs(x[k], x[k-1]) < e || err_rel(x[k], x[k-1]) < e || fabsf(f(x[k])) < e) 
			return x[k];
		k++;
	}

	printf("O metodo nao obteve uma solucao em %d iteracoes", maxInteracao);
	exit(1);

}

int main() {
	int maxInteracao;
	float e, a, b, c, inicial;

	// intervalo [a, b]
	a = 0;

	// Descobri agora que C tem definicoes para Pi, euler, ln, etc...na biblioteca math.h
	b = M_PI / 3;

	// Número maximo de iterações
	maxInteracao = 100;

	e = 0.005;

	inicial = M_PI / 4;

	if (f(a) * f(b) < 0) {
		c = ponto_fixo(inicial, e, maxInteracao);
		printf("x= %f\n", c);
	} else {
		printf("Nao foi encontrada\n");
	}

	return 0;
}
