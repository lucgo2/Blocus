#ifndef ROBOT_H
#define ROBOT_H
#include<graph.h>
#include<time.h>
#include "structure.h"
#include "outils.h"
#define TAILLE 9


void determine_tour_IA(int taille_grille, int *cord_x, int *cord_y);
void jouer_tour_partie_IA(char liste_tour[], char tour, Rect grille_image[TAILLE][TAILLE], int grille_valeur[TAILLE][TAILLE], char taille_map, Joueur *j1, Joueur *j2, Jeu *jeu);
void tour_1_partie_IA(char liste_tour[], char tour, Rect grille_image[TAILLE][TAILLE], int grille_valeur[TAILLE][TAILLE], char taille_map, Joueur *j1, Joueur *j2, Jeu *jeu);

#endif /* robot.h */