#include "../include/file.h"

File initFile(){
    return NULL;
}

File allocRempMemCell(int elt){
File f;

    f = (File)malloc(sizeof(File));
    f->donnee = elt;
    f->suivant = initFile();
    return f;
}

File suivant(File f){
    return f->suivant;
}

int estVideFile(File f){
    if(f == NULL){
        return 1;
    }else{
        return 0;
    }
}
File dernier(File f){
    
    if(estVideFile(f)) return NULL;
    while(!estVideFile(suivant(f))){
        f=suivant(f);
    }
    return f;
}
File enfiler(int elt, File f){
    if(estVideFile(f)){
        File ff;

        ff = allocRempMemCell(elt);
        return ff;
    }else{
        File tmp= dernier(f);
        File temp = allocRempMemCell(elt);
        tmp->suivant = temp;
        return f;
    }
}

File defiler(File f){
File as;

    as = f;
    f = suivant(f);
    free(as);
    return f;
}
//returns queue first in or -1 in case of errors
int SommetFile(File f){ return (f==NULL)? -1: f->donnee;}

void afficheFile(File f){
    if(!estVideFile(f)){
        do{
            printf("%d",f->donnee+1);
            f = suivant(f);
            if(estVideFile(f)){
                printf("\n");
            }else{
                printf(",");
            }
        }while(!estVideFile(f));
    }
}
int estPresent(int chercher,File f){if(!estVideFile(f)) do{ if(f->donnee == chercher) return 1; f=f->suivant; }while(!estVideFile(f));return 0;}
