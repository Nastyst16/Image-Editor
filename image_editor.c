// Nastase Cristian-Gabriel 315CA
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#define NMAX 100

int main(void)
{
	// declaram variabila v. Aceasta va stoca fotografia noastra
	// si toate detaliile de care avem nevoie;
	struct imagine v;
	char *comanda, *p;
	v.imagine_incarcata = 0, v.selectat = 0;
	p = (char *)malloc(NMAX + 1 * sizeof(char));
	v.v_frecventa = (int *)calloc(256, sizeof(int));
	while (1) {
		// am stabilit ca e mai bine sa citesc toata comanda
		// impreuna cu parametrii deoarece este necesar sa tratez
		// cazurile in care nu am numarul de parametrii corespunzatori.
		// De-a lungul codului vom folosi strtok pentru a separa
		// fiecare parametru in parte si a putea fi verificat.
		fgets(p, NMAX, stdin);
		comanda = strtok(p, "\n ");
		if (strcmp(comanda, "LOAD") == 0) {
			comanda = strtok(NULL, "\n ");
			LOAD(&v, comanda);

		} else if (strcmp(comanda, "SELECT") == 0) {
			comanda = strtok(NULL, "\n ");
			if (!comanda)
				SELECT(&v, comanda);
			else if (strcmp(comanda, "ALL") == 0)
				SELECT_ALL(&v);
			else
				SELECT(&v, comanda);

		} else if (strcmp(comanda, "HISTOGRAM") == 0) {
			comanda = strtok(NULL, "\n ");
			HISTOGRAM(&v, comanda);

		} else if (strcmp(comanda, "EQUALIZE") == 0) {
			EQUALIZE(&v);

		} else if (strcmp(comanda, "ROTATE") == 0) {
			comanda = strtok(NULL, "\n ");
			ROTATE(&v, comanda);

		} else if (strcmp(comanda, "CROP") == 0) {
			CROP(&v);

		} else if (strcmp(comanda, "APPLY") == 0) {
			comanda = strtok(NULL, "\n ");
			APPLY(&v, comanda);

		} else if (strcmp(comanda, "SAVE") == 0) {
			comanda = strtok(NULL, "\n ");
			SAVE(&v, comanda);

		} else if (strcmp(comanda, "EXIT") == 0) {
			if (v.imagine_incarcata == 1)
				eliberare_matrice(&v);
			else
				printf("No image loaded\n");

			free(comanda);
			free(v.v_frecventa);
			break;

		} else {
			printf("Invalid command\n");
		}
	}
	return 0;
}
