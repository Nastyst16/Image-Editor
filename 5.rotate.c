// Nastase Cristian-Gabriel 315CA
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#define NMAX 100

int verif_comanda_rotate(struct imagine *v, char *comanda, char *plus_sau_minus,
						 int *unghi)
{
	if (!comanda) {
		printf("Invalid command\n");
		return 0;
	}

	for (unsigned char i = 0; i < strlen(comanda); i++) {
		if (!isdigit(comanda[(int)i]) && comanda[0] != '-' &&
			comanda[0] != '+') {
			printf("Invalid command\n");
			return 0;
		}
	}

	// in cazul in care avem parametru fara semn, se intelege faptul ca
	// semnul va fi '+'. In acest if tratam comanda fara semn;
	if (strcmp(comanda, "0") == 0 || strcmp(comanda, "90") == 0 ||
		strcmp(comanda, "180") == 0 || strcmp(comanda, "270") == 0 ||
		strcmp(comanda, "360") == 0) {
		*unghi = atoi(comanda);
		*plus_sau_minus = '+';
		printf("Rotated %d\n", *unghi);
		return -1;
	}

	*plus_sau_minus = comanda[0];

	// atribuim valorii 'comanda[0]' 0, ca functia atoi sa returneze
	// numarul de care avem nevoie;
	if (comanda[0] == '-' || comanda[0] == '+')
		comanda[0] = '0';

	*unghi = atoi(comanda);
	if (*unghi != 0 && *unghi != 90 && *unghi != 180 && *unghi != 270 &&
		*unghi != 360) {
		printf("Unsupported rotation angle\n");
		return 0;
	}

	if ((v->x1 == 0 && v->y1 == 0 && v->x2 == v->latime &&
		 v->y2 == v->inaltime) == 0)
		if ((v->x1 != v->x2 || v->y1 != v->y2) &&
			((v->x2 - v->x1) != (v->y2 - v->y1))) {
			printf("The selection must be square\n");
			return 0;
		}
	printf("Rotated %c%d\n", *plus_sau_minus, *unghi);
	return 1;
}

int rotire_90_grade_ALL(struct imagine *v)
{
	// daca rotim la 90 va trebui sa luam matrici auxiliare care vor avea
	// dimensiuni diferite: am dat swap la inaltime si latime in comanda rotate;
	unsigned char **portiune_rotita;
	portiune_rotita =
		(unsigned char **)malloc(v->inaltime * sizeof(unsigned char *));
	if (!portiune_rotita)
		exit(1);
	for (int i = 0; i < v->inaltime; i++) {
		portiune_rotita[i] =
			(unsigned char *)malloc(v->latime * sizeof(unsigned char));
		if (!portiune_rotita[i])
			exit(1);
	}
	unsigned char **r_aux, **g_aux, **b_aux;
	if (v->magic_word == 3 || v->magic_word == 6)
		alocare_rgb_ALL(v, &r_aux, &g_aux, &b_aux);
	// copiem imaginea rotita in matricile auxiliare;
	for (int i = 0; i < v->inaltime; i++)
		for (int j = 0; j < v->latime; j++) {
			portiune_rotita[i][j] = v->a[j][v->inaltime - i - 1];
			if (v->magic_word == 3 || v->magic_word == 6) {
				r_aux[i][j] = v->r[j][v->inaltime - i - 1];
				g_aux[i][j] = v->g[j][v->inaltime - i - 1];
				b_aux[i][j] = v->b[j][v->inaltime - i - 1];
			}
		}
	// acum ca am stocat poza rotita, putem dealoca si realoca cu
	// noile dimensiuni matricile pozei (adica cele din structura);
	for (int i = 0; i < v->latime; i++) {
		free(v->a[i]);
		if (v->magic_word == 3 || v->magic_word == 6) {
			free(v->r[i]);
			free(v->g[i]);
			free(v->b[i]);
		}
	}
	free(v->a);
	if (v->magic_word == 3 || v->magic_word == 6) {
		free(v->r);
		free(v->g);
		free(v->b);
	}
	v->a = (unsigned char **)malloc(v->inaltime * sizeof(char *));
	if (!v->a)
		exit(1);
	for (int i = 0; i < v->inaltime; i++) {
		v->a[i] = (unsigned char *)malloc(v->latime * sizeof(char));
		if (!v->a[i])
			exit(1);
	}
	if (v->magic_word == 3 || v->magic_word == 6)
		alocare_rgb_ALL(v, &v->r, &v->g, &v->b);
	// copiem valorile;
	for (int i = 0; i < v->inaltime; i++)
		for (int j = 0; j < v->latime; j++) {
			v->a[i][j] = portiune_rotita[i][j];
			if (v->magic_word == 3 || v->magic_word == 6) {
				v->r[i][j] = r_aux[i][j];
				v->g[i][j] = g_aux[i][j];
				v->b[i][j] = b_aux[i][j];
			}
		}
	for (int i = 0; i < v->inaltime; i++) {
		free(portiune_rotita[i]);
		if (v->magic_word == 3 || v->magic_word == 6) {
			free(r_aux[i]);
			free(g_aux[i]);
			free(b_aux[i]);
		}
	}
	free(portiune_rotita);
	if (v->magic_word == 3 || v->magic_word == 6) {
		free(r_aux);
		free(g_aux);
		free(b_aux);
	}
	v->x2 = v->latime;
	v->y2 = v->inaltime;
	return 1;
}

int rotire_180_grade_ALL(struct imagine *v)
{
	// aceasta functie este putin diferita. avand in vedere ca
	// rotim la 180 de grade dimensiunile pozei rotite vor fi
	// aceleasi...asca ca nu mai trebuie sa realocam matricile;
	unsigned char **portiune_rotita;
	portiune_rotita =
		(unsigned char **)malloc(v->inaltime * sizeof(unsigned char *));
	if (!portiune_rotita)
		exit(1);
	for (int i = 0; i < v->inaltime; i++) {
		portiune_rotita[i] =
			(unsigned char *)malloc(v->latime * sizeof(unsigned char));
		if (!portiune_rotita[i])
			exit(1);
	}

	unsigned char **r_aux, **g_aux, **b_aux;
	if (v->magic_word == 3 || v->magic_word == 6)
		alocare_rgb_ALL(v, &r_aux, &g_aux, &b_aux);

	// in matricile auxiliare copiem poza rotita;
	for (int i = 0; i < v->inaltime; i++) {
		for (int j = 0; j < v->latime; j++) {
			portiune_rotita[i][j] =
				v->a[v->inaltime - i - 1][v->latime - j - 1];
			if (v->magic_word == 3 || v->magic_word == 6) {
				r_aux[i][j] = v->r[v->inaltime - i - 1][v->latime - j - 1];
				g_aux[i][j] = v->g[v->inaltime - i - 1][v->latime - j - 1];
				b_aux[i][j] = v->b[v->inaltime - i - 1][v->latime - j - 1];
			}
		}
	}
	for (int i = 0; i < v->inaltime; i++) {
		for (int j = 0; j < v->latime; j++) {
			v->a[i][j] = portiune_rotita[i][j];
			if (v->magic_word == 3 || v->magic_word == 6) {
				v->r[i][j] = r_aux[i][j];
				v->g[i][j] = g_aux[i][j];
				v->b[i][j] = b_aux[i][j];
			}
		}
	}

	for (int i = 0; i < v->inaltime; i++) {
		free(portiune_rotita[i]);
		if (v->magic_word == 3 || v->magic_word == 6) {
			free(r_aux[i]);
			free(g_aux[i]);
			free(b_aux[i]);
		}
	}
	free(portiune_rotita);
	if (v->magic_word == 3 || v->magic_word == 6) {
		free(r_aux);
		free(g_aux);
		free(b_aux);
	}

	return 1;
}

int rotire_90_grade_portiune(struct imagine *v)
{
	unsigned char **portiune_rotita;
	portiune_rotita =
		(unsigned char **)malloc(v->latime * sizeof(unsigned char *));
	if (!portiune_rotita)
		exit(1);
	for (int i = 0; i < v->latime; i++) {
		portiune_rotita[i] =
			(unsigned char *)malloc(v->inaltime * sizeof(unsigned char));
		if (!portiune_rotita[i])
			exit(1);
	}

	unsigned char **r_aux, **g_aux, **b_aux;
	if (v->magic_word == 3 || v->magic_word == 6)
		alocare_rgb_portiune(v, &r_aux, &g_aux, &b_aux);

	// rotim toata poza in matricile auxiliare;
	for (int i = 0; i < v->latime; i++) {
		for (int j = 0; j < v->inaltime; j++) {
			portiune_rotita[i][j] = v->a[j][v->latime - i - 1];
			if (v->magic_word == 3 || v->magic_word == 6) {
				r_aux[i][j] = v->r[j][v->latime - i - 1];
				g_aux[i][j] = v->g[j][v->latime - i - 1];
				b_aux[i][j] = v->b[j][v->latime - i - 1];
			}
		}
	}
	// ne ramane decat sa copiem in poza
	// noastra patratul de care avem nevoie;
	for (int i = v->y1, a = 0; i < v->y2; i++, a++) {
		for (int j = v->x1, b = 0; j < v->x2; j++, b++) {
			v->a[i][j] = portiune_rotita[v->latime - v->x2 + a][v->y1 + b];
			if (v->magic_word == 3 || v->magic_word == 6) {
				v->r[i][j] = r_aux[v->latime - v->x2 + a][v->y1 + b];
				v->g[i][j] = g_aux[v->latime - v->x2 + a][v->y1 + b];
				v->b[i][j] = b_aux[v->latime - v->x2 + a][v->y1 + b];
			}
		}
	}

	// nu mai avem nevoie de matricie auxiliare -> le dealocam
	for (int i = 0; i < v->latime; i++) {
		free(portiune_rotita[i]);
		if (v->magic_word == 3 || v->magic_word == 6) {
			free(r_aux[i]);
			free(g_aux[i]);
			free(b_aux[i]);
		}
	}
	free(portiune_rotita);
	if (v->magic_word == 3 || v->magic_word == 6) {
		free(r_aux);
		free(g_aux);
		free(b_aux);
	}
	return 1;
}

int ROTATE(struct imagine *v, char *comanda)
{
	if (!verificare_existenta_imagine(*v))
		return 0;

	int unghi;
	char plus_sau_minus;

	if (!verif_comanda_rotate(v, comanda, &plus_sau_minus, &unghi))
		return 0;

	if (unghi == 360)
		return 1;

	if (v->x1 == 0 && v->y1 == 0 && v->x2 == v->latime &&
		v->y2 == v->inaltime) {
		if (unghi == 90 && plus_sau_minus == '+') {
			rotire_180_grade_ALL(v);
			swap(&v->inaltime, &v->latime);
			rotire_90_grade_ALL(v);
		} else if (unghi == 270 && plus_sau_minus == '+') {
			swap(&v->inaltime, &v->latime);
			rotire_90_grade_ALL(v);
		} else if (unghi == 90 && plus_sau_minus == '-') {
			swap(&v->inaltime, &v->latime);
			rotire_90_grade_ALL(v);

		} else if (unghi == 270 && plus_sau_minus == '-') {
			rotire_180_grade_ALL(v);
			swap(&v->inaltime, &v->latime);
			rotire_90_grade_ALL(v);
		} else if (unghi == 180) {
			rotire_180_grade_ALL(v);
		}
	} else {
		if (unghi == 90 && plus_sau_minus == '+') {
			rotire_90_grade_portiune(v);
			rotire_90_grade_portiune(v);
			rotire_90_grade_portiune(v);
		} else if (unghi == 270 && plus_sau_minus == '+') {
			rotire_90_grade_portiune(v);
		} else if (unghi == 90 && plus_sau_minus == '-') {
			rotire_90_grade_portiune(v);
		} else if (unghi == 270 && plus_sau_minus == '-') {
			rotire_90_grade_portiune(v);
			rotire_90_grade_portiune(v);
			rotire_90_grade_portiune(v);
		} else if (unghi == 180) {
			rotire_90_grade_portiune(v);
			rotire_90_grade_portiune(v);
		}
	}

	return 1;
}
