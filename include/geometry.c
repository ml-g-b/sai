#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"geometry.h"
#include"../MACRO_function.h"

vecteur Vecteur(double x, double y, double pas){
    vecteur v=(vecteur)malloc(sizeof(vecteur_struct));
    v->x=x;
    v->y=y;
    v->pas=pas;
    return v;
}

vecteur Vecteur_COPY(vecteur vi){
    vecteur v=(vecteur)malloc(sizeof(vecteur_struct));
    v->x=vi->x;
    v->y=vi->y;
    v->pas=vi->pas;
    return v;
}

vecteur applyAngle(double teta, vecteur v){
    v->x=cos(teta)*v->pas;
    v->y=sin(teta)*v->pas;
    printf(">>> %f ",v->pas);
    printVecteur(v);
    return v;
}
 
void printVecteur(vecteur v){
    printf("Vecteur:{x=%f ; y=%f ; pas=%f}\n",v->x,v->y,v->pas);
}


personnage Personnage(double x, double y, double z){
    personnage p=(personnage)malloc(sizeof(personnage_struct));
    p->x=x;
    p->y=y;
    p->z=z;
    p->v=Vecteur(0,0,0);
    p->teta=0;
    return p;
}

void sens(personnage p, unsigned int dir, double *vx, double *vy){
    switch(dir){
    case 1: // UP
        *vx=p->v->x*cos(p->teta+M_PI/(double)2);
        *vy=p->v->y*sin(p->teta+M_PI/(double)2);
        break;
    case 3: // DOWN
        *vx=-p->v->x*cos(p->teta+M_PI/(double)2);
        *vy=-p->v->y*sin(p->teta+M_PI/(double)2);
        break;
    case 2: // RIGHT
        *vx=p->v->x*cos(p->teta);
        *vy=p->v->y*sin(p->teta);
        break;
    case 0: // LEFT
        *vx=p->v->x*cos(p->teta+M_PI);
        *vy=p->v->y*sin(p->teta+M_PI);
        break;
    }
}

personnage avancer(personnage p, unsigned int dir){
    double vx, vy;
    sens(p, dir, &vx, &vy);
    p->x=p->x+vx;
    p->y=p->y+vy;
    return p;
}
/*
personnage avancer(personnage p){
    vecteur v=p->v;
    p->x=v->x*cos(p->teta+M_PI/(double)2)+p->x;
    p->y=v->y*sin(p->teta+M_PI/(double)2)+p->y;
    p->v=v;
    return p;
}

personnage droite(personnage p){
    vecteur v=p->v;
    p->x=v->y*sin(p->teta+M_PI/(double)2)+p->x;
    p->y=v->x*cos(p->teta+M_PI/(double)2)+p->y;
    p->v=v;
    return p;
}

personnage gauche(personnage p){
    vecteur v=p->v;
    p->x=-v->y*sin(p->teta+M_PI/(double)2)+p->x;
    p->y=v->x*cos(p->teta+M_PI/(double)2)+p->y;
    p->v=v;
    return p;
}

personnage reculer(personnage p){
    vecteur v=p->v;
    p->x=p->x+v->x*cos(p->teta+M_PI/(double)2);
    p->y=p->y-v->y*sin(p->teta+M_PI/(double)2);
    p->v=v;
    return p;
}
*/
void printPersonnage(personnage p){
    printf("Coordonnées(%f,%f,%f):\n\t",p->x,p->y,p->z);
    printVecteur(p->v);
}

personnage changerVecteur(vecteur v, personnage p){
    p->v->x=v->x;
    p->v->y=v->y;
    p->v->pas=v->pas;
    return p;
}

void freePersonnage(personnage p){
    free(p->v);
    free(p);
}

intervalle Intervalle(double a, double b){
    intervalle I=(intervalle)malloc(sizeof(intervalle_struct));
    I->min=F_MIN(a,b);
    I->max=F_MAX(a,b);
    return I;
}

int estDans(double e, intervalle I){
    return (e>=I->min) && (e<=I->max);
}