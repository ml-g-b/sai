#include"collision.h"

int est_dans_l_intervalle(double x, double i1, double i2){
    return x>= i1 && x<= i2;
}

/* int intersectionPave(double ox1, double oy1, double oz1, double ox2, double oy2, double oz2, double px1, double py1, double pz1, double px2, double py2, double pz2){ */
/*     if(isk() */
/* } */


// Un pan du mur est modélisé par mx my et mz de base carré size x size 
int intersectionMurPersonnage(double mx, double my, double mz, double size, double px, double py, double pz, double psize){
    return (est_dans_l_intervalle(px,mx,mx+size)) && (est_dans_l_intervalle(py,my,my+size)) && (est_dans_l_intervalle(pz,0,mz));
}