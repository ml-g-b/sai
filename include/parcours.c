#include <stdlib.h>
#include "xmalloc.h"
#include "parcours.h"

Tparcours *creer_parcours_vide(int nb_sommets) {
  /* Alloue la memoire pour stocker les tableaux couleur et pere. 
     Initialise couleur à BLANC.
     Initialise p->nb_sommets, p->nb_sommets_explores. 
     fonction appelée dans main()
  */
  Tparcours *p;
  int i;

  p = (Tparcours *) xmalloc(sizeof(struct parcours));
  p->nb_sommets_explores = 0;
  p->nb_sommets = nb_sommets;
  p->algo = 0;
  p->animation = 0;
  p->attente = 0;
  p->couleur = (int *) xmalloc((nb_sommets + 1) * sizeof(int));
  p->pere = (int *) xmalloc((nb_sommets + 1) * sizeof(int));
  
  for (i=1; i<= p->nb_sommets; i++) {
    p->couleur[i] = BLANC;
  }

  return p;
}

