#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Player
{
private:
	int _numPlayer;		// numéro du joueur (1 ou 2)
	int _PV;			// points de vie du joueur
	sf::RectangleShape _barrePV;	// barre de vie graphique du joueur sous la forme d'un rectangle

	void _resetAttributs();	//initialisation des attributs de position
	int _posHorizontale;	//attribut de position horizontale
	int _posVerticale;		//attribut de position verticale
	int _action;			//attribut déterminant l'action à effectuer
	/* 	relation int-action
	   -1 - rien
	    0 - garde
		1 - punch
		2 - kick
		3 - SP
	*/

	// attributs des joysticks permettant de diriger le champion
	float joystick0_axisX;	
	float joystick0_axisY;
	float joystick1_axisX;
	float joystick1_axisY;

public:
	Player(){};		//constructeur vide
	Player(int,sf::RenderWindow&);	//constructeur de Player
	
	void recuperationCommandesP1();	//recuperation des commandes dans le cas du joueur 1
	void recuperationAttaquesP1();	//recuperation d'une demande de coup de point ou pied dans le cas ou le joueur est en l'air
	
	void recuperationCommandesP2();	//recuperation des commandes dans le cas du joueur 2
	void recuperationAttaquesP2();	//recuperation d'une demande de coup de point ou pied dans le cas ou le joueur est en l'air

	void gestionDesCommandes(bool avancer, bool reculer, bool accroupi, bool saut, bool sautAvant, bool sautArriere,bool garde, bool punch, bool kick, bool SP1);
	// gestion de la superposition decommandes et de l'ordre d'importance de ces dernières

	int getPosHorizontale();	//recupération de la position horizontale demandée
	int getPosVerticale();		//recupération de la position verticale demandée
	int getAction();			//recupération de l'action demandée
	int getPV();				//recupération des points de vie
	void resetPV();				//reinitialisation des points de vie
	void setDegats(int);		//inflige un nombre de dégats passés en arguments
	sf::RectangleShape getBarrePV();	//renvoi la barre de vie pour permettre son affichage
};

#endif