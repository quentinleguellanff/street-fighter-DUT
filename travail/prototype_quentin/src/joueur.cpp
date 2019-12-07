#include "Joueur.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"

Joueur::Joueur(int i,Broly& broly)
{

    prendcoup = false;
    _attaque = false;
    _peutcoup = true;
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
        _barreVie.setPosition(1280-20-_nbPointVie, 20.f); //positionne la barre de vie
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

void Joueur::statique(sf::Clock& clock,sf::RenderWindow& window)
{
    if(!_avancedroite && !_avancegauche && !_saut && !_attaque && !prendcoup)
    {
        _Broly.debout(clock,window);
    }
    else if(_avancedroite && _avancegauche && !prendcoup)
    {
        _Broly.debout(clock,window);
    }
}

void Joueur::avancedroite(sf::Clock& clockanim, sf::Clock& clockmove,sf::RenderWindow& window)
{
    if(_avancedroite && !_avancegauche && !_saut && !_attaque && !prendcoup)
    {
        if(_Broly.getorientation()== -1)
            _Broly.avancer(clockanim,clockmove,window);
        else
            _Broly.reculer(clockanim,clockmove,window);
    }
}

void Joueur::avancegauche(sf::Clock& clockanim, sf::Clock& clockmove,sf::RenderWindow& window)
{
    if(!_avancedroite && _avancegauche && !_saut && !_attaque && !prendcoup)
    {
        if(_Broly.getorientation()== -1)
            _Broly.reculer(clockanim,clockmove,window);
        else
            _Broly.avancer(clockanim,clockmove,window);
    }
}

void Joueur::coupDePoing(sf::Clock& clock,sf::RectangleShape hurtboxEnnemi,bool& touche,sf::RenderWindow& window)
{
    if(_couppoing && _peutcoup && !prendcoup)
    {
        _attaque = true;
        _peutcoup = false;
    }
    if(_attaque)
    {
        if(prendcoup){
            _attaque = false;

            //_Broly.spriteBroly.setPosition(_Broly.spriteBroly.getPosition().x+112*_Broly.getorientation(),_Broly.spriteBroly.getPosition().y);
            _Broly.resetcoup();
            //exception a lancer quand broly se prend un coup lorsqu'il tape pour le deplacer et remettre ses anim a 0
        }
        _attaque = _Broly.coupDePoing(clock,hurtboxEnnemi,touche,window);
        if(!_couppoing)
        {
            _peutcoup = true;
        }
    }
}

void Joueur::prendCoup(sf::Clock& clock,bool& touche,sf::RenderWindow& window){
    if(prendcoup){
        _attaque = false;
        _peutcoup = false;
        _Broly.prendcoup(clock,touche,window);
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
