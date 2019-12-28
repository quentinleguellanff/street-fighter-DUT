#ifndef COMBAT_H
#define COMBAT_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"
#include "joueur.h"

using namespace std;


class Combat
{
    public:
        Combat(Joueur& joueur1,Joueur& joueur2, sf::RectangleShape& sol);
        bool partie(sf::RenderWindow& window,bool& toucheJ1, bool& toucheJ2);
        bool hitGraphique(sf::RenderWindow&);
        virtual ~Combat();

    protected:

    private:
        Joueur _joueur1;
        Joueur _joueur2;
        sf::RectangleShape _sol;
        sf::Texture _Texturehitspark;
        sf::Texture _TextureBackground;
        sf::Sprite _spritehitspark;
        sf::Sprite _spriteBackground;
        sf::Clock _clock;
        bool hitspark;
        int _cptanim;

};

#endif // COMBAT_H
