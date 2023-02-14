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

// faux
int somSuivant(int *s , int n , int *visite){
    while( *s< n && visite[*s]){
        (*s)++;
    }
    return *s<n; 
}

void reParcoursProfondeur(int s, int *visite, MatAdj g, int *nbSomVisite){
    visite[s] = 1;
    printf("je traite le %d-eme sommet \n", s+1);
    *nbSomVisite++;
    for(int t = s; t<g.nbSommets;t++ ){
        if(!visite[t]&& g.mat[s][t]){
            reParcoursProfondeur(t, visite, g,nbSomVisite);
        }
    }
}

void parcoursProfondeurMatAdj(int sd, MatAdj g){
    int n , s, nbSomVisite, finParcours;
    int *visite;
    
    n = g.nbSommets;
    visite = (int*) malloc (sizeof(int)*n);
    for(s = 0 ; s<n; s++){
        visite[s] = 0;
    }
    s = sd;
    nbSomVisite = 0;
    finParcours = 0;
    while(!finParcours){
        reParcoursProfondeur(s, visite, g, &nbSomVisite);
        if(!(somSuivant(&s, n ,visite))){
            finParcours= 1;
        }
        printf("\n Fin Parcours=%d", finParcours);
    }
}

MatAdj creerMatAdjFichier(FILE* fd){
int nbSommets, j , i, tmp; MatAdj res; int garbage;
    fscanf(fd,"\n#Description du graphe");
    fscanf(fd,"\nnbSom = %d", &nbSommets);
    res=creerMatriceAdjVide(nbSommets);
    while(fscanf(fd, "\nArc%d : Pred = %d Succ = %d",&garbage,&j, &i)>0){
        i--;j--;
        res.mat[i][j]=1;
        res.mat[j][i]=1;
    }
    parcoursProfondeurMatAdj(0, res);
    return res;
}

int main(void){
    FILE* fd;
    if((fd=fopen("adjacence.txt","r"))==NULL)
        return 1;
    MatAdj test= creerMatAdjFichier(fd);
    fclose(fd);
    //parcoursMatAdj(test);
    return 0;
}