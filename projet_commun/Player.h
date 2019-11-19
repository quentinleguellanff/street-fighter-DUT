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
	int _numPlayer;

	void _resetAttributs();
	int _posHorizontale;
	int _posVerticale;
	int _action;
	/* 	relation int-action
		0-rien
		1-punch
		2-kick
		3-SP1
	*/
	sf::Event _eventTouche;
	float joystick0_axisX;
	float joystick0_axisY;
	float joystick1_axisX;
	float joystick1_axisY;

public:
	Player(){};
	Player(int);
	void recuperationCommandesP1();
	void recuperationCommandesP2();
	void gestionDesCommandes(bool avancer, bool reculer, bool accroupi, bool saut, bool sautAvant, bool sautArriere, bool punch, bool kick, bool SP1);
	int getPosHorizontale();
	int getPosVerticale();
	int getAction();

};

#endif