#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#include<time.h>
#include "robot.h"
#include "partie.h"
#define TAILLE 9


void determine_tour_IA(int taille_grille, int *cord_x, int *cord_y) {
    /* attribut une position dans la map au robot */
    *cord_y = rand() % taille_grille;
    *cord_x = rand() % taille_grille;
}

void jouer_tour_partie_IA(char liste_tour[], char tour, Rect grille_image[TAILLE][TAILLE], int grille_valeur[TAILLE][TAILLE], char taille_map, Joueur *j1, Joueur *j2, Jeu *jeu) {
    /*-2: represente le joueur bleu | -1: represente le joueur orange | 0: represente la case vide | 1: represente une croix orange | 2: represente une croix bleu*/
    int i, j;
    char passage_tour_suivant = 0;
    if (tour <= 1) { 
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
                        } else { /* placement de croix orange */
                            grille_valeur[i][j] = 1;
                            passage_tour_suivant = 1;
                        } 
                    }
                }
            }
        }
    } else if (tour == 2) {
        /* deplacement du pion bleu */
        determine_tour_IA(taille_map, &i, &j);
        if (condition_deplacement_pion(j2, (char)i, (char)j) && grille_valeur[i][j] == 0) {
            grille_valeur[j2->position_joueur_x][j2->position_joueur_y] = 0;
            grille_valeur[i][j] = -2;
            j2->position_joueur_x = i;
            j2->position_joueur_y = j;
            passage_tour_suivant = 1;
        }
    } else if (tour == 3) { /* placement de croix bleu */
        determine_tour_IA(taille_map, &i, &j);
        if (grille_valeur[i][j] == 0) {
            grille_valeur[i][j] = 2;
            passage_tour_suivant = 1;
        }
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

void tour_1_partie_IA(char liste_tour[], char tour, Rect grille_image[TAILLE][TAILLE], int grille_valeur[TAILLE][TAILLE], char taille_map, Joueur *j1, Joueur *j2, Jeu *jeu) {
    /*-2: represente le joueur bleu | -1: represente le joueur orange */
    int i, j;
    if (!tour) { 
        if (SourisCliquee()) {
            for(i = 0; i < taille_map; i++) {
                for(j = 0; j < taille_map; j++) {
                    if (detection_bouton(grille_image[i][j]) && grille_valeur[i][j] == 0) {
                        grille_valeur[j1->position_joueur_x][j1->position_joueur_y] = 0;
                        grille_valeur[i][j] = -1;
                        j1->position_joueur_x = i;
                        j1->position_joueur_y = j;                        
                        liste_tour[0] = 0;
                        liste_tour[1] = 1;
                    }
                }
            }
        }
    } else { 
        /* s'assure que la position priose par le robot soit correcte */
        determine_tour_IA(taille_map, &i, &j);
        while (grille_valeur[i][j] != 0) {
            determine_tour_IA(taille_map, &i, &j);
        }
        grille_valeur[j2->position_joueur_x][j2->position_joueur_y] = 0;
        grille_valeur[i][j] = -2;
        j2->position_joueur_x = i;
        j2->position_joueur_y = j;
        jeu->premier_tour = 0;
    }
}