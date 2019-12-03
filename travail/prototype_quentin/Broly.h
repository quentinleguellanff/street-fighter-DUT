#ifndef BROLY_H
#define BROLY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


class Broly : public sf::Sprite
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
        bool _ok;

        sf::RectangleShape _hurtbox;




    public:
        Broly(int);
        void debout(sf::Clock& clock);
        void avancer(sf::Clock& clock);
        void reculer(sf::Clock& clock);
        void sauter(sf::Clock& clock);
        bool coupDePoing(sf::Clock& clock,sf::RectangleShape hurtboxEnnemi,bool& touche);
        int getorientation();
        bool collisioncoup(sf::RectangleShape hurtboxEnnemi);
        bool collisioncorps(Broly& ennemi);
        bool prendcoup(sf::Clock& clock);
        sf::RectangleShape gethurtbox();
        virtual ~Broly();

};

#endif // BROLY_H
