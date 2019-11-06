#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "fonction.h"
#include "hitbox.h"
#include "background.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

const int SCALE=2.5;

class Personnage
{
private:
 
    sf::Texture _texturePersonnage; //Texture du perso
    sf::Sprite _spritePersonnage;     //Sprite du perso
    float _x;                   //Position X du perso
    float _y;                   //Position Y du perso
    sf::Vector2f _tailleSprite;
    void setSprite(int, int, int, int);
    Hitbox _structure;

public:

    Personnage(){};
    Personnage(Background);    //Constructeur
    int getTailleY() const;
    sf::Vector2f getTaille() const;
    void keepInWalls(Background);
    sf::Sprite getSprite() const; //récupère le sprite du personnage
    int	getPosX() const;
    int getPosY() const;
	void reset(Background);

	sf::RectangleShape getCorps() const;
	sf::RectangleShape getBras() const;


    void moveRight(Background,int);
    void moveLeft(Background,int);
    void jumpNoMove(Background,int);
    void jumpMoveRight(Background,int,bool);
    void jumpMoveLeft(Background,int,bool);

    void punch(Background ,int);
    void kick(Background b,int x);
  
 
};

#endif