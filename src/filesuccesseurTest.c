#include <stdio.h>
#include <stdlib.h>
#include "../include/fileSucc.h"

int main(void){
    FILE *fd;
    if((fd = fopen("fs.txt","r")) == NULL){
        return 1;
    }
    FileSucc res;
    res = creerFileSuccFichier(fd);
    affichetab(res.fs,res.nbArcs+1);
    affichetab(res.aps, res.nbSom+1);
    fclose(fd);
}