#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#include "outils.h"
#include "regles.h"

void dessine_page_regles(couleur noir, couleur blanc, couleur orange, char option) {
    Bouton bouton_retour = {"Retour", 1, blanc, orange, orange, {20, 450, 80, 30}};
    dessine_bouton(bouton_retour);
    ChoisirCouleurDessin(noir);
    EcrireTexte(162, 70, "BLOCUS.io !", 2);
    EcrireTexte(22, 110, "Le jeu se deroule sur une grille carree de taille", 1);
    EcrireTexte(22, 130, "choisie entre 3 et 9 cases de cote. Chaque", 1);
    EcrireTexte(22, 150, "joueur place son pion sur une case vide, sans que", 1);
    EcrireTexte(22, 170, "les pions ne se chevauchent. Les joueurs alternent", 1);
    EcrireTexte(22, 190, "alternent les tours: a chaque tour, un joueur ", 1);
    EcrireTexte(22, 210, "deplace son pion vers une case adjacente (y", 1);
    EcrireTexte(22, 230, "compris en diagonale), puis il choisit une case libre", 1);
    EcrireTexte(22, 250, "a condammer, la rendant inaccessible. Le but est  ", 1);
    EcrireTexte(22, 270, "de bloque l'adversaire en l'empechant de deplacer ", 1);
    EcrireTexte(22, 290, "son pion. La partie se termine lorsque l'un des  ", 1);
    EcrireTexte(22, 310, "joueurs ne peut plus deplacer son pion, car toutes ", 1);
    EcrireTexte(22, 330, "les cases adjacentes sont soit occupees, soit ", 1);
    EcrireTexte(22, 350, "condamnees. En mode a un joueur, le programme ", 1);
    EcrireTexte(22, 370, "simule le second joueur, sans strategie complexe", 1);
    EcrireTexte(22, 390, "mais en respectant les regles du jeu.", 1);
}


void retour(char *regle, char *menu) {
    Rect retour_bouton = {20, 450, 80, 30};
    if (SourisCliquee() && detection_bouton(retour_bouton)) {
        *regle = 0;
        *menu = 1;
    }
}