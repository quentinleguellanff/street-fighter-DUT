#include "personnage.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

using namespace std;



Personnage::Personnage(Background b,int i) 
{
	switch (i)
	{
	case 1:
		_orientation=-1;
		if (!_texturePersonnage.loadFromFile("images/Brolyspriteok.png"))
		{
		    std::cout<<"Erreur au chargement du sprite";
		}
		_spritePersonnage.setTexture(_texturePersonnage);
		_spritePersonnage.scale(_orientation*SCALE,SCALE);
		setSprite(2,466,121,201);
		_x=0.f;_y=b.getBottom()-getTailleY();
		_spritePersonnage.setPosition(sf::Vector2f(_x,_y ));
	    
	    break;
	case 2:
		_orientation=1;
		if (!_texturePersonnage.loadFromFile("images/Brolyspriteok.png"))
		{
		    std::cout<<"Erreur au chargement du sprite";
		}
		_spritePersonnage.setTexture(_texturePersonnage);
		_spritePersonnage.scale(_orientation*SCALE,SCALE);
		setSprite(2,466,121,201);
		_x=1920.f-_tailleSprite.x;_y=b.getBottom()-getTailleY();
		_spritePersonnage.setPosition(sf::Vector2f(_x,_y ));
	    break;
	}
	keepInWalls(b);
    Hitbox tempHit(_tailleSprite,_x,_y,_orientation);
    _structure=tempHit;
}

void Personnage::keepInWalls(Background b)
{
	if(_orientation==-1)
	{
		if(_x-_tailleSprite.x<b.getLeftLimit())
			_x=b.getLeftLimit()+_tailleSprite.x;
		else if(_x>b.getRightLimit())
			_x=b.getRightLimit();   
	}else if(_orientation==1)
	{
		if(_x<b.getLeftLimit())
			_x=b.getLeftLimit();
		else if(_x+_tailleSprite.x>b.getRightLimit())
			_x=b.getRightLimit()-_tailleSprite.x;   
	}
	if(_y+_tailleSprite.y>b.getBottom())
			_y=b.getBottom()-_tailleSprite.y;
	_spritePersonnage.setPosition(sf::Vector2f(_x,_y ));

}

///// Deplacements //////////////////

void Personnage::moveForward(Background b,int x)
{
	setSprite(2+130*x,874,128,202);
	if(_orientation==-1)
		_x=_x+5;
	else
		_x=_x-5;
	_spritePersonnage.setPosition(sf::Vector2f(_x,_y));
	keepInWalls(b);
	_structure.setCorps("forward",_x,_y);
	_structure.setBrasD("forward",x,_x,_y);
}

void Personnage::moveBackward(Background b,int x)
{
	if(x<=0)
        setSprite(2,11437,153,207);
    else
        setSprite(157,11437,153,207);
	_x=_x-5;
	_spritePersonnage.setPosition(sf::Vector2f(_x,_y));
	keepInWalls(b);

}

void Personnage::crouch(Background b,int x)
{
	if(x<=1)
		setSprite(2+137*x,1862,135,172);
	else
		setSprite(2+274,1862,135,172);
	if(x==0)	
		_y=_y+30;
	_spritePersonnage.setPosition(sf::Vector2f(_x,_y));
	keepInWalls(b);
}

void Personnage::jumpNoMove(Background b,int x)
{
	sf::IntRect tempRect;
	tempRect=_spritePersonnage.getTextureRect();
	setSprite(2+158*x,1650,156,208);
	if(!tempRect.intersects(_spritePersonnage.getTextureRect()))
	{
		if(x<3 && x>0)
    		_y=_y-105;
    	else if(x<6 && x>2)
    		_y=_y+70;
    	_spritePersonnage.setPosition(sf::Vector2f(_x,_y));	
    	keepInWalls(b);
	}
    _structure.setCorps("jump",_x,_y);
    _structure.setBrasD("jump",x,_x,_y);
}

void Personnage::jumpMoveRight(Background b,int x, bool monte)
{
	sf::IntRect tempRect;
	tempRect=_spritePersonnage.getTextureRect();
	setSprite(2+162*x,3970,160,221);
	if(!tempRect.intersects(_spritePersonnage.getTextureRect()))
	{
		if( x==1 || x==2)
		{
			if(monte)
			{
				_y=_y-140;
				_x+=100;
			}	
			else
			{
				_y=_y+140;
				_x+=100;
			}
		}
		_spritePersonnage.setPosition(sf::Vector2f(_x,_y));	
		keepInWalls(b);
	}
}

void Personnage::jumpMoveLeft(Background b,int x,bool monte)
{
	sf::IntRect tempRect;
	tempRect=_spritePersonnage.getTextureRect();
	setSprite(2+162*x,3970,160,221);
	if(!tempRect.intersects(_spritePersonnage.getTextureRect()))
	{
		if( x==1 || x==2)
		{
			if(monte)
			{
				_y=_y-140;
				_x-=100;
			}	
			else
			{
				_y=_y+140;
				_x-=100;
			}
		}
		_spritePersonnage.setPosition(sf::Vector2f(_x,_y));	
		keepInWalls(b);
	}
}

void Personnage::punch(Background b,int x)
{
    sf::IntRect tempRect;
    tempRect=_spritePersonnage.getTextureRect();
    setSprite(2+218*x,2960,216,201);
    if(!tempRect.intersects(_spritePersonnage.getTextureRect()))
    {
        if(x==0)
            _x+=_tailleSprite.x*0.56;
        else if(x==5)
        {
            _x-=_tailleSprite.x*0.56;
            reset(b,9);
        }
        _spritePersonnage.setPosition(sf::Vector2f(_x,_y));
    }
    	_structure.setCorps("punch",_x,_y);
    	_structure.setBrasD("punch",x,_x,_y);   
}

void Personnage::kick(Background b,int x)
{
    sf::IntRect tempRect;
    tempRect=_spritePersonnage.getTextureRect();
    setSprite(2+437*x,3605,435,189);
    if(!tempRect.intersects(_spritePersonnage.getTextureRect()))
    {
        if(x==0)
            _x+=_tailleSprite.x*0.1;
        else if(x==2)
        	_x+=_tailleSprite.x*0.2;
        else if(x==3)
        	_x-=_tailleSprite.x*0.1;
        else if(x==6)
        	_x-=_tailleSprite.x*0.2;
        _spritePersonnage.setPosition(sf::Vector2f(_x,_y));
    }    
}

void Personnage::reset(Background b,int x)
{
	setSprite(2+123*x,466,121,201);
	_y=b.getBottom()-getTailleY();
	_spritePersonnage.setPosition(sf::Vector2f(_x,_y));
    Hitbox tempHit(_tailleSprite,_x,_y,_orientation);
    _structure=tempHit;
}

///// Méthodes de manipulation /////////

void Personnage::setSprite(int n1, int n2, int i1, int i2)
{
	_tailleSprite.x=i1*SCALE;_tailleSprite.y=i2*SCALE;
	_spritePersonnage.setTextureRect(sf::IntRect(n1, n2,i1,i2));
}

sf::Sprite Personnage::getSprite() const
{
	return _spritePersonnage;
}

int Personnage::getTailleY() const
{
	return _tailleSprite.y;
}

sf::Vector2f Personnage::getTaille() const
{
	sf::Vector2f tempTab{_tailleSprite.x,_tailleSprite.x};
	return tempTab;
}

int Personnage::getPosX() const
{
	return _x;
}

int Personnage::getPosY() const
{
	return _y;
}

sf::RectangleShape Personnage::getCorps() const
{
    return _structure.getBody();
}

sf::RectangleShape Personnage::getBras() const
{
    return _structure.getBrasD();
}