#ifndef LABY_H
#define LABY_H
#include <stdio.h>
#include <stdlib.h>

/* ****************************************************************/
/********************* Type Tlaby *******************************/
/* ****************************************************************/

/* Valeurs possibles pour les cases du tableau matrice */
#define PLEIN 0    /* mur */
#define VIDE  1    /* case vide dans laquelle on peut se déplacer */
#define BORDER 2
#define MARK 3 


typedef struct laby{
  /* - Les cases sont numérotés à partir de 1 (et pas 0). 
     - larg et haut sont la largeur et la hauteur totale du labyrinthe, y
     compris la premiere et derniere ligne et la premiere et derniere
     colonne dont toutes les cases valent PLEIN. La taille "utile" de la
     matrice est donc (larg-2) colonnes et (haut-2) lignes */
  int larg; /* largeur matrice */
  int haut; /* hauteur matrice */
  int fin; /* numero du sommet à atteindre */
  int *matrice; /* Matrice à une dimension contenant le labyrinthe. */
} Tlaby;


Tlaby *genere_laby_aleatoire(double p, int l, int h);
/* Genere et retourne un labyrinthe aléatoire */

Tlaby *lecture_laby(FILE *f);
/* Lit un labyrinthe dans le fichier f et renvoie le labyrinthe qui
   le represente. */

/* **************************************************** */
/* **************** Affichage ************************* */
/* **************************************************** */

/* Couleurs utilisées pour l'affichage */
#define COUL_BLANC coul_gris(23)
#define COUL_GRIS coul_gris(18)
//coul_rvb(2,2,3) 
#define COUL_NOIR coul_gris(10)
//coul_gris(3)
#define COUL_CHEMIN coul_rvb(5,0,3)
#define COUL_PLEIN coul_rvb(3,2,1)

void afficher_laby(Tlaby *l);
void glutLaby(Tlaby *,int,int,int,int,int);
int direction(Tlaby *,int,int,int);

#endif
