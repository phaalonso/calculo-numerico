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

double f2linha(double x) {
	return - 1 / pow((x + 1), 2);
}

double h(Intervalo in) {
	// Necessita a realização de um casting, devido a in.subintervalos ser um inteiro
	// e o C não tem interferencia de tipos, ou seja ele irá realizar a divisão como se esperasse
	// o resultado em números inteiros.
	return  (in.fim - in.inicio) / (double) in.subintervalos;
}

/*
 * ln ≅ h/2 * (f(x₀) + 2f(x₁) + 2f(x₃) + ... + 2f(xn-1) + f(xn)) 
 */
double trapezio_repetido(Intervalo in) {
	double sum = 0;
	double xn, fx0, fx, tamanho_passo ;

	xn = in.inicio;
	tamanho_passo = h(in);

	// Calcular f0
	fx0 = f(xn);
	printf("f(%.2f) = %f \n", xn, fx);
	xn += tamanho_passo;

	// Percorra realizando o somatório das equações
	while (xn < (in.fim - tamanho_passo)) {
		fx = f(xn);
		sum += fx;
		printf("f(%.2f) = %f \n", xn, fx);
		xn += tamanho_passo;
	}

	// Ultimo numero, não é multiplicado por 2
	fx = f(xn);
	printf("f(%.2f) = %f \n", xn, fx);

	return (tamanho_passo / 2 ) * (fx0 + (2 * sum) + fx);
}

double maximo(Intervalo in) {
	double passo = h(in);
	double x, maior, aux;

	x = in.inicio;
	maior = fabs(f2linha(x));
	x += passo;

	while (x < in.fim) {
		aux = fabs(f2linha(x));
		if (aux > maior) 
			maior = aux;
		x += passo;
	}
	
	printf("M: %f\n", maior);
	return maior;
}

// Erro causado pelo calculo utilizando o trapezio_repetido, com a quantidade de intervalos presente na
// struct Intervalo
double trapezio_repetido_erro(Intervalo in) {
	return ((in.fim - in.inicio) / (double) 12) * pow(h(in), 2) * maximo(in);
}

// Quantidade minima de subintervalos para o erro ficar superior a min_err
double trapezio_repetido_min_sub(Intervalo in, double min_err) {
	return pow((in.fim - in.inicio), 2) * maximo(in) / sqrt(12 * min_err); 
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

	printf("Resolucao: %f\n", trapezio_repetido(in));

	printf("Erro: %f\n", trapezio_repetido_erro(in));

	min_err = 0.0001;
	printf("Quantidade minima de subintervalos: %f para que o erro fique inferior a %f\n", trapezio_repetido_min_sub(in, min_err), min_err);

	return 0;
}
