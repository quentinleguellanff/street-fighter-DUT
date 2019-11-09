#include "Broly.h"
#include "Arene.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace std;

Broly::Broly(int Orientation)
{
    _orientation = Orientation;
    _Texture.loadFromFile("Brolyspriteok.png");
    _scale = 2;
    setTexture(_Texture);
    setScale(_scale*_orientation,_scale);
    setPosition(0.f,460.f);
    setTextureRect(sf::IntRect(2, 467,120,200));
    setOrigin(120.f, 0.f);
}

Broly::~Broly()
{
    //dtor
}

void Broly::debout(int& cptanimstatic,sf::Clock& clock)
{
    sf::Time elapsed = clock.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    cout << "temps pour le broly classe  : " << timeanim << endl;
    if(timeanim > 100){
        cptanimstatic++;
        clock.restart();
    }
    cout << "compteur : " <<  cptanimstatic << endl;
    if(cptanimstatic >= 10){
        cptanimstatic = 0;
    }
    setTextureRect(sf::IntRect(2+cptanimstatic*123, 466,121,201));
}

