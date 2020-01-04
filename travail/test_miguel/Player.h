#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "IncludeManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Player
{
private:
	Personnage* _champion;
	int _PV;			// points de vie du joueur
	sf::RectangleShape _barrePV;	// barre de vie graphique du joueur sous la forme d'un rectangle

	// attributs des joysticks permettant de diriger le champion
	float joystick0_axisX;	
	float joystick0_axisY;
	float joystick1_axisX;
	float joystick1_axisY;

	void _resetAttributs();	//initialisation des attributs de position
	int _posHorizontale;	//attribut de position horizontale
	int _posVerticale;		//attribut de position verticale
	int _action;			//attribut déterminant l'action à effectuer
	/* 	relation entier - action effectuée
	   -1 - rien
	    0 - garde
		1 - punch
		2 - kick
		3 - SP
	*/

	int _prendCoup;
	bool _apparitionsFini;
	bool _actionFini;
	bool _etaitAccroupi;
	int _derniereAction;

	sf::Clock _clockAnim;
	sf::Clock _clockAttente;
	sf::Sprite _effet;
	sf::Music son;

public:
	Player(){};		//constructeur vide
	Player(int,sf::RenderWindow&);	//constructeur de Player

	void resetPlayer();

	void setChampion(Personnage*);
	Personnage* getChampion();
	sf::Sprite getEffet();
	
	void recuperationCommandesP1(Player&);	//recuperation des commandes dans le cas du joueur 1
	void recuperationAttaquesP1();	//recuperation d'une demande de coup de point ou pied dans le cas ou le joueur est en l'air
	
	void recuperationCommandesP2(Player&);	//recuperation des commandes dans le cas du joueur 2
	void recuperationAttaquesP2();	//recuperation d'une demande de coup de point ou pied dans le cas ou le joueur est en l'air

	void gestionDesCommandes(Player&, bool, bool, bool, bool, bool, bool, bool, bool, bool, bool);
	// gestion de la superposition decommandes et de l'ordre d'importance de ces dernières

	bool lancerApparition();
	bool lancerActions(Player&);

	bool finPartie();
	int getPV();				//recupération des points de vie
	void resetPV();				//reinitialisation des points de vie
	void setDegats(int);		//inflige un nombre de dégats passés en arguments
	sf::RectangleShape getBarrePV();	//renvoi la barre de vie pour permettre son affichage

	int getAction();
	int* getPrendCoup();
	void setPrendCoup(int);

	int getPC();
};

#endif