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



int main(void){
    FILE *fd;
    if((fd = fopen("fs.txt","r")) == NULL){
        return 1;
    }

    MatIncidColCol mb = creerMatIncidColColFichier(fd);

    fclose(fd);
    return 0;
}