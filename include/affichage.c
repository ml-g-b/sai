/* vous n'avez pas besoin d'utiliser ces fonctions ni donc de lire ce fichier. */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include "affichage.h"

// https://en.wikipedia.org/wiki/ANSI_escape_code

int coul_rvb(int r, int v, int b) {
  // valeurs r,v et b entre 0 et 5.
  return 16+36*r+6*v+b;
}

int coul_gris(int n) {
  // niveau de gris n entre 0 et 23
  return 232+n;
}

void couleur_fond(int coul) {
  printf("\033[48;5;%dm",coul);
  //printf("\033[4%dm", coul);
}

void couleur_texte(int coul) {
  printf("\033[38;5;%dm",coul);
  //printf("\033[3%dm", coul);
}

void reset_couleurs() {
  printf("\033[0m");
}

void efface_ecran() {
  printf("\033[2J");
}

/* Deplacement du curseur */

void goto_haut_gauche() {
  printf("\033[1;1H");
}

void goto_xy(int x, int y) {
  printf("\033[%d;%dH", x, y);
}

void goto_up(int x) {
  printf("\033[%dA", x);
}

void goto_down(int x) {
  printf("\033[%dB", x);
}

void goto_forward(int x) {
  printf("\033[%dC", x);
}

void goto_backward(int x) {
  printf("\033[%dD", x);
}

void save_cursor_pos() {
  printf("\033[s");
}

void restore_cursor_pos() {
  printf("\033[u");
}

// chaines de caractères UTF-8 utilisés pour afficher le graphe.
//static char magic[][8]={"•","╵","╶","└","╷","│","┌","├","╴","┘","─","┴","┐","┤","┬","┼"};
static char magic[][8]={"•","╹","╺","┗","╻","┃","┏","┣","╸","┛","━","┻","┓","┫","┳","╋"}; // version "gras"

void affiche_symbole(int numero_symbole) {
  printf("%s",magic[numero_symbole]);
}

