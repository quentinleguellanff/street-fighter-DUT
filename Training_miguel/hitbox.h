#ifndef HITBOX_H
#define HITBOX_H


#include "personnage.h"
#include "background.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string.h>


class Hitbox
{
private:	
	    sf::Vector2f _taille;

	    sf::RectangleShape _corps;
	    sf::RectangleShape _tete;
	    sf::RectangleShape _brasD;
	    sf::RectangleShape _jambeD;

	    sf::Vector2f posMainD;
	    sf::Vector2f posPiedD;

	    int _rotation;

public:

	Hitbox(){};
	Hitbox(sf::Vector2f taille,int posX,int posY,int rotate);
	void setCorps(std::string s,int posX,int posY);
	void setBrasD(std::string s,int i,int posX,int posY);



	sf::RectangleShape getBody() const;
	sf::RectangleShape getTete() const;
	sf::RectangleShape getBrasD() const;



};


#endif