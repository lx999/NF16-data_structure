//Xiang LI
//Cédric BARRETEAU

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // pour strtok
#include <errno.h>

#define N 10 // lignes
#define M 10 // colonnes
#define MAX 30

typedef struct element{
  int colonne;
  int valeur;
  struct element *next;
} element;

typedef element *liste_ligne;

typedef struct matrice_creuse{
  liste_ligne *ptr;
  int Nlignes;
  int Ncolonnes;
} matrice_creuse;

void constructMat(matrice_creuse *m, int t[N][M],int Nlig, int Ncol);
void lireFichier(matrice_creuse *m, char nomFichier[MAX]);
void afficherMat(matrice_creuse m);
int getValue(matrice_creuse m, int i, int j);
void putValue(matrice_creuse m, int i, int j, int val);
void addMat(matrice_creuse m1, matrice_creuse m2);
int nombreOctetsGagnes(matrice_creuse m1);
