#ifndef __FILE_H_
#define __FILE_H_

#include <stdio.h>
#include <stdlib.h>


typedef struct cellule{
    int donnee;
    struct cellule *suivant;
}*File;

File initFile();

File suivant(File f);

int estVideFile(File f);

File allocRempMemCell(int elt);

File dernier(File f);

File defiler(File f);


File enfiler(int elt, File f);


int SommetFile(File f);
void afficheFile(File f);
int estPresent(int chercher,File f);
#endif