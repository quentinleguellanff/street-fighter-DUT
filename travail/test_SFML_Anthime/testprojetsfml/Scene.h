#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Scene
{
private:
	sf::Texture _textureScene;
	sf::Sprite _spriteScene;
	sf::Vector2u _tailleWindow;

	sf::RectangleShape _solScene;
	sf::RectangleShape _wallLeft;
	sf::RectangleShape _wallRight;
	int _hauteurSol;
	int _limiteSol;
	int _largeurWindow;

	void chargementXenoverse();

public:
	Scene(){};
	Scene(sf::RenderWindow&, int);
	sf::Sprite getSprite() const;	// Renvoi la scene

	void lancerMusique(sf::Music&);

	// Permet de dessiner les limites de la map	& gerer les positions limites
	int getBottom() const;
	int getLeftLimit() const;
	int getRightLimit() const;

	sf::RectangleShape getSol() const;
};

#endif