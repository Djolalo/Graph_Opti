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

int somSuivantListeAdj(int i, int j, int *visite){
    while( i < j && visite[i-1]){
        i++;
    }
    return i;
}

void reParcoursProfondeurListeAdj(int s, ListeAdj la, int *visite, int *nbSomVisite){
    Liste l = la.tabAdj[s-1];
    visite[s-1] = 1;
    (*nbSomVisite)++;
    printf("Sommet %d visité\n",s);
    printf("Les successeurs de %d sont : ",s);
    afficheListe(l);
    while(!estVide(l)){
        if(visite[l->sommet-1] == 0){
            reParcoursProfondeurListeAdj(l->sommet, la, visite, nbSomVisite);
        }
        l = l->suiv;
    }
    
}

void parcoursProfondeurListeAdj(ListeAdj la,int sd){

    int n = la.nbSom;
    int *visite = (int*)malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++){
        visite[i] = 0;
    }
    affichetab(visite,n);

    int s = sd;
    int nbSomVisite = 0;
    int finParcours = 0;

    while(finParcours == 0){
        reParcoursProfondeurListeAdj(s, la, visite, &nbSomVisite);
        if(nbSomVisite < n){
            printf("Retour : changement de sommet\n");
            printf("Nb de sommets visités : %d\n",nbSomVisite);
            s = somSuivantListeAdj(s,n,visite);
            printf("Nouveau sommet : %d\n",s);
        }else{
            printf("Fin parcours !\n");
            finParcours = 1;
        }
    }
    affichetab(visite,n);
}