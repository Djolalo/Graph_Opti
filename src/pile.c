#include "../include/pile.h"

Pile suivant(Pile p){
    return p->suivant;
}

bool estVidePile(Pile p){
    if(p == NULL){
        return 1;
    }else{
        return 0;
    }
}

Pile allocMemRempPile(TElement elt){
Pile pp;

    pp = (Pile)malloc(sizeof(Pile));
    pp->elt = elt;
    pp->suivant = NULL;
    return pp;
}

Pile empiler(Pile p, TElement elt){
Pile pp;

    pp = allocMemRempPile(elt);
    pp->suivant = p;
    p = pp;
    return p;
}

Pile depiler(Pile p){
Pile as;

    as = p;
    p = suivant(p);
    free(as);
    return p;
}

int sommetPile(Pile p){
    return p->elt;
}

void affichePile(Pile p){
    if(!estVidePile(p)){
        do{
            printf("%d",p->elt);
            p = suivant(p);
            if(estVidePile(p)){
                printf("\n");
            }else{
                printf(",");
            }
        }while(!estVidePile(p));
    }
}