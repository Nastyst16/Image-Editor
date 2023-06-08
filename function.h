// Nastase Cristian-Gabriel 315CA
#pragma once

// Avem o structura in care sunt stocate toate informatiile
// necesare de care avem nevoie in rezolvarea codului
// Prin aceasta structura putem crea functii care sa aiba
// putini parametrii, deoarece aproape toate variabilele de
// care avem nevoie sunt in structura.
struct imagine {
	int *v_frecventa, selectat, imagine_incarcata;
	unsigned char **a;
	int latime, inaltime, magic_word, valoare_maxima;
	int x1, y1, x2, y2;
	unsigned char **r, **g, **b;
};

int verificare_comentariu(FILE *in);

int alocare_rgb_ALL(struct imagine *v, unsigned char ***r, unsigned char ***g,
					unsigned char ***b);

int alocare_rgb_portiune(struct imagine *v, unsigned char ***r,
						 unsigned char ***g, unsigned char ***b);

int eliberare_matrice(struct imagine *v);

int LOAD(struct imagine *v, char *nume_fisier);

int verificare_existenta_imagine(struct imagine v);

int SAVE(struct imagine *v, char *fisier_nou);

int verif_comanda_select(int *x1, int *y1, int *x2, int *y2, char *comanda);

int verif_coordonate(struct imagine *v, int x1, int y1, int x2, int y2);

void swap(int *a, int *b);

int SELECT(struct imagine *v, char *comanda);

int SELECT_ALL(struct imagine *v);

int verif_comanda_histograma(int *X, int *Y, char *comanda);

int HISTOGRAM(struct imagine *v, char *comanda);

int alocare_rgb_crop(struct imagine *v, unsigned char ***r, unsigned char ***g,
					 unsigned char ***b);

int CROP(struct imagine *v);

void limitare_rezultate(double *x);

int EQUALIZE(struct imagine *v);

int verif_comanda_rotate(struct imagine *v, char *comanda, char *plus_sau_minus,
						 int *unghi);

int rotire_90_grade_ALL(struct imagine *v);

int rotire_180_grade_ALL(struct imagine *v);

int rotire_90_grade_portiune(struct imagine *v);

int ROTATE(struct imagine *v, char *comanda);

int apply_edge(struct imagine *v, unsigned char **r_aux,
			   unsigned char **g_aux, unsigned char **b_aux, int i, int j);

int apply_sharpen(struct imagine *v, unsigned char **r_aux,
				  unsigned char **g_aux, unsigned char **b_aux, int i, int j);

int apply_blur(struct imagine *v, unsigned char **r_aux, unsigned char **g_aux,
			   unsigned char **b_aux, int i, int j);

int apply_gaussian_blur(struct imagine *v, unsigned char **r_aux,
						unsigned char **g_aux, unsigned char **b_aux,
						int i, int j);

int APPLY(struct imagine *v, char *comanda);

