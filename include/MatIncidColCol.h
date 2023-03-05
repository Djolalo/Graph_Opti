#ifndef __MATINCIDCOLCOL_H_
#define __MATINCIDCOLCOL_H_

#include "tabs.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int nbSom;
    int nbArcs;
    int *alpha;
    int *beta;
}MatIncidColCol;

MatIncidColCol creerMatIncidColColVide(int nbSommets, int nbArcs);

MatIncidColCol creerMatIncidColColFichier(FILE *fd);

#endif