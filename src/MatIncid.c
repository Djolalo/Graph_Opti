#include "../include/MatIncid.h"

int **allocMat(int nbSom, int nbArcs){
    int **mat;
    mat = malloc(nbSom*sizeof(int*));
    if(mat ==NULL){
        fprintf(stderr, "Erreur");
    }
    for(int i = 0; i<nbSom; i++){
        mat[i] = malloc(nbArcs*sizeof(int));
    }
    return mat;
}

MatIncid creerMatriceVide(int nbSom, int nbArcs){
MatIncid ma;

    ma.mat = allocMat(nbSom,nbArcs);
    ma.nbSom = nbSom;
    ma.nbArcs = nbArcs;
    for(int i = 0; i < nbSom; i++){
        for(int j = 0; j < nbArcs; j++){
            ma.mat[i][j] = 0;
        }
    }
    return ma;
}

void afficheMatIncid(MatIncid ma){
    for(int i=0; i<ma.nbSom;i++){
        for(int j=0; j<ma.nbArcs;j++){
        if(ma.mat[i][j]==-1){
            printf("%d ", ma.mat[i][j]);
        }
        else{
            printf(" %d ", ma.mat[i][j]);
        }
        }
        puts("");
    }
}

MatIncid creerMatriceIncidFichier(FILE *fd){
int nbSommets, nbArcs, j, i, indiceDepart, indiceArrivee;
MatIncid res;
    fscanf(fd,"\n#Description du graphe");
    fscanf(fd,"\nnbSom = %d", &nbSommets);
    fscanf(fd,"\nnbArcs = %d", &nbArcs);
    res=creerMatriceVide(nbSommets,nbArcs);
    while(fscanf(fd,"\nArc%d:Pred = %d; Succ = %d",&j, &indiceDepart, &indiceArrivee)>0){
        res.mat[indiceDepart-1][j-1]=PREDECESSEUR;
        res.mat[indiceArrivee-1][j-1]=SUCCESSEUR;
    }
    return res;
}

