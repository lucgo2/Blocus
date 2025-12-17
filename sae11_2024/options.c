#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#include "outils.h"

void dessine_page_setting(couleur orange, couleur blanc, couleur noir) {
    Bouton change_couleur = {"Clair / Sombre", 2, blanc, orange, orange, {100, 175, 300, 100}};
    Bouton bouton_retour = {"Retour", 1, blanc, orange, orange, {20, 450, 80, 30}};
    ChoisirCouleurDessin(noir);
    EcrireTexte(162, 70, "BLOCUS.io !", 2);
    dessine_bouton(change_couleur);
    dessine_bouton(bouton_retour);
}

void fonction_setting(Options *objet, char *menu) {
    Rect change_couleur = {100, 175, 300, 100};
    Rect bouton_retour = {20, 450, 80, 30};
    if (SourisCliquee()) { 
        if (detection_bouton(change_couleur)) {
            if (objet->est_sombre) {
                objet->est_sombre = 0;
            } else {
                objet->est_sombre = 1;
            } 
        } else if (detection_bouton(bouton_retour)) {
            objet->est_option = 0;
            *menu = 1;
        }
    }
}