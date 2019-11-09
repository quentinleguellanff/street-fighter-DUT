#ifndef JOUEUR_H
#define JOUEUR_H
#include <SFML/Graphics.hpp>
#include "Broly.h"
class Joueur
{
    private:
        sf::Sprite _perso;
    public:
        Joueur(sf::Sprite& Perso);
        sf::Sprite getPerso();
        bool avancer();
        bool reculer();
        bool coup();
        bool couppied();
        bool baisser();
        bool sauter();
};

#endif // JOUEUR_H
