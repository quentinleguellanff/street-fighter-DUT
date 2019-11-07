#include "fonction.h"
#include "hitbox.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string.h>

using namespace std;

Hitbox::Hitbox(sf::Vector2f t,int posX,int posY)
{
    _taille.x=t.x;_taille.y=t.y;
    _corps.setSize(sf::Vector2f(_taille.x/2, _taille.y*0.9));
    _corps.setPosition(posX-(_taille.x*0.7),posY+_taille.y*0.1);
    _corps.setFillColor(sf::Color(250, 250, 250,1));
    _corps.setOutlineThickness(5);
	_corps.setOutlineColor(sf::Color(250, 0, 0));

    _brasD.setSize(sf::Vector2f(_taille.x/5, _taille.y*0.2));
    _brasD.setPosition(posX-_taille.x*0.2,posY+_taille.y*0.35);
    _brasD.setFillColor(sf::Color(250, 250, 250,1));
    _brasD.setOutlineThickness(5);
	_brasD.setOutlineColor(sf::Color(250, 0, 0));

}

void Hitbox::setCorps(std::string s,int posX,int posY)
{
	if(s=="jump")
	{
		_corps.setSize(sf::Vector2f(_taille.x/1.5, _taille.y));
		_corps.setPosition(posX-(_taille.x*0.7),posY+_taille.y*0.1);	
	}else if(s=="forward")
		_corps.setPosition(posX-(_taille.x*0.8),posY+_taille.y*0.1);
	else if("punch")
		_corps.setPosition(posX-(_taille.x*1.3),posY+_taille.y*0.1);
}

void Hitbox::setBrasD(std::string s,int i,int posX,int posY)
{
	if(s=="forward")
	{
		if(i>=0 && i<6)
			_brasD.setSize(sf::Vector2f(0, 0));
		else
			_brasD.setSize(sf::Vector2f(_taille.x*0.2, _taille.y*0.2));

		_brasD.setPosition(posX-_taille.x*0.3,posY+_taille.y*0.4);
	}else if(s=="backward" || s=="jump")
	{
		_brasD.setSize(sf::Vector2f(0, 0));
	}else if("punch")
	{
		if(i==2 || i==3)
		{
			_brasD.setSize(sf::Vector2f(_taille.x*0.8, _taille.y*0.2));
			_brasD.setPosition(posX-(_taille.x*0.80),posY+_taille.y*0.35);
		}else
			_brasD.setSize(sf::Vector2f(0, 0));
		
	}
}









sf::RectangleShape Hitbox::getBody() const
{
    return _corps;
}

sf::RectangleShape Hitbox::getTete() const
{
    return _tete;
}

sf::RectangleShape Hitbox::getBrasD() const
{
    return _brasD;
}