#ifndef __MATINCIDLIGLIG_H_
#define __MATINCIDLIGLIG_H_

#include "tabs.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int nbSom;
    int nbArcs;
    int *fs;
    int *aps;
    int *as;
}MatIncidLigLig;

MatIncidLigLig creerMatIncidLigLigVide(int nbSommets, int nbArcs);

MatIncidLigLig creerMatIncidLigLigFichier(FILE *fd);

#endif