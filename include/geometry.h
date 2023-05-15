typedef struct {
    double x;
    double y;
    double pas;
}vecteur_struct;

typedef vecteur_struct *vecteur;

vecteur Vecteur(double,double,double);
vecteur Vecteur_COPY(vecteur);
vecteur applyAngle(double, vecteur);

void printVecteur(vecteur);

typedef struct{
    double x;
    double y;
    double z;
    vecteur v;
    double teta;
}personnage_struct;

typedef personnage_struct *personnage;

personnage Personnage(double, double, double);
void sens(personnage, unsigned int, double*, double*);
personnage avancer(personnage,unsigned int);/*
personnage avancer(personnage);
personnage reculer(personnage);
personnage droite(personnage );
personnage gauche(personnage);*/
void printPersonnage(personnage);
personnage changerVecteur(vecteur, personnage);
personnage tourner(double, personnage);

void freePersonnage(personnage);


typedef struct{
    double min;
    double max;
}intervalle_struct;

typedef intervalle_struct *intervalle;

intervalle Intervalle(double, double);
int estDans(double, intervalle);