#ifndef __LISTEADJPRESUCC_H_
#define __LISTEADJPRESUCC_H_

#include "MatAdj.h"
#include "liste.h"
#include "listeAdj.h"
#include "tabs.h"

typedef struct lsp{
    Liste lSucc;
    Liste lPred;
}ListeSuccPred;

typedef struct lasp{
    int nbSom;
    ListeSuccPred *tabAdjSuccPred;
}ListeAdjSuccPred;

ListeAdjSuccPred creerListeAdjSuccPredVide(int nbsommets);

ListeAdjSuccPred creerListeAdjSuccPredMatAdj(MatAdj ma);

#endif