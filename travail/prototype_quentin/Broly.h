#ifndef BROLY_H
#define BROLY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Personnage.h"

class Broly : public Personnage
{
    private:
        bool _ok;
        int cptanimprendcoupbis;
    public:
        Broly();
        Broly(int,sf::RectangleShape&);
        virtual ~Broly();
        void debout(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi) override;
        void avancer(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi) override;
        void reculer(sf::RenderWindow& window) override;
        bool coupDePoing(sf::RectangleShape,bool&,sf::RenderWindow&) override;
        void prendCoup(bool&,sf::RenderWindow&) override;
        bool sauter(sf::RenderWindow&,sf::RectangleShape) override;
        bool sauterAvancer(sf::RenderWindow&,sf::RectangleShape) override;
        bool sauterArriere(sf::RenderWindow&,sf::RectangleShape) override;

        void restartPrendcoup();
        void resetcoup();
        void retourner();

        /*
        Broly();
        Broly(int,sf::RectangleShape& sol);
        void debout(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi);
        void avancer(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi);
        void reculer(sf::RenderWindow& window);
        bool sauter(sf::RenderWindow& window,int direction,bool ennemiensaut,sf::RectangleShape hurtboxEnnemi);
        bool coupDePoing(sf::RectangleShape hurtboxEnnemi,bool& touche,sf::RenderWindow& window);
        int getorientation();
        bool collisioncoup(sf::RectangleShape hurtboxEnnemi);
        bool collisioncorps(sf::RectangleShape hurtboxEnnemi);
        void prendcoup(bool& touche,sf::RenderWindow& window);
        sf::RectangleShape gethurtbox();
        sf::RectangleShape gethitbox();
        void resetcoup();
        void restartPrendcoup();
        void ResteDansFenetre();
        void setVitesseX(int);
        int getVitesseX();
        void collisionPersonnage(sf::RectangleShape hurtboxEnnemi);
        void collision(sf::RectangleShape hurtboxEnnemi);
        void collisionsaut(sf::RectangleShape hurtboxEnnemi);
        void deplacer(int vitesse);
        void retourner();
        void pauseAnimation();
        void restartClock();
        virtual ~Broly();
        sf::Sprite getSprite();
        */

};

#endif // BROLY_H
