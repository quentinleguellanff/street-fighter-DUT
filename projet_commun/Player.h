#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "IncludeManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Player
{
private:
	Personnage* _champion;
	double ratioScale;
    sf::Sprite _effet;
	sf::Sprite _portrait;
	sf::Sprite _barreInfos;
	sf::Texture _textureBI;
	int _PV;			// points de vie du joueur
	std::vector<sf::RectangleShape> _barrePV;	// barre de vie graphique du joueur sous la forme d'un rectangle

	int _energie;
	int _sauvegardeEnergie;
	sf::Clock _clockPasAssez;
	std::vector<sf::RectangleShape> _barreEnergie;

	// attributs des joysticks permettant de diriger le champion
	float joystick0_axisX;
	float joystick0_axisY;
	float joystick0_axisZ;
	float joystick0_axisR;

	float joystick1_axisX;
	float joystick1_axisY;
	float joystick1_axisZ;
	float joystick1_axisR;

	int _posHorizontale;	//attribut de position horizontale
	int _posVerticale;		//attribut de position verticale
	int _action;			//attribut déterminant l'action à effectuer
	/* 	relation entier - action effectuée
	   -1 - rien
	    0 - garde
		1 - punch
		2 - punchSP
		3 - kick
		4 - kickSP
		5 - SP
	*/

	int _prendCoup;
	bool _apparitionsFini;
	bool _actionFini;

	std::vector<bool> _tabActions;
	/* 0-avancer | 1-reculer | 2-accroupi | 3-saut | 4-sautAvant | 5-sautArriere | 6-garde | 7-punch | 8-punchSP | 9-kick | 10-kickSP | 11-SP */
	std::vector<bool> _tabPeutAction;
	/* 0-peutPunch / 1-peutPunchSP / 2-peutKick / 3-peutKickSP / 4-peutSp */

	//std::vector<sf::Clock> _clockAnim;
	/* 0-clock pour les sprites | 1-clock pour le deplacement */


	sf::Clock _clockEffet;
	bool _effetEnCours;
	int _cptAnimEffet;
	sf::Texture _textureEffet;
	sf::Music son;
	sf::Sprite _spriteHitSpark;

public:
	Player(){};		//constructeur vide
	Player(int,sf::RenderWindow&);	//constructeur de Player

	void resetPlayer();
	void resetAttributs();	//initialisation des attributs de position

	void setChampion(Personnage*);
	Personnage* getChampion();
	sf::Sprite getEffet();

	void recuperationAttaqueLancee();

	void peutAttaquerP1(sf::Event&, sf::RenderWindow&);
	void recuperationCommandesP1(Player&);	//recuperation des commandes dans le cas du joueur 1
	void recuperationAttaquesP1();	//recuperation d'une demande de coup de point ou pied dans le cas ou le joueur est en l'air

	void peutAttaquerP2(sf::Event&, sf::RenderWindow&);
	void recuperationCommandesP2(Player&);	//recuperation des commandes dans le cas du joueur 2
	void recuperationAttaquesP2();	//recuperation d'une demande de coup de point ou pied dans le cas ou le joueur est en l'air

	void gestionDesCommandes(Player&);
	// gestion de la superposition decommandes et de l'ordre d'importance de ces dernières

	bool lancerApparition();
	bool lancerActions(Player&);

	bool finPartie();
	int getPV();				//recupération des points de vie
	void resetPV();				//reinitialisation des points de vie
	void setDegats(int);		//inflige un nombre de dégats passés en arguments

	void afficherEnergie(sf::RenderWindow&);
	void affichageChampion(sf::RenderWindow&);

	int getAction();
	int* getPrendCoup();
	void setPrendCoup(int);

	void affichageEffet(sf::RenderWindow& window);

	int getPC();
};

#endif
