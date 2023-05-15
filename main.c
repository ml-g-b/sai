/*

 CREATION : 09/02/2023

 SUBJECT : TP1 : Synthèse et Animation d'Images -> Horloge avec GLUT

*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<time.h>
#include<errno.h>
#include<threads.h>
#include<signal.h>
#include<sys/resource.h>

#include"GL/gl.h"
#include"GL/glut.h"

#include"MACRO_function.h"
#include"include/laby.h"
#include"header/window.h"
#include"include/geometry.h"
#include"include/collision.h"


#define WIN_SIZE 800
#define DEMITAILLE 0.5
#define TAILLE 250

personnage perso;
int const coefficient_de_rotation = 4;
double rotation=M_PI/(double)coefficient_de_rotation;

double pj_x=EX, pj_y=EY, pj_z=EZ+1;

double ex=EX, ey=EY, ez=EZ;

int dx=1, dy=0, dz=0;
int prev_x=0, prev_y=0;


int n=0;
double size=0;

double deplacement=0.2;

// Labyrinthe

Tlaby *labyrinthe;

int iteration=0;

int nanosleep(const struct timespec *req, struct timespec *rem);
int msleep(long msec){
    struct timespec ts;
    int res;
    if(msec < 0){
        errno=EINVAL;
        return -1;
    }
    ts.tv_sec=msec/1000;
    ts.tv_nsec=(msec%1000) * 1000000;
    do{
        res=nanosleep(&ts,&ts);
    }
    while(res && errno==EINTR);
    return res;
}

void colorGlut(double colR, double colG, double colB){
    glColor3f(colR,colG,colB);
}

void randomColor(){
    double r=F_RAND(0,1), g=F_RAND(0,1), b=F_RAND(0,1);
    colorGlut(r,g,b);
}

void longcube(double a, double c, double b, double s, double height){
    glBegin(GL_QUADS);
    colorGlut(0,1,0);
    glVertex3f(a+s,b+height,c);
    glVertex3f(a,b+height,c);
    glVertex3f(a,b+height,c+s);
    glVertex3f(a+s,b+height,c+s);

    colorGlut(0,0,1);
    glVertex3f(a+s,b,c+s);
    glVertex3f(a,b,c+s);
    glVertex3f(a,b,c);
    glVertex3f(a+s,b,c);

    colorGlut(1,0,0);
    glVertex3f(a+s,b+height,c+s);
    glVertex3f(a,b+height,c+s);
    glVertex3f(a,b,c+s);
    glVertex3f(a+s,b,c+s);

    colorGlut(1,1,0);
    glVertex3f(a+s,b,c);
    glVertex3f(a,b,c);
    glVertex3f(a,b+height,c);
    glVertex3f(a+s,b+height,c);

    colorGlut(0,1,1);
    glVertex3f(a,b+height,c+s);
    glVertex3f(a,b+height,c);
    glVertex3f(a,b,c);
    glVertex3f(a,b,c+s);

    colorGlut(1,0,1);
    glVertex3f(a+s,b+height,c);
    glVertex3f(a+s,b+height,c+s);
    glVertex3f(a+s,b,c+s);
    glVertex3f(a+s,b,c);
    glEnd();
}


void repere(){
    double x=10000;
    glBegin(GL_LINES); // Axe des x : rouge
    colorGlut(1,0,0);
    glVertex3f(-x,0,0);
    glVertex3f(x,0,0);

    colorGlut(0,1,0); // Axe des y : vert
    glVertex3f(0,-x,0);
    glVertex3f(0,x,0);

    colorGlut(0,0,1); // Axe des z : bleu
    glVertex3f(0,0,-x);
    glVertex3f(0,0,x);
    glEnd();
}

void pave(int x1, int y1, int z1, int x2, int y2, int z2){
    glBegin(GL_POLYGON);
    glVertex3f(x1,z1,y1);
    glVertex3f(x1,z1,y2);
    glVertex3f(x2,z1,y2);
    glVertex3f(x2,z1,y1);
    glVertex3f(x1,z2,y1);
    glVertex3f(x1,z2,y2);
    glVertex3f(x2,z2,y2);
    glVertex3f(x2,z2,y1);
    glEnd();
}

void carre(double x1, double y1, double x2, double y2){
    glBegin(GL_QUADS);
    glVertex3f(x1,0,y1);
    glVertex3f(x1,0,y2);
    glVertex3f(x2,0,y2);
    glVertex3f(x2,0,y1);
    glEnd();
}

void labyrinthe2d(Tlaby *t, int x, int y, int z){
    int h=t->haut, w=t->larg;
    int i, j;
    t->matrice[prev_x+prev_y]=PLEIN;
    for(i=0 ; i<h ; i++){
        /* double c=i/(double)h; */
        for(j=1 ; j<=w ; j++){
            /* double d=j/(double)w; */
            /* colorGlut(c,0,d); */
            int n=t->matrice[i*w+j];
            int x1=x+i*WALL_SIZE;
            int x2=x1+WALL_SIZE;
            int y1=y+j*WALL_SIZE;
            int y2=y1+WALL_SIZE;
            if(n==PLEIN){     // Mur
                longcube(x1,y1,z,WALL_SIZE+0.5,WALL_HEIGHT);
            }
            else if(n==MARK){
                prev_x = i*w;
                prev_y=j;
                COLOR_GREY_SHADE(0.5);
                carre(x1,y1,x2,y2);
                t->matrice[i*w+j]=VIDE;
            }
            else {            // Chemin (pas un mur)
                COLOR_WHITE;
                carre(x1,y1,x2,y2);
            }
        }
    }
}

void losange(double centreX, double centreY, double rayon, double angle){
    double rotation=M_PI/(double)2;
    double delta=M_PI/(double)4;
    double x, y;
    int i;
    glBegin(GL_QUADS);
    for(i=0 ; i<4 ; i++){
        x=centreX+rayon*cos(angle+delta+i*rotation);
        y=centreY+rayon*sin(angle+delta+i*rotation);
        glVertex3f(x,0,y);
    }
    glEnd();
    
    x=centreX+DISTANCE*cos(angle+rotation);
    y=centreY+DISTANCE*sin(angle+rotation);
    glLineWidth(2);
    COLOR_BLACK;
    glBegin(GL_LINES);
    glVertex3f(centreX,0,centreY);
    glVertex3f(x,0,y);
    glEnd();
}

void pnj(){
    double x=perso->x*WALL_SIZE, y=perso->y*WALL_SIZE;
    COLOR_BLUE;
    losange(x,y,PERSO_SIZE/2,perso->teta);
    //fprintf(stderr,"COORD PERSONNAGE : {%.5f ; %.5f}\n",x,y);
}

void vClavier(unsigned char key, int x, int y){
    fprintf(DEV_NULL,"%d,%d\n",x, y);
    if(key==GLUT_KEY_SPACE){
        perso->teta+=rotation;
        if(perso->teta > 2*M_PI)
            perso->teta=0;
        glutPostRedisplay(); 
    }
}

int intersection(double xp, double yp, intervalle x, intervalle y){
    
}

int deplacement_possible(unsigned int dir){
    int possibilite=0; // si possible de se deplacer renvoyer 0 sinon autre chose
    double vx, vy; // coordonnes du vecteur
    double blockX, blockY; // coordonnees du block cible
    sens(perso, dir, &vx, &vy);
    double x=vx+perso->x;
    double y=vy+perso->y;
    possibilite=intersection(x, y, Intervalle(a,b), Intervalle(a,b)) && intersection;
    printf("PERSO : %f %f\n",perso->x, perso->y);
    
    return possibilite;
}

void gererClavier(int key, int mouse_x, int mouse_y){
    fprintf(DEV_NULL,"%d,%d\n",mouse_x, mouse_y);
    unsigned int dir=0;
    switch(key){
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
    case GLUT_KEY_LEFT:
    case GLUT_KEY_RIGHT:
        dir=key-GLUT_KEY_LEFT;
        if(deplacement_possible(dir)==0)
            perso=avancer(perso, dir);
        break;
    }/*
    if(key==GLUT_KEY_UP){
        perso=avancer(perso);
    }
    if(key==GLUT_KEY_DOWN){
        perso=reculer(perso);
    }
    if(key==GLUT_KEY_RIGHT){
        perso=droite(perso);
    }
    if(key==GLUT_KEY_LEFT){
        perso=gauche(perso);
        }*/
    /* switch(key){ */
    /* case GLUT_KEY_LEFT: */
    /*     if(!(F_INT(pj_x))){ */
    /*         if(!(intersectionMurPersonnage(x*WALL_SIZE,y*WALL_SIZE,(labyrinthe->matrice[(x-1)*h+y]==PLEIN ? WALL_HEIGHT : 0),WALL_SIZE,pj_x*WALL_SIZE, pj_y*WALL_SIZE, pj_z, PERSO_SIZE))){ */
    /*             pj_x-=deplacement; */
    /*             ex-=deplacement; */
    /*             dx=-1; */
    /*             dy=0; */
    /*         } */
    /*     } */
    /*         /\*else{ *\/ */
    /*     /\*     labyrinthe->matrice[(x-1)*h+y]=MARK; *\/ */
    /*     /\* } *\/ */
    /*     break; */
    /* case GLUT_KEY_RIGHT: */
    /*     //if(direction(labyrinthe,'r',x+1,y)==0){ */
    /*     if(!(F_INT(pj_x))){ */
    /*         if(!(intersectionMurPersonnage(x*WALL_SIZE,y*WALL_SIZE,(labyrinthe->matrice[(x)*h+y]==PLEIN ? WALL_HEIGHT : 1),WALL_SIZE,pj_x*WALL_SIZE, pj_y*WALL_SIZE, pj_z, PERSO_SIZE))){ */
    /*             pj_x+=deplacement; */
    /*             ex+=deplacement; */
    /*             dx=1; */
    /*             dy=0; */
    /*         } */
    /*     } */
    /*         //} */
    /*     /\* else{ *\/ */
    /*     /\*     labyrinthe->matrice[(x+1)*h+y]=MARK; *\/ */
    /*     /\* } *\/ */
    /*     break; */
    /* case GLUT_KEY_UP: */
    /*     //if(direction(labyrinthe,'u',x,y+1)==0){ */
    /*         pj_y+=deplacement; */
    /*         ez+=deplacement; */
    /*         dy=1; */
    /*         dx=0; */
    /*         //} */
    /*     /\* else{ *\/ */
    /*     /\*     labyrinthe->matrice[(y+1)+x*h]=MARK; *\/ */
    /*     /\* } *\/ */
    /*     break; */
    /* case GLUT_KEY_DOWN: */
    /*     //if(direction(labyrinthe,'d',x,y-1)==0){ */
    /*         pj_y-=deplacement; */
    /*         ez-=deplacement; */
    /*         dy=-1; */
    /*         dx=0; */
    /*         //} */
    /*     /\* else{ *\/ */
    /*     /\*     labyrinthe->matrice[(y-1)+x*h]=MARK; *\/ */
    /*     /\* } *\/ */
    /*     break; */
    /* default: */
    /*     ; */
    /* } */
    glutPostRedisplay(); 
}  

void affichage(){
    double vx=perso->x*WALL_SIZE, vy=perso->y*WALL_SIZE, vz=0;
    /* printf("(%f,%f,%f) - (%d,%d)\n",vx,vy,vz,dx,dy); */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(WIN_LEFT,WIN_RIGHT,WIN_TOP,WIN_BOTTOM,1,1000);
    gluLookAt(vx,vz+2*WALL_HEIGHT,vy,vx,vz,vy,0,0,1);
    glPushMatrix();
    pnj();
    labyrinthe2d(labyrinthe, 0, 0, 0);
    repere();
    iteration++;
    glutSwapBuffers();
}

void print(int i){
    long int temps=time(NULL);
    fprintf(stderr,"Signal SIGSEGV reçu à [%ld]\n",temps);
    fprintf(stderr,"Il y a eu %d itérations\n",iteration);

    long page_size = sysconf(_SC_PAGESIZE); // Get the page size of the system
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage); // Get the resource usage of the program
    long used_mem = usage.ru_idrss * page_size; // Memory used by program

    fprintf(stderr,"On utilise %ld mémoire\n",used_mem);
    
}

int main(int argc, char **argv){
    FILE *f=fopen("ex_labys/laby1.txt","r");
    labyrinthe=lecture_laby(f);
    fclose(f);

    struct sigaction action;
    action.sa_handler=print;
    
    sigaction(SIGSEGV, &action, NULL);
    printf("pid : %d\n",getpid());
    
    perso=Personnage(EX+0.5,EY+0.5,EZ);
    perso=changerVecteur(Vecteur(0.1,0.1,0.1),perso);
    srand(getpid());
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIN_SIZE,WIN_SIZE);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Projet V0");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(affichage);
    glutSpecialFunc(gererClavier);
    glutKeyboardFunc(vClavier);
    glutMainLoop();
    exit(EXIT_SUCCESS);
} 