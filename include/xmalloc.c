#include <stdio.h>
#include <stdlib.h>

void *xmalloc(int l) {
  /* Cette fonction fait comme malloc sauf qu'elle termine le programme en cas
     d'erreur */
  void *p;
  
  p = malloc(l);
  if (p == NULL) {
    fprintf(stderr,"Pb d'allocation mémoire ...\n");
    exit(1);
  }
  return p;
}

