// Nastase Cristian-Gabriel 315CA
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#define NMAX 100

// aceasta functie este folosita pentru rotirea intregii imagini (ALL)
int alocare_rgb_ALL(struct imagine *v, unsigned char ***r, unsigned char ***g,
					unsigned char ***b)
{
	// avand in vedere ca aloc 3 matrici in acelasi timp, va trebui sa
	// am ***, deoarece lucez cu adresele de memorie.
	*r = (unsigned char **)malloc(v->inaltime * sizeof(unsigned char *));
	if (!(*r))
		exit(1);
	*g = (unsigned char **)malloc(v->inaltime * sizeof(unsigned char *));
	if (!(*g))
		exit(1);
	*b = (unsigned char **)malloc(v->inaltime * sizeof(unsigned char *));
	if (!(*b))
		exit(1);
	for (int i = 0; i < v->inaltime; i++) {
		(*r)[i] = (unsigned char *)malloc(v->latime * sizeof(unsigned char));
		if (!(*r)[i])
			exit(1);
		(*g)[i] = (unsigned char *)malloc(v->latime * sizeof(unsigned char));
		if (!(*g)[i])
			exit(1);
		(*b)[i] = (unsigned char *)malloc(v->latime * sizeof(unsigned char));
		if (!(*b)[i])
			exit(1);
	}

	return 1;
}

// analog functiei anterioare, doar ca aici se
// foloseste pentru rotirea unei portiuni din imagine;
int alocare_rgb_portiune(struct imagine *v, unsigned char ***r,
						 unsigned char ***g, unsigned char ***b)
{
	*r = (unsigned char **)malloc(v->latime * sizeof(unsigned char *));
	if (!(*r))
		exit(1);
	*g = (unsigned char **)malloc(v->latime * sizeof(unsigned char *));
	if (!(*g))
		exit(1);
	*b = (unsigned char **)malloc(v->latime * sizeof(unsigned char *));
	if (!(*b))
		exit(1);
	for (int i = 0; i < v->latime; i++) {
		(*r)[i] = (unsigned char *)malloc(v->inaltime * sizeof(unsigned char));
		if (!(*r)[i])
			exit(1);
		(*g)[i] = (unsigned char *)malloc(v->inaltime * sizeof(unsigned char));
		if (!(*g)[i])
			exit(1);
		(*b)[i] = (unsigned char *)malloc(v->inaltime * sizeof(unsigned char));
		if (!(*b)[i])
			exit(1);
	}

	return 1;
}

// aceasta functie elibereaza matricile din structura 'v';
int eliberare_matrice(struct imagine *v)
{
	for (int i = 0; i < v->inaltime; i++)
		free(v->a[i]);
	free(v->a);

	if (v->magic_word == 3 || v->magic_word == 6) {
		for (int i = 0; i < v->inaltime; i++) {
			free(v->r[i]);
			free(v->g[i]);
			free(v->b[i]);
		}
	free(v->r);
	free(v->g);
	free(v->b);
	}

	return 1;
}

// verificam daca este vreo imagine incarcata;
int verificare_existenta_imagine(struct imagine v)
{
	if (v.imagine_incarcata == 0) {
		printf("No image loaded\n");
		return 0;
	}
	return 1;
}

void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

void limitare_rezultate(double *x)
{
	if (*x > 255)
		*x = 255;
	else if (*x < 0)
		*x = 0;
}
