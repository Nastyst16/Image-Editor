// Nastase Cristian-Gabriel 315CA
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#define NMAX 100

int apply_edge(struct imagine *v, unsigned char **r_aux,
			   unsigned char **g_aux, unsigned char **b_aux, int i, int j)
{
	// aplicam formula pentru EDGE
	double suma = 0;
	suma = r_aux[i - 1][j - 1] * (-1) + r_aux[i - 1][j] * (-1) +
			r_aux[i - 1][j + 1] * (-1) + r_aux[i][j - 1] * (-1) +
			r_aux[i][j] * (8) + r_aux[i][j + 1] * (-1) +
			r_aux[i + 1][j - 1] * (-1) + r_aux[i + 1][j] * (-1) +
			r_aux[i + 1][j + 1] * (-1);
	limitare_rezultate(&suma);
	v->r[i][j] = round(suma);
	suma = g_aux[i - 1][j - 1] * (-1) + g_aux[i - 1][j] * (-1) +
			g_aux[i - 1][j + 1] * (-1) + g_aux[i][j - 1] * (-1) +
			g_aux[i][j] * (8) + g_aux[i][j + 1] * (-1) +
			g_aux[i + 1][j - 1] * (-1) + g_aux[i + 1][j] * (-1) +
			g_aux[i + 1][j + 1] * (-1);
	limitare_rezultate(&suma);
	v->g[i][j] = round(suma);
	suma = b_aux[i - 1][j - 1] * (-1) + b_aux[i - 1][j] * (-1) +
			b_aux[i - 1][j + 1] * (-1) + b_aux[i][j - 1] * (-1) +
			b_aux[i][j] * (8) + b_aux[i][j + 1] * (-1) +
			b_aux[i + 1][j - 1] * (-1) + b_aux[i + 1][j] * (-1) +
			b_aux[i + 1][j + 1] * (-1);
	limitare_rezultate(&suma);
	v->b[i][j] = round(suma);

	return 1;
}

int apply_sharpen(struct imagine *v, unsigned char **r_aux,
				  unsigned char **g_aux, unsigned char **b_aux, int i, int j)
{
	// aplicam formula pentru SHARPEN
	double suma = 0;
	suma = r_aux[i - 1][j - 1] * (0) + r_aux[i - 1][j] * (-1) +
			r_aux[i - 1][j + 1] * (0) + r_aux[i][j - 1] * (-1) +
			r_aux[i][j] * (5) + r_aux[i][j + 1] * (-1) +
			r_aux[i + 1][j - 1] * (0) + r_aux[i + 1][j] * (-1) +
			r_aux[i + 1][j + 1] * (0);
	limitare_rezultate(&suma);
	v->r[i][j] = round(suma);
	suma = g_aux[i - 1][j - 1] * (0) + g_aux[i - 1][j] * (-1) +
			g_aux[i - 1][j + 1] * (0) + g_aux[i][j - 1] * (-1) +
			g_aux[i][j] * (5) + g_aux[i][j + 1] * (-1) +
			g_aux[i + 1][j - 1] * (0) + g_aux[i + 1][j] * (-1) +
			g_aux[i + 1][j + 1] * (0);
	limitare_rezultate(&suma);
	v->g[i][j] = round(suma);
	suma = b_aux[i - 1][j - 1] * (0) + b_aux[i - 1][j] * (-1) +
			b_aux[i - 1][j + 1] * (0) + b_aux[i][j - 1] * (-1) +
			b_aux[i][j] * (5) + b_aux[i][j + 1] * (-1) +
			b_aux[i + 1][j - 1] * (0) + b_aux[i + 1][j] * (-1) +
			b_aux[i + 1][j + 1] * (0);
	limitare_rezultate(&suma);
	v->b[i][j] = round(suma);

	return 1;
}

int apply_blur(struct imagine *v, unsigned char **r_aux, unsigned char **g_aux,
			   unsigned char **b_aux, int i, int j)
{
	// aplicam formula pentru BLUR
	double suma = 0;
	suma = r_aux[i - 1][j - 1] * (1) + r_aux[i - 1][j] * (1) +
			r_aux[i - 1][j + 1] * (1) + r_aux[i][j - 1] * (1) +
			r_aux[i][j] * (1) + r_aux[i][j + 1] * (1) +
			r_aux[i + 1][j - 1] * (1) + r_aux[i + 1][j] * (1) +
			r_aux[i + 1][j + 1] * (1);
	suma = suma / 9;
	v->r[i][j] = round(suma);
	suma = g_aux[i - 1][j - 1] * (1) + g_aux[i - 1][j] * (1) +
			g_aux[i - 1][j + 1] * (1) + g_aux[i][j - 1] * (1) +
			g_aux[i][j] * (1) + g_aux[i][j + 1] * (1) +
			g_aux[i + 1][j - 1] * (1) + g_aux[i + 1][j] * (1) +
			g_aux[i + 1][j + 1] * (1);
	suma = suma / 9;
	v->g[i][j] = round(suma);
	suma = b_aux[i - 1][j - 1] * (1) + b_aux[i - 1][j] * (1) +
			b_aux[i - 1][j + 1] * (1) + b_aux[i][j - 1] * (1) +
			b_aux[i][j] * (1) + b_aux[i][j + 1] * (1) +
			b_aux[i + 1][j - 1] * (1) + b_aux[i + 1][j] * (1) +
			b_aux[i + 1][j + 1] * (1);
	suma = suma / 9;
	v->b[i][j] = round(suma);

	return 1;
}

int apply_gaussian_blur(struct imagine *v, unsigned char **r_aux,
						unsigned char **g_aux, unsigned char **b_aux,
						int i, int j)
{
	// aplicam formula pentru GAUSSIAN_BLUR
		double suma = 0;
	suma = r_aux[i - 1][j - 1] * (1) + r_aux[i - 1][j] * (2) +
			r_aux[i - 1][j + 1] * (1) + r_aux[i][j - 1] * (2) +
			r_aux[i][j] * 4 + r_aux[i][j + 1] * (2) +
			r_aux[i + 1][j - 1] * (1) + r_aux[i + 1][j] * (2) +
			r_aux[i + 1][j + 1] * (1);
	suma = suma / 16;
	v->r[i][j] = round(suma);
	suma = g_aux[i - 1][j - 1] * (1) + g_aux[i - 1][j] * (2) +
			g_aux[i - 1][j + 1] * (1) + g_aux[i][j - 1] * (2) +
			g_aux[i][j] * 4 + g_aux[i][j + 1] * (2) +
			g_aux[i + 1][j - 1] * (1) + g_aux[i + 1][j] * (2) +
			g_aux[i + 1][j + 1] * (1);
	suma = suma / 16;
	v->g[i][j] = round(suma);
	suma = b_aux[i - 1][j - 1] * (1) + b_aux[i - 1][j] * (2) +
			b_aux[i - 1][j + 1] * (1) + b_aux[i][j - 1] * (2) +
			b_aux[i][j] * 4 + b_aux[i][j + 1] * (2) +
			b_aux[i + 1][j - 1] * (1) + b_aux[i + 1][j] * (2) +
			b_aux[i + 1][j + 1] * (1);
	suma = suma / 16;
	v->b[i][j] = round(suma);

	return 1;
}

int APPLY(struct imagine *v, char *comanda)
{
	// verificam comanda in urmatoarele 4 if uri;
	if (!verificare_existenta_imagine(*v))
		return 0;
	if (!comanda) {
		printf("Invalid command\n");
		return 0;
	}
	if (v->magic_word == 2 || v->magic_word == 5) {
		printf("Easy, Charlie Chaplin\n");
		return 0;
	}
	if (strcmp(comanda, "EDGE") != 0 && strcmp(comanda, "SHARPEN") != 0 &&
		strcmp(comanda, "BLUR") != 0 && strcmp(comanda, "GAUSSIAN_BLUR") != 0) {
		printf("APPLY parameter invalid\n");
		return 0;
	}
	unsigned char **r_aux, **g_aux, **b_aux;
	alocare_rgb_ALL(v, &r_aux, &g_aux, &b_aux);

	for (int i = 0; i < v->inaltime; i++) {
		for (int j = 0; j < v->latime; j++) {
			r_aux[i][j] = v->r[i][j];
			g_aux[i][j] = v->g[i][j];
			b_aux[i][j] = v->b[i][j];
		}
	}

	// inlantuire de if-uri are urmatorul rol:
	// daca imaginea este selectata, asta inseamna ca pe marginile
	// selectiei vom avea vecini suficienti pentru a face APPLY ul
	// daca este selectata toata imaginea, asta inseamna ca pe margini
	// nu vom avea vecini;
	// urmatoarele doua for-uri pornesc de la a la b,
	// respectiv de la c la d;
	// if-urile au grija ca a, b, c, d sa aiba valorile corespunzatoare;
	int a = v->y1, b = v->y2, c = v->x1, d = v->x2;
	if (v->selectat == 1) {
		if (v->y1 == 0)
			a++;
		if (v->y2 == v->inaltime)
			b--;
		if (v->x1 == 0)
			c++;
		if (v->x2 == v->latime)
			d--;
	} else if (v->selectat == 0) {
		++a;
		--b;
		++c;
		--d;
	}
	for (int i = a; i < b; i++)
		for (int j = c; j < d; j++)
			if (strcmp(comanda, "EDGE") == 0)
				apply_edge(v, r_aux, g_aux, b_aux, i, j);
			else if (strcmp(comanda, "SHARPEN") == 0)
				apply_sharpen(v, r_aux, g_aux, b_aux, i, j);
			else if (strcmp(comanda, "BLUR") == 0)
				apply_blur(v, r_aux, g_aux, b_aux, i, j);
			else if (strcmp(comanda, "GAUSSIAN_BLUR") == 0)
				apply_gaussian_blur(v, r_aux, g_aux, b_aux, i, j);
	printf("APPLY %s done\n", comanda);
	// nu mai avem nevoie de matricile auxiliare
	for (int i = 0; i < v->inaltime; i++) {
		free(r_aux[i]);
	free(g_aux[i]);
	free(b_aux[i]);
	}
	free(r_aux);
	free(g_aux);
	free(b_aux);
	return 1;
}
