#ifndef __LISTEADJ_H_
#define __LISTEADJ_H_

#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "file.h"

typedef struct{
    int nbSom;
    Liste *tabAdj;
}ListeAdj;

ListeAdj creerListeAdjVide(int nbSom);

void afficheListeAdj(ListeAdj l);

ListeAdj creerListeAdjFichier(FILE *fd);

#endif