#include "Broly.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace std;

Broly::Broly(int Orientation,sf::RectangleShape& sol)
{
    _orientation = -Orientation;
    if (!_Texture.loadFromFile("sprite/Brolyspriteok.png"))//load de la texture du personnage
    {
        cout << "erreur" << endl;
    }
    _scale = 2; // ratio de scale du personnage, zoom le sprite pour qu'il apparaisse plus grand
    _spritePerso.setTexture(_Texture); // charge le sprite avec la texture initialisé précedemment
    _spritePerso.setScale(_scale*_orientation,_scale); //permet de mettre le scale en définissant l'orientation du perso
    _spritePerso.setPosition(800.f,460.f);// position initiale du perso/sprite dans la fenetre
    _spritePerso.setTextureRect(sf::IntRect(2, 467,120,200));
    _cptanimstatic = 0;
    _cptanimavancer = 0;
    _cptanimjump = 0;
    _cptAnimCoupPoing = 0;
    _cptanimprendcoup = 0;
    _vitesseX = 0;
    _cptTimePauseAnim = 0;
    _vsaut = -40;
     // position initiale du perso/sprite dans la fenetre
    /*sf::Vector2i tailleBroly = sf::Vector2i(120,200);
    sf::IntRect(2,467,120,200);*/
    /*
    _spritePerso.setTextureRect(sf::IntRect(2, 467,120,200));
    _cptanimstatic = 0;
    _cptanimavancer = 0;
    _cptanimjump = 0;
    _cptAnimCoupPoing = 0;
    _cptanimprendcoup = 0;
    _vitesseX = 0;
    _cptTimePauseAnim = 0;
    _vsaut = -40;
    if(_orientation == -1)
    {
        _spritePerso.setOrigin(_spritePerso.getLocalBounds().width, 0.f);
        _spritePerso.setPosition(300.f,460.f); // position initiale du perso/sprite dans la fenetre
        _hitbox.setOrigin(_spritePerso.getLocalBounds().width,0.f);
        _hurtbox.setOrigin(_spritePerso.getLocalBounds().width,0.f);

    }
    _ok = false;

    _hurtbox.setFillColor(sf::Color(0,0,255,100));
    _hurtbox.setPosition(_spritePerso.getPosition().x, _spritePerso.getPosition().y);
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width/2,_spritePerso.getGlobalBounds().height/2));
    _hurtbox.setScale(_scale*_orientation,_scale);



    _hitbox.setScale(_scale*_orientation,_scale);
    _hitbox.setFillColor(sf::Color(255,0,0,255));
    _hitbox.setPosition(_spritePerso.getPosition().x, _spritePerso.getPosition().y+97*2);
    _hitbox.setSize(sf::Vector2f(23.f,21.f));
    cptanimprendcoupbis = 6;
    */
}

Broly::Broly() {}

Broly::~Broly()
{
    //dtor
}

void Broly::debout(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi)
{
    _cptanimjump = 0;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    if(timeanim > 100)
    {
        _cptanimstatic +=1;
        _clockanim.restart();
    }
    if(_cptanimstatic >= 10)
    {
        _cptanimstatic = 0;
    }
    _spritePerso.setTextureRect(sf::IntRect(2+_cptanimstatic*123, 466,120,200));
    //collision(hurtboxEnnemi);
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width/3,_spritePerso.getGlobalBounds().height/2));
    _hurtbox.setPosition(_spritePerso.getPosition().x + 50.f*_orientation,_spritePerso.getPosition().y);
    ResteDansFenetre();
    window.draw(_spritePerso);
}

void Broly::avancer(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi)
{
    sf::Time elapsed1 = _clockanim.getElapsedTime();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    if(_cptanimavancer == 0)
    {
        _spritePerso.setTextureRect(sf::IntRect(2, 873,128,200));
    }
    int timeanim = elapsed1.asMilliseconds();
    if(timeanim > 70)
    {
        _cptanimavancer += 1;
        _clockanim.restart();
    }
    if(_cptanimavancer >= 13)
    {
        _cptanimavancer = 1;
    }
    if(_cptanimavancer > 0)
    {
        _spritePerso.setTextureRect(sf::IntRect(2+_cptanimavancer*130, 873,128,200));
    }
    int timemove = elapsed2.asMilliseconds();
    _vitesseX = 15 * -_orientation;
    collision(hurtboxEnnemi);
    if(timemove > 20)
    {
        ResteDansFenetre();
        _spritePerso.setPosition(_spritePerso.getPosition().x+_vitesseX,_spritePerso.getPosition().y);
        _clockmove.restart();
    }
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width*0.3,_spritePerso.getGlobalBounds().height/2));
    _hurtbox.setPosition(_spritePerso.getPosition().x + 60.f*_orientation,_spritePerso.getPosition().y);
    window.draw(_spritePerso);
}

void Broly::reculer(sf::RenderWindow& window)
{
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width*0.3-10,_spritePerso.getGlobalBounds().height/2-6));
    // la position par rapport au sol doit être parout pareil d'ou le -6 (à l'exception du saut)
    _hurtbox.setPosition(_spritePerso.getPosition().x + 60.f*_orientation,_spritePerso.getPosition().y);
    sf::Time elapsed1 = _clockanim.getElapsedTime();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    _spritePerso.setTextureRect(sf::IntRect(2, 11437,153,207));
    int timeanim = elapsed1.asMilliseconds();
    if(timeanim > 70)
    {
        _spritePerso.setTextureRect(sf::IntRect(157, 11437,153,206));
    }
    int timemove = elapsed2.asMilliseconds();
    //collision(hurtboxEnnemi);
    _vitesseX = -15*-_orientation;
    if(timemove > 20)
    {

        ResteDansFenetre();
        _spritePerso.setPosition(_spritePerso.getPosition().x+_vitesseX,_spritePerso.getPosition().y);
        _clockmove.restart();
    }
    window.draw(_spritePerso);
}

bool Broly::sauter(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi)
{
    int direction = 0;
    int v_grav = 6;
    _vitesseX = 20*direction;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timemove = elapsed2.asMilliseconds();
    if(timeanim > 100)
    {
        _cptanimjump += 1;
        _clockanim.restart();
    }
    if(_cptanimjump >= 5)
    {
        _spritePerso.setTextureRect(sf::IntRect(2+(5*158), 1650,156,208));
    }
    else
    {
        _spritePerso.setTextureRect(sf::IntRect(2+_cptanimjump*158, 1650,156,208));
    }
    if(timemove > 20)
    {
        _vsaut += v_grav;
        collisionsaut(hurtboxEnnemi);
        ResteDansFenetre();
        _spritePerso.setPosition(_spritePerso.getPosition().x+_vitesseX,_spritePerso.getPosition().y+_vsaut);
        _clockmove.restart();
    }
    if(_spritePerso.getPosition().y >= 460)
    {
        _vsaut = -75;
        _spritePerso.setPosition(_spritePerso.getPosition().x,460.f);
        _spritePerso.setTextureRect(sf::IntRect(123, 466,120,200));
        _hurtbox.setSize(sf::Vector2f(_hurtbox.getSize().x,_spritePerso.getGlobalBounds().height));
        _cptanimjump = 0;
        _clockanim.restart();
        return false;
    }
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width*0.22,_spritePerso.getGlobalBounds().height/4));
    _hurtbox.setPosition(_spritePerso.getPosition().x + 60.f*_orientation,_spritePerso.getPosition().y);
    window.draw(_spritePerso);
    return true;
}

bool Broly::sauterAvancer(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi){
    int direction = 1;
    int v_grav = 6;
    _vitesseX = 20*direction;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timemove = elapsed2.asMilliseconds();
    if(timeanim > 100)
    {
        _cptanimjump += 1;
        _clockanim.restart();
    }
    if(_cptanimjump >= 5)
    {
        _spritePerso.setTextureRect(sf::IntRect(2+(5*158), 1650,156,208));
    }
    else
    {
        _spritePerso.setTextureRect(sf::IntRect(2+_cptanimjump*158, 1650,156,208));
    }
    if(timemove > 20)
    {
        _vsaut += v_grav;
        collisionsaut(hurtboxEnnemi);
        ResteDansFenetre();
        _spritePerso.setPosition(_spritePerso.getPosition().x+_vitesseX,_spritePerso.getPosition().y+_vsaut);
        _clockmove.restart();
    }
    if(_spritePerso.getPosition().y >= 460)
    {
        _vsaut = -75;
        _spritePerso.setPosition(_spritePerso.getPosition().x,460.f);
        _spritePerso.setTextureRect(sf::IntRect(123, 466,120,200));
        _hurtbox.setSize(sf::Vector2f(_hurtbox.getSize().x,_spritePerso.getGlobalBounds().height));
        _cptanimjump = 0;
        _clockanim.restart();
        return false;
    }
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width*0.22,_spritePerso.getGlobalBounds().height/4));
    _hurtbox.setPosition(_spritePerso.getPosition().x + 60.f*_orientation,_spritePerso.getPosition().y);
    window.draw(_spritePerso);
    return true;
}

bool Broly::sauterArriere(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi){
    int direction = -1;
    int v_grav = 6;
    _vitesseX = 20*direction;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timemove = elapsed2.asMilliseconds();
    if(timeanim > 100)
    {
        _cptanimjump += 1;
        _clockanim.restart();
    }
    if(_cptanimjump >= 5)
    {
        _spritePerso.setTextureRect(sf::IntRect(2+(5*158), 1650,156,208));
    }
    else
    {
        _spritePerso.setTextureRect(sf::IntRect(2+_cptanimjump*158, 1650,156,208));
    }
    if(timemove > 20)
    {
        _vsaut += v_grav;
        collisionsaut(hurtboxEnnemi);
        ResteDansFenetre();
        _spritePerso.setPosition(_spritePerso.getPosition().x+_vitesseX,_spritePerso.getPosition().y+_vsaut);
        _clockmove.restart();
    }
    if(_spritePerso.getPosition().y >= 460)
    {
        _vsaut = -75;
        _spritePerso.setPosition(_spritePerso.getPosition().x,460.f);
        _spritePerso.setTextureRect(sf::IntRect(123, 466,120,200));
        _hurtbox.setSize(sf::Vector2f(_hurtbox.getSize().x,_spritePerso.getGlobalBounds().height));
        _cptanimjump = 0;
        _clockanim.restart();
        return false;
    }
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width*0.22,_spritePerso.getGlobalBounds().height/4));
    _hurtbox.setPosition(_spritePerso.getPosition().x + 60.f*_orientation,_spritePerso.getPosition().y);
    window.draw(_spritePerso);
    return true;
}


bool Broly::coupDePoing(sf::RectangleShape hurtboxEnnemi,bool& touche,sf::RenderWindow& window)
{

    int decalagex = -112*_orientation;
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width/4,_spritePerso.getGlobalBounds().height/2));
    _hurtbox.setPosition(_spritePerso.getPosition().x-decalagex,_spritePerso.getPosition().y);
    if(!_ok)
    {
        _spritePerso.setPosition(_spritePerso.getPosition().x+decalagex,_spritePerso.getPosition().y+20);
        _ok = true;
    }
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    if(timeanim > 40)
    {
        _cptAnimCoupPoing++;
        _clockanim.restart();
    }

    if(_cptAnimCoupPoing == 1)
    {
        _hitbox.setPosition(_spritePerso.getPosition().x, _spritePerso.getPosition().y+90*2);
        if(collisioncoup(hurtboxEnnemi))
        {
            touche = true;
            window.draw(_hitbox);
        }
    }
    if(_cptAnimCoupPoing >= 5)
    {
        _clockanim.restart();
        _cptAnimCoupPoing = 0;
        _spritePerso.setTextureRect(sf::IntRect(2, 466,120,200));
        _spritePerso.setPosition(_spritePerso.getPosition().x-decalagex,_spritePerso.getPosition().y-20);
        _ok = false;
        window.draw(_spritePerso);
        return false;
    }
    else
    {
        _spritePerso.setTextureRect(sf::IntRect(2+_cptAnimCoupPoing*179, 2765,177,190));
    }
    window.draw(_spritePerso);
    //cout << _cptAnimCoupPoing << endl;
    return true;
}

void Broly::prendCoup(bool& touche,sf::RenderWindow& window)
{
    if(!_ok)
    {
        _spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y+60);
        _ok = true;
    }
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    if(timeanim > 60)
    {
        _cptanimprendcoup +=1;
        _clockanim.restart();
    }
    if(_cptanimprendcoup == 3)
    {
        _cptanimprendcoup = 0;
        _clockanim.restart();
        _spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y-60);
        _ok = false;
        touche = false;
    }
    _spritePerso.setTextureRect(sf::IntRect(2+_cptanimprendcoup*158, 8488,156,187));

    if(_cptanimprendcoup==2)
    {
        _spritePerso.setTextureRect(sf::IntRect(2, 8488,156,187));
    }
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    _vitesseX = 20*_orientation;
    int timemove = elapsed2.asMilliseconds();
    if(timemove > 20)
    {
        ResteDansFenetre();
        _spritePerso.setPosition(_spritePerso.getPosition().x+_vitesseX,_spritePerso.getPosition().y);
        _clockmove.restart();
    }
    _hurtbox.setPosition(_spritePerso.getPosition());
    window.draw(_spritePerso);
}

void Broly::restartPrendcoup()
{
    _cptanimprendcoup = 0;
}

void Broly::resetcoup()
{
    int decalagex = -112*_orientation;
    _spritePerso.setPosition(_spritePerso.getPosition().x-decalagex,_spritePerso.getPosition().y-10);
    _cptAnimCoupPoing = 0;
    _ok = false;
}

void Broly::retourner()
{
    _orientation = -_orientation;
    sf::Vector2f positionBaseBroly = _spritePerso.getPosition();

    if(_orientation == -1)
    {
        _spritePerso.setOrigin(_spritePerso.getLocalBounds().width, 0.f);
        _hitbox.setOrigin(_spritePerso.getLocalBounds().width,0.f);
        _hurtbox.setOrigin(_spritePerso.getLocalBounds().width,0.f);
    }
    else
    {
        _spritePerso.setOrigin(0.f,0.f);
        _hitbox.setOrigin(0.f,0.f);
        _hurtbox.setOrigin(0.f,0.f);
    }
    _spritePerso.setScale(_scale*_orientation,_scale);
    _hurtbox.setScale(_scale*_orientation,_scale);
    _hitbox.setScale(_scale*_orientation,_scale);
    _spritePerso.setPosition(positionBaseBroly);
    _hurtbox.setPosition(_spritePerso.getPosition().x, _spritePerso.getPosition().y);
}
