#ifndef DHALSIM_H
#define DHALSIM_H

#include "../IncludeManager.h"

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


class Dhalsim : public sf::Sprite
{
private:
	const int SCALE=3.5;
	int _orientation;
	sf::Texture _texture;

	sf::Vector2f _tailleSprite;
	Scene _scene;

	float _posX;                   //Position X du perso
    float _posY;                   //Position Y du perso

	int _cptAvancer;
	int _cptReculer;
	int _cptStatic;
	int _cptAccroupi;

	int _cptSauter;

	int _cptApparition;
	int _cptAction;

public:
	Dhalsim(){};
	Dhalsim(int,const Scene&);
	void setSprite(int,int,int,int);

	void keepInWalls();
	sf::Sprite getSprite() const;
	int getOrientation() const;


	void reset();
	void resetAccroupi();
	void rotate(const sf::Sprite&);

	void statique(sf::Clock&,const sf::Sprite&);
	void garde(sf::Clock&);
	void avancer(sf::Clock&,const sf::Sprite&);
	void reculer(sf::Clock&);

	bool sauter(sf::Clock&,sf::Clock&);
	bool sauterAvant(sf::Clock&,const sf::Sprite&);
	bool sauterArriere(sf::Clock&);
	void accroupi(sf::Clock&,bool);

	bool apparition(sf::Clock&,sf::Sprite&);
	bool punch(sf::Clock&);
	bool sautPunch(sf::Clock&);
	bool kick(sf::Clock&);
	bool sautKick(sf::Clock&);
	bool SP(sf::Clock&,sf::Sprite&);
	
};

#endif