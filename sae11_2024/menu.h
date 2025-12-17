#ifndef MENU_H
#define MENU_H
#include<graph.h>
#include "structure.h"
#include "outils.h"
#define TAILLE 9


void dessine_page_menu(couleur noir, couleur blanc, couleur orange);
void fonction_bouton(Jeu *jeu, char *regle, char *option, char *en_jeu, Menu *menu, couleur noir, couleur blanc, couleur orange);
void dessine_barre_taille_map(couleur noir);
char detection_barre(taille);
void dessine_cercle(char taille, couleur orange);
void dessine_menu_map(couleur noir, couleur orange, couleur blanc, char *taille);
void fonction_bouton_menu_map(Menu *menu, Jeu *jeu, char *taille_map);
void dessine_menu_fin_jeu(Joueur *vainqueur, Joueur *perdant, couleur orange, couleur noir, couleur blanc);
void fonction_bouton_menu_fin(char *jeu_en_cour, Menu *menu, Jeu *jeu, char *taille_grille, int grille_contenu[TAILLE][TAILLE], char liste_tour_1[2], char liste_tour[4], Joueur *j1, Joueur *j2);


#endif /* menu.h */