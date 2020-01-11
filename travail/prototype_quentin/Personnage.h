#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class Personnage
{
    protected:
        int _orientation;
        sf::Texture _Texture;
        float _scale;
        int _cptanimstatic;
        int _cptanimavancer;
        int _cptanimjump;
        int _cptAnimCoupPoing;
        int _cptanimprendcoup;
        int _cptanimprendcoupbis;
        int _cptTimePauseAnim;
        float _vsaut;
        float _vitesseX;
        bool _ok;
        float _posY;
        float _posX;

        sf::Sprite _spritePerso;
        sf::RectangleShape _hurtbox;
        sf::RectangleShape _hitbox;
        sf::Clock _clockanim;
        sf::Clock _clockmove;
        sf::Vector2f _tailleSprite;
        sf::RectangleShape _sol;

    public:
        Personnage();
        Personnage(int,sf::RectangleShape&);
        virtual ~Personnage();
        int getorientation();
        bool collisioncoup(sf::RectangleShape hurtboxEnnemi);
        bool collisioncorps(sf::RectangleShape hurtboxEnnemi);
        sf::RectangleShape gethurtbox();
        sf::RectangleShape gethitbox();
        void resetcoup();
        void ResteDansFenetre();
        void setVitesseX(int);
        int getVitesseX();
        void collision(sf::RectangleShape hurtboxEnnemi);
        void collisionsaut(sf::RectangleShape hurtboxEnnemi);
        void deplacer(int vitesse);
        void retourner();
        void restartPrendcoup();
        void setSprite(int,int,int,int);
        sf::Sprite getSprite();

        virtual void debout(sf::RenderWindow&,sf::RectangleShape){}
        virtual void avancer(sf::RenderWindow&,sf::RectangleShape){}
        virtual void reculer(sf::RenderWindow&){}
        virtual bool coupDePoing(sf::RectangleShape,bool&,sf::RenderWindow&){return true;}
        virtual void prendCoup(bool&,sf::RenderWindow&){}
        virtual bool sauter(sf::RenderWindow&,sf::RectangleShape){return true;}
};

#endif // PERSONNAGE_H
