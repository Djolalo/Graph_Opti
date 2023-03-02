#ifndef __FILESUCC_H_
#define __FILESUCC_H_

#include <stdio.h>
#include <stdlib.h>
#include "tabs.h"

typedef struct{
    int nbSom;
    int nbArcs; 
    int *fs;
    int *aps;
}FileSucc;

FileSucc creerFileSuccVide(int t, int a);

FileSucc creerFileSuccFichier(FILE *fd);

#endif