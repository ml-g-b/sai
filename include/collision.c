#include<math.h>
#include"collision.h"
#include"../header/window.h"
#include"../MACRO_function.h"

int detecterCollision(Tlaby *t, double player_x, double player_y, double teta) {
    int h = t->haut;
    int w = t->larg;
    int wall = PLEIN;
    double wallSize = WALL_SIZE;

    // Conversion des coordonnées en indices de la matrice
    int x = (int) ((player_x + cos(teta + M_PI/4))/ wallSize);
    int y = (int) ((player_y + sin(teta + M_PI/4)) / wallSize);


    // Vérification des positions adjacentes
    if (x < 0 || x >= h || y < 0 || y >= w) {
        // Le personnage est en dehors des limites du labyrinthe
        return 1; // Collision détectée
    }

    int player_pos = x*w + y;
    printf("Valeur x = %d et y = %d || Indice %d valeur = %d\n", x, y, player_pos, t->matrice[player_pos]);
    if (t->matrice[player_pos] == wall) {
        // Le personnage est sur un mur
        return 1; // Collision détectée
    }

    // Pas de collision détectée
    return 0;
}