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
        int _cpttouche;

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
        bool _seretourner;
        bool _prendcoup;
        bool _pause;



        Broly _Broly;
        sf::RectangleShape _barreVie;
        sf::Clock _clockjoueur;


    public:

        Joueur();
        Joueur(int i,Broly& broly);
        virtual ~Joueur();

        void prendDegats();
        void recupCommande();
        void avancedroite(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi);
        void avancegauche(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi);
        void coupDePoing(sf::RectangleShape hurtboxEnnemi,bool& touche,sf::RenderWindow& window);
        void statique(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi);
        void antiSpam(sf::Event& event);
        void prendCoup(bool& touche, sf::RenderWindow& window);
        void saut(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi,bool ennemiensaut);
        void setVitesseX(int);
        int getVitesseX();
        int getOrientation();
        void deplacer(int);
        void seretourner(sf::RectangleShape hurtboxEnnemi);
        sf::RectangleShape getBarreVie();
        Broly getBroly();
        bool getEtat();
        void pauseAnim();
        sf::RectangleShape getHurtbox();
        sf::RectangleShape getHitbox();
};

#endif // JOUEUR_H
