#ifndef BACKGROUND_H
#define BACKGROUND_H


#include "hitbox.h"
#include "personnage.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

class Background
{
private:

	sf::Texture _textureBackground;
	sf::Sprite _spriteBackground;
	sf::RectangleShape _solBackground;
	sf::RectangleShape _wallLeft;
	sf::RectangleShape _wallRight;
	int _hauteurSol;
	int _limiteSol;
	int _largeurWindow;

public:

	Background(){};
	Background(sf::RenderWindow& window);
	sf::Sprite getSprite() const;
	sf::RectangleShape getSol() const;
	sf::RectangleShape getWallLeft() const;
	sf::RectangleShape getWallRight() const;
	int getBottom() const;
	int getLeftLimit() const;
	int getRightLimit() const;
};

#endif