
#include "xmalloc.h"
#include "liste.h"
#include "affichage.h"
#include "parcours.h"
#include "graphe_TLA.h"
#include "laby.h"

/* ****************************************************************/
/* ********************** fonctions de base  **********************/
/* ****************************************************************/

Tlaby *creer_laby_vide(int largeur, int hauteur) {
  /* Alloue la memoire pour stocker le labyrinthe. 
     Ne fait aucune initialisation. */
  Tlaby *l;

  l = (Tlaby *) xmalloc(sizeof(struct laby));
  l->matrice = (int *) xmalloc((hauteur * largeur + 1) * sizeof(int));
  return l;
}


Tlaby *genere_laby_aleatoire(double p, int l, int h) {
  /* Retourne un labyrinthe aléatoire */
  Tlaby *laby;
  int col, ligne;
  int i;

  if ((h < 3) || (l < 3)) {
    fprintf(stderr, "La largeur et la hauteur doivent etre superieures à 3 l: %d h: %d\n", l, h);
    exit(2);
  }
  /* Allocation de la mémoire pour stocker le graphe */
  laby = creer_laby_vide(l,h);
  /* Remplissage des champs de la structure laby */
  laby->larg = l;
  laby->haut = h;
  /* *********** remplissage de la matrice **************** */
  for (i = 1; i <= l; i++) /* ligne 1 */
    laby->matrice[i] = PLEIN;
  for (i = l+1; i <= (h-1)*l; i++)   /* lignes 2 à h-1 */
    if (i%l == 0 || i%l == 1) /* colonne 1 et l */
      laby->matrice[i] = PLEIN;
    else
      if (p > (double)random()/RAND_MAX) 
	laby->matrice[i] = VIDE;
      else
	laby->matrice[i] = PLEIN;
  for (i = (h-1)*l+1; i <= h*l; i++) /* ligne h */
    laby->matrice[i] = PLEIN;
  
  laby->matrice[l+2] = VIDE; /* La case de départ est mise à VIDE */
  
  /* tirage de la case d'arrivée */
  col = (int) ((double) random()/RAND_MAX*0.999999*(l-2)+2);
  ligne = (int) ((double) random()/RAND_MAX*0.999999*(h-2)+2);
  laby->fin = (ligne-1) * l + col;
  laby->matrice[(ligne-1) * l + col] = VIDE; /* La case d'arrivée est mise à VIDE */
  return laby;
}

Tlaby *lecture_laby(FILE *f){
  /* Lit un labyrinthe dans le fichier f et le renvoie. */
  Tlaby *laby;
  int i, j, numero_sommet, caractere_lu, largeur, hauteur;

  int nb = fscanf(f, "%d %d", &hauteur, &largeur);
  if (nb != 2) {
    fprintf(stderr, "Le labyrinthe d'entrée n'est pas au bon format : manque hauteur et/ou largeur\n");
    exit(2);
  }
  getc(f); /* pour consommer le \n à la fin de la 1ere ligne*/

  laby = creer_laby_vide(hauteur,largeur);
  laby->larg = largeur;
  laby->haut = hauteur;
  numero_sommet = 1;
  for (j = 1; j <= laby->haut; j++) {
    for (i = 1; i <= laby->larg; i++) {
      caractere_lu = getc(f);
      switch (caractere_lu) {
	case 'X':
	  laby->fin = numero_sommet;
          break;
	case ' ':
	  laby->matrice[numero_sommet] = VIDE;
	  break;
	case '#':
	  laby->matrice[numero_sommet] = PLEIN;
	  break;
      case '+':
          laby->matrice[numero_sommet] = BORDER;
	  break;
	default:
          fprintf(stderr,
                  "Erreur dans le laby (l: %d, c:%d) : caractere %c invalide\n",
                  j, i, caractere_lu);
          exit(2);
      }
      numero_sommet++;
    }
    getc(f); /* consomme le \n à la fin de la ligne */
  }
  return laby;
}

void afficher_laby(Tlaby *l){
    int i, j;
    for(i=0 ; i<l->haut ; i++){
        for(j=0 ; j<=l->larg ; j++){
            printf("%s ",(l->matrice[i*l->larg+j]==VIDE) ? "\033[40m" : "\033[103m");
        }
        printf("\033[0m\n");
    }
}

void glutLaby(Tlaby *l, int x, int y, int z, int size, int height){
    int i, j;
    for(i=0 ; i<l->haut ; i++){
        for(j=0 ; j<=l->larg ; j++){
            int n=l->matrice[i*l->larg+j];
            if(n==PLEIN){
                int x1=x+j*size;
                int x2=x1+size;
                int p=(l->haut-1-i);
                int y1=y+p*size;
                int y2=y1+size;
                int z1=z;
                int z2=height+z;
                printf("(%d,%d,%d)->(%d,%d,%d)\n",x1,y1,z1,x2,y2,z2);
            }
        }
    }
}

void display(Tlaby *l){
    int h=l->haut, w=l->larg, i, j;
    for(i=0 ; i<h ; i++){
        for(j=1 ; j<=w ; j++){
            printf("case(%d,%d)=%d\n",i,j,l->matrice[i*h+j]);
        }
    }
}

int direction(Tlaby *l, int d, int x, int y){
    int h=l->haut, w=l->larg, value=-1;
    if(x<=0 || x>=h || y<=0 || y>w)
        return -1;
    switch(d){
    case 'l':
        value=l->matrice[(x-1)*h+y];
        break;
    case 'r':
        value=l->matrice[(x+1)*h+y];
        break;
    case 'u':
        value=l->matrice[(y+1)+x*h];
        break;
    case 'd':
        value=l->matrice[(y-1)+x*h];
        break;
    default:
        value=-1;
    }
    return (value==VIDE) ? 0 : 1;
}