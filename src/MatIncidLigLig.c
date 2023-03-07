#include "../include/MatIncidLigLig.h"

MatIncidLigLig creerMatIncidLigLigVide(int nbSommets, int nbArcs){
MatIncidLigLig ma;
    
    ma.nbSom = nbSommets;
    ma.nbArcs = nbArcs;
    ma.fs = malloc(sizeof(int)*nbArcs + 1);
    ma.aps = malloc(sizeof(int)*nbSommets + 1);
    ma .as = malloc(sizeof(int)*nbArcs + 1);
    for(int i = 0; i <nbArcs; i++){
        ma.fs[i] = 0;
        ma.as[i] = 0;
    }
    for(int i = 0; i < nbSommets; i++){
        ma.aps[i] = 0;
    }
    return ma;
}

MatIncidLigLig creerMatIncidLigLigFichier(FILE *fd){
MatIncidLigLig res;
int nbSommets, nbArcs, i, j, garbage;
    fseek(fd, SEEK_SET, 0);
    fscanf(fd,"\n#Description du graphe");
    fscanf(fd,"\nnbSom = %d", &nbSommets);
    fscanf(fd,"\nnbArcs = %d",&nbArcs);

    res = creerMatIncidLigLigVide(nbSommets,nbArcs);
    while(fscanf(fd,"\nArc%d : Pred = %d Succ = %d",&garbage,&i,&j)>0){
        res.aps[i]++;
    }
    for(int z=2;z<nbSommets+1;z++){
        if(res.aps[z]!=0){res.aps[z]+=res.aps[z-1];}
        else {res.aps[z]= res.aps[z-1];}
    }
    fseek(fd, 0,SEEK_SET);
    fscanf(fd,"\n#Description du graphe");
    fscanf(fd,"\nnbSom = %d", &nbSommets);
    fscanf(fd,"\nnbArcs = %d", &nbArcs);
    int z;
    while(fscanf(fd,"\nArc%d : Pred = %d Succ = %d", &garbage, &i, &j)>0){
        z=res.aps[i-1];
        while(z<res.aps[i]&&res.fs[z]!=0){z++;}
        res.fs[z]=garbage;
        res.as[z]=j;
    }

    affichetab(res.aps, nbSommets + 1);
    affichetab(res.fs,nbArcs + 1);
    affichetab(res.as,nbArcs + 1);
}