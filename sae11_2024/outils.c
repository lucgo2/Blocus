#include<stdio.h>
#include<stdlib.h>
#include<graph.h>
#include "outils.h"


int detection_bouton(Rect rectangle) {
    if (_X >= rectangle.cord_x && _X <= (rectangle.cord_x + rectangle.longueur) && _Y >= rectangle.cord_y && _Y <= (rectangle.cord_y + rectangle.largeur)) {
        return 1;
    }
    return 0;
}

void dessine_bouton(Bouton bouton) {
    int hauteur_texte = TailleSupPolice(bouton.taille_texte) + TailleInfPolice(bouton.taille_texte);
    int cord_y_texte = bouton.rectangle.cord_y + ((bouton.rectangle.largeur - hauteur_texte) / 2) + TailleSupPolice(bouton.taille_texte);
    int longueur_texte = TailleChaineEcran(bouton.texte, bouton.taille_texte);
    int cord_x_texte = bouton.rectangle.cord_x + ((bouton.rectangle.longueur - longueur_texte) / 2);
    ChoisirCouleurDessin(bouton.couleur_fond);
    RemplirRectangle(bouton.rectangle.cord_x, bouton.rectangle.cord_y, bouton.rectangle.longueur, bouton.rectangle.largeur);
    ChoisirCouleurDessin(bouton.couleur_bord);
    DessinerRectangle(bouton.rectangle.cord_x, bouton.rectangle.cord_y, bouton.rectangle.longueur, bouton.rectangle.largeur);
    ChoisirCouleurDessin(bouton.couleur_texte);
    EcrireTexte(cord_x_texte, cord_y_texte, bouton.texte, bouton.taille_texte);
}
