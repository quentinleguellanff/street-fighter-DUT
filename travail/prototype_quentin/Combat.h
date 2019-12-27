#ifndef COMBAT_H
#define COMBAT_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"
#include "joueur.h"


class Combat
{
    public:
        Combat(Joueur& joueur1,Joueur& joueur2, sf::RectangleShape& sol);
        bool partie(sf::RenderWindow& window,bool& toucheJ1, bool& toucheJ2);
        virtual ~Combat();

    protected:

    private:
        Joueur _joueur1;
        Joueur _joueur2;
        sf::RectangleShape _sol;

};

#endif // COMBAT_H
