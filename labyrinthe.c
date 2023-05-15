/*

 CREATION : 

 SUBJECT :

*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "include/laby.h"

int main(int argc, char **argv){
    int l=5, h=10;
    Tlaby *labyrinthe;
    FILE *f=fopen("tp5/ex_labys/laby1.txt","r");
    srand(time(NULL));
    labyrinthe=lecture_laby(f);
    afficher_laby(labyrinthe);
    fclose(f);
    glutLaby(labyrinthe,0,0,0,5,10);
    exit(EXIT_SUCCESS);
}
 