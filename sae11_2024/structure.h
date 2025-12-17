#ifndef STRUCTURE_H
#define STRUCTURE_H
#include<graph.h>


typedef struct Rect {
    int cord_x;
    int cord_y;
    int longueur;
    int largeur;
} Rect;

typedef struct Bouton {
    char texte[200];
    int taille_texte;
    couleur couleur_texte;
    couleur couleur_fond;
    couleur couleur_bord;
    Rect rectangle;
} Bouton;

typedef struct Menu {
    char est_menu;
    char est_menu_map;
    char est_menu_fin_jeu;
} Menu;

typedef struct Jeu {
    char est_jeu;
    char est_jeu_IA;
    char jeu;
    char jeu_IA;
    char premier_tour;
} Jeu;

typedef struct Regles {
    char est_regles;
} Regles;

typedef struct Options {
    char est_option;
    char est_sombre;
} Options;

typedef struct Joueur {
    int position_joueur_x;
    int position_joueur_y;
    int sprite_pion;
    int sprite_croix;
    int sprite_pion_default;
    int sprite_croix_default;
    char gagne;
} Joueur; 


#endif /* structure.h */