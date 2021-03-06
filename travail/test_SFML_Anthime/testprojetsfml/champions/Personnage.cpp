#include "../IncludeManager.h"

using namespace std;


sf::Sprite Personnage::getSprite()
{
	return _sprite;
}


void Personnage::setSprite(int n1, int n2, int i1, int i2)
{
	_tailleSprite.x=i1*SCALE;_tailleSprite.y=i2*SCALE;
	_sprite.setTextureRect(sf::IntRect(n1, n2,i1,i2));
}
sf::RectangleShape Personnage::getHurtbox()
{
	return _hurtbox;
}

sf::RectangleShape Personnage::getHitbox()
{
	return _hitbox;
}

void Personnage::resetHitbox()
{
    _hitbox.setSize(sf::Vector2f(0,0));
}

sf::RectangleShape Personnage::getGardebox()
{
    return _gardebox;
}


bool Personnage::collisioncoup(Personnage& ennemi){

    return _hitbox.getGlobalBounds().intersects(ennemi.getHurtbox().getGlobalBounds());
}

void Personnage::collision(Personnage& ennemi, int& deplacement)
{
    if( (_orientation==1 && _posX+_tailleSprite.x+deplacement*2 >= ennemi.getPosX()-ennemi.getHurtbox().getGlobalBounds().width)
              || (_orientation==-1 && _posX-_tailleSprite.x-deplacement*2 <= ennemi.getPosX()+ennemi.getHurtbox().getGlobalBounds().width))
    {
        deplacement=0;
    }
        
    _sprite.setPosition(_posX,_posY);
}

void Personnage::keepInWalls()
{
	if(_orientation==-1)
	{
		if(_posX-_tailleSprite.x<_scene.getLeftLimit())
			_posX=_scene.getLeftLimit()+_tailleSprite.x;
		else if(_posX>_scene.getRightLimit())
			_posX=_scene.getRightLimit();   
	}else if(_orientation==1)
	{
		if(_posX<_scene.getLeftLimit())
			_posX=_scene.getLeftLimit();
		else if(_posX+_tailleSprite.x>_scene.getRightLimit())
			_posX=_scene.getRightLimit()-_tailleSprite.x;   
	}
	if(_posY+_tailleSprite.y>_scene.getBottom())
			_posY=_scene.getBottom()-_tailleSprite.y;
	_sprite.setPosition(sf::Vector2f(_posX,_posY ));
}


void Personnage::rotate(Personnage& ennemi)
{
	if( (_orientation==1 && _hurtbox.getPosition().x > ennemi.getHurtbox().getPosition().x) || (_orientation==-1 && _hurtbox.getPosition().x< ennemi.getHurtbox().getPosition().x) )
	{
        _orientation=_orientation*-1;
        if(_orientation==-1)
        {
            _hurtbox.setScale(-1,1);
            _hitbox.setScale(-1,1);
        }else
        {
            _hurtbox.setScale(1,1);
            _hitbox.setScale(1,1);
        }
		_posX=_posX-_tailleSprite.x*_orientation;
		_sprite.setPosition(_posX,_posY);
		_sprite.setScale(_orientation*SCALE,SCALE);
	}
}

bool Personnage::auSol()
{
    return(_posY+_tailleSprite.y>=_scene.getBottom()-5);
}

int Personnage::getOrientation() const
{
	return _orientation*-1;
}

void Personnage::setPosX(int n)
{
    _posX=n;
}

int Personnage::getPosX()
{
    return _posX;
}

void Personnage::setPosY(int n)
{
    _posY=n;
}

int Personnage::getPosY()
{
    return _posY;
}



void Personnage::resetCptAccroupi()
{
	_cptAccroupi=0;
}

void Personnage::collisionsaut(Personnage& ennemi,int& deplacement)
{
    if(_hurtbox.getGlobalBounds().intersects(ennemi.getHurtbox().getGlobalBounds()))
    {
        float positionGauche = _hurtbox.getGlobalBounds().left;
        float positionDroite = _hurtbox.getGlobalBounds().left + _hurtbox.getGlobalBounds().width;
        float positionBasse = _hurtbox.getPosition().y + _hurtbox.getGlobalBounds().height;
        float positionHaute = _hurtbox.getPosition().y;

        float positionGaucheEnnemi = ennemi.getHurtbox().getGlobalBounds().left;
        float positionDroiteEnnemi = ennemi.getHurtbox().getGlobalBounds().width + ennemi.getHurtbox().getGlobalBounds().left;
        float positionHauteEnnemi = ennemi.getHurtbox().getPosition().y;
        float positionBasseEnnemi = ennemi.getHurtbox().getPosition().y + ennemi.getHurtbox().getGlobalBounds().height;

        /*
            _scene.getBottom() est la position du sol
            le perso verifie si l'autre perso est au sol ou en saut, le comportement est different en saut et au sol
            normalement les personnages ne peuvent pas sortir de la fenetre, lorsqu'ils se croisent en saut leurs vitesses = 0,
            un personnage qui saute et qui retombe sur un autre perso ira a sa droite ou ?? sa gauche en fonction de sa position en x
            par rapport ?? l'autre personnage


        */
        //on verifie que le perso cible est le seul ?? ??tre en saut
        if(positionBasse < positionBasseEnnemi && positionBasseEnnemi >= _scene.getBottom())
        {
            if(_orientation == -1)
            {
                //on ne fait rien si il n'y a pas collision
                if(!(positionGauche + deplacement > positionDroiteEnnemi && positionBasse > positionHauteEnnemi)){
                    //on verifie si le perso cible d??passe l'autre si oui on le deplace ?? droite, sinon ?? gauche
                    if((positionDroite + deplacement >= positionDroiteEnnemi && positionBasse > positionHauteEnnemi && positionDroiteEnnemi < _scene.getRightLimit() - ennemi.getHurtbox().getGlobalBounds().width/2)
                            || positionGauche < 0 && positionGaucheEnnemi  < _hurtbox.getGlobalBounds().width/2 && positionBasse > positionHauteEnnemi)
                    {
                        _posX+=(positionDroiteEnnemi - positionGauche + 15*SCALE);
                        deplacement = 0;
                    }
                    else if(positionDroite + deplacement > positionGaucheEnnemi && positionBasse > positionHauteEnnemi)
                    {
                        _posX+=(-positionDroite + positionGaucheEnnemi - deplacement*2 - 15*SCALE);
                        deplacement = 0;
                    }
                }
            }
            else if(_orientation == 1)
            {
                //m??me chose mais avec une orientation diff??rente
                if(!(positionDroite + deplacement < positionGaucheEnnemi && positionBasse > positionHauteEnnemi)){
                    if((positionGauche + deplacement <= positionGaucheEnnemi && positionBasse > positionHauteEnnemi && positionGaucheEnnemi > ennemi.getHurtbox().getGlobalBounds().width/2)
                            || positionDroite > _scene.getRightLimit() && positionDroiteEnnemi > _scene.getRightLimit() - _hurtbox.getGlobalBounds().width/2 && positionBasse > positionHauteEnnemi)
                    {
                        _posX+=(-positionDroite+positionGaucheEnnemi - deplacement);
                    }
                    else if(positionGauche + deplacement < positionDroiteEnnemi && positionBasse > positionHauteEnnemi)
                    {
                        _posX+=(positionDroiteEnnemi - positionGauche - deplacement*2);
                    }
                }
            }
        }
        //si les deux personnages sont en saut on les emp??che de se confondre et on stoppe leur vitesse
        else if(positionBasse < _scene.getBottom() && positionBasseEnnemi < _scene.getBottom())
        {
            if(_orientation == -1)
            {
                if(positionDroite + deplacement >= positionGaucheEnnemi)
                {
                    _posX+=(-deplacement);
                    deplacement = 0;
                }
            }
            else if(_orientation == 1)
            {
                if(positionGauche + deplacement <= positionDroiteEnnemi)
                {
                    _posX+=(-deplacement);
                    deplacement = 0;
                }
            }
        }
        _sprite.setPosition(_posX,_posY);
        keepInWalls();
    }
}