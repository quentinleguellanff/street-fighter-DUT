#ifndef JOUEUR_H
#define JOUEUR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class Joueur
{

    private:
        int _nbPointVie;
        sf::RectangleShape _barreVie;
        int _numero;

    public:
        Joueur(int i);
        virtual ~Joueur();
        sf::RectangleShape getBarreVie();

};

#endif // JOUEUR_H
