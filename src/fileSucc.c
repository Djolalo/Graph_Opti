#include "../include/fileSucc.h"

FileSucc creerFileSuccVide(int t, int a){
FileSucc f;

    f.nbSom = t;
    f.nbArcs = a;
    // t + 1 et a + 1 pour le sommet virtuel
    f.fs = malloc(sizeof(int)*a+1);
    f.aps = malloc(sizeof(int)*t+1);
    for(int i =0; i<a;i++){
        f.fs[i]=0;
    }
    for(int i=0; i<t;i++){
        f.aps[i]=0;
    }
    return f;
}

FileSucc creerFileSuccFichier(FILE *fd){
FileSucc res; int nbSommets; int nbArcs; int i; int j; int garbage;
    fscanf(fd,"\n#Description du graphe");
    fscanf(fd,"\nnbSom = %d", &nbSommets);
    fscanf(fd,"\nnbArcs = %d", &nbArcs);
    res = creerFileSuccVide(nbSommets,nbArcs);
    while(fscanf(fd,"\nArc%d : Pred = %d Succ = %d", &garbage, &i, &j)>0){
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
        res.fs[z]=j;
    }
    return res;
}