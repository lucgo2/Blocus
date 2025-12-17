#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#include "outils.h"
#include "menu.h"
#include "partie.h"


void dessine_page_menu(couleur noir, couleur blanc, couleur orange){
    char i;
    Rect rectangle_ia = {60, 160, 180, 70};
	Rect rectangle_joueur = {260, 160, 180, 70};
    Rect rectangle_regles = {60, 273, 180, 70};
	Rect rectangle_reglage = {260, 273, 180, 70};
	Rect rectangle_quitter = {160, 385, 180, 70};
	Bouton bouton_1joueur = {"Joueur VS IA", 1, blanc, orange, orange, rectangle_ia};
	Bouton bouton_2joueur = {"Joueur VS Joueur", 1, blanc, orange, orange, rectangle_joueur};
	Bouton bouton_regles = {"Regles", 1, blanc, orange, orange, rectangle_regles};
	Bouton bouton_quitter = {"Quitter", 1, blanc, orange, orange, rectangle_quitter};
	Bouton bouton_reglage = {"Parametres", 1, blanc, orange, orange, rectangle_reglage};
	Bouton bouton_du_menu[] = {bouton_1joueur, bouton_2joueur, bouton_regles, bouton_reglage, bouton_quitter};
    ChoisirCouleurDessin(noir);
    EcrireTexte(162, 70, "BLOCUS.io !", 2);
    for(i = 0; i < 5; i++) {
        dessine_bouton(bouton_du_menu[i]);
    }
}

void fonction_bouton(Jeu *jeu, char *regle, char *option, char *en_jeu, Menu *menu, couleur noir, couleur blanc, couleur orange) { /* bouton menu */
    if (menu->est_menu && !menu->est_menu_map) { 
        Rect rectangle_ia = {60, 160, 180, 70};
        Rect rectangle_joueur = {260, 160, 180, 70};
        Rect rectangle_regles = {60, 273, 180, 70};
        Rect rectangle_reglage = {260, 273, 180, 70};
        Rect rectangle_quitter = {160, 385, 180, 70};
        if (SourisCliquee()) { 
            if (detection_bouton(rectangle_ia)) {
                menu->est_menu_map = 1;
                jeu->jeu_IA = 1;    
            } else if (detection_bouton(rectangle_joueur)) {
                menu->est_menu_map = 1;
                jeu->jeu = 1;
            } else if (detection_bouton(rectangle_regles)) {
                menu->est_menu = 0;
                *regle = 1;
            } else if (detection_bouton(rectangle_reglage)) {
                menu->est_menu = 0;
                *option = 1;
            } else if (detection_bouton(rectangle_quitter)) {
                *en_jeu = 0;
            }
        }
    }
}

void dessine_barre_taille_map(couleur noir) {
    char i;
    Rect liste_cord_lvl[7] = {{134, 365, 33, 23}, {167, 365, 33, 23}, {200, 365, 33, 23}, {233, 365, 33, 23}, {266, 365, 33, 23}, {299, 365, 33, 23}, {332, 365, 33, 23}};
    ChoisirCouleurDessin(noir);
    for(i = 0; i < 7; i++) {
        DessinerRectangle(liste_cord_lvl[i].cord_x, liste_cord_lvl[i].cord_y, liste_cord_lvl[i].longueur, liste_cord_lvl[i].largeur);
    }
} 

char detection_barre(taille) {
    char i;
    Rect liste_cord_lvl[10] = {{0}, {0}, {0}, {134, 365, 33, 25}, {167, 365, 33, 25}, {200, 365, 33, 25}, {233, 365, 33, 25}, {266, 365, 33, 25}, {299, 365, 33, 25}, {332, 365, 33, 25}};
    if (SourisCliquee()) {
        for(i = 3; i < 10; i++) {
            if (detection_bouton(liste_cord_lvl[i])) {
                return i;
            }
        }
    }
    return taille;
}

void dessine_cercle(char taille, couleur orange) {
    Rect liste_cord_lvl[10] = {{0}, {0}, {0}, {135, 366, 32, 22}, {168, 366, 32, 22}, {201, 366, 32, 22}, {234, 366, 32, 22}, {267, 366, 32, 22}, {300, 366, 32, 22}, {333, 366, 32, 22}};
    ChoisirCouleurDessin(orange);
    RemplirRectangle(liste_cord_lvl[taille].cord_x, liste_cord_lvl[taille].cord_y, liste_cord_lvl[taille].longueur, liste_cord_lvl[taille].largeur);
}


void dessine_menu_map(couleur noir, couleur orange, couleur blanc, char *taille) {
    Rect grille_qui_sert_a_rien[TAILLE][TAILLE];
    Bouton bouton_retour = {"Retour", 1, blanc, orange, orange, {20, 20, 80, 30}};
    Bouton bouton_valider = {"Valider", 1, blanc, orange, orange, {210, 423, 80, 30}};
    Rect espace_grille = {175, 125, 150, 150};
    dessine_bouton(bouton_retour);
    dessine_bouton(bouton_valider);
    dessine_barre_taille_map(noir);
    dessine_grille(*taille, noir, 1, espace_grille, grille_qui_sert_a_rien);
    EcrireTexte(162, 50, "BLOCUS.io !", 2);
    *taille = detection_barre(*taille);
    dessine_cercle(*taille, orange);
}


void fonction_bouton_menu_map(Menu *menu, Jeu *jeu, char *taille_map) {
    Rect bouton_retour = {20, 20, 80, 30};
    Rect bouton_valider = {210, 423, 80, 30};
    if (!SourisCliquee()) {
        if (detection_bouton(bouton_retour)) {
            menu->est_menu_map = 0;
            jeu->est_jeu = 0;
            jeu->est_jeu_IA = 0;
            *taille_map = 3;
        } else if (detection_bouton(bouton_valider)) {
            jeu->est_jeu = (jeu->jeu) ? 1 : 0;
            jeu->est_jeu_IA = (jeu->jeu_IA) ? 1 : 0;
            jeu->premier_tour = 1;
        }
    }
}

void dessine_menu_fin_jeu(Joueur *vainqueur, Joueur *perdant, couleur orange, couleur noir, couleur blanc) {
    Rect zone_rejouer = {86, 313, 120, 60};
    Rect zone_menu = {292, 313, 120, 60};
    Rect zone_quitter = {190, 426, 120, 60};
    Bouton rejouer = {"Rejouer", 1, blanc, orange, orange, zone_rejouer};
    Bouton menu = {"Menu", 1, blanc, orange, orange, zone_menu}; 
    Bouton quitter = {"Quitter", 1, blanc, orange, orange, zone_quitter};
    dessine_bouton(rejouer);
    dessine_bouton(menu);
    dessine_bouton(quitter);
    ChoisirCouleurDessin(noir);
    EcrireTexte(162, 50, "BLOCUS.io !", 2);
    AfficherSprite(vainqueur->sprite_pion_default, 245, 90);
    AfficherSprite(perdant->sprite_pion_default, 200, 122);
    RemplirRectangle(250, 150, 50, 100);
    RemplirRectangle(200, 180, 50, 70);
}

void fonction_bouton_menu_fin(char *jeu_en_cour, Menu *menu, Jeu *jeu, char *taille_grille, int grille_contenu[TAILLE][TAILLE], char liste_tour_1[2], char liste_tour[4], Joueur *j1, Joueur *j2) {
    Rect zone_quitter = {190, 426, 120, 60};
    Rect zone_menu = {292, 313, 120, 60};
    Rect zone_rejouer = {86, 313, 120, 60};
    if (SourisCliquee()) {
        if (detection_bouton(zone_quitter)) {
            *jeu_en_cour = 0;
        } else if (detection_bouton(zone_menu) || detection_bouton(zone_rejouer)) {
            char i, j;
            jeu->premier_tour = 1;
            jeu->est_jeu = 0;
            jeu->est_jeu_IA = 0;
            *taille_grille = 3;
            menu->est_menu_fin_jeu = 0;
            liste_tour_1[0] = 1, liste_tour_1[1] = 0;
            liste_tour[0] = 1, liste_tour[1] = 0, liste_tour[2] = 0, liste_tour[3] = 0;
            j1->position_joueur_x = NULL, j1->position_joueur_y = NULL;
            j2->position_joueur_x = NULL, j2->position_joueur_y = NULL;
            j1->gagne = 0, j2->gagne = 0;
            for (i = 0; i < TAILLE; i++) {
                for (j = 0; j < TAILLE; j++) {
                    grille_contenu[i][j] = 0;
                }
            }
            if (detection_bouton(zone_menu)) {
                menu->est_menu_map = 0;
                jeu->jeu = 0;
                jeu->jeu_IA = 0;  
            }
        }
    }
}