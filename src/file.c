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
int SommetFile(File f){ File tmp = dernier(f); return tmp->donnee;}

void afficheFile(File f){
    if(!estVideFile(f)){
        do{
            printf("%d",f->donnee);
            f = suivant(f);
            if(estVideFile(f)){
                printf("\n");
            }else{
                printf(",");
            }
        }while(!estVideFile(f));
    }
}
