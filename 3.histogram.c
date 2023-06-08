// Nastase Cristian-Gabriel 315CA
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#define NMAX 100

int verif_comanda_histograma(int *X, int *Y, char *comanda)
{
	// se intampla acelasi lucru ca si in functia
	// 'verif_comanda_select' (linia 295);

	char *numere;
	if (!comanda) {
		printf("Invalid command\n");
		return -1;
	}

	*X = atoi(comanda);

	numere = strtok(NULL, "\n ");

	if (!numere) {
		printf("Invalid command\n");
		return -1;
	}

	*Y = atoi(numere);

	numere = strtok(NULL, "\n ");

	if (numere) {
		printf("Invalid command\n");
		return -1;
	}

	return 1;
}

int HISTOGRAM(struct imagine *v, char *comanda)
{
	int X, Y;
	// trecem comanda prin toate verificarile necesare;
	if (!verificare_existenta_imagine(*v))
		return -1;

	if (verif_comanda_histograma(&X, &Y, comanda) == -1)
		return -1;

	if (v->magic_word == 3 || v->magic_word == 6) {
		printf("Black and white image needed\n");
		return -1;
	}
	int dimensiune_bin = 256 / Y;
	double nr_max_stelute = 0, s = 0, stelute;

	for (int i = 0; i < 256; i++)
		v->v_frecventa[i] = 0;

	// calculam frecventa pixelilor;
	for (int i = 0; i < v->inaltime; i++)
		for (int j = 0; j < v->latime; j++)
			v->v_frecventa[v->a[i][j]]++;

	// mai intai calculam numarul maxim de stelute, deoarece
	// avem nevoie de aceasta valoare pentru formula de calcul
	// a histogramei;
	for (int i = 0; i < 256; i++) {
		s = s + v->v_frecventa[i];
		if ((i + 1) % dimensiune_bin == 0) {
			if (nr_max_stelute < s)
				nr_max_stelute = (int)s;

			s = 0;
		}
	}
	s = 0;
	// folosim formula data in tema;
	for (int i = 0; i < 256; i++) {
		s = s + v->v_frecventa[i];
		if ((i + 1) % dimensiune_bin == 0) {
			stelute = 1.0 * s * X / nr_max_stelute;
			printf("%d\t|\t", (int)stelute);
			for (int j = 0; j < (int)stelute; j++)
				printf("*");

			printf("\n");
			s = 0;
		}
	}
	return 1;
}
