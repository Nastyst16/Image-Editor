// Nastase Cristian-Gabriel 315CA
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#define NMAX 100

// aceasta functie verifica comanda SELECT;
int verif_comanda_select(int *x1, int *y1, int *x2, int *y2, char *comanda)
{
	// luam fiecare parametru in parte cu strtok;
	// daca dupa ce folosim strtok rezultatul va fi NULL,
	// inseamna ca nu avem suficienti parametrii si comanda
	// este invalida
	// fiecare parametru il parcurgem cu un for si verificam
	// cu ajutorul functiei "isdigit", daca parametrul este numar;
	// in caz contrar comanda este invalida;
	char *coordonate;
	if (!comanda) {
		printf("Invalid command\n");
		return -1;
	}

	for (unsigned char i = 0; i < strlen(comanda); i++) {
		if (!isdigit(comanda[(int)i]) && comanda[0] != '-') {
			printf("Invalid command\n");
			return -1;
		}
	}
	*x1 = atoi(comanda);

	coordonate = strtok(NULL, "\n ");

	if (!coordonate) {
		printf("Invalid command\n");
		return -1;
	}

	for (unsigned char i = 0; i < strlen(coordonate); i++) {
		if (!isdigit(coordonate[(int)i]) && coordonate[0] != '-') {
			printf("Invalid command\n");
			return -1;
		}
	}
	*y1 = atoi(coordonate);

	coordonate = strtok(NULL, "\n ");

	if (!coordonate) {
		printf("Invalid command\n");
		return -1;
	}

	for (unsigned char i = 0; i < strlen(coordonate); i++) {
		if (!isdigit(coordonate[(int)i]) && coordonate[0] != '-') {
			printf("Invalid command\n");
		return -1;
		}
	}

	*x2 = atoi(coordonate);

	coordonate = strtok(NULL, "\n ");

	if (!coordonate) {
		printf("Invalid command\n");
		return -1;
	}

	for (unsigned char i = 0; i < strlen(coordonate); i++) {
		if (!isdigit(coordonate[(int)i]) && coordonate[0] != '-') {
			printf("Invalid command\n");
			return -1;
		}
	}

	*y2 = atoi(coordonate);

	// daca avem 5 parametrii comanda este invalida;
	coordonate = strtok(NULL, "\n ");
	if (coordonate) {
		printf("Invalid command\n");
		return -1;
	}

	return -11;
}

// aceasta functie verifica daca coordonatele introduse se afla in
// interiorul pozei;
int verif_coordonate(struct imagine *v, int x1, int y1, int x2, int y2)
{
	if (x1 < 0 || x1 > v->latime) {
		printf("Invalid set of coordinates\n");
		return -1;
	} else if (y1 < 0 || y1 > v->inaltime) {
		printf("Invalid set of coordinates\n");
		return -1;
	} else if (x2 < 0 || x2 > v->latime) {
		printf("Invalid set of coordinates\n");
		return -1;
	} else if (y2 < 0 || y2 > v->inaltime) {
		printf("Invalid set of coordinates\n");
		return -1;
	} else if (x1 == x2 || y1 == y2) {
		printf("Invalid set of coordinates\n");
		return -1;
	}
	return -11;
}

int SELECT(struct imagine *v, char *comanda)
{
	// facem toate verificarile necesare cu urmatoarele 3 if-uri;
	if (!verificare_existenta_imagine(*v))
		return 0;

	int x1_aux, y1_aux, x2_aux, y2_aux;
	if (verif_comanda_select(&x1_aux, &y1_aux, &x2_aux, &y2_aux, comanda) == -1)
		return -1;

	if (verif_coordonate(v, x1_aux, y1_aux, x2_aux, y2_aux) == -1)
		return -1;

	// folosim coordonate auxiliare pentru ca in cazul in care selectia este
	// invalida selectia anterioara trebuie sa se pastreze...asa ca daca se
	// trece de toate if-urile de abia atunci putem stoca selectia noua;
	v->x1 = x1_aux;
	v->y1 = y1_aux;
	v->x2 = x2_aux;
	v->y2 = y2_aux;

	if (v->x1 > v->x2) {
		int aux;
		aux = v->x1;
		v->x1 = v->x2;
		v->x2 = aux;
	}
	if (v->y1 > v->y2) {
		int aux;
		aux = v->y1;
		v->y1 = v->y2;
		v->y2 = aux;
	}
	printf("Selected %d %d %d %d\n", v->x1, v->y1, v->x2, v->y2);
	v->selectat = 1;

	return 1;
}

int SELECT_ALL(struct imagine *v)
{
	if (!verificare_existenta_imagine(*v))
		return 0;

	v->x1 = 0;
	v->y1 = 0;
	v->x2 = v->latime;
	v->y2 = v->inaltime;
	v->selectat = 0;
	printf("Selected ALL\n");

	return 1;
}

