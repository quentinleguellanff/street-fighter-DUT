#include "fonction.h"
#include "hitbox.h"
#include "personnage.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

using namespace std;

Background::Background(sf::RenderWindow& window)
{
	if(!_textureBackground.loadFromFile("images/ring_xenoverse_V2.jpg")){cout<<"Erreur chargement de background"<<endl;}
	else{
		_textureBackground.setSmooth(true);
		_spriteBackground.setTexture(_textureBackground);
	}
	_hauteurSol=75.f;
	_limiteSol=window.getSize().y-_hauteurSol;
	_largeurWindow=window.getSize().x;

	_solBackground.setSize(sf::Vector2f(1920.f, _hauteurSol));
	_solBackground.setPosition(0.f, _limiteSol);
	_solBackground.setFillColor(sf::Color(250,250,250,0));
	//_solBackground.setOutlineThickness(2.f);
	//_solBackground.setOutlineColor(sf::Color(250, 130, 1));

	_wallLeft.setSize(sf::Vector2f(5.f, window.getSize().y));
	_wallLeft.setPosition(0.f, 0.f);
	_wallLeft.setFillColor(sf::Color(50,250,60,1));
	
	_wallRight.setSize(sf::Vector2f(5.f, window.getSize().y));
	_wallRight.setPosition(window.getSize().x-5, 0.f);
	_wallRight.setFillColor(sf::Color(50,250,60,1));
	
}

sf::Sprite Background::getSprite() const
{
	return _spriteBackground;
}

sf::RectangleShape Background::getSol() const
{
	return _solBackground;
}

sf::RectangleShape Background::getWallLeft() const
{
	return _wallLeft;
}

sf::RectangleShape Background::getWallRight() const
{
	return _wallRight;
}

int Background::getBottom() const
{
	return _limiteSol;
}

int Background::getLeftLimit() const
{
	return _wallLeft.getSize().x;
}

int Background::getRightLimit() const
{
	return _largeurWindow-_wallRight.getSize().x;
}