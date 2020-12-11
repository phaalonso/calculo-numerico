#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct intervalo {
	int inicio;
	int fim;
	int subintervalos;
}Intervalo;

// Calcular o valor de f(x)
double f(double x) {
	return log(x + 1);
}

double h(Intervalo in) {
	// Necessita a realização de um casting, devido a in.subintervalos ser um inteiro
	// e o C não tem interferencia de tipos, ou seja ele irá realizar a divisão como se esperasse
	// o resultado em números inteiros.
	return  (in.fim - in.inicio) / (double) in.subintervalos;
}

double simp(Intervalo in) {
	double aux, fx1, fxn, sumPar, sumImpar, passo, x;
	int counter = 0;
	sumPar = 0;
	sumImpar = 0;

	passo = h(in);
	x = in.inicio;

	fx1 = f(x);
	printf("f(%lf) = %lf\n", x, fx1);
	x += passo;
	counter++;

	while (x < (in.fim - passo) && counter < in.subintervalos) {
		aux = f(x);
		if (counter % 2 == 0) {
			sumPar += aux;
		} else {
			sumImpar += aux;
		}
		printf("f(%lf) = %lf\n", x, aux);

		x += passo;
		counter++;
	}

	fxn = f(x);
	printf("f(%lf) = %lf\n", x, fxn);

	return (passo / 3) * (fx1 + 4 * sumImpar + 2 * sumPar + fxn);
}

void imprimir_intervalo(Intervalo in) {
	printf("[%d, %d] n = %d\n", in.inicio, in.fim, in.subintervalos);
}

int main() {
	Intervalo in;
	double res, min_err;

	in.inicio = 0;
	in.fim = 1;
	in.subintervalos = 10;

	imprimir_intervalo(in);

	printf("Resolucao: %f\n", simp(in));

	return 0;
}
