#ifndef GESTIONFENETRE_H
#define GESTIONFENETRE_H

#include "IncludeManager.h"
#include "Player.h"
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class GestionFenetre
{
private:
	/* fenetre */
	sf::RenderWindow window;

	/* scene qui définie le fond du combat*/
	Scene scene;

	/* GESTION DES DIFFERENTS MENUS */
	/* variable de selection du menu en cours */
	int selecEcran;

	/* Déclaration menu acceuil */
    MenuPrincipal* menuPrinc;

    /* Déclaration menu commandes */
    MenuCommandes* menuCommandes;

    /* Déclaration menu selection */
    MenuSelection* menuSel;

    /* Déclaration menu sélection scene */
    MenuBackground* menuBackground;


	/* GESTION DU COMBAT */
	/* variables pour affichage ready, fight */
	sf::Texture readyF;
    sf::Sprite readyFight;
	sf::Clock clockReadyFight;

	/* Création des 2 classes Player */
	Player* joueur1;
	Player* joueur2;

	/* variables destinées à la selection du champion */
	int selecChamp_P1;	
	int selecChamp_P2;
	/* Variable de création des deux champions */
	Personnage* champion_P1;
	Personnage* champion_P2;

	/* vecteur de gestion de status des actions du combat */
	std::vector<bool> _tabActionCombat;
	/* 0-apparitionsFinies_P1 | 1-apparitionsFinies_P2 | 2-actionFini_P1 | 3-actionFini_P2 | 4-animationFinLancee | 5-animationFin_P1 | 6-animationFin_P2 */

	/* Musique de fond */
	sf::Music musique;

public:
	GestionFenetre();
	~GestionFenetre(){};

	sf::RenderWindow& returnWindow();
	void action();

	void gestionMenuPrinc(sf::Event&);
	void gestionSelecPerso(sf::Event&);
	void gestionMenuCommande(sf::Event&);
	void gestionSelecScene(sf::Event&);

	void combat(sf::Event&);
	void affichageCombat();
};

#endif