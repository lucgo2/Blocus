#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#include"outils.h"
#include "partie.h"
#define TAILLE 9

void dessine_grille(char taille_grille, couleur noir, char mode, Rect espace_grille, Rect grille2[TAILLE][TAILLE]) {
    char i, j;
    int cord_x = espace_grille.cord_x, cord_y = espace_grille.cord_y;
    if (mode) {
        Rect grille[taille_grille][taille_grille];
        Rect espace_previsualisation_grille = {150, 100, 200, 200};
        DessinerRectangle(espace_previsualisation_grille.cord_x, espace_previsualisation_grille.cord_y, espace_previsualisation_grille.longueur, espace_previsualisation_grille.largeur);
        ChoisirCouleurDessin(noir); 
        for (i = 0; i < taille_grille; i++) {
            cord_x = espace_grille.cord_x;
            for (j = 0; j < taille_grille; j++) {
                grille[i][j].cord_x = cord_x;
                grille[i][j].cord_y = cord_y;
                grille[i][j].longueur = espace_grille.longueur / taille_grille;
                grille[i][j].largeur = espace_grille.largeur / taille_grille;
                DessinerRectangle(grille[i][j].cord_x, grille[i][j].cord_y, grille[i][j].longueur, grille[i][j].largeur);
                cord_x += grille[i][j].longueur;
            }
            cord_y += grille[i][0].largeur;
        }
    } else { 
        ChoisirCouleurDessin(noir); 
        for (i = 0; i < taille_grille; i++) {
            cord_y = espace_grille.cord_x;
            for (j = 0; j < taille_grille; j++) {
                grille2[i][j].cord_x = cord_x;
                grille2[i][j].cord_y = cord_y;
                grille2[i][j].longueur = espace_grille.longueur / taille_grille;
                grille2[i][j].largeur = espace_grille.largeur / taille_grille;
                DessinerRectangle(grille2[i][j].cord_x, grille2[i][j].cord_y, grille2[i][j].longueur, grille2[i][j].largeur);
                cord_y += grille2[i][j].longueur;
            }
            cord_x += grille2[i][0].largeur;
        }
    }
}

void dessine_page_partie(couleur noir, couleur blanc, couleur orange) {
    Bouton bouton_retour = {"Retour", 1, blanc, orange, orange, {20, 20, 80, 30}};
    dessine_bouton(bouton_retour);
    ChoisirCouleurDessin(noir);
    EcrireTexte(162, 50, "BLOCUS.io !", 2);
}

void dessine_tour(char tour, couleur noir, Joueur *j1, Joueur *j2) {
    ChoisirCouleurDessin(noir);
    DessinerRectangle(210, 415, 80, 80);
    if (tour == 0) {
        AfficherSprite(j1->sprite_pion_default, 215, 417);
    } else if (tour == 1) {
        AfficherSprite(j1->sprite_croix_default, 215, 417);
    } else if (tour == 2) {
        AfficherSprite(j2->sprite_pion_default, 213, 416);
    } else if (tour == 3) {
        AfficherSprite(j2->sprite_croix_default, 213, 416);
    }
}

char determine_tour(char *liste_tour_bool) {
    char i;
    for (i = 0; i < 4; i++) {
        if (liste_tour_bool[i]) {
            return i;
        }
    }
}

void retour_jeu(Menu *menu, Jeu *jeu, char *taille_grille, Joueur *j1, Joueur *j2, int grille_contenu[TAILLE][TAILLE], char liste_tour_1[2], char liste_tour[4]) {
    Rect retour_bouton = {20, 20, 80, 30};
    char i, j;
    if (detection_bouton(retour_bouton)) {
        jeu->premier_tour = 1;
        jeu->est_jeu = 0;
        jeu->jeu = 0;
        jeu->est_jeu_IA = 0;
        jeu->jeu_IA = 0;
        menu->est_menu_map = 0;
        *taille_grille = 3;
        liste_tour_1[0] = 1, liste_tour_1[1] = 0;
        liste_tour[0] = 1, liste_tour[1] = 0, liste_tour[2] = 0, liste_tour[3] = 0;
        j1->position_joueur_x = NULL, j1->position_joueur_y = NULL;
        j2->position_joueur_x = NULL, j2->position_joueur_y = NULL;
        for (i = 0; i < TAILLE; i++) {
            for (j = 0; j < TAILLE; j++) {
                grille_contenu[i][j] = 0;
            }
        }
    }
}

char condition_deplacement_pion(Joueur *j, char position_clic_x, char position_clic_y) {
    if (abs(position_clic_x - j->position_joueur_x) <= 1 && abs(position_clic_y - j->position_joueur_y) <= 1 && ((position_clic_x != j->position_joueur_x) || (position_clic_y != j->position_joueur_y))) {
        return 1; 
    }
    return 0; 
}

void jouer_tour(char liste_tour[], char tour, Rect grille_image[TAILLE][TAILLE], int grille_valeur[TAILLE][TAILLE], char taille_map, Joueur *j1, Joueur *j2) {
    /*-2: represente le joueur bleu | -1: represente le joueur orange | 0: represente la case vide | 1: represente une croix orange | 2: represente une croix bleu*/
    char i, j, passage_tour_suivant = 0;
    if (SourisCliquee()) {
        for(i = 0; i < taille_map; i++) {
            for(j = 0; j < taille_map; j++) {
                if (detection_bouton(grille_image[i][j]) && (grille_valeur[i][j] == 0)) {
                    if (tour == 0) { 
                        if (condition_deplacement_pion(j1, i, j)) { /* deplacement du pion orange */
                            grille_valeur[j1->position_joueur_x][j1->position_joueur_y] = 0;
                            grille_valeur[i][j] = -1;
                            j1->position_joueur_x = i;
                            j1->position_joueur_y = j;
                            passage_tour_suivant = 1;
                        }
                    } else if (tour == 1) { /* placement de croix orange */
                        grille_valeur[i][j] = 1;
                        passage_tour_suivant = 1;
                    } else if (tour == 2) {
                        if (condition_deplacement_pion(j2, i, j)) { /* deplacement du pion bleu */
                            grille_valeur[j2->position_joueur_x][j2->position_joueur_y] = 0;
                            grille_valeur[i][j] = -2;
                            j2->position_joueur_x = i;
                            j2->position_joueur_y = j;
                            passage_tour_suivant = 1;
                        }
                    } else { /* placement de croix bleu */
                        grille_valeur[i][j] = 2;
                        passage_tour_suivant = 1;
                    }
                    /* passage au tour suivant */
                    if (passage_tour_suivant) {
                        liste_tour[tour] = 0;
                        if (tour == 3) {
                            liste_tour[0] = 1;
                        } else {
                            liste_tour[tour + 1] = 1;
                        }
                    }
                }   
            }
        }
    }
}


void tour_1(char liste_tour[], char tour, Rect grille_image[TAILLE][TAILLE], int grille_valeur[TAILLE][TAILLE], char taille_map, Joueur *j1, Joueur *j2, char *premier_tour) {
    char i, j;
    if (SourisCliquee()) {
        for(i = 0; i < taille_map; i++) {
            for(j = 0; j < taille_map; j++) {
                if (detection_bouton(grille_image[i][j]) && grille_valeur[i][j] == 0) {
                    if (tour == 0) {
                        grille_valeur[j1->position_joueur_x][j1->position_joueur_y] = 0;
                        grille_valeur[i][j] = -1;
                        j1->position_joueur_x = i;
                        j1->position_joueur_y = j;                        
                        liste_tour[0] = 0;
                        liste_tour[1] = 1;
                    } else {
                        grille_valeur[j2->position_joueur_x][j2->position_joueur_y] = 0;
                        grille_valeur[i][j] = -2;
                        j2->position_joueur_x = i;
                        j2->position_joueur_y = j;
                        *premier_tour = 0;
                    }
                }   
            }
        }
    }
}

void dessine_elt_map(int grille[TAILLE][TAILLE], Rect grille_image[TAILLE][TAILLE], Joueur *j1, Joueur *j2, char taille_map) { 
    char i, j;
    for (i = 0; i < taille_map; i++) {
        for (j = 0; j < taille_map; j++) {
            if (grille[i][j] == -2) {
                AfficherSprite(j2->sprite_pion, grille_image[i][j].cord_x, grille_image[i][j].cord_y);
            } else if (grille[i][j] == -1) {
                AfficherSprite(j1->sprite_pion, grille_image[i][j].cord_x, grille_image[i][j].cord_y);
            } else if (grille[i][j] == 1) {
                AfficherSprite(j1->sprite_croix, grille_image[i][j].cord_x, grille_image[i][j].cord_y);
            } else if (grille[i][j] == 2) {
                AfficherSprite(j2->sprite_croix, grille_image[i][j].cord_x, grille_image[i][j].cord_y);
            }
        }
    }
}

char condition_fin_jeu(int grille[TAILLE][TAILLE], Joueur *j1, Joueur *j2, char taille_map) {
    if (j1->position_joueur_x >= 0 && j1->position_joueur_x < taille_map && j1->position_joueur_y >= 0 && j1->position_joueur_y < taille_map && j2->position_joueur_x >= 0 && j2->position_joueur_x < taille_map && j2->position_joueur_y >= 0 && j2->position_joueur_y < taille_map) {
        char i, j;
        for (i = 0; i < taille_map; i++) {
            for (j = 0; j < taille_map; j++) {
                if (abs(i - j1->position_joueur_x) <= 1 && abs(j - j1->position_joueur_y) <= 1 && ((i != j1->position_joueur_x) || (j != j1->position_joueur_y))) {
                    if (grille[i][j] == 0) {
                        return 0;
                    }
                }
            }
        }
    } else {
        return 0;
    }
    return 1;
}

