// Nastase Cristian-Gabriel 315CA
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#define NMAX 100

// in aceasta functie verificam daca exista comentarii
// pe o linie;
int verificare_comentariu(FILE *in)
{
	char comentariu[256];

	do {
		// citim 256 caractere daca gasim # sau \n;
		fgets(comentariu, 256, in);

	} while (comentariu[0] == '#' || comentariu[0] == '\n');

	// informatia din comentariu a fost stocata in variabila 'comentariu',
	// iar acum cu ajutorul lui fseek mutam cursorul in fisier la urmatoarea
	// linie, de dupa comentariu;
	fseek(in, ftell(in) - strlen(comentariu), SEEK_SET);

	return 1;
}

void citire_info_poza(struct imagine *v, FILE *in)
{
	char P;
	// citim informatiile despre poza si in acelasi timp
	// verificam pentru fiecare linie existenta comentariului;
	verificare_comentariu(in);
	fscanf(in, "%c%d", &P, &v->magic_word);
	verificare_comentariu(in);
	fscanf(in, "%d%d", &v->latime, &v->inaltime);
	verificare_comentariu(in);
	fscanf(in, "%d", &v->valoare_maxima);

	// facem aceste atribuiri deoarece este selectata toata poza
	// deci coordonatele x1, y1, x2, y2 vor avea urmatoarele valori:
	v->x1 = 0;
	v->y1 = 0;
	v->x2 = v->latime;
	v->y2 = v->inaltime;
}

int LOAD(struct imagine *v, char *nume_fisier)
{
	char gunoi;
	int failed_to_load = 0;

	FILE *in = fopen(nume_fisier, "r");
	if (!in) {
		printf("Failed to load %s\n", nume_fisier);
		failed_to_load = 1;
		if (v->imagine_incarcata == 0)
			return -1;
	}

	// verificam daca avem deja o poza incarcata si daca da, o eliberam
	if (v->imagine_incarcata == 1) {
		eliberare_matrice(v);
		if (failed_to_load == 1) {
			v->imagine_incarcata = 0;
			return -1;
		}
	}

	citire_info_poza(v, in);

	v->a = (unsigned char **)malloc(v->inaltime * sizeof(unsigned char *));
	if (!v->a)
		exit(1);
	for (int i = 0; i < v->inaltime; i++) {
		v->a[i] = (unsigned char *)malloc(v->latime * sizeof(unsigned char));
		if (!v->a[i])
			exit(1);
	}
	// avem cate un caz special pentru fiecare tip de poza
	if (v->magic_word == 2) {
		for (int i = 0; i < v->inaltime; i++)
			for (int j = 0; j < v->latime; j++)
				fscanf(in, "%hhd", &v->a[i][j]);

	} else if (v->magic_word == 5) {
		// am observat faptul ca dupa citirea informatiilor pozei imi apare
		// si un endline (\n). Nu stiu de ce se intampla asta, dar am stocat
		// acest endline in variabila 'gunoi', pentru a nu avea probleme;
		fread(&gunoi, sizeof(char), 1, in);
		for (int i = 0; i < v->inaltime; i++)
			fread(v->a[i], sizeof(unsigned char), v->latime, in);

	} else if (v->magic_word == 3 || v->magic_word == 6) {
		alocare_rgb_ALL(v, &v->r, &v->g, &v->b);

		if (v->magic_word == 3) {
			for (int i = 0; i < v->inaltime; i++)
				for (int j = 0; j < v->latime; j++) {
					v->a[i][j] = i + j;
					// citim 3 valori de odata, fiecare
					// valoare corespunde unei culori;
					fscanf(in, "%hhd%hhd%hhd", &v->r[i][j],
						   &v->g[i][j], &v->b[i][j]);
				}

		} else if (v->magic_word == 6) {
			// am observat faptul ca dupa citirea informatiilor pozei imi apare
			// si un endline (\n). Nu stiu de ce se intampla asta, dar am stocat
			// acest endline in variabila 'gunoi', pentru a nu avea probleme;
			fread(&gunoi, sizeof(char), 1, in);
			for (int i = 0; i < v->inaltime; i++)
				for (int j = 0; j < v->latime; j++) {
					v->a[i][j] = i + j;
					// citim 3 valori de odata, fiecare
					// valoare corespunde unei culori;
					fread(&v->r[i][j], sizeof(unsigned char), 1, in);
					fread(&v->g[i][j], sizeof(unsigned char), 1, in);
					fread(&v->b[i][j], sizeof(unsigned char), 1, in);
				}
		}
	}
	v->imagine_incarcata = 1;
	printf("Loaded %s\n", nume_fisier);
	fclose(in);
	return 1;
}
