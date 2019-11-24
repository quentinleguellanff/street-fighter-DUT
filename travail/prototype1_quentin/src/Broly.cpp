#include "../include/Broly.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace std;

Broly::Broly(int Orientation)
{
    _orientation = Orientation; // permet de définir l'orientation du personnage
    if (!_Texture.loadFromFile("Brolyspriteok.png"))//load de la texture du personnage
    {
        cout << "erreur" << endl;
    }
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
    _cptanimprendcoup = 0;
    if(_orientation == -1){
        setOrigin(getLocalBounds().width, 0.f);
        //_hitboxcorps.setOrigin(120.f, 0.f);
    }
    _ok = false;

    _hitboxpoing.setSize(sf::Vector2f(46.f,44.f));
    _hitboxpoing.setFillColor(sf::Color(255,255,255,0));
    _hitboxpoing.setOutlineThickness(5);
    _hitboxpoing.setOutlineColor(sf::Color::Red);

    _hitboxcorps.setSize(sf::Vector2f(getLocalBounds().width,getLocalBounds().height*2));
    _hitboxcorps.setFillColor(sf::Color(255,255,255,0));
    _hitboxcorps.setOutlineThickness(5);
    _hitboxcorps.setOutlineColor(sf::Color::Blue);
    cptanimprendcoupbis = 6;


}

int Broly::getorientation(){
    return _orientation;
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
    setTextureRect(sf::IntRect(2+_cptanimstatic*123, 466,120,201));

    _hitboxcorps.setPosition(getPosition().x+getLocalBounds().width/2,getPosition().y);
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
    _hitboxcorps.setPosition(getPosition().x+60,getPosition().y);
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
    _hitboxcorps.setPosition(getPosition().x+60,getPosition().y);

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
        int decalagex = -112*_orientation;
        if(!_ok){
            setPosition(getPosition().x+decalagex,getPosition().y+20);
            _ok = true;
        }
        sf::Time elapsed = clock.getElapsedTime();
        int timeanim = elapsed.asMilliseconds();
        if(timeanim > 30){
            _cptAnimCoupPoing++;
            clock.restart();
        }

        if(_cptAnimCoupPoing == 1 || _cptAnimCoupPoing == 2 ){
            //_hitboxpoing.setPosition(getPosition().x+decalagex+120, getPosition().y+182);
            if(_orientation == 1){
                _hitboxpoing.setPosition(getPosition().x, getPosition().y+182);
            }
            else{
                _hitboxpoing.setPosition(getPosition().x+getLocalBounds().width*2-120-46+5, getPosition().y+182);
                cout << "position de la hitbox" << _hitboxpoing.getPosition().x << endl; // 56 = taille de l'anim - taille joueur
            }
        }
        else{
            if(_orientation == 1){
                _hitboxpoing.setPosition(getPosition().x+166, getPosition().y+60);
            }
            else{
                _hitboxpoing.setPosition(getPosition().x, getPosition().y+60);
            }
        }

        if(_cptAnimCoupPoing >= 5){
            clock.restart();
            _cptAnimCoupPoing = 0;
            setTextureRect(sf::IntRect(2, 466,120,201));
            cout <<" position du sprite "<< endl;
            cout << getPosition().x << endl;
            cout << getPosition().y << endl;
            setPosition(getPosition().x-decalagex,getPosition().y-20);
            _ok = false;
            return false;
        }
        else{
            setTextureRect(sf::IntRect(2+_cptAnimCoupPoing*179, 2765,177,191));
        }
        return true;
}
/*
bool Broly::touche(sf::RectangleShape hitboxcorps){

    if(_orientation == -1){
            cout << "voici la position du poing de broly -1 : " << _hitboxpoing.getPosition().x << endl;
            cout <<endl;
            cout <<"Voici la position du corps de broly 1 : " << hitboxcorps.getPosition().x << endl;
        if(_hitboxpoing.getPosition().x >=  hitboxcorps.getPosition().x){
            return true;
        }
        else{
            return false;
        }
    }
    if(_orientation == 1){
        if((_hitboxpoing.getPosition().x <=  (hitboxcorps.getPosition().x + hitboxcorps.getSize().x))){
                cout << "voici la position du poing de broly 1 : " << _hitboxpoing.getPosition().x << endl;
            cout <<endl;
            cout <<"Voici la position du corps de broly -1 : " << hitboxcorps.getPosition().x << endl;
            return true;
        }
        else{
            return false;
        }
    }
}
*/
bool Broly::prendcoup(sf::Clock& clock){
    if(!_ok){
        setPosition(getPosition().x,getPosition().y+20);
        _ok = true;
    }
    sf::Time elapsed = clock.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    if(timeanim > 20){
        _cptanimprendcoup +=1;
        cptanimprendcoupbis -=1;
        clock.restart();
    }
    if(cptanimprendcoupbis == 0){
        _cptanimprendcoup = 0;
        cptanimprendcoupbis = 6;
        clock.restart();
        _ok = false;
        setPosition(getPosition().x,getPosition().y-20);
        return false;
    }
    if(_cptanimprendcoup < 4){
        setTextureRect(sf::IntRect(2+_cptanimprendcoup*142, 8288,140,196));
    }
    if(cptanimprendcoupbis <= 2){
        setTextureRect(sf::IntRect(2+cptanimprendcoupbis*142, 8288,140,196));
    }
    return true;
}

sf::RectangleShape Broly::getHitboxpoing(){
    return _hitboxpoing;
}

sf::RectangleShape Broly::getHitboxcorps(){
    return _hitboxcorps;
}
