#include<graph.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "outils.h"
#include "menu.h"
#include "regles.h"
#include "options.h"
#include "partie.h"
#include "robot.h"
#define TAILLE 9

int main(void) {

	/* initialisation des structures */
	Menu menu = {1, 0, 0};
	Regles regles = {0};
	Options options = {0, 0};
	Jeu jeu = {0, 0, 0, 0, 0};

    /* initialisation générale */
	Rect grille[TAILLE][TAILLE];
	int grille_contenu[TAILLE][TAILLE];
	int sprite_pion_orange[7], sprite_pion_bleu[7], sprite_croix_orange[7], sprite_croix_bleu[7];
	char jeu_en_cour = 1, i, j, taille_grille = 3;
	Joueur joueur_1, joueur_2;
	int liste_sprite_default[4];
	char determine_tour_lst[4] = {1, 0, 0, 0}, determine_tour_lst_premier_tour[2] = {1, 0};

	/* lancement du mode graphique */
	InitialiserGraphique();
	CreerFenetre(0, 0, 500, 500);
	srand(time(NULL));

	/* sprite disponible pour le pion orange */
	sprite_pion_orange[0] = ChargerSprite("./images/pion_orange3.png"), sprite_pion_orange[1] = ChargerSprite("./images/pion_orange4.png"), sprite_pion_orange[2] = ChargerSprite("./images/pion_orange5.png"),
	sprite_pion_orange[3] = ChargerSprite("./images/pion_orange6.png"), sprite_pion_orange[4] = ChargerSprite("./images/pion_orange7.png"), sprite_pion_orange[5] = ChargerSprite("./images/pion_orange8.png"),
	sprite_pion_orange[6] = ChargerSprite("./images/pion_orange9.png");

	/* sprite disponible pour le pion bleu */
	sprite_pion_bleu[0] = ChargerSprite("./images/pion_bleu3.png"), sprite_pion_bleu[1] = ChargerSprite("./images/pion_bleu4.png"), sprite_pion_bleu[2] = ChargerSprite("./images/pion_bleu5.png"),
	sprite_pion_bleu[3] = ChargerSprite("./images/pion_bleu6.png"), sprite_pion_bleu[4] = ChargerSprite("./images/pion_bleu7.png"), sprite_pion_bleu[5] = ChargerSprite("./images/pion_bleu8.png"),
	sprite_pion_bleu[6] = ChargerSprite("./images/pion_bleu9.png");

	/* sprite disponible pour la croix orange */
	sprite_croix_orange[0] = ChargerSprite("./images/croix_orange3.png"), sprite_croix_orange[1] = ChargerSprite("./images/croix_orange4.png"), sprite_croix_orange[2] = ChargerSprite("./images/croix_orange5.png"),
	sprite_croix_orange[3] = ChargerSprite("./images/croix_orange6.png"), sprite_croix_orange[4] = ChargerSprite("./images/croix_orange7.png"), sprite_croix_orange[5] = ChargerSprite("./images/croix_orange8.png"),
	sprite_croix_orange[6] = ChargerSprite("./images/croix_orange9.png");

	/* sprite disponible pour la croix bleu */
	sprite_croix_bleu[0] = ChargerSprite("./images/croix_bleu3.png"), sprite_croix_bleu[1] = ChargerSprite("./images/croix_bleu4.png"), sprite_croix_bleu[2] = ChargerSprite("./images/croix_bleu5.png"),
	sprite_croix_bleu[3] = ChargerSprite("./images/croix_bleu6.png"), sprite_croix_bleu[4] = ChargerSprite("./images/croix_bleu7.png"), sprite_croix_bleu[5] = ChargerSprite("./images/croix_bleu8.png"),
	sprite_croix_bleu[6] = ChargerSprite("./images/croix_bleu9.png");

	/* initialisation des attribut des joueurs */
	joueur_1.position_joueur_x = NULL, joueur_2.position_joueur_x = NULL;
	joueur_1.position_joueur_y = NULL, joueur_2.position_joueur_y = NULL;
	joueur_1.gagne = 0, joueur_2.gagne = 0;
	joueur_1.sprite_pion_default = sprite_pion_orange[2], joueur_2.sprite_pion_default = sprite_pion_bleu[2];
	joueur_1.sprite_croix_default = sprite_croix_orange[2], joueur_2.sprite_croix_default = sprite_croix_bleu[2];

	/* initialisation des sprite pour les tours */
	liste_sprite_default[0] = sprite_pion_orange[1], liste_sprite_default[1] =  sprite_croix_orange[1], liste_sprite_default[2] = sprite_pion_bleu[1], liste_sprite_default[3] = sprite_croix_bleu[1];
	
	/* initialisation de la map */
	for (i = 0; i < TAILLE; i++) {
		for (j = 0; j < TAILLE; j++) {
			grille_contenu[i][j] = 0;
		}
	}

	/* boucle du jeu */
	while(jeu_en_cour) {

		/* initialisation des couleurs en fonction du thème apliqué */
		couleur rouge = CouleurParComposante(255, 0, 0);
		couleur blanc = CouleurParComposante(255, 255, 255);
		couleur noir, bleu, orange;
		if (options.est_sombre) {  /* mode sombre */
			noir = CouleurParComposante(255, 255, 255);
			bleu = CouleurParComposante(255, 158, 0);
			orange = CouleurParComposante(0, 182, 255);
		} else { /* mode normal */
			noir = CouleurParComposante(0, 0, 0);
			orange = CouleurParComposante(255, 158, 0);
			bleu = CouleurParComposante(0, 182, 255);
		} 

		/* affiche le fond en fonction du thème */
		(options.est_sombre) ? ChargerImageFond("./images/fond_jeu_sombre.jpg") : ChargerImageFond("./images/fond_jeu.jpg");

		if (menu.est_menu) {  /* le jeu est dans le menu principal */
			if (!menu.est_menu_map) { 
			dessine_page_menu(noir, blanc, orange);
			fonction_bouton(&jeu, &regles.est_regles, &options.est_option, &jeu_en_cour, &menu, noir, blanc, orange);
			} else { /* le jeu est dans le menu de la map */
				if (!jeu.est_jeu && !jeu.est_jeu_IA) { 
					dessine_menu_map(noir, orange, blanc, &taille_grille);
					fonction_bouton_menu_map(&menu, &jeu, &taille_grille);
					joueur_1.sprite_pion = sprite_pion_orange[taille_grille - 3], joueur_2.sprite_pion = sprite_pion_bleu[taille_grille - 3]; 
					joueur_1.sprite_croix = sprite_croix_orange[taille_grille - 3], joueur_2.sprite_croix = sprite_croix_bleu[taille_grille - 3];
				} else {
					if (jeu.est_jeu) { 
						if (!menu.est_menu_fin_jeu) { /* le jeu commence en mode joueur vs joueur */
							Rect espace_grille = {100, 100, 300, 300};
							dessine_grille(taille_grille, noir, 0, espace_grille, grille);
							dessine_page_partie(noir, blanc, orange);
						}
						if (jeu.premier_tour) { /* le premier tour de l partie */
							char tour = determine_tour(determine_tour_lst_premier_tour);
							if (tour) { 
								dessine_tour(tour + 1, noir, &joueur_1, &joueur_2);
							} else {
								dessine_tour(tour, noir, &joueur_1, &joueur_2);
							}
							tour_1(determine_tour_lst_premier_tour, tour, grille, grille_contenu, taille_grille, &joueur_1, &joueur_2, &jeu.premier_tour);
							retour_jeu(&menu, &jeu, &taille_grille, &joueur_1, &joueur_2, grille_contenu, determine_tour_lst_premier_tour, determine_tour_lst);
							dessine_elt_map(grille_contenu, grille, &joueur_1, &joueur_2, taille_grille); 
						} else { 
							if (!joueur_1.gagne && !joueur_2.gagne) { /* le est la dans la partie mais dans le premier tour */
								char indice_tour = determine_tour(determine_tour_lst);
								dessine_tour(indice_tour, noir, &joueur_1, &joueur_2);
								jouer_tour(determine_tour_lst, indice_tour, grille, grille_contenu, taille_grille, &joueur_1, &joueur_2);
								dessine_elt_map(grille_contenu, grille, &joueur_1, &joueur_2, taille_grille); 
								retour_jeu(&menu, &jeu, &taille_grille, &joueur_1, &joueur_2, grille_contenu, determine_tour_lst_premier_tour, determine_tour_lst);
								joueur_1.gagne = condition_fin_jeu(grille_contenu, &joueur_2, &joueur_1, taille_grille);
								joueur_2.gagne = condition_fin_jeu(grille_contenu, &joueur_1, &joueur_2, taille_grille);
								menu.est_menu_fin_jeu = (joueur_1.gagne || joueur_2.gagne) ? 1 : 0;
							} else {
								if (menu.est_menu_fin_jeu) { /* fin de partie du joueur vs joueur */
									fonction_bouton_menu_fin(&jeu_en_cour, &menu, &jeu, &taille_grille, grille_contenu, determine_tour_lst_premier_tour, determine_tour_lst, &joueur_1, &joueur_2);
									if (joueur_1.gagne) { 
										dessine_menu_fin_jeu(&joueur_1, &joueur_2, orange, noir, blanc);
									} else if (joueur_2.gagne) {
										dessine_menu_fin_jeu(&joueur_2, &joueur_1, orange, noir, blanc);
									}
								}
							}
						}
					} else if (jeu.est_jeu_IA) { /* la partie commence dans joueur vs IA */
						if (!menu.est_menu_fin_jeu) { 
							Rect espace_grille = {100, 100, 300, 300};
							dessine_grille(taille_grille, noir, 0, espace_grille, grille);
							dessine_page_partie(noir, blanc, orange);
						}
						if (jeu.premier_tour) { /* premier tour de la  partie de joueur vs IA */
							char tour = determine_tour(determine_tour_lst_premier_tour);
							if (tour) { 
								dessine_tour(tour + 1, noir, &joueur_1, &joueur_2);
							} else {
								dessine_tour(tour, noir, &joueur_1, &joueur_2);
							}
							tour_1_partie_IA(determine_tour_lst_premier_tour, tour, grille, grille_contenu, taille_grille, &joueur_1, &joueur_2, &jeu);
							retour_jeu(&menu, &jeu, &taille_grille, &joueur_1, &joueur_2, grille_contenu, determine_tour_lst_premier_tour, determine_tour_lst);
							dessine_elt_map(grille_contenu, grille, &joueur_1, &joueur_2, taille_grille); 
						} else { 
							if (!joueur_1.gagne && !joueur_2.gagne) {  /* jeu est dans la partie de joueur vs IA mais pas dans la premier tour */
								char indice_tour = determine_tour(determine_tour_lst);
								dessine_tour(indice_tour, noir, &joueur_1, &joueur_2);
								jouer_tour_partie_IA(determine_tour_lst, indice_tour, grille, grille_contenu, taille_grille, &joueur_1, &joueur_2, &jeu);
								dessine_elt_map(grille_contenu, grille, &joueur_1, &joueur_2, taille_grille); 
								retour_jeu(&menu, &jeu, &taille_grille, &joueur_1, &joueur_2, grille_contenu, determine_tour_lst_premier_tour, determine_tour_lst);
								joueur_1.gagne = condition_fin_jeu(grille_contenu, &joueur_2, &joueur_1, taille_grille);
								joueur_2.gagne = condition_fin_jeu(grille_contenu, &joueur_1, &joueur_2, taille_grille);
								menu.est_menu_fin_jeu = (joueur_1.gagne || joueur_2.gagne) ? 1 : 0;
							} else {
								if (menu.est_menu_fin_jeu) {  /* menu de fin de partie */
									fonction_bouton_menu_fin(&jeu_en_cour, &menu, &jeu, &taille_grille, grille_contenu, determine_tour_lst_premier_tour, determine_tour_lst, &joueur_1, &joueur_2);
									if (joueur_1.gagne) {
										dessine_menu_fin_jeu(&joueur_1, &joueur_2, orange, noir, blanc);
									} else if (joueur_2.gagne) {
										dessine_menu_fin_jeu(&joueur_2, &joueur_1, orange, noir, blanc);
									}
								}
							}
						}
					}
				}
			}
		} else if (regles.est_regles) { /* le jeu est dans les règles */
			dessine_page_regles(noir, blanc, orange, options.est_sombre);
			retour(&regles.est_regles, &menu.est_menu); 
		} else if (options.est_option) { /* le jeu est dans les paramètres */
			dessine_page_setting(orange, blanc, noir);
			fonction_setting(&options, &menu.est_menu);
		}
	}
	FermerGraphique();
	return EXIT_SUCCESS;
}