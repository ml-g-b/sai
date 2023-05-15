#ifndef AFFICHAGE_H
#define AFFICHAGE_H

/****************************************************************************/
/*******************   fichier affichage.h **********************************/
/****************************************************************************/
/* 
 Vous n'avez pas besoin d'utiliser directement ces fonctions ni donc de lire 
 ce fichier. 

 On peut fixer la couleur du texte et du fond dans un terminal avec des
 séquences de caratères spéciales. Je vous fournis ici des fonctions pour 
 le faire simplement (pour voir les séquences, cf. affichage.c).
 https://en.wikipedia.org/wiki/ANSI_escape_code

 L'affichage (avec printf(...)) se fait à partir de la position
 courante du curseur. On peut deplacer celui-ci avec les fonctions goto_*
*/

int coul_rvb(int r, int v, int b);
// valeurs r,v et b entre 0 et 5 (valeurs de rouge, vert et bleu)
// renvoie le numero de la couleur du triplet r,v,b.
// Ce numéro de couleur peut être utilisé ensuite dans les fonctions couleur_fond et couleur_texte.

int coul_gris(int n);
// niveau de gris n entre 0 (noir)  et 23 (blanc)
// renvoie le numero de la couleur du niveau de gris n.

void couleur_fond(int coul);
/* fixe la couleur de fond : coul entre 0 et 255; 
   on peut utiliser les fonctions coul_rvb et coul_gris pour calculer la
   valeur coul correspondant à un triplet r,v,b ou un niveau de gris voulu */

void couleur_texte(int coul);
/* fixe la couleur du texte : coul entre 0 et 255 */

void reset_couleurs();
/* remet les couleurs de texte et de fond par defaut*/

void efface_ecran();
  /* efface l'ecran du terminal */

void goto_haut_gauche();
  /* place le curseur dans le coin supérieur gauche du terminal */ 

void goto_xy(int x, int y);
  /* place le curseur ligne x colonne y dans le terminal */

void goto_up(int x);
/* deplace le curseur x lignes vers le haut */

void goto_down(int x); 
/* deplace le curseur x lignes vers le bas */

void goto_forward(int x); 
/* deplace le curseur x colonnes vers la droite */

void goto_backward(int x);
/* deplace le curseur x colonnes vers la gauche */

void save_cursor_pos();

void restore_cursor_pos();

/************************************************************************/
/*********** pour l'affichage du graphe sur le labyrinthe ***************/
/************************************************************************/

#define NORD  1
#define EST   2
#define SUD   4
#define OUEST 8


void affiche_symbole(int numero_symbole);
/* pour afficher le symbole dont l'indice est numero_symbole dans la
   table (cf ci-dessous). Cette fonction est utilisée pour dessiner 
   le graphe.
*/

/* Pour calculer le numero_symbole, on utilise les pseudo constantes
   NORD = 1, EST = 2, SUD = 4 et OUEST = 8. 

   Par ex, pour obtenir le numéro du symbole avec un
   trait vers le SUD le NORD et l'OUEST : 
   numero_symbole = NORD + SUD + OUEST = 1 + 4 + 8 = 13.

   L'appel affiche_symbole(13) affichera alors le symbole correspondant
   (cf la table ci-dessous).
   

  (Ouest, Sud, Est, Nord) : numero de symbole en binaire
   |
   |   numero de symbole en decimal
   |   |
  OSEN |   resultat de affiche_symbole(numero_symbole)
  0000 0   |
                  calcul du numéro de symbole :   
  0001 1   │     NORD 

  0010 2   ─     EST

  0011 3   └     NORD + EST
 
  0100 4   │     SUD

  0101 5   │     SUD + NORD

  0110 6   ┌     SUD + EST

  0111 7   ├     SUD + EST + NORD

  1000 8   ─     ....

  1001 9   ┘  

  1010 10  ─ 

  1011 11  ┴

  1100 12  ┐

  1101 13  ┤

  1110 14  ┬

  1111 15  ┼

*/
#endif
