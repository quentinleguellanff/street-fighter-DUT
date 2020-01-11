#include "Joueur.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"

using namespace std;

Joueur::Joueur(int i,Broly& broly,Personnage* Perso)
{

    _prendcoup = false;
    _attaque = false;
    _ensaut = false;
    _ensautgauche = false;
    _ensautdroite =false;
    _peutcoup = true;
    _peutsauter = true;
    _seretourner = false;
    _cpttouche = 0;
    _numero = i;
    _nbPointVie = 500;
    _barreVie.setFillColor(sf::Color(0,0,255,150));
    _personnage = Perso;
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
        _pause = sf::Keyboard::isKeyPressed(sf::Keyboard::N);
    }
    else
    {
        _avancedroite = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        _avancegauche = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        _couppoing = sf::Keyboard::isKeyPressed(sf::Keyboard::M);
        _saut = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        _pause = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    }
}

void Joueur::saut(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi,bool ennemiensaut){
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
    if(_saut && _peutsauter && _avancedroite && _avancegauche){
        _ensaut = true;
        _saut = false;
        _peutsauter = false;
    }
    if(_ensautdroite){
        /*if(!_Broly.sauter(window,1,ennemiensaut,hurtboxEnnemi)){
            _ensautdroite = false;
            seretourner(hurtboxEnnemi);
            _peutsauter = true;
        }*/
        if(_personnage->getorientation() == 1){
            if(!_personnage->sauterAvancer(window,hurtboxEnnemi)){
                _ensautdroite = false;
                _peutsauter = true;
                seretourner(hurtboxEnnemi);
            }
        }
        else{
            if(!_personnage->sauterArriere(window,hurtboxEnnemi)){
                _ensautdroite = false;
                _peutsauter = true;
                seretourner(hurtboxEnnemi);
            }
        }
    }
    if(_ensautgauche){
        /*if(!_Broly.sauter(window,-1,ennemiensaut,hurtboxEnnemi)){
            _ensautgauche = false;
            seretourner(hurtboxEnnemi);
            _peutsauter = true;
        }*/
        if(_personnage->getorientation() == 1){
            if(!_personnage->sauterArriere(window,hurtboxEnnemi)){
                _ensautgauche = false;
                _peutsauter = true;
                seretourner(hurtboxEnnemi);
            }
        }
        else{
            if(!_personnage->sauterAvancer(window,hurtboxEnnemi)){
                _ensautgauche = false;
                _peutsauter = true;
                seretourner(hurtboxEnnemi);
            }
        }

    }
    if(_ensaut){
        if(!_personnage->sauter(window,hurtboxEnnemi)){
            _ensaut = false;
            seretourner(hurtboxEnnemi);
            _peutsauter = true;
        }
    }
}

void Joueur::statique(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi)
{
    if(!_avancedroite && !_avancegauche && !_ensaut && !_attaque && !_prendcoup && !_ensautgauche && !_ensautdroite)
    {
        //_Broly.debout(window,hurtboxEnnemi);
        _personnage->debout(window,hurtboxEnnemi);
        seretourner(hurtboxEnnemi);
    }
    else if(_avancedroite && _avancegauche && !_prendcoup && !_ensaut && !_ensautgauche && !_ensautdroite && !_attaque)
    {
        //_Broly.debout(window,hurtboxEnnemi);
        _personnage->debout(window,hurtboxEnnemi);
        seretourner(hurtboxEnnemi);
    }
}

void Joueur::avancedroite(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi)
{
    if(_avancedroite && !_avancegauche && !_saut && !_attaque && !_prendcoup && !_ensaut && !_ensautgauche && !_ensautdroite)
    {/*
        if(_Broly.getorientation()== -1){
            _Broly.avancer(window,hurtboxEnnemi);
            seretourner(hurtboxEnnemi);
        }
        else{
            _Broly.reculer(window);
            seretourner(hurtboxEnnemi);
        }
    */
        if(_personnage->getorientation() == 1){
            _personnage->avancer(window,hurtboxEnnemi);
            seretourner(hurtboxEnnemi);
        }
        else{
            _personnage->reculer(window);
            seretourner(hurtboxEnnemi);
        }
    }
}

void Joueur::avancegauche(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi)
{
    if(!_avancedroite && _avancegauche && !_saut && !_attaque && !_prendcoup && !_ensaut && !_ensautgauche && !_ensautdroite)
    {/*
        if(_Broly.getorientation()== -1){
            _Broly.reculer(window);
            seretourner(hurtboxEnnemi);
            _personnage->avancer(window,hurtboxEnnemi);
        }
        else{
            _Broly.avancer(window,hurtboxEnnemi);
            _personnage->reculer(window);
            seretourner(hurtboxEnnemi);
        }
        */
        if(_personnage->getorientation() == -1){
            _personnage->avancer(window,hurtboxEnnemi);
            seretourner(hurtboxEnnemi);
        }
        else{
            _personnage->reculer(window);
            seretourner(hurtboxEnnemi);
        }
    }
}

void Joueur::coupDePoing(sf::RectangleShape hurtboxEnnemi,bool& touche,sf::RenderWindow& window)
{
    if(_couppoing && _peutcoup && !_prendcoup && !_ensaut && !_ensautgauche && !_ensautdroite)
    {
        _attaque = true;
        _peutcoup = false;
        _peutsauter = false;
    }
    if(_attaque)
    {
        _peutsauter = false;
        if(_prendcoup){
            _attaque = false;
            _Broly.resetcoup();
        }else{
            //_attaque = _Broly.coupDePoing(hurtboxEnnemi,touche,window);
            _attaque = _personnage->coupDePoing(hurtboxEnnemi,touche,window);
        }
        if(_prendcoup){
            _attaque = false;
            _Broly.resetcoup();
        }
        if(!_attaque && !_couppoing)
        {
            _personnage->debout(window,hurtboxEnnemi);
            _peutcoup = true;
        }
        if(!_attaque){
            _personnage->debout(window,hurtboxEnnemi);
            _peutsauter = true;
        }
    }
}

void Joueur::prendCoup(bool& touche,sf::RenderWindow& window){
    if(touche){
        _prendcoup = true;
        _peutcoup = false;
        _peutsauter = false;
    }
    if(_prendcoup){
        sf::Time elapsed = _clockjoueur.getElapsedTime();
        int delai = elapsed.asMilliseconds();
        //_Broly.prendcoup(_prendcoup,window);
        _personnage->prendCoup(_prendcoup,window);
        if(delai > 100){
            if(touche){
                _cpttouche += 1;
                cout << _cpttouche << endl;
                _clockjoueur.restart();
            }
        }
        if(_cpttouche == 2){
            //restart animation prendcoup
            _personnage->restartPrendcoup();
            prendDegats();
            _cpttouche = 0;
        }
        touche = false;
        if(!_prendcoup){
            _peutsauter = true;
            if(!_couppoing){
                _peutcoup = true;
            }
            prendDegats();
            _cpttouche = 0;
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

void Joueur::seretourner(sf::RectangleShape hurtboxEnnemi){
    if(_personnage->getorientation() == 1){
        if(_personnage->gethurtbox().getGlobalBounds().left  > (hurtboxEnnemi.getGlobalBounds().left + hurtboxEnnemi.getGlobalBounds().width)){
            _seretourner = true;
        }
    }
    if(_personnage->getorientation() == -1){
        if(_personnage->gethurtbox().getGlobalBounds().left + _personnage->gethurtbox().getGlobalBounds().width < hurtboxEnnemi.getGlobalBounds().left){
            _seretourner = true;
        }
    }
    if(_seretourner){
        _personnage->retourner();
        _seretourner = false;
    }
}

Broly Joueur::getBroly()
{
    return _Broly;
}

sf::RectangleShape Joueur::getHurtbox()
{
    return _personnage->gethurtbox();
}

sf::RectangleShape Joueur::getHitbox(){
    return _personnage->gethitbox();
}

int Joueur::getOrientation(){
    return _Broly.getorientation();
}

void Joueur::setVitesseX(int vitesse){
    _Broly.setVitesseX(vitesse);
}

int Joueur::getVitesseX(){
    return _Broly.getVitesseX();
}

void Joueur::deplacer(int vitesse){
    _Broly.deplacer(vitesse);
}

bool Joueur::getEtat(){
    if(_ensautdroite)
        return _ensautdroite;
    if(_ensautgauche)
        return _ensautgauche;
    else
        return _ensaut;
}

void Joueur::pauseAnim(){
    _Broly.pauseAnimation();
}

void Joueur::restartClockPerso(){
    _Broly.restartClock();
}

Joueur::Joueur(){}

Joueur::~Joueur()
{
    //dtor
}
