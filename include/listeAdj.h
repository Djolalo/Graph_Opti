#ifndef __LISTEADJ_H_
#define __LISTEADJ_H_

#include <stdio.h>
#include <stdlib.h>
#include "tabs.h"
#include "liste.h"
#include "file.h"

typedef struct{
    int nbSom;
    Liste *tabAdj;
}ListeAdj;

ListeAdj creerListeAdjVide(int nbSom);

void afficheListeAdj(ListeAdj l);

ListeAdj creerListeAdjFichier(FILE *fd);

int somSuivantListeAdj(int i, int j, int *visite);

void reParcoursProfondeurListeAdj(int s, ListeAdj la, int *visite, int *nbSomVisite);

void parcoursProfondeurListeAdj(ListeAdj la, int sd);

#endif