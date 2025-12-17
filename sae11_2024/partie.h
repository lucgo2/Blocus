#ifndef PARTIE_H
#define PARTIE_H
#include<graph.h>
#include "structure.h"
#include "outils.h"
#define TAILLE 9



void dessine_grille(char taille_grille, couleur noir, char mode, Rect espace_grille, Rect grille2[TAILLE][TAILLE]);
void dessine_page_partie(couleur noir, couleur blanc, couleur orange);
void dessine_tour(char tour, couleur noir, Joueur *j1, Joueur *j2);
char determine_tour(char *liste_tour_bool);
void retour_jeu(Menu *menu, Jeu *jeu, char *taille_grille, Joueur *j1, Joueur *j2, int grille_contenu[TAILLE][TAILLE], char liste_tour_1[2], char liste_tour[4]);
char condition_deplacement_pion(Joueur *j, char position_clic_x, char position_clic_y);
void jouer_tour(char liste_tour[], char tour, Rect grille_image[TAILLE][TAILLE], int grille_valeur[TAILLE][TAILLE], char taille_map, Joueur *j1, Joueur *j2);
void tour_1(char liste_tour[], char tour, Rect grille_image[TAILLE][TAILLE], int grille_valeur[TAILLE][TAILLE], char taille_map, Joueur *j1, Joueur *j2, char *premier_tour);
void dessine_elt_map(int grille[TAILLE][TAILLE], Rect grille_image[TAILLE][TAILLE], Joueur *j1, Joueur *j2, char taille_map);
char condition_fin_jeu(int grille[TAILLE][TAILLE], Joueur *j1, Joueur *j2, char taille_map);

#endif /* partie.h */