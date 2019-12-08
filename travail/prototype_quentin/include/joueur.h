#ifndef JOUEUR_H
#define JOUEUR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"

class Joueur
{

    private:
        int _nbPointVie;
        int _numero;

        bool _avancedroite;
        bool _avancegauche;
        bool _saut;
        bool _couppoing;
        bool _attaque;
        bool _peutcoup;
        bool _ensaut;
        bool _statique;
        bool _peutsauter;
        bool _ensautgauche;
        bool _ensautdroite;

        Broly _Broly;
        sf::RectangleShape _barreVie;


    public:

        bool prendcoup;

        Joueur(int i,Broly& broly);
        virtual ~Joueur();

        void prendDegats();
        void recupCommande();
        void avancedroite(sf::Clock& clockanim, sf::Clock& clockmove,sf::RenderWindow& window);
        void avancegauche(sf::Clock& clockanim, sf::Clock& clockmove,sf::RenderWindow& window);
        void coupDePoing(sf::Clock& clock,sf::RectangleShape hurtboxEnnemi,bool& touche,sf::RenderWindow& window);
        void statique(sf::Clock& clock,sf::RenderWindow& window);
        void antiSpam(sf::Event& event);
        void prendCoup(sf::Clock& clock,sf::Clock& clockmove,bool& touche, sf::RenderWindow& window);
        void saut(sf::Clock& clock, sf::Clock& clockmove,sf::RenderWindow& window);

        sf::RectangleShape getBarreVie();
        Broly getBroly();
        sf::RectangleShape getHurtbox();
        sf::RectangleShape getHitbox();
};

#endif // JOUEUR_H
