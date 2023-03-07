#include "../include/MatAdj.h"

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
int estVideMatAdj(MatAdj g){
    for(int i =0; i<g.nbSommets; i++){
        for(int j=0; j<g.nbSommets; j++){
            if(g.mat[i][j]==1){
                return 0;
            }
        }
    }
    return 1;
}
void afficheMatAdj(MatAdj g){
    for(int i=0; i<g.nbSommets;i++){
        for(int j=0; j<g.nbSommets;j++)printf("%d", g.mat[i][j]);
        puts("");
    }
}

int somSuivant(int s , int n , int *visite){
    while( s < n && visite[s]){
        s++;
    }
    return s; 
}

void reParcoursProfondeurMatAdj(int s, int *visite, MatAdj g, int *nbSomVisite){
    visite[s] = 1;
    int j;
    printf("Sommet = %d\n",s+1);
    affichetab(visite,g.nbSommets);
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
        //On visite tous les successeurs de u.
        if(visite[u]==0){
            visite[u]=1;            
            (*nbSomVisite)++;
            int t=0;
            for(t=0; t<n; t++){
                if(g.mat[u][t] && !visite[t] && !estPresent(t,f)){
                    f=enfiler(t,f);
                }
            }
            afficheFile(f);
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
    fseek(fd,SEEK_SET,0);
    fscanf(fd,"\n#Description du graphe");
    fscanf(fd,"\nnbSom = %d", &nbSommets);
    res=creerMatriceAdjVide(nbSommets);
    while(fscanf(fd, "\nArc%d : Pred = %d Succ = %d",&garbage,&j, &i)>0){
        i--;j--;
        /**
         * la ligne est à décommenter dans le cas d'un graphe orienté.
         * */// res.mat[i][j]=1;
        res.mat[j][i]=1;
    }
    parcoursLargeurMatAdj(0, res);
    return res;
}

int estSansBoucle(MatAdj g){
    int n; int j=0; int i=0;
    n = g.nbSommets;
    while((i<n) && (!g.mat[i][i])){printf("la matrice a cette case %d\n",g.mat[i][i]);i++;};
    return i==n;
}

MatAdj reParcoursProfondeurMatAdjConnexes(int s, int *visite, MatAdj g,MatAdj *ger ,int *nbSomVisite){
    visite[s] = 1;
    int j;
    printf("Sommet = %d\n",s+1);
    affichetab(visite,g.nbSommets);
    (*nbSomVisite)++;
    for(int t = 0; t < g.nbSommets; t++){
        if(visite[t] == 0 && g.mat[s][t] == 1){
            if(ger==NULL){
                ger=malloc(sizeof(MatAdj));
                *(ger)= creerMatriceAdjVide(g.nbSommets);
                ger->mat[s][t]=1;
                *(ger)= reParcoursProfondeurMatAdjConnexes(t,visite,g,ger ,nbSomVisite);
            }
            else{
                ger->mat[s][t]=1;
                *(ger) =reParcoursProfondeurMatAdjConnexes(t,visite,g,ger,nbSomVisite);
            }
        }
        if(visite[t] ==1 && g.mat[s][t]==1 && s==t){
            if(ger==NULL){
                ger=malloc(sizeof(MatAdj));
                *(ger)= creerMatriceAdjVide(g.nbSommets);
                ger->mat[s][t]=1;
            }
            else{
                ger->mat[s][t]=1;
            }
        }
    }
    if(ger == NULL){ 
        ger = malloc(sizeof(MatAdj)), 
        (*ger)=creerMatriceAdjVide(g.nbSommets);
    }
    return *ger;
}

void determinerComposantesConnexes(int sd, MatAdj g){

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
    int *pereConnexes=malloc(sizeof(int)*n);
    MatAdj *ret= malloc(n*sizeof(MatAdj));
    for(int i =0; i<n;i++){
        ret[i]= creerMatriceAdjVide(n);
    } int i =0;
    for(int z = 0 ;z<n;z++){
        pereConnexes[z] = 0;
    }
    // Phase de traitement
    while(finParcours == 0){
        ret[i]=reParcoursProfondeurMatAdjConnexes(s,visite,g,NULL,&nbSomVisite);        
        pereConnexes[i]=1;
        if(nbSomVisite < n){
            s = somSuivant(s,n,visite);
            i = s;
        }else{
            finParcours = 1;
        }
    }
    for(int i =0; i<n;i++){
        (pereConnexes[i])?printf("le %d eme sommet forme une composante connexe que voici\n",i+1),afficheMatAdj(ret[i]):printf("le %d eme sommet ne forme pas de composante fortement connexe partant de lui\n",i+1);
    }
}