#include "include/Broly.h"
#include "include/Arene.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace std;

Broly::Broly(int Orientation)
{
    _orientation = Orientation; // permet de définir l'orientation du personnage
    _Texture.loadFromFile("Brolyspriteok.png"); //load de la texture du personnage
    _scale = 2; // ratio de scale du personnage, zoom le sprite pour qu'il apparaisse plus grand
    setTexture(_Texture); // charge le sprite avec la texture initialisé précedemment
    setScale(_scale*_orientation,_scale); //permet de mettre le scale en définissant l'orientation du perso
    setPosition(300.f,460.f); // position initiale du perso/sprite dans la fenetre
    /*sf::Vector2i tailleBroly = sf::Vector2i(120,200);
    sf::IntRect(2,467,120,200);*/
    setTextureRect(sf::IntRect(2, 467,120,200));
    _cptanimstatic = 0;
    _cptanimavancer = 0;
    _cptanimjump = 0;
    _cptAnimCoupPoing = 0;
    if(_orientation == -1){
        setOrigin(120.f, 0.f);
    }
    _ok = false;
}

Broly::~Broly()
{
    //dtor
}

void Broly::debout(sf::Clock& clock)
{
    _cptanimjump = 0;
    sf::Time elapsed = clock.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    if(timeanim > 100){
        _cptanimstatic +=1;
        clock.restart();
    }
    if(_cptanimstatic >= 10){
        _cptanimstatic = 0;
    }
    setTextureRect(sf::IntRect(2+_cptanimstatic*123, 466,121,201));
}

void Broly::avancer(sf::Clock& clock)
{
    if(_cptanimavancer == 0){
        setTextureRect(sf::IntRect(2, 873,128,200));
    }
    sf::Time elapsed = clock.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    if(timeanim > 70){
        _cptanimavancer += 1;
        clock.restart();
    }
    if(_cptanimavancer >= 13){
        _cptanimavancer = 1;
    }
    if(_cptanimavancer > 0){
        setTextureRect(sf::IntRect(2+_cptanimavancer*130, 873,128,200));
    }
}

void Broly::reculer(sf::Clock& clock)
 {
    setTextureRect(sf::IntRect(2, 11437,153,207));
    sf::Time elapsed = clock.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    cout << "temps anim reculer " << timeanim << endl;
    if(timeanim > 70){
        setTextureRect(sf::IntRect(157, 11437,153,207));
    }

 }

void Broly::sauter(sf::Clock& clock){

    sf::Time elapsed = clock.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    if(timeanim > 100){
        _cptanimjump += 1;
        clock.restart();
    }
    if(_cptanimjump >= 5){
        setTextureRect(sf::IntRect(2+(5*158), 1650,156,208));
    }
    else{
        setTextureRect(sf::IntRect(2+_cptanimjump*158, 1650,156,208));
    }
 }

bool Broly::coupDePoing(sf::Clock& clock){

        if(!_ok){
            setPosition(getPosition().x+112,getPosition().y+20);
            _ok = true;
        }
        sf::Time elapsed = clock.getElapsedTime();
        int timeanim = elapsed.asMilliseconds();
        if(timeanim > 30){
            _cptAnimCoupPoing++;
            clock.restart();
        }

        if(_cptAnimCoupPoing >= 5){
            _cptAnimCoupPoing = 0;
            setTextureRect(sf::IntRect(2, 466,121,201));
            cout <<" position du sprite "<< endl;
            cout << getPosition().x << endl;
            cout << getPosition().y << endl;
            setPosition(getPosition().x-112,getPosition().y-20);
            _ok = false;
            return false;
        }
        else{
            setTextureRect(sf::IntRect(2+_cptAnimCoupPoing*179, 2765,177,191));
        }
        return true;
}
