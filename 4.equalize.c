// Nastase Cristian-Gabriel 315CA
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#define NMAX 100

int EQUALIZE(struct imagine *v)
{
	if (!verificare_existenta_imagine(*v))
		return 0;

	if (v->magic_word == 3 || v->magic_word == 6) {
		printf("Black and white image needed\n");
		return -1;
	}
	for (int i = 0; i < 256; i++)
		v->v_frecventa[i] = 0;

	double pixel, suprafata = v->inaltime * v->latime;
	for (int i = 0; i < v->inaltime; i++)
		for (int j = 0; j < v->latime; j++)
			v->v_frecventa[v->a[i][j]]++;

	for (int i = 0; i < v->inaltime; i++) {
		for (int j = 0; j < v->latime; j++) {
			int suma = 0;

		for (int k = 0; k <= v->a[i][j]; k++)
			suma += v->v_frecventa[k];

		pixel = 255 * suma / suprafata;
		limitare_rezultate(&pixel);
		v->a[i][j] = pixel;
		}
	}
	printf("Equalize done\n");

	return 1;
}
