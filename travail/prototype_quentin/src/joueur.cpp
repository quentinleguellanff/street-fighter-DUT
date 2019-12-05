#include "Joueur.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

Joueur::Joueur(int i)
{
    _numero = i;
    _nbPointVie = 500;
    _barreVie.setFillColor(sf::Color(0,0,255,150));
    if(_numero == 1){
        _barreVie.setPosition(20.f, 20.f);
    }
    else{
        _barreVie.setPosition(660.f, 20.f);

    }
    _barreVie.setSize(sf::Vector2f(_nbPointVie,50.f));


}

sf::RectangleShape Joueur::getBarreVie(){
    return _barreVie;
}

Joueur::~Joueur()
{
    //dtor
}
