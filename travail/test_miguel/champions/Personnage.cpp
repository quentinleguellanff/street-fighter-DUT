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

bool Personnage::collisioncoup(sf::RectangleShape hurtboxEnnemi){

    return _hitbox.getGlobalBounds().intersects(hurtboxEnnemi.getGlobalBounds());
}

bool Personnage::collisioncorps(sf::RectangleShape hurtboxEnnemi){

    return _hurtbox.getGlobalBounds().intersects(hurtboxEnnemi.getGlobalBounds());
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
	if( (_sprite.getScale().x==SCALE && _posX> ennemi.getSprite().getPosition().x*0.9) || (_sprite.getScale().x==SCALE*-1 && _posX< ennemi.getSprite().getPosition().x*0.9) )
	{
		_orientation=_orientation*-1;
		_posX=_posX-_tailleSprite.x*_orientation;
		_sprite.setPosition(_posX,_posY);
		_sprite.setScale(_orientation*SCALE,SCALE);
	}

	if(_orientation==-1)
    {
		_hurtbox.setScale(-1,1);
		_hitbox.setScale(-1,1);
	}else
	{
		_hurtbox.setScale(1,1);
		_hitbox.setScale(1,1);
	}
}

int Personnage::getOrientation() const
{
	return _orientation*-1;
}


void Personnage::resetCptAccroupi()
{
	_cptAccroupi=0;
}

