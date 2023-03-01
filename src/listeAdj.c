#include <stdio.h>
#include <stdlib.h>

typedef struct cellule{
    int sommet;
    struct cellule *suiv;
}*Liste;

typedef struct{
    int nbSom;
    Liste *tabAdj;
}ListeAdj;

int estVide(Liste l){
    return l == NULL;
}
Liste allocRempMemCell(int elt){
Liste f;

    f = malloc(sizeof(Liste));
    f->sommet = elt;
    f->suiv = NULL;
    return f;
}
Liste dernier(Liste f){
    
    if(estVide(f)) return NULL;
    while(!estVide(f->suiv)){
        f=f->suiv;
    }
    return f;
}
Liste inserQueue(Liste l, int sommet){
    if(estVide(l)){
        Liste ff;

        ff = allocRempMemCell(sommet);
        puts("insertion en tete");
        return ff;
    }else{
        Liste tmp= dernier(l);
        Liste temp = allocRempMemCell(sommet);
        tmp->suiv = temp;
        puts("insertion en queue reussie");
        return l;
    }
}
ListeAdj creerListeAdjVide(int nbSom){
    ListeAdj ret; 
    ret.tabAdj = malloc(sizeof(Liste)*nbSom);
    ret.nbSom = nbSom;
    for(int i = 0; i < nbSom; i++){
        ret.tabAdj[i] = NULL;
    }
    return ret;
}
void afficheListe(Liste p){
    if(estVide(p)){
    puts("liste vide");
    return;
    }
        do{
            printf("%d",p->sommet);
            p = p->suiv;
            if(estVide(p)){
                printf("\n");
            }else{
                printf(",");
            }
        }while(!estVide(p));
}
ListeAdj creerListeAdjFichier(FILE *fd){
int nbSommets; ListeAdj res; int i; int j; int garbage;
    fscanf(fd,"\n#Description du graphe");
    fscanf(fd,"\nnbSom = %d", &nbSommets);
    res = creerListeAdjVide(nbSommets);
    while(fscanf(fd, "\nArc%d : Pred = %d Succ = %d",&garbage, &j,&i) > 0){
        j--; 
        res.tabAdj[j]=inserQueue(res.tabAdj[j], i);
    }
    for(int z = 0; z<res.nbSom; z++){
        afficheListe(res.tabAdj[z]);
    }
    return res;
}

int main(){
    FILE* fd;
    if((fd=fopen("ls.txt","r"))==NULL)
        return 1;
    ListeAdj test = creerListeAdjFichier(fd);
    fclose(fd);
    return 0;
}
