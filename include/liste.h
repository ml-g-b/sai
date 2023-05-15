#ifndef LISTES_H
#define LISTES_H

/****************************************************************************/
/*******************   fichier liste.h  *************************************/
/****************************************************************************/

/* Listes de type FIFO ou LIFO.
   Pour une liste LIFO (pile), utiliser empile et depile 
   Pour une liste FIFO (file d'attente), utiliser enfile et defile
    rmq : depile et defile font la même chose.
*/

/* Le type des listes est "Liste" *********************/
typedef struct liste Liste;

Liste *creer_liste_vide();
/* Renvoie un pointeur sur une liste vide */

void detruit_liste(Liste *l);
/* Detruit la liste et libere la memoire utilisé par la liste */
/* Cette fonction doit être appelée à chaque fois qu'une liste 
   n'est plus utilisée */

int est_vide(Liste *l);
/* Renvoie vrai si la liste l est vide */

void enfile(int sommet, Liste *l);
/* Ajoute le sommet à la fin de la liste l (FIFO) */
/* La liste l passé en paramètre est donc modifiée */

void empile(int sommet, Liste *l);
/* Ajoute le sommet au début de la liste l */
/* La liste l passé en paramètre est donc modifiée */

int defile(Liste *l);
/* Retire le premier sommet de la liste l et le renvoie */ 
/* La liste l passé en paramètre est donc modifiée */
/* Appeler defile sur une liste vide plante probablement */

int depile(Liste *l);
/* idem defile */

int taille(Liste *l);
/* Retourne le nombre d'éléments de la liste */


/************************* entrée/sorties ***************************/

void affiche_liste(Liste *l);
  /* affiche la liste passée en paramètre */


/* ************** Iterateurs sur les listes  ********************/

typedef struct element iterateur_l;

/* Un itérateur est un pointeur sur un élément d'une liste. Il peut
   également pointer sur la fin de liste.
   par ex:
   < 2, 5, 6, 2, 3>
     ^
   Ici l'itérateur (représenté par le ^, pointe sur l'element 2.

   Pour creer un itérateur sur une liste existante, utiliser init_it().

   Pour récuperer l'élément pointé (dans l'exemple ci-dessus, 2), il
   faut utiliser la fonction element_it().

   On peut faire avancer l'itérateur dans la liste avec la fonction
   suivant_it() et on peut tester si l'itérateur est arrivé à la fin
   de la liste avec fini_it().

   Par exemple, avec l = < 2, 5, 6, 2, 3 >
   mon_it = init_it(l) 
   donne :
   < 2, 5, 6, 2, 3 >
     ^
   ensuite, 
   mon_it = suivant_it(mon_it)
   donne :
   < 2, 5, 6, 2, 3 >
        ^
   Et du coup:
   element_it(mon_it) 
   retournera la valeur 5.
   
   la suite d'opérations:
   mon_it = suivant_it(mon_it)
   mon_it = suivant_it(mon_it)
   mon_it = suivant_it(mon_it)
   mon_it = suivant_it(mon_it)
   donnera 
   < 2, 5, 6, 2, 3 >
                   ^
   L'itérateur est arrivé à la fin de la liste.
   et du coup fini_it(mon_it) retournera vrai.

 */

iterateur_l *init_it(Liste *l);
/* Retourne un iterateur sur le 1er élément de la liste */
/* Si la liste est vide, l'itérateur est sur la fin de la liste. */
/* Plante probablement si l n'est pas une liste (ou pas initialisée) */

iterateur_l *suivant_it(iterateur_l *it);
/* Retourne un iterateur sur l'élément suivant celui pointé par it*/
/* Plante probablement si it n'est n'est pas initialisé ou est arrivé à la
 fin de la liste */

int element_it(iterateur_l *it);
/* retourne l'élément pointé par l'iterateur */
/* Plante probablement si it n'est n'est pas initialisé ou est arrivé à la
 fin de la liste */

void modif_element_it(iterateur_l *it, int v);
// Vous n'avez par besoin de cette fonction. ne pas utiliser.

int fini_it(iterateur_l *it);
/* retourne vrai si l'iterateur est arrivé à la fin de la liste */
/* Plante probablement si it n'est n'est pas initialisé */



#endif
