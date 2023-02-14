/**
 * DOC ICI
 * 
 * @author
 * @version
 * @since 
*/
#ifndef __PILE__
#define __PILE__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int TElement;

typedef struct pile {
    TElement elt;
    struct pile *suivant;
}*Pile;

Pile suivant(Pile p);

bool estVidePile(Pile p);

Pile allocMemRempPile(TElement elt);

Pile empiler(Pile p, TElement elt);

Pile depiler(Pile p);

int sommetPile(Pile p);

void affichePile(Pile p);

#endif