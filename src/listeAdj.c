#include "../include/listeAdj.h"

ListeAdj creerListeAdjVide(int nbSom){
    ListeAdj ret; 
    ret.tabAdj = malloc(sizeof(Liste)*nbSom);
    ret.nbSom = nbSom;
    for(int i = 0; i < nbSom; i++){
        ret.tabAdj[i] = NULL;
    }
    return ret;
}

void afficheListeAdj(ListeAdj l){
    for(int z = 0; z<l.nbSom; z++){
        printf("Les successeurs du sommet %d sont : ",z+1);
        afficheListe(l.tabAdj[z]);
    }
}

ListeAdj creerListeAdjFichier(FILE *fd){
int nbSommets; ListeAdj res; int i; int j; int garbage;
    fseek(fd,SEEK_SET,0);
    fscanf(fd,"\n#Description du graphe");
    fscanf(fd,"\nnbSom = %d", &nbSommets);
    res = creerListeAdjVide(nbSommets);
    while(fscanf(fd, "\nArc%d : Pred = %d Succ = %d",&garbage, &j,&i) > 0){
        j--; 
        res.tabAdj[j]=inserQueue(res.tabAdj[j], i);
    }
    return res;
}