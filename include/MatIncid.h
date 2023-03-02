#ifndef __MATINCID_H_
#define __MATINCID_H_
#include <stdio.h>
#include <stdlib.h>

#define PREDECESSEUR 1
#define SUCCESSEUR -1

typedef struct{
    int nbSom;
    int nbArcs;
    int **mat;
}MatIncid;

int **allocMat(int nbSom, int nbArcs);

MatIncid creerMatriceVide(int nbSom, int nbArcs);

void afficheMatIncid(MatIncid ma);

MatIncid creerMatriceIncidFichier(FILE *fd);

#endif