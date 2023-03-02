#include "../include/liste.h"

int estVide(Liste l){
    return l == NULL;
}

Liste allocRempMemCellListe(int elt){
Liste f;

    f = malloc(sizeof(Liste));
    f->sommet = elt;
    f->suiv = NULL;
    return f;
}

Liste dernierListe(Liste f){
    
    if(estVide(f)) return NULL;
    while(!estVide(f->suiv)){
        f=f->suiv;
    }
    return f;
}

Liste inserQueue(Liste l, int sommet){
    if(estVide(l)){
        Liste ff;

        ff = allocRempMemCellListe(sommet);
        return ff;
    }else{
        Liste tmp= dernierListe(l);
        Liste temp = allocRempMemCellListe(sommet);
        tmp->suiv = temp;
        return l;
    }
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