// Couleurs

#define COLOR_WHITE colorGlut(1,1,1)
#define COLOR_BLACK colorGlut(0,0,0)
#define COLOR_RED colorGlut(1,0,0)
#define COLOR_YELLOW colorGlut(1,1,0)
#define COLOR_GREEN colorGlut(0,1,0)
#define COLOR_CYAN colorGlut(0,1,1)
#define COLOR_BLUE colorGlut(0,0,1)
#define COLOR_MAGENTA colorGlut(1,0,1)
#define COLOR_GREY_SHADE(n) (colorGlut(1*n,1*n,1*n))

// Mur du labyrinthe

#define WALL_HEIGHT 50
#define WALL_SIZE 25
#define WIDTH 10
#define HEIGHT 10

// Sol du labyrinthe

#define NUMBER_OF_SQUARE 2 // Nombre de carrés dans 1 colonne 
#define FLOOR_SPACE 1
#define FLOOR_COLOR COLOR_GREY_SHADE(0.5);

// Point de vue

#define EX 1
#define EY 2
#define EZ 2

// Taille plan projection

#define T 5
#define WIN_LEFT -T
#define WIN_RIGHT -T
#define WIN_TOP -T
#define WIN_BOTTOM T

// Taille Personnage

#define PERSO_SIZE 10
#define PERSO_HEIGHT 10
#define DISTANCE 10

#define GLUT_KEY_SPACE 32
#define DEV_NULL fopen("/dev/null", "w")

// Mathémagiques

#define PI2 M_PI/(double)2
#define RAYON 5