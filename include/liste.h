#ifndef __liste_h_
#define __liste_h_

#include <stdio.h>
#include <stdlib.h>

typedef struct cellule{
    int sommet;
    struct cellule *suiv;
}*Liste;

int estVide(Liste l);

Liste allocRempMemCellListe(int elt);

Liste dernierListe(Liste f);

Liste inserQueue(Liste l, int sommet);

void afficheListe(Liste p);

#endif