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
        bool _ok;




    public:
        Broly(int);
        void debout(sf::Clock& clock);
        void avancer(sf::Clock& clock);
        void reculer(sf::Clock& clock);
        void sauter(sf::Clock& clock);
        bool coupDePoing(sf::Clock& clock);
        virtual ~Broly();

};

#endif // BROLY_H
