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
        float _vitesseX;
        bool _ok;

        sf::Sprite spriteBroly;
        sf::RectangleShape _hurtbox;
        sf::RectangleShape _hitbox;
        sf::Clock _clockanim;
        sf::Clock _clockmove;




    public:
        Broly();
        Broly(int);
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
        virtual ~Broly();

};

#endif // BROLY_H
