#include "../include/tabs.h"

void affichetab(int *tab, int nb){
    for(int i = 0; i < nb;i++){
        printf("%d|",tab[i]);
    }puts("");
}