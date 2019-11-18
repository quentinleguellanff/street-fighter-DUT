#ifndef DHALSIM_H
#define DHALSIM_H

#include "Scene.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

const int SCALE=3.5;

class Dhalsim : public sf::Sprite
{
private:
	int _orientation;
	sf::Texture _texture;
	sf::Vector2f _tailleSprite;
	Scene _scene;
	float _posX;                   //Position X du perso
    float _posY;                   //Position Y du perso

	int _cptStatic;
	int _cptAvancer;
	int _cptReculer;

	int _cptSauter;

	int _cptApparition;
	int _cptEffet;
	int _cptPunch;

	void _setSprite(int, int, int, int);

public:
	Dhalsim(){};
	Dhalsim(int,const Scene&);

	void keepInWalls();
	sf::Sprite getSprite() const;

	void reset();

	void statique(sf::Clock&);
	void avancer(sf::Clock&);
	void reculer(sf::Clock&);

	void sauter(sf::Clock&);

	bool apparition(sf::Clock&,sf::Sprite&);
	void punch(sf::Clock&);
	
};

#endif