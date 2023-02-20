#include <stdio.h>
#include <stdlib.h>
#include "../include/file.h"
typedef struct {
    int nbSommets;
    int **mat;
}MatAdj;

int** allouerMatrice(int nbLignes, int nbColonnes){
    int **mat;
    mat= malloc(sizeof(int*)*nbLignes);
    if(mat==NULL){
        perror("Erreur");
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

void afficheMatAdj(MatAdj g){
    for(int i=0; i<g.nbSommets;i++){
        for(int j=0; j<g.nbSommets;j++)printf("%d", g.mat[i][j]);
        puts("");
    }
}

/* 

                    VERSION DJILALI

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
}*/

int somSuivant(int s , int n , int *visite){
    while( s < n && visite[s]){
        s++;
    }
    return s; 
}

void affichetab(int *tab, MatAdj g){
    for(int i = 0; i < g.nbSommets;i++){
        printf("%d,",tab[i]);
    }puts("");
}

void reParcoursProfondeurMatAdj(int s, int *visite, MatAdj g, int *nbSomVisite){
    visite[s] = 1;
    int j;
    printf("Sommet = %d\n",s+1);
    affichetab(visite,g);
    (*nbSomVisite)++;
    for(int t = 0; t < g.nbSommets; t++){
        if(visite[t] == 0 && g.mat[s][t] == 1){
            reParcoursProfondeurMatAdj(t,visite,g,nbSomVisite);
        }
    }
}

void parcoursProfondeurMatAdj(int sd, MatAdj g){

    // Phase d'initialisation
    int j;
    int n = g.nbSommets;
    int *visite;
    visite = (int*)malloc(sizeof(int)*n);
    for(int s = 0; s < n; s++){
        visite[s] = 0;
    }

    int s = sd;
    int nbSomVisite = 0;
    int finParcours = 0;

    // Phase de traitement
    while(finParcours == 0){
        reParcoursProfondeurMatAdj(s,visite,g,&nbSomVisite);
        if(nbSomVisite < n){
            s = somSuivant(s,n,visite);
        }else{
            finParcours = 1;
        }

    }
}
int prochainSuccesseurdeU(int *col, MatAdj g, int ligne ){
    for(*col; (*col)<g.nbSommets;(*col)++){
        printf("donnee de g[%d][%d] = %d",ligne,*col,g.mat[ligne][(*col)]);
        if(g.mat[ligne][(*col)]){
            goto fincorrecte; 
        }
    }
    return (*col)<g.nbSommets;
    fincorrecte:
        return 1; 
}
void itParcoursLargeurMatAdj(int s, int *visite, MatAdj g, int *nbSomVisite){
int n;
    File f = initFile();
    f= enfiler(s,f);
    n=g.nbSommets;
    while(!estVideFile(f)){
        int u = SommetFile(f);
        f = defiler(f);
        printf("u = %d\n", u+1);
        if(visite[u]==0){
            visite[u]=1;            
            (*nbSomVisite)++;
            int t=0;
            for(t=0; t<n; t++){
                if(g.mat[u][t] && !visite[t]){
                    f=enfiler(t,f);
                }
            }
            }
        }
}

void parcoursLargeurMatAdj(int sd, MatAdj g){
    // Phase d'initialisation
    int n = g.nbSommets;
    int *visite;
    visite = (int*)malloc(sizeof(int)*n);
    for(int s = 0; s < n; s++){
        visite[s] = 0;
    }
    
    int s = sd;
    int nbSomVisite = 0;
    int finParcours = 0;
    
    // Phase de traitement
    while(finParcours == 0){
        itParcoursLargeurMatAdj(s,visite,g,&nbSomVisite);
        if(nbSomVisite < n){
            s = somSuivant(s,n,visite);
        }else{
            finParcours = 1;
        }
    }
}



MatAdj creerMatAdjFichier(FILE* fd){
int nbSommets, j , i, tmp; MatAdj res; int garbage;
    fscanf(fd,"\n#Description du graphe");
    fscanf(fd,"\nnbSom = %d", &nbSommets);
    res=creerMatriceAdjVide(nbSommets);
    while(fscanf(fd, "\nArc%d : Pred = %d Succ = %d",&garbage,&j, &i)>0){
        i--;j--;
        // res.mat[i][j]=1;
        res.mat[j][i]=1;
    }
    parcoursLargeurMatAdj(0, res);
    return res;
}

int main(void){
    FILE* fd;
    if((fd=fopen("adjacence.txt","r"))==NULL)
        return 1;
    MatAdj test= creerMatAdjFichier(fd);
    fclose(fd);
    afficheMatAdj(test);
    return 0;
}