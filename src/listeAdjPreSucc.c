#include "../include/listeAdjPreSucc.h"


ListeAdjSuccPred creerListeAdjSuccPredVide(int nbSommets){
    int i;
    ListeAdjSuccPred lasp;
    lasp.tabAdjSuccPred=malloc(nbSommets * sizeof(ListeSuccPred));
    for(i = 0; i < nbSommets; i++){
        lasp.tabAdjSuccPred[i].lPred = NULL;
        lasp.tabAdjSuccPred[i].lSucc = NULL;
    }
    return lasp;
}

ListeAdjSuccPred creerListeAdjSuccPredMatAdj(MatAdj ma){
    int i, j;
    ListeAdjSuccPred res = creerListeAdjSuccPredVide(ma.nbSommets);
    res.nbSom = ma.nbSommets;
    for(i = 0; i < ma.nbSommets; i++){
        for(j = 0; j < ma.nbSommets; j++){
            if(ma.mat[i][j] == 1){
                res.tabAdjSuccPred[i].lSucc = inserQueue(res.tabAdjSuccPred[i].lSucc,j);
                res.tabAdjSuccPred[j].lPred = inserQueue(res.tabAdjSuccPred[j].lPred,i);
            }
        }
    }
    for(int i = 0 ;  i<res.nbSom; i++){
        printf("Le sommet %d a pour prédécesseurs : ",i+1);
        afficheListe(res.tabAdjSuccPred[i].lPred);        
        printf(" et comme successeurs : ");
        afficheListe(res.tabAdjSuccPred[i].lSucc);
    }
    return res;
}