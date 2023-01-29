#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int nbSommets;
    int **mat;
}MatAdj;

int** allouerMatrice(int nbLignes, int nbColonnes){
    int **mat;
    mat= malloc(sizeof(int*)*nbLignes);
    if(mat==NULL){
        fprintf(stderr, "Erreur");
    }
    for(int i =0; i<nbLignes;i++){
        mat[i]=malloc(sizeof(int)*nbColonnes);
    }
    return mat;
}

MatAdj creerMatriceAdjVide(int taille){
    MatAdj res;
    res.mat=allouerMatrice(taille,taille);
    res.nbSommets=taille;
    for ( int i = 0;i<taille;i++){
        for (int j=0; j<taille;j++){
            res.mat[i][j]=0;
        }
    }
    return res;
}

void parcoursMatAdj(MatAdj g){
    for(int i=0; i<g.nbSommets;i++){
        for(int j=0; j<g.nbSommets;j++)printf("%d", g.mat[i][j]);
        puts("");
    }
}
MatInc creerMatIndFichier(FILE* fd){
int nbSommets,nbArcs, j , i, tmp; MatInc res;
    fscanf(fd,"\n#Description du graphe");
    fscanf(fd,"\nnbSom = %d", &nbSommets);
    fscanf(fd,"\nnbArcs = %d",&nbArcs);
    res=creerMatriceIncVide(nbSommets, nbArcs);
    for(int z=0;z<nbSommets;z++){
        fscanf(fd,"\nSom%d:",&j);
        j--;
        fscanf(fd,"%d", &tmp);
        res.mat[j][0]=tmp;
        i=1;
        while(fscanf(fd,";%d", &tmp)>0){
            res.mat[j][i]=tmp;
            i++;
        }
    }
    return res;
}    
MatAdj creerMatAdjFichier(FILE* fd){
int nbSommets, j , i, tmp; MatAdj res;
    fscanf(fd,"\n#Description du graphe");
    fscanf(fd,"\nnbSom = %d", &nbSommets);
    res=creerMatriceAdjVide(nbSommets);
    for(int z=0;z<nbSommets;z++){
        fscanf(fd,"\nSom%d:",&j);
        j--;
        fscanf(fd,"%d", &tmp);
        res.mat[j][0]=tmp;
        i=1;
        while(fscanf(fd,";%d", &tmp)>0){
            res.mat[j][i]=tmp;
            i++;
        }
    }
    return res;
}

int main(void){
    FILE* fd;
    if((fd=fopen("adjacence.txt","r"))==NULL)
        return 1;
    MatAdj test= creerMatAdjFichier(fd);
    fclose(fd);
    parcoursMatAdj(test);
    return 0;
}