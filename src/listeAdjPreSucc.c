#include "../include/listeAdjPreSucc.h"


ListeAdjSuccPred creerListeAdjSuccPredVide(int nbSommets){
    int i;
    ListeAdjSuccPred lasp;
    ListeSuccPred lsp;

    lsp->lPred = malloc(sizeof(Liste)*nbSommets);
    lsp->lSucc = malloc(sizeof(Liste)*nbSommets);

    for(i = 0; i < nbSommets; i++){
        lsp->lPred[i] = NULL;
        lsp->lSucc[i] = NULL;
    }

    lasp.nbSom = nbSommets;
    lasp.tabAdjSuccPred = lsp;

    return lasp;
}

ListeAdjSuccPred creerListeAdjSuccPredMatAdj(MatAdj ma){
    int i, j;
    ListeAdjSuccPred res = creerListeAdjSuccPredVide(ma.nbSommets);
    ListeSuccPred lsp = res.tabAdjSuccPred;
    for(i = 0; i < res.nbSom; i++){
        for(j = 0; j < res.nbSom; j++){
            if(ma.mat[i][j] == 1){
                lsp->lSucc[i] = inserQueue(lsp->lSucc[i],j);
                lsp->lPred[j] = inserQueue(lsp->lPred[j],i);
            }
        }
    }
    affichetab(lsp->lPred,res.nbSom);
    affichetab(lsp->lSucc,res.nbSom);
    return res;
}