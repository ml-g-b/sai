#ifndef GRAPHE_TLA
#define GRAPHE_TLA
#include "liste.h"

typedef struct tgraphe Tgraphe;

/* ********************************************************* */
/*           Opérations de base sur les graphes              */
/* ********************************************************* */

Tgraphe *creer_graphe(int n); 
/* Retourne un graphe à n sommets et sans arc.
   Les sommets sont numérotés de 1 à n. */


void detruit_graphe(Tgraphe *g);
/* Detruit le graphe et libère la mémoire utilisée */

int ajoute_arc(int origine, int extremite, Tgraphe *G);
/* Rajoute l'arc (origine, extremité) au graphe G.
   Cette fonction retourne 0 si l'un des sommets origine ou extremité
   n'est pas dans le graphe (i.e., n'est pas entre 1 et n).*/

int nb_sommets(Tgraphe *G);
/* Renvoie le nombre de sommets du graphe.*/

iterateur_l *liste_succ(int s, Tgraphe *g) ;
/* Retourne un itérateur sur la liste des successeurs de s. Pour des
 * exemples d'utilisation des itérateurs, voir le fichier liste.h. */


/* *********************************************************** */
/*          Entrées / Sorties                                  */
/************************************************************* */

void afficheTLA(Tgraphe *G);
/* affiche le TLA du graphe G */

Tgraphe *lire_graphe(void);
/* Renvoie le graphe lu sur l'entree standard.
   Le graphe est dans le format utilisé dans les tp 1 et 2 :
   1ere ligne : nb de sommets
   2e ligne : nb d'arcs
   lignes suivantes arcs (a,b) sous la forme : a b */


#endif
