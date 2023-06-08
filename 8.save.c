// Nastase Cristian-Gabriel 315CA
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#define NMAX 100

int SAVE(struct imagine *v, char *fisier_nou)
{
	if (!verificare_existenta_imagine(*v))
		return 0;

	FILE *out = fopen(fisier_nou, "w");
	if (!out) {
		fprintf(stderr, "Failed to save %s\n", fisier_nou);
	return -1;
	}

	int ok = 0;
	char *ascii;
	ascii = strtok(NULL, "\n ");
	// daca dupa executia lui strtok vom avea rezultat diferit de NULL,
	// inseamna ca trebuie sa stocam poza in mod text;
	// in urmatoarea inlantuire de if uri schimb magic-wordul daca este nevoie;
	if (ascii) {
		if (v->magic_word == 4) {
			fprintf(out, "P1\n");
			v->magic_word = 1;
		} else if (v->magic_word == 5) {
			fprintf(out, "P2\n");
			v->magic_word = 2;
		} else if (v->magic_word == 6) {
			fprintf(out, "P3\n");
			v->magic_word = 3;
		} else {
			ok = 1;
		}
	} else {
		if (v->magic_word == 1) {
			fprintf(out, "P4\n");
			v->magic_word = 4;
		} else if (v->magic_word == 2) {
			fprintf(out, "P5\n");
			v->magic_word = 5;
		} else if (v->magic_word == 3) {
			fprintf(out, "P6\n");
			v->magic_word = 6;
		} else {
			ok = 1;
		}
	}
	if (ok)
		fprintf(out, "P%d\n", v->magic_word);

	fprintf(out, "%d %d\n", v->latime, v->inaltime);

	if (v->magic_word == 2 || v->magic_word == 3 || v->magic_word == 5 ||
		v->magic_word == 6)
		fprintf(out, "%d\n", v->valoare_maxima);
	// in continuare, in functie de magic-word, scriem in fisier matricea;
	if (v->magic_word == 2) {
		for (int i = 0; i < v->inaltime; i++) {
			for (int j = 0; j < v->latime; j++)
				fprintf(out, "%d ", (int)v->a[i][j]);
			fprintf(out, "\n");
		}
	} else if ((v->magic_word == 3)) {
		for (int i = 0; i < v->inaltime; i++) {
			for (int j = 0; j < v->latime; j++)
				fprintf(out, "%d %d %d\t", v->r[i][j], v->g[i][j], v->b[i][j]);
			fprintf(out, "\n");
		}
	} else if (v->magic_word == 5) {
		for (int i = 0; i < v->inaltime; i++)
			fwrite(v->a[i], sizeof(unsigned char), v->latime, out);

	} else if (v->magic_word == 6) {
		for (int i = 0; i < v->inaltime; i++) {
			for (int j = 0; j < v->latime; j++) {
				fwrite(&v->r[i][j], sizeof(unsigned char), 1, out);
				fwrite(&v->g[i][j], sizeof(unsigned char), 1, out);
				fwrite(&v->b[i][j], sizeof(unsigned char), 1, out);
			}
		}
	}
	printf("Saved %s\n", fisier_nou);
	fclose(out);
	return 1;
}
