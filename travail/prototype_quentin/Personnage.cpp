#include "Personnage.h"

Personnage::Personnage(int,sf::RectangleShape&)
{
}

Personnage::Personnage()
{
    _hurtbox.setFillColor(sf::Color(0,0,255,100));
    _hitbox.setFillColor(sf::Color(255,0,0,100));
}

Personnage::~Personnage()
{
    //dtor
}

int Personnage::getorientation()
{
    return _orientation;
}
void Personnage::setSprite(int positionTextureX,int positionTextureY,int tailleX,int tailleY)
{
    _spritePerso.setTextureRect(sf::IntRect(positionTextureX,positionTextureY,tailleX,tailleY));
}


bool Personnage::collisioncoup(sf::RectangleShape hurtboxEnnemi)
{

    return _hitbox.getGlobalBounds().intersects(hurtboxEnnemi.getGlobalBounds());
}

bool Personnage::collisioncorps(sf::RectangleShape hurtboxEnnemi)
{

    return _hurtbox.getGlobalBounds().intersects(hurtboxEnnemi.getGlobalBounds());
}

sf::RectangleShape Personnage::gethurtbox()
{
    return _hurtbox;
}

void Personnage::restartPrendcoup()
{
    _cptanimprendcoup = 0;
}

sf::RectangleShape Personnage::gethitbox()
{
    return _hitbox;
}

void Personnage::resetcoup()
{
    /* SPECIFIQUE A BROLY
    int decalagex = -112*_orientation;
    _spritePerso.setPosition(_spritePerso.getPosition().x-decalagex,_spritePerso.getPosition().y-10);
    */
    _cptAnimCoupPoing = 0;
    _ok = false;
}

void Personnage::setVitesseX(int vitesse)
{
    _vitesseX = vitesse;
}

int Personnage::getVitesseX()
{
    return _vitesseX;
}

void Personnage::deplacer(int vitesse)
{
    //_spritePerso.move(vitesse,0.f);
    _spritePerso.setPosition(_spritePerso.getPosition().x+vitesse,_spritePerso.getPosition().y);
}

void Personnage::ResteDansFenetre()
{
    //_hurtbox.setPosition(spriteBroly.getPosition());
    float positiongauche = _hurtbox.getGlobalBounds().left;
    float positiondroite = _hurtbox.getGlobalBounds().left + _hurtbox.getGlobalBounds().width;
    //cout << positiongauche << endl;
    if(positiongauche < 0)
    {
        //deplacer(-positiongauche);
        if(_vitesseX < 0)
            _vitesseX = 0;
    }
    if(positiondroite > 1440)
    {
        //deplacer(1440 -positiondroite);
        if(_vitesseX > 0)
            _vitesseX = 0;
    }
}

void Personnage::collision(sf::RectangleShape hurtboxEnnemi)
{
    float positiongauche = _hurtbox.getGlobalBounds().left;
    float positiondroite = _hurtbox.getGlobalBounds().left + _hurtbox.getGlobalBounds().width;
    float positionbasse = _hurtbox.getPosition().y + _hurtbox.getGlobalBounds().height;
    float positionhaute = _hurtbox.getPosition().y;

    float positiongaucheennemi = hurtboxEnnemi.getGlobalBounds().left;
    float positiondroiteennemi = hurtboxEnnemi.getGlobalBounds().width + hurtboxEnnemi.getGlobalBounds().left;
    float positionbasseennemi = hurtboxEnnemi.getPosition().y + hurtboxEnnemi.getGlobalBounds().height;
    float positionhauteennemi = hurtboxEnnemi.getPosition().y;

    // collision debout
    if(positionbasse == positionbasseennemi)
    {
        if(_orientation == 1)
        {
            if(positiondroite + _vitesseX >= positiongaucheennemi)
            {
                //deplacer(positiongaucheennemi - positiondroite);
                _vitesseX = 0;
            }
        }
        else
        {
            //cout << _vitesseX << endl;
            if(positiongauche + _vitesseX <= positiondroiteennemi)
            {
                //deplacer(positiondroiteennemi - positiongauche);
                _vitesseX = 0;
            }
        }
    }
}

void Personnage::collisionsaut(sf::RectangleShape hurtboxEnnemi)
{
    float positiongauche = _hurtbox.getGlobalBounds().left;
    float positiondroite = _hurtbox.getGlobalBounds().left + _hurtbox.getGlobalBounds().width;
    float milieu = _hurtbox.getPosition().x + _hurtbox.getGlobalBounds().width/2;
    float positionbasse = _hurtbox.getPosition().y + _hurtbox.getGlobalBounds().height;
    float positionhaute = _hurtbox.getPosition().y;

    float positiongaucheennemi = hurtboxEnnemi.getGlobalBounds().left;
    float positiondroiteennemi = hurtboxEnnemi.getGlobalBounds().width + hurtboxEnnemi.getGlobalBounds().left;
    float positionhauteennemi = hurtboxEnnemi.getPosition().y;
    float positionbasseennemi = hurtboxEnnemi.getPosition().y + hurtboxEnnemi.getGlobalBounds().height;
    float milieuennemi = hurtboxEnnemi.getGlobalBounds().left + hurtboxEnnemi.getGlobalBounds().width/2;

    /*
        860 est la position du sol
        le perso verifie si l'autre perso est au sol ou en saut, le comportement est different en saut et au sol
        normalement les personnages ne peuvent pas sortir de la fenetre, lorsqu'ils se croisent en saut leurs vitesses = 0,
        un personnage qui saute et qui retombe sur un autre perso ira a sa droite ou à sa gauche en fonction de sa position en x
        par rapport à l'autre personnage


    */
    //on verifie que le perso cible est le seul à être en saut
    if(positionbasse < positionbasseennemi && positionbasseennemi >= 860)
    {
        if(_orientation == -1)
        {
            //on ne fait rien si il n'y a pas collision
            if(!(positiongauche + _vitesseX > positiondroiteennemi && positionbasse > positionhauteennemi)){
                //on verifie si le perso cible dépasse l'autre si oui on le deplace à droite, sinon à gauche
                if((positiondroite + _vitesseX >= positiondroiteennemi && positionbasse > positionhauteennemi && positiondroiteennemi < 1440 - hurtboxEnnemi.getGlobalBounds().width/2)
                        || (positiongauche < 0 && positiongaucheennemi  < _hurtbox.getGlobalBounds().width/2 && positionbasse > positionhauteennemi))
                {
                    deplacer(positiondroiteennemi - positiongauche + 15);
                    _vitesseX = 0;
                }
                else if(positiondroite + _vitesseX > positiongaucheennemi && positionbasse > positionhauteennemi)
                {
                    deplacer(-positiondroite + positiongaucheennemi - _vitesseX*2 - 15);
                    _vitesseX = 0;
                }
            }
        }
        else if(_orientation == 1)
        {
            //même chose mais avec une orientation différente
            if(!(positiondroite + _vitesseX < positiongaucheennemi && positionbasse > positionhauteennemi)){
                if((positiongauche + _vitesseX <= positiongaucheennemi && positionbasse > positionhauteennemi && positiongaucheennemi > hurtboxEnnemi.getGlobalBounds().width/2)
                        || (positiondroite > 1440 && positiondroiteennemi > 1440 - _hurtbox.getGlobalBounds().width/2 && positionbasse > positionhauteennemi))
                {
                    deplacer(-positiondroite+positiongaucheennemi - _vitesseX);
                }
                else if(positiongauche + _vitesseX < positiondroiteennemi && positionbasse > positionhauteennemi)
                {
                    deplacer(positiondroiteennemi - positiongauche - _vitesseX*2);
                }
            }
        }
    }
    //si les deux personnages sont en saut on les empêche de se confondre et on stoppe leur vitesse
    else if(positionbasse < 860 && positionbasseennemi < 860)
    {
        if(_orientation == 1)
        {
            if(positiondroite + _vitesseX >= positiongaucheennemi)
            {
                deplacer(-_vitesseX);
                _vitesseX = 0;
            }
        }
        else if(_orientation == -1)
        {
            if(positiongauche + _vitesseX <= positiondroiteennemi)
            {
                deplacer(-_vitesseX);
                _vitesseX = 0;
            }
        }
    }
}

void Personnage::retourner()
{
    _orientation = -_orientation;
    _spritePerso.setScale(_scale*_orientation,_scale);
    _hurtbox.setScale(_orientation,1);
    _hitbox.setScale(_scale*_orientation,_scale);
    _spritePerso.setPosition(_spritePerso.getPosition().x-_spritePerso.getGlobalBounds().width*_orientation,_spritePerso.getPosition().y);
    _hurtbox.setPosition(_spritePerso.getPosition().x, _spritePerso.getPosition().y);
}

sf::Sprite Personnage::getSprite(){
    return _spritePerso;
}
