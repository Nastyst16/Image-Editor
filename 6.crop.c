// Nastase Cristian-Gabriel 315CA
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#define NMAX 100

int alocare_rgb_crop(struct imagine *v, unsigned char ***r, unsigned char ***g,
					 unsigned char ***b)
{
	// analog celorlaltor functii de alocare, doar ca aceasta
	// functie este folosita pentru comanda CROP;
	*r = (unsigned char **)malloc((v->y2 - v->y1) * sizeof(unsigned char *));
	if (!(*r))
		exit(1);
	*g = (unsigned char **)malloc((v->y2 - v->y1) * sizeof(unsigned char *));
	if (!(*g))
		exit(1);
	*b = (unsigned char **)malloc((v->y2 - v->y1) * sizeof(unsigned char *));
	if (!(*b))
		exit(1);
	for (int i = 0; i < v->y2 - v->y1; i++) {
		(*r)[i] =
			(unsigned char *)malloc((v->x2 - v->x1) * sizeof(unsigned char));
		if (!(*r)[i])
			exit(1);
		(*g)[i] =
			(unsigned char *)malloc((v->x2 - v->x1) * sizeof(unsigned char));
		if (!(*g)[i])
			exit(1);
		(*b)[i] =
			(unsigned char *)malloc((v->x2 - v->x1) * sizeof(unsigned char));
		if (!(*b)[i])
			exit(1);
	}
	return 1;
}

int CROP(struct imagine *v)
{
	if (!verificare_existenta_imagine(*v))
		return 0;
	// luam matrici auxiliare si le alocam cu dimensiunile necesare:
	// inaltimea noii poze va fi (v->y2 - v->y1)
	// latimea noii poze va fi (v->x2 - v->x1)
	int inaltime_crop = v->y2 - v->y1, latime_crop = v->x2 - v->x1;

	unsigned char **imagine_taiata;
	imagine_taiata =
		(unsigned char **)malloc(inaltime_crop * sizeof(unsigned char *));
	for (int i = 0; i < inaltime_crop; i++) {
		imagine_taiata[i] =
		(unsigned char *)malloc(latime_crop * sizeof(unsigned char));
	}
	unsigned char **r_aux, **g_aux, **b_aux;
	if (v->magic_word == 3 || v->magic_word == 6)
		alocare_rgb_crop(v, &r_aux, &g_aux, &b_aux);
	// copiem din poza totala in matricile auxiliare partea pozei ceruta
	for (int i = 0; i < inaltime_crop; i++) {
		for (int j = 0; j < latime_crop; j++) {
			imagine_taiata[i][j] = v->a[v->y1 + i][v->x1 + j];
			if (v->magic_word == 3 || v->magic_word == 6) {
				r_aux[i][j] = v->r[v->y1 + i][v->x1 + j];
				g_aux[i][j] = v->g[v->y1 + i][v->x1 + j];
				b_aux[i][j] = v->b[v->y1 + i][v->x1 + j];
			}
		}
	}
	eliberare_matrice(v);
	// realocam poza noastra cu noile dimensiuni, acum ca am salvat
	// partea pozei de care avem nevoie;
	if (v->magic_word == 3 || v->magic_word == 6)
		alocare_rgb_crop(v, &v->r, &v->g, &v->b);

	v->a = (unsigned char **)malloc(inaltime_crop * sizeof(unsigned char *));
	if (!v->a)
		exit(1);
	for (int i = 0; i < inaltime_crop; i++) {
		v->a[i] =
			(unsigned char *)malloc(latime_crop * sizeof(unsigned char));
		if (!v->a[i])
			exit(1);
	}
	v->latime = latime_crop;
	v->inaltime = inaltime_crop;
	v->x1 = 0;
	v->y1 = 0;
	v->x2 = v->latime;
	v->y2 = v->inaltime;
	// copiem valorile in structura;
	for (int i = 0; i < v->inaltime; i++) {
		for (int j = 0; j < v->latime; j++) {
			v->a[i][j] = imagine_taiata[i][j];
			if (v->magic_word == 3 || v->magic_word == 6) {
				v->r[i][j] = r_aux[i][j];
			v->g[i][j] = g_aux[i][j];
			v->b[i][j] = b_aux[i][j];
			}
		}
	}
	for (int i = 0; i < 256; i++)
		v->v_frecventa[i] = 0;
	// nu mai avem nevoie de matricile auxiliare si le dealocam
	for (int i = 0; i < v->inaltime; i++)
		free(imagine_taiata[i]);
	free(imagine_taiata);

	if (v->magic_word == 3 || v->magic_word == 6) {
		for (int i = 0; i < v->inaltime; i++) {
			free(r_aux[i]);
			free(g_aux[i]);
			free(b_aux[i]);
		}
	free(r_aux);
	free(g_aux);
	free(b_aux);
	}
	printf("Image cropped\n");
	return 1;
}
