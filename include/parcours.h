#ifndef PARCOURS_H 
#define PARCOURS_H

/****************************************************************************/
/*******************   fichier parcours.h ***********************************/
/****************************************************************************/

/* valeurs possibles dans le tableau couleur */
#define BLANC 1
#define GRIS 2
#define NOIR 3
#define CHEMIN 4 /* pour marquer les cases du chemin trouvé par l'algorithme 
		    (fonction trace_chemin) */

/* types d'algos possibles (dans le champ "algo")*/
#define PROFONDEUR     1
#define RECURSIF       2
#define LARGEUR        3

typedef struct parcours{
  /* Les sommets sont numérotés à partir de 1 */
  int nb_sommets;/* nb de sommets du graphe */
  int nb_sommets_explores; /* nb de sommets explores */
  int * couleur; /* à initialiser à BLANC */
  int * pere;    /* initialiser  pere[racine] à 0 */
  int algo;      /* type d'algo à utiliser pour le parcours (cf plus haut) */
  int animation; /* 0 : pas d'animation du parcours. */
                 /* 1 : animation : votre fonction  doit redessiner
		    le labyrinthe à chaque modification dans le tableau couleur[] */
  int attente;   /* Lors d'une animation du parcours :*/
                 /* 0  : pas d'attente avant de redessiner le graphe;*/
                 /* > 0 : temps d'attente en ms avant de redessiner (pour
		    l'attente, utiliser la fonction milli_sleep() definie
		    dans labyrinthe.c) */
  int dessine;   /* 1 : dessiner le graphe lors de l'affichage de la matrice */
} Tparcours;


Tparcours *creer_parcours_vide(int nb);
/* Alloue la memoire pour stocker les tableaux couleur et pere.
   Le parametre nb doit etre le nombre de sommets du graphe.
   Initialise couleur à BLANC.
   Initialise nb_sommets à nb.
   Initialise nb_sommets_explores à 0.
   fonction appelée dans main()
*/


#endif
