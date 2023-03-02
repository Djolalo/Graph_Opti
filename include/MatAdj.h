#ifndef __MATADJ_H_
#define __MATADJ_H_

#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "tabs.h"

typedef struct {
    int nbSommets;
    int **mat;
}MatAdj;

int** allouerMatrice(int nbLignes, int nbColonnes);

MatAdj creerMatriceAdjVide(int taille);

void afficheMatAdj(MatAdj g);

int somSuivant(int s , int n , int *visite);

void reParcoursProfondeurMatAdj(int s, int *visite, MatAdj g, int *nbSomVisite);

void parcoursProfondeurMatAdj(int sd, MatAdj g);

void itParcoursLargeurMatAdj(int s, int *visite, MatAdj g, int *nbSomVisite);

int prochainSuccesseurdeU(int *col, MatAdj g, int ligne );

void parcoursLargeurMatAdj(int sd, MatAdj g);

MatAdj creerMatAdjFichier(FILE* fd);
#endif