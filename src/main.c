#include "../include/MatAdj.h"
#include "../include/listeAdj.h"
#include "../include/fileSucc.h"
#include "../include/tabs.h"
#include "../include/listeAdjPreSucc.h"
#include "../include/MatIncidColCol.h"
#include "../include/MatIncidLigLig.h"

ListeAdj transfoMatAdjListeAdj(MatAdj ma){
    int i, j;
    int nbSommets = ma.nbSommets;
    ListeAdj la = creerListeAdjVide(nbSommets);
    for(i = 0; i < nbSommets; i++){
        for(j = 0; j < nbSommets; j++){
            if(ma.mat[i][j] == 1){
                la.tabAdj[i] = inserQueue(la.tabAdj[i],j);
            }
        }
    }
    return la;
}

FileSucc transfoMatAdjListeSucc(MatAdj ma){
    int i, j, z;
    int nbSommets = ma.nbSommets;
    // On compte le nombre d'arcs pour la construction de la fileSucc
    int nbArcs = 0;
    for(i = 0; i < nbSommets; i++){
        for(j = 0; j < nbSommets; j++){
            if(ma.mat[i][j] == 1){
                nbArcs++;
            }
        }
    }
    FileSucc res = creerFileSuccVide(nbSommets,nbArcs);
    // On commence par remplir le tab aps
    res.aps[0] = 0;
    for(i = 0; i < nbSommets; i++){
        for(j = 0; j < nbSommets; j++){
            if(ma.mat[i][j] == 1){
                res.aps[i+1]++;
            }
        }
    }
    for(z = 2; z < nbSommets+1; z++){
        res.aps[z] += res.aps[z-1];
    }

    // Ensuite on s'attaque au tab fs
    res.aps[0] = 1;
    for(i = 0; i < nbSommets; i++){
        for(j = 0; j < nbSommets; j++){
            if(ma.mat[i][j] == 1){
                z = res.aps[i-1];
                if(z == 1) z--;
                while(z < res.aps[i] && res.fs[z] != 0){
                    z++;
                }
                res.fs[z] = j;
            }
        }
    }
    return res;
}

MatAdj carreMatAdj(MatAdj ma){
MatAdj res;
int u;

    res = creerMatriceAdjVide(ma.nbSommets);
    for(int i = 0; i < res.nbSommets; i++){
        for(int j = 0; j < res.nbSommets; j++){
            u = 0;
            while(u < res.nbSommets && (ma.mat[i][u]*ma.mat[u][j]) == 0){
                u++;
            }
            if(u < res.nbSommets){
                res.mat[i][j] = 1;
            }else{
                res.mat[i][j] = 0;
            }
        }
    }
    return res;
}

ListeAdj carreListeAdj(ListeAdj l){
ListeAdj res;
Liste ls, ll, lu;
int i,k,som;

    res = creerListeAdjVide(l.nbSom);
    for(i = 0; i < res.nbSom; i++){
        ls = l.tabAdj[i];
        ll = NULL;
        while(!estVide(ls)){
            som = ls->sommet;
            printf("Sommet 1 : %d\n",som);
            ls = ls->suiv;
            lu = l.tabAdj[som-1];
            while(!estVide(lu)){
                k = lu->sommet;
                printf("Sommet 2 : %d\n",k);
                lu = lu->suiv;
                ll = inserQueue(ll,k);
            }
        }
        res.tabAdj[i] = ll;
        printf("Insertion...\n");
    }
    return res;
}


int main(void){
    FILE *fd; FILE *efd;
    if((fd = fopen("adjacence.txt","r")) == NULL){
        return 1;
    }
    ListeAdj la = creerListeAdjFichier(fd);
    afficheListeAdj(la);
    parcoursProfondeurListeAdj(la,1);

    fclose(fd);
    // MatAdj g = creerMatAdjFichier(fd);
    // puts("matadj créée");
    // printf("%d\n", estSansBoucle(g));

    return 0;
}