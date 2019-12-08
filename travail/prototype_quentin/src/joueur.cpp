#include "Joueur.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"

using namespace std;

Joueur::Joueur(int i,Broly& broly)
{

    prendcoup = false;
    _attaque = false;
    _ensaut = false;
    _ensautgauche = false;
    _ensautdroite =false;
    _peutcoup = true;
    _peutsauter = true;
    _numero = i;
    _nbPointVie = 500;
    _barreVie.setFillColor(sf::Color(0,0,255,150));
    if(_numero == 1)
    {
        _barreVie.setPosition(20.f, 20.f); //positionne la barre de vie
        _Broly = broly;
    }
    else
    {
        _barreVie.setPosition(1440-20-_nbPointVie, 20.f); //positionne la barre de vie
        _Broly = broly;
    }
    _barreVie.setSize(sf::Vector2f(_nbPointVie,50.f));


}

void Joueur::prendDegats()
{
    int degats = 50;
    _nbPointVie -= degats;

    if(_nbPointVie <= 0)
        _nbPointVie = 0;

    if(_numero == 1)
    {
        _barreVie.setSize(sf::Vector2f(_nbPointVie,50.f));
    }
    else
    {
        _barreVie.setSize(sf::Vector2f(_nbPointVie,50.f));
        _barreVie.move(degats,0.f);
    }

}

sf::RectangleShape Joueur::getBarreVie()
{
    return _barreVie;
}

void Joueur::recupCommande()
{
    if(_numero == 1)
    {
        _avancedroite = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        _avancegauche = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
        _couppoing = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        _saut = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    }
    else
    {
        _avancedroite = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        _avancegauche = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        _couppoing = sf::Keyboard::isKeyPressed(sf::Keyboard::M);
        _saut = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

    }
}

void Joueur::saut(sf::Clock& clock, sf::Clock& clockmove, sf::RenderWindow& window){
    if(_saut && _peutsauter && !_avancedroite && !_avancegauche){
        _ensaut = true;
        _saut = false;
        _peutsauter = false;
    }
    if(_saut && _peutsauter && _avancedroite && !_avancegauche){
        _ensautdroite = true;
        _saut = false;
        _peutsauter = false;
    }
    if(_saut && _peutsauter && !_avancedroite && _avancegauche){
        _ensautgauche = true;
        _saut = false;
        _peutsauter = false;
    }
    if(_ensautdroite){
        if(!_Broly.sauter(clock,clockmove,window,1)){
            _ensautdroite = false;
            _peutsauter = true;

        }
    }
    if(_ensautgauche){
        if(!_Broly.sauter(clock,clockmove,window,-1)){
            _ensautgauche = false;
            _peutsauter = true;

        }
    }
    if(_ensaut){
        if(!_Broly.sauter(clock,clockmove,window,0)){
            _ensaut = false;
            _peutsauter = true;

        }
    }
}

void Joueur::statique(sf::Clock& clock,sf::RenderWindow& window)
{
    if(!_avancedroite && !_avancegauche && !_ensaut && !_attaque && !prendcoup && !_ensautgauche && !_ensautdroite)
    {
        _Broly.debout(clock,window);
    }
    else if(_avancedroite && _avancegauche && !prendcoup && !_ensaut && !_ensautgauche && !_ensautdroite)
    {
        _Broly.debout(clock,window);
    }
}

void Joueur::avancedroite(sf::Clock& clockanim, sf::Clock& clockmove,sf::RenderWindow& window)
{
    if(_avancedroite && !_avancegauche && !_saut && !_attaque && !prendcoup && !_ensaut && !_ensautgauche && !_ensautdroite)
    {
        if(_Broly.getorientation()== -1)
            _Broly.avancer(clockanim,clockmove,window);
        else
            _Broly.reculer(clockanim,clockmove,window);
    }
}

void Joueur::avancegauche(sf::Clock& clockanim, sf::Clock& clockmove,sf::RenderWindow& window)
{
    if(!_avancedroite && _avancegauche && !_saut && !_attaque && !prendcoup && !_ensaut && !_ensautgauche && !_ensautdroite)
    {
        if(_Broly.getorientation()== -1)
            _Broly.reculer(clockanim,clockmove,window);
        else
            _Broly.avancer(clockanim,clockmove,window);
    }
}

void Joueur::coupDePoing(sf::Clock& clock,sf::RectangleShape hurtboxEnnemi,bool& touche,sf::RenderWindow& window)
{
    if(_couppoing && _peutcoup && !prendcoup && !_ensaut && !_ensautgauche && !_ensautdroite)
    {
        _attaque = true;
        _peutcoup = false;
        _peutsauter = false;
    }
    if(_attaque)
    {
        _peutsauter = false;
        _attaque = _Broly.coupDePoing(clock,hurtboxEnnemi,touche,window);
        if(prendcoup){
            _attaque = false;
            _Broly.resetcoup();
        }
        if(!_couppoing)
        {
            _peutcoup = true;
        }
        if(!_attaque){
            _peutsauter = true;
        }
    }
}

void Joueur::prendCoup(sf::Clock& clock,sf::Clock& clockmove,bool& touche,sf::RenderWindow& window){
    if(prendcoup){
        _peutcoup = false;
        _peutsauter = false;
        _Broly.prendcoup(clock,clockmove,touche,window);
        if(!prendcoup){
            _peutcoup = true;
            prendDegats();
        }
    }
}

void Joueur::antiSpam(sf::Event& event){
    if(_numero == 1){
        if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A){
            _peutcoup = true;
        }
    }
    else{
        if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::M){
            _peutcoup = true;
        }
    }
}

Broly Joueur::getBroly()
{
    return _Broly;
}

sf::RectangleShape Joueur::getHurtbox()
{
    return _Broly.gethurtbox();
}

sf::RectangleShape Joueur::getHitbox(){
    return _Broly.gethitbox();
}

Joueur::~Joueur()
{
    //dtor
}
