#include "../include/MatIncidColCol.h"

MatIncidColCol creerMatIncidColColVide(int nbSommets, int nbArcs){
MatIncidColCol ma;

    ma.nbSom = nbSommets;
    ma.nbArcs = nbArcs;
    ma.alpha = malloc(sizeof(int)*nbArcs);
    ma.beta = malloc(sizeof(int)*nbArcs);
    for(int i = 0; i < nbArcs; i++){
        ma.alpha[i] = 0;
        ma.beta[i] = 0;
    }
    return ma;
}

MatIncidColCol creerMatIncidColColFichier(FILE *fd){
MatIncidColCol res;
int nbSommets, nbArcs, i, j, garbage;

    fscanf(fd,"\n#Description du graphe");
    fscanf(fd,"\nnbSom = %d", &nbSommets);
    fscanf(fd,"\nnbArcs = %d",&nbArcs);

    res = creerMatIncidColColVide(nbSommets, nbArcs);
    while(fscanf(fd,"\nArc%d : Pred = %d Succ = %d",&garbage,&i,&j)>0){
        garbage--;
        res.alpha[garbage] = i;
        res.beta[garbage] = j;
    }
    affichetab(res.alpha,nbArcs);
    affichetab(res.beta,nbArcs);
    return res;
}