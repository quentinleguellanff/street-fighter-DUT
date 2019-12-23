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
    _vitesseX = 0;
    _vsaut = -75;
    if(_orientation == -1){
        spriteBroly.setOrigin(spriteBroly.getLocalBounds().width, 0.f);
        spriteBroly.setPosition(300.f,460.f); // position initiale du perso/sprite dans la fenetre
        _hitbox.setOrigin(spriteBroly.getLocalBounds().width,0.f);

    }
    _ok = false;

    _hurtbox.setFillColor(sf::Color(0,0,255,100));
    _hurtbox.setPosition(spriteBroly.getPosition().x, spriteBroly.getPosition().y);
    _hurtbox.setOrigin(-2*spriteBroly.getGlobalBounds().width/10, 0.f);
    _hurtbox.setSize(sf::Vector2f(6*spriteBroly.getGlobalBounds().width/10,spriteBroly.getGlobalBounds().height));

    _hitbox.setScale(_scale*_orientation,_scale);
    _hitbox.setFillColor(sf::Color(255,0,0,100));
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

void Broly::debout(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi)
{
    _cptanimjump = 0;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    if(timeanim > 100){
        _cptanimstatic +=1;
        _clockanim.restart();
    }
    if(_cptanimstatic >= 10){
        _cptanimstatic = 0;
    }
    spriteBroly.setTextureRect(sf::IntRect(2+_cptanimstatic*123, 466,120,200));
    _hurtbox.setOrigin(-2*spriteBroly.getGlobalBounds().width/10, 0.f);
    _hurtbox.setPosition(spriteBroly.getPosition());
    //collision(hurtboxEnnemi);
    ResteDansFenetre();
    window.draw(spriteBroly);
}

void Broly::avancer(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi)
{
    sf::Time elapsed1 = _clockanim.getElapsedTime();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    if(_cptanimavancer == 0){
        spriteBroly.setTextureRect(sf::IntRect(2, 873,128,200));
    }
    int timeanim = elapsed1.asMilliseconds();
    if(timeanim > 70){
        _cptanimavancer += 1;
        _clockanim.restart();
    }
    if(_cptanimavancer >= 13){
        _cptanimavancer = 1;
    }
    if(_cptanimavancer > 0){
        spriteBroly.setTextureRect(sf::IntRect(2+_cptanimavancer*130, 873,128,200));
    }
    int timemove = elapsed2.asMilliseconds();
    _vitesseX = 15 * -_orientation;
    collision(hurtboxEnnemi);
    if(timemove > 20)
    {
        ResteDansFenetre();
        spriteBroly.setPosition(spriteBroly.getPosition().x+_vitesseX,spriteBroly.getPosition().y);
        _clockmove.restart();
    }
    _hurtbox.setPosition(spriteBroly.getPosition());
    window.draw(spriteBroly);
}

void Broly::reculer(sf::RenderWindow& window)
 {
    sf::Time elapsed1 = _clockanim.getElapsedTime();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    spriteBroly.setTextureRect(sf::IntRect(2, 11437,153,207));
    int timeanim = elapsed1.asMilliseconds();
    cout << "temps anim reculer " << timeanim << endl;
    if(timeanim > 70){
        spriteBroly.setTextureRect(sf::IntRect(157, 11437,153,206));
    }
    int timemove = elapsed2.asMilliseconds();
    //collision(hurtboxEnnemi);
    _vitesseX = -15*-_orientation;
    if(timemove > 20)
    {
        _hurtbox.setPosition(spriteBroly.getPosition());
        ResteDansFenetre();
        spriteBroly.setPosition(spriteBroly.getPosition().x+_vitesseX,spriteBroly.getPosition().y);
        _clockmove.restart();
    }
    _hurtbox.setPosition(spriteBroly.getPosition());
    window.draw(spriteBroly);
}

bool Broly::sauter(sf::RenderWindow& window,int direction,bool ennemiensaut,sf::RectangleShape hurtboxEnnemi){
    //if(_vsaut > 0)
        collisionsaut(hurtboxEnnemi);
    int v_grav = 6;
    _vitesseX = 20*direction;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timemove = elapsed2.asMilliseconds();
    if(timeanim > 100){
        _cptanimjump += 1;
        _clockanim.restart();
    }
    if(_cptanimjump >= 5){
        spriteBroly.setTextureRect(sf::IntRect(2+(5*158), 1650,156,208));
    }
    else{
        spriteBroly.setTextureRect(sf::IntRect(2+_cptanimjump*158, 1650,156,208));
    }
    if(timemove > 20){
        _vsaut += v_grav;
        ResteDansFenetre();
        spriteBroly.setPosition(spriteBroly.getPosition().x+_vitesseX,spriteBroly.getPosition().y+_vsaut);
        _clockmove.restart();
    }
    if(spriteBroly.getPosition().y >= 460){
                _vsaut = -75;
                spriteBroly.setPosition(spriteBroly.getPosition().x,460.f);
                spriteBroly.setTextureRect(sf::IntRect(123, 466,120,200));
                _hurtbox.setSize(sf::Vector2f(_hurtbox.getSize().x,spriteBroly.getGlobalBounds().height));
                _cptanimjump = 0;
                _clockanim.restart();
                return false;
    }
    _hurtbox.setSize(sf::Vector2f(_hurtbox.getSize().x,3*spriteBroly.getGlobalBounds().height/5));
    _hurtbox.setPosition(spriteBroly.getPosition());
    window.draw(spriteBroly);
    return true;
}

bool Broly::coupDePoing(sf::RectangleShape hurtboxEnnemi,bool& touche,sf::RenderWindow& window){

        int decalagex = -112*_orientation;
        int decalage_hurtbox = 60*_orientation;
        if(!_ok){
            spriteBroly.setPosition(spriteBroly.getPosition().x+decalagex,spriteBroly.getPosition().y+20);
            _hurtbox.setPosition(spriteBroly.getPosition().x+decalage_hurtbox,spriteBroly.getPosition().y-20);
            _ok = true;
        }
        sf::Time elapsed = _clockanim.getElapsedTime();
        int timeanim = elapsed.asMilliseconds();
        if(timeanim > 20){
            _cptAnimCoupPoing++;
            _clockanim.restart();
        }

        if(_cptAnimCoupPoing == 1){
                _hitbox.setPosition(spriteBroly.getPosition().x, spriteBroly.getPosition().y+90*2);
                if(collisioncoup(hurtboxEnnemi)){
                    touche = true;
                }
        }
        if(_cptAnimCoupPoing >= 5){
            _clockanim.restart();
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

bool Broly::collisioncorps(sf::RectangleShape hurtboxEnnemi){

    return _hurtbox.getGlobalBounds().intersects(hurtboxEnnemi.getGlobalBounds());
}

void Broly::collisionPersonnage(sf::RectangleShape hurtboxEnnemi){
    if(collisioncorps(hurtboxEnnemi)){
        _vitesseX = -_vitesseX;
    }
}

void Broly::prendcoup(bool &touche, sf::RenderWindow& window){
    if(!_ok){
        spriteBroly.setPosition(spriteBroly.getPosition().x,spriteBroly.getPosition().y+60);
        _ok = true;
    }
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    if(timeanim > 60){
        _cptanimprendcoup +=1;
        _clockanim.restart();
    }
    if(_cptanimprendcoup == 3){
        _cptanimprendcoup = 0;
        _clockanim.restart();
        spriteBroly.setPosition(spriteBroly.getPosition().x,spriteBroly.getPosition().y-60);
        _ok = false;
        touche = false;
    }
    spriteBroly.setTextureRect(sf::IntRect(2+_cptanimprendcoup*158, 8488,156,187));

    if(_cptanimprendcoup==2){
        spriteBroly.setTextureRect(sf::IntRect(2, 8488,156,187));
    }
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    _vitesseX = -20*-_orientation;
    int timemove = elapsed2.asMilliseconds();
    if(timemove > 20)
    {
        ResteDansFenetre();
        spriteBroly.setPosition(spriteBroly.getPosition().x+_vitesseX,spriteBroly.getPosition().y);
        _clockmove.restart();
    }
    _hurtbox.setPosition(spriteBroly.getPosition());
    window.draw(spriteBroly);
}

sf::RectangleShape Broly::gethurtbox(){
    return _hurtbox;
}

void Broly::restartPrendcoup(){
    _cptanimprendcoup = 0;
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

void Broly::setVitesseX(int vitesse){
    _vitesseX = vitesse;
}

int Broly::getVitesseX(){
    return _vitesseX;
}

void Broly::deplacer(int vitesse){
    spriteBroly.move(vitesse,0.f);
}

void Broly::ResteDansFenetre(){
        _hurtbox.setPosition(spriteBroly.getPosition());
        float positiongauche = _hurtbox.getPosition().x - _hurtbox.getOrigin().x;
        float positiondroite = _hurtbox.getPosition().x + _hurtbox.getGlobalBounds().width - _hurtbox.getOrigin().x;
        if(positiongauche + getVitesseX() < 0){
            //deplacer(-positiongauche);
            if(_vitesseX < 0)
                _vitesseX = 0;
        }
        if(positiondroite + getVitesseX() > 1440){
            //deplacer(1440 -positiondroite);
            if(_vitesseX > 0)
                _vitesseX = 0;
        }
}

/*void Broly::collisiondeplacement(sf::RectangleShape hurtboxEnnemi){
    if(_hurtbox.getGlobalBounds().intersects(hurtboxEnnemi.getGlobalBounds())){
        _vitesseX = _vitesseX;
    }


}*/

void Broly::collision(sf::RectangleShape hurtboxEnnemi){
    _hurtbox.setPosition(spriteBroly.getPosition());
    float positiongauche = _hurtbox.getPosition().x - _hurtbox.getOrigin().x;
    float positiondroite = _hurtbox.getPosition().x + _hurtbox.getGlobalBounds().width - _hurtbox.getOrigin().x;
    float positionbasse = _hurtbox.getPosition().y - _hurtbox.getGlobalBounds().height;
    float positionhaute = _hurtbox.getPosition().y;

    float positiongaucheennemi = hurtboxEnnemi.getGlobalBounds().left;
    float positiondroiteennemi = hurtboxEnnemi.getGlobalBounds().width + hurtboxEnnemi.getGlobalBounds().left;
    float positionbasseennemi = hurtboxEnnemi.getGlobalBounds().top - hurtboxEnnemi.getGlobalBounds().height;
    float positionhauteennemi = hurtboxEnnemi.getGlobalBounds().top;

    cout << positionhauteennemi << endl;
    if(positionhaute == positionhauteennemi){
        if(_orientation == -1){
            if(positiondroite + _vitesseX >= positiongaucheennemi){
                deplacer(positiongaucheennemi - positiondroite);
                _vitesseX = 0;
            }
        }
        else{
            //cout << _vitesseX << endl;
            if(positiongauche + _vitesseX <= positiondroiteennemi){
                deplacer(positiondroiteennemi - positiongauche);
                _vitesseX = 0;
            }
        }
    }
}

void Broly::collisionsaut(sf::RectangleShape hurtboxEnnemi){
    _hurtbox.setPosition(spriteBroly.getPosition());
    float positiongauche = _hurtbox.getPosition().x - _hurtbox.getOrigin().x;
    float positiondroite = _hurtbox.getPosition().x + _hurtbox.getGlobalBounds().width - _hurtbox.getOrigin().x;
    float positiongaucheennemi = hurtboxEnnemi.getGlobalBounds().left;
    float positiondroiteennemi = hurtboxEnnemi.getGlobalBounds().width + hurtboxEnnemi.getGlobalBounds().left;

    if(_hurtbox.getGlobalBounds().intersects(hurtboxEnnemi.getGlobalBounds())){
        if(_orientation == -1){
            cout << positiondroite << endl;
            cout << positiondroiteennemi << endl;

            if(positiongaucheennemi < _hurtbox.getGlobalBounds().width - _hurtbox.getOrigin().x){
                deplacer(positiondroiteennemi - positiongauche);
                ResteDansFenetre();
            }
            else if(positiondroiteennemi >  1440 - positiongauche){
                deplacer(-60);
                ResteDansFenetre();
            }
            else if(positiondroite > positiondroiteennemi + 15){
                //verifier qu'il y a la place à faire pour les bords de la fenetres
                deplacer(positiondroiteennemi - positiongauche);
                ResteDansFenetre();
                //spriteBroly.setPosition(sf::Vector2f(positiondroiteennemi-65,spriteBroly.getPosition().y));
                _vitesseX = 0;
            }
            else{
                deplacer(-positiondroite + positiongaucheennemi);
                ResteDansFenetre();
                _vitesseX = 0;
            }

        }
        else{
            if(positiongauche < positiongaucheennemi){
                deplacer(-positiondroite + positiongaucheennemi);
                ResteDansFenetre();
            }
            else if(positiondroiteennemi >  1440 - positiongauche){
                deplacer(-positiondroite + positiongaucheennemi);
                ResteDansFenetre();
            }
            else{
                deplacer(positiondroiteennemi - positiongauche);
                ResteDansFenetre();
            }
            _vitesseX = 0;
        }
    }
}

void Broly::retourner(){
    _orientation = -_orientation;
    if(_orientation == 1){
        spriteBroly.setOrigin(0.f, 0.f);
        _hitbox.setOrigin(0.f,0.f);
        //_hurtbox.setOrigin(-2*spriteBroly.getGlobalBounds().width/10, 0.f);
    }
    else{
        spriteBroly.setOrigin(spriteBroly.getLocalBounds().width, 0.f);
        _hitbox.setOrigin(spriteBroly.getLocalBounds().width,0.f);
        //_hurtbox.setOrigin(-2*spriteBroly.getGlobalBounds().width/10, 0.f);
    }
    sf::Vector2f positionbroly = spriteBroly.getPosition();
    spriteBroly.setScale(_scale*_orientation,_scale);
    _hitbox.setScale(_scale*_orientation,_scale);
    spriteBroly.setPosition(positionbroly);
}


