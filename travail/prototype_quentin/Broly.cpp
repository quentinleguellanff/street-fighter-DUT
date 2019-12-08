#include "Broly.h"
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
    spriteBroly.setTexture(_Texture); // charge le sprite avec la texture initialisé précedemment
    spriteBroly.setScale(_scale*_orientation,_scale); //permet de mettre le scale en définissant l'orientation du perso
    spriteBroly.setPosition(800.f,460.f); // position initiale du perso/sprite dans la fenetre
    /*sf::Vector2i tailleBroly = sf::Vector2i(120,200);
    sf::IntRect(2,467,120,200);*/
    spriteBroly.setTextureRect(sf::IntRect(2, 467,120,200));
    _cptanimstatic = 0;
    _cptanimavancer = 0;
    _cptanimjump = 0;
    _cptAnimCoupPoing = 0;
    _cptanimprendcoup = 0;
    _vsaut = -70;
    if(_orientation == -1){
        spriteBroly.setOrigin(spriteBroly.getLocalBounds().width, 0.f);
        spriteBroly.setPosition(300.f,460.f); // position initiale du perso/sprite dans la fenetre
        _hitbox.setOrigin(spriteBroly.getLocalBounds().width,0.f);

    }
    _ok = false;

    _hurtbox.setFillColor(sf::Color(255,255,255,0));
    _hurtbox.setOutlineColor(sf::Color::Blue);
    _hurtbox.setOutlineThickness(2);
    _hurtbox.setPosition(spriteBroly.getPosition().x, spriteBroly.getPosition().y);
    _hurtbox.setOrigin(-2*spriteBroly.getGlobalBounds().width/10, 0.f);
    _hurtbox.setSize(sf::Vector2f(6*spriteBroly.getGlobalBounds().width/10,spriteBroly.getGlobalBounds().height));

    _hitbox.setScale(_scale*_orientation,_scale);
    _hitbox.setFillColor(sf::Color(255,255,255,0));
    _hitbox.setOutlineColor(sf::Color::Red);
    _hitbox.setOutlineThickness(2);
    _hitbox.setPosition(spriteBroly.getPosition().x, spriteBroly.getPosition().y+97*2);
    _hitbox.setSize(sf::Vector2f(23.f,21.f));
    cptanimprendcoupbis = 6;

}

int Broly::getorientation(){
    return _orientation;
}

Broly::Broly(){}

Broly::~Broly()
{
    //dtor
}

void Broly::debout(sf::Clock& clock,sf::RenderWindow& window)
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
    spriteBroly.setTextureRect(sf::IntRect(2+_cptanimstatic*123, 466,120,200));
    _hurtbox.setPosition(spriteBroly.getPosition());
    window.draw(spriteBroly);
}

void Broly::avancer(sf::Clock& clockanim,sf::Clock& clockmove,sf::RenderWindow& window)
{
    sf::Time elapsed1 = clockanim.getElapsedTime();
    sf::Time elapsed2 = clockmove.getElapsedTime();
    if(_cptanimavancer == 0){
        spriteBroly.setTextureRect(sf::IntRect(2, 873,128,200));
    }
    int timeanim = elapsed1.asMilliseconds();
    if(timeanim > 70){
        _cptanimavancer += 1;
        clockanim.restart();
    }
    if(_cptanimavancer >= 13){
        _cptanimavancer = 1;
    }
    if(_cptanimavancer > 0){
        spriteBroly.setTextureRect(sf::IntRect(2+_cptanimavancer*130, 873,128,200));
    }
    int timemove = elapsed2.asMilliseconds();
    int v_x = 15*-_orientation;
    if(timemove > 20)
    {
        spriteBroly.setPosition(spriteBroly.getPosition().x+v_x,spriteBroly.getPosition().y);
        clockmove.restart();
    }
    _hurtbox.setPosition(spriteBroly.getPosition());
    ResteDansFenetre();
    window.draw(spriteBroly);
}

void Broly::reculer(sf::Clock& clockanim,sf::Clock& clockmove,sf::RenderWindow& window)
 {
    sf::Time elapsed1 = clockanim.getElapsedTime();
    sf::Time elapsed2 = clockmove.getElapsedTime();
    spriteBroly.setTextureRect(sf::IntRect(2, 11437,153,207));
    int timeanim = elapsed1.asMilliseconds();
    cout << "temps anim reculer " << timeanim << endl;
    if(timeanim > 70){
        spriteBroly.setTextureRect(sf::IntRect(157, 11437,153,206));
    }
    int timemove = elapsed2.asMilliseconds();
    int v_x = 15*-_orientation;
    if(timemove > 20)
    {
        spriteBroly.setPosition(spriteBroly.getPosition().x-v_x,spriteBroly.getPosition().y);
        clockmove.restart();
    }
    _hurtbox.setPosition(spriteBroly.getPosition());
    ResteDansFenetre();
    window.draw(spriteBroly);
}

bool Broly::sauter(sf::Clock& clock,sf::Clock& clockmove,sf::RenderWindow& window,int vitesse){
    int v_grav = 6;
    int v_x = vitesse*20;
    sf::Time elapsed = clock.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    sf::Time elapsed2 = clockmove.getElapsedTime();
    int timemove = elapsed2.asMilliseconds();
    if(timeanim > 100){
        _cptanimjump += 1;
        clock.restart();
    }
    if(_cptanimjump >= 5){
        spriteBroly.setTextureRect(sf::IntRect(2+(5*158), 1650,156,208));
    }
    else{
        spriteBroly.setTextureRect(sf::IntRect(2+_cptanimjump*158, 1650,156,208));
    }
    if(timemove > 20){
        _vsaut += v_grav;
        spriteBroly.setPosition(spriteBroly.getPosition().x+v_x,spriteBroly.getPosition().y+_vsaut);
        clockmove.restart();
    }
    if(spriteBroly.getPosition().y >= 460){
                _vsaut = -80;
                spriteBroly.setPosition(spriteBroly.getPosition().x,460.f);
                spriteBroly.setTextureRect(sf::IntRect(123, 466,120,200));
                _hurtbox.setSize(sf::Vector2f(_hurtbox.getSize().x,spriteBroly.getGlobalBounds().height));
                _cptanimjump = 0;
                clock.restart();
                return false;
    }
    _hurtbox.setSize(sf::Vector2f(_hurtbox.getSize().x,2*spriteBroly.getGlobalBounds().height/3));
    _hurtbox.setPosition(spriteBroly.getPosition());
    ResteDansFenetre();
    window.draw(spriteBroly);
    return true;
}

bool Broly::coupDePoing(sf::Clock& clock,sf::RectangleShape hurtboxEnnemi,bool& touche,sf::RenderWindow& window){

        int decalagex = -112*_orientation;
        int decalage_hurtbox = 60*_orientation;
        if(!_ok){
            spriteBroly.setPosition(spriteBroly.getPosition().x+decalagex,spriteBroly.getPosition().y+20);
            _hurtbox.setPosition(spriteBroly.getPosition().x+decalage_hurtbox,spriteBroly.getPosition().y-20);
            _ok = true;
        }
        sf::Time elapsed = clock.getElapsedTime();
        int timeanim = elapsed.asMilliseconds();
        if(timeanim > 20){
            _cptAnimCoupPoing++;
            clock.restart();
        }

        if(_cptAnimCoupPoing == 1){
                _hitbox.setPosition(spriteBroly.getPosition().x, spriteBroly.getPosition().y+90*2);
                if(collisioncoup(hurtboxEnnemi)){
                    touche = true;
                }
        }
        if(_cptAnimCoupPoing >= 5){
            clock.restart();
            _cptAnimCoupPoing = 0;
            spriteBroly.setTextureRect(sf::IntRect(2, 466,120,200));
            spriteBroly.setPosition(spriteBroly.getPosition().x-decalagex,spriteBroly.getPosition().y-20);
            _ok = false;
            window.draw(spriteBroly);
            return false;
        }
        else{
            spriteBroly.setTextureRect(sf::IntRect(2+_cptAnimCoupPoing*179, 2765,177,190));
        }
        window.draw(spriteBroly);
        return true;
}

bool Broly::collisioncoup(sf::RectangleShape hurtboxEnnemi){

    return _hitbox.getGlobalBounds().intersects(hurtboxEnnemi.getGlobalBounds());
}

bool Broly::collisioncorps(Broly& ennemi){

    return _hurtbox.getGlobalBounds().intersects(ennemi.gethurtbox().getGlobalBounds());
}

void Broly::prendcoup(sf::Clock& clock, sf::Clock& clockmove, bool &touche, sf::RenderWindow& window){
    /*if(!_ok){
        spriteBroly.setPosition(spriteBroly.getPosition().x,spriteBroly.getPosition().y+20);
        _ok = true;
    }
    sf::Time elapsed = clock.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    if(timeanim > 20){
        _cptanimprendcoup +=1;
        cptanimprendcoupbis -=1;
        spriteBroly.setPosition(spriteBroly.getPosition().x,spriteBroly.getPosition().y);
        _hurtbox.setPosition(spriteBroly.getPosition());
        clock.restart();
    }
    if(cptanimprendcoupbis == 0){
        _cptanimprendcoup = 0;
        cptanimprendcoupbis = 6;
        spriteBroly.setPosition(spriteBroly.getPosition().x,spriteBroly.getPosition().y-20);
        _ok = false;
        touche = false;
        clock.restart();
    }
    if(_cptanimprendcoup < 4){
        spriteBroly.setTextureRect(sf::IntRect(2+_cptanimprendcoup*142, 8288,140,196));
    }
    if(cptanimprendcoupbis <= 2){
        spriteBroly.setTextureRect(sf::IntRect(2+cptanimprendcoupbis*142, 8288,140,196));
    }*/

    if(!_ok){
        spriteBroly.setPosition(spriteBroly.getPosition().x,spriteBroly.getPosition().y+60);
        _ok = true;
    }
    sf::Time elapsed = clock.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    if(timeanim > 70){
        _cptanimprendcoup +=1;
        clock.restart();
    }
    if(_cptanimprendcoup == 3){
        _cptanimprendcoup =0;
        clock.restart();
        spriteBroly.setPosition(spriteBroly.getPosition().x,spriteBroly.getPosition().y-60);
        _ok = false;
        touche = false;
    }
    spriteBroly.setTextureRect(sf::IntRect(2+_cptanimprendcoup*158, 8488,156,187));

    if(_cptanimprendcoup==2){
        spriteBroly.setTextureRect(sf::IntRect(2, 8488,156,187));
    }
    sf::Time elapsed2 = clockmove.getElapsedTime();
    int timemove = elapsed2.asMilliseconds();
    if(timemove > 20)
    {
        spriteBroly.setPosition(spriteBroly.getPosition().x+15*_orientation,spriteBroly.getPosition().y);
        clockmove.restart();
    }
    _hurtbox.setPosition(spriteBroly.getPosition());
    ResteDansFenetre();
    window.draw(spriteBroly);
}

sf::RectangleShape Broly::gethurtbox(){
    return _hurtbox;
}

sf::RectangleShape Broly::gethitbox(){
    return _hitbox;
}

void Broly::resetcoup(){
    int decalagex = -112*_orientation;
    spriteBroly.setPosition(spriteBroly.getPosition().x-decalagex,spriteBroly.getPosition().y-20);
    _cptAnimCoupPoing = 0;
    _ok = false;
}

void Broly::ResteDansFenetre(){
        if(_hurtbox.getPosition().x - _hurtbox.getOrigin().x < 0){
            float depassement = _hurtbox.getPosition().x - _hurtbox.getOrigin().x;
            spriteBroly.setPosition(spriteBroly.getPosition().x - depassement,spriteBroly.getPosition().y);
        }
        if(_hurtbox.getPosition().x + _hurtbox.getGlobalBounds().width - _hurtbox.getOrigin().x > 1440){
            float depassement = _hurtbox.getPosition().x + _hurtbox.getGlobalBounds().width - _hurtbox.getOrigin().x;
            spriteBroly.setPosition(spriteBroly.getPosition().x - depassement+1440,spriteBroly.getPosition().y);
        }
}
