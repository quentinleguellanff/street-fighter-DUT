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




    public:
        Broly(int);
        void debout(int& cptanimstatic,sf::Clock& clockanim);
        virtual ~Broly();

};

#endif // BROLY_H
