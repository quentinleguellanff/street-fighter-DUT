#ifndef BROLY_H
#define BROLY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


class Broly
{
    private:
        int _orientation;
        sf::Texture _Texture;
        int _scale;
        int _cptanimstatic;
        int _cptanimavancer;
        int _cptanimjump;
        int _cptAnimCoupPoing;
        int _cptanimprendcoup;
        int cptanimprendcoupbis;
        int _vsaut;
        bool _ok;
        sf::Sprite spriteBroly;

        sf::RectangleShape _hurtbox;
        sf::RectangleShape _hitbox;




    public:
        Broly();
        Broly(int);
        void debout(sf::Clock& clock,sf::RenderWindow& window);
        void avancer(sf::Clock& clockanim,sf::Clock& clockmove,sf::RenderWindow& window);
        void reculer(sf::Clock& clockanim,sf::Clock& clockmove,sf::RenderWindow& window);
        bool sauter(sf::Clock& clock,sf::Clock& clockmove,sf::RenderWindow& window,int vitesse);
        bool coupDePoing(sf::Clock& clock,sf::RectangleShape hurtboxEnnemi,bool& touche,sf::RenderWindow& window);
        int getorientation();
        bool collisioncoup(sf::RectangleShape hurtboxEnnemi);
        bool collisioncorps(Broly& ennemi);
        void prendcoup(sf::Clock& clock,sf::Clock& clockmove,bool& touche,sf::RenderWindow& window);
        sf::RectangleShape gethurtbox();
        sf::RectangleShape gethitbox();
        void resetcoup();
        void ResteDansFenetre();
        virtual ~Broly();

};

#endif // BROLY_H
