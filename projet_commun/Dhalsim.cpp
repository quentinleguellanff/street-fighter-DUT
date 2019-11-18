#include "Dhalsim.h"
#include "Scene.h"

using namespace std;

Dhalsim::Dhalsim(int orientation,const Scene& s)
{
	_orientation=-orientation;
	_scene=s;
	_cptStatic=0;_cptAvancer=0;_cptReculer=0;_cptSauter=0;_cptApparition=0;_cptPunch=0;_cptEffet=0;

	if (!_texture.loadFromFile("sprites/sprite_dhalsim.png"))
	{
	    std::cout<<"Erreur au chargement du sprite";
	}
	setTexture(_texture);
	scale(_orientation*SCALE,SCALE);
	_setSprite(24,32,51,115);

	if(_orientation==1)
		_posX=100.f;
	else
		_posX=_scene.getRightLimit()-100.f;

	_posY=_scene.getBottom()-_tailleSprite.y;
	setPosition(_posX,_posY);
	keepInWalls();
}

void Dhalsim::_setSprite(int n1, int n2, int i1, int i2)
{
	_tailleSprite.x=i1*SCALE;_tailleSprite.y=i2*SCALE;
	setTextureRect(sf::IntRect(n1, n2,i1,i2));
}

void Dhalsim::keepInWalls()
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
	setPosition(sf::Vector2f(_posX,_posY ));

}


/* ANIMATIONS */

void Dhalsim::reset()
{
	_setSprite(409,32,51,115);
	_posY=_scene.getBottom()-_tailleSprite.y;
	setPosition(_posX,_posY);
}

bool Dhalsim::apparition(sf::Clock& clockAnim,sf::Sprite& bandeau)
{
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    bool fini=false;
    int delai=200;
    
   	switch(_cptApparition)
	{
	case 0:
		bandeau.setTexture(_texture);
	    bandeau.setTextureRect(sf::IntRect(0,0,0,0));
	    bandeau.setScale(_orientation*SCALE,SCALE);
	    bandeau.setPosition(_posX-(_tailleSprite.x*_orientation),_posY);

		_setSprite(24,32,51,115);
		_cptApparition ++;
		break;
	case 1:
		if(timeAnim > delai){
		    _cptApparition ++;
		    clockAnim.restart();
		    _setSprite(83,32,52,115);
		    _posX-=1*SCALE*_orientation;
			setPosition(_posX,_posY);
		}
		break;
	case 2:
		if(timeAnim > delai){
		    _cptApparition ++;
		    clockAnim.restart();
		    _setSprite(143,32,53,115);
		    _posX-=1*SCALE*_orientation;
			setPosition(_posX,_posY);    
		}
		break;
	case 3:
		if(timeAnim > delai){
		    _cptApparition ++;
		    clockAnim.restart();
		    _setSprite(204,32,59,115);
		    _posX-=6*SCALE*_orientation;
			setPosition(_posX,_posY);
		    bandeau.setTextureRect(sf::IntRect(462, 70,78,77));
		}
		break;
	case 4:
		if(timeAnim > delai){
		    _cptApparition ++;
		    clockAnim.restart();
		    _setSprite(271,32,64,115);
		    _posX-=5*SCALE*_orientation;
			setPosition(_posX,_posY);
			bandeau.setTextureRect(sf::IntRect(542, 70,78,77));
		}
		break;
	case 5:
		if(timeAnim > delai){
		    _cptApparition ++;
		    clockAnim.restart();
		    _setSprite(343,32,58,115);
		    _posX+=6*SCALE*_orientation;
			setPosition(_posX,_posY);
		    bandeau.setTextureRect(sf::IntRect(622, 70,78,77));
		}
		break;
	case 6:
		if(timeAnim > delai){
		    _cptApparition ++;
		    clockAnim.restart();
		    _setSprite(409,32,51,115);
		    _posX+=13*SCALE*_orientation;
			setPosition(_posX,_posY);
			//bandeau.setPosition(_posX-(_tailleSprite.x*_orientation),_posY);
		}
		break;
	}
	if(_cptApparition>=6)
	{
		bandeau.setPosition(_posX-((_tailleSprite.x+_cptEffet*4)*_orientation),_posY+_cptEffet);
		_cptEffet++;
	}
	if(_cptEffet==50)
	{
		bandeau.setTextureRect(sf::IntRect(0,0,0,0));
		_cptEffet=0;
		fini=true;
	}

	
	return fini;
}

void Dhalsim::statique(sf::Clock& clockAnim)
{
    sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=150;
    switch (_cptStatic)
    {
    case 0:
    	if(timeAnim > delai){
		    _cptStatic +=1;
		    clockAnim.restart();
    		_setSprite(24,163,96,103);
    		_posY=_scene.getBottom()-_tailleSprite.y;
			setPosition(_posX,_posY);
		}
    	break;
    case 1:
    	if(timeAnim > delai){
		    _cptStatic +=1;
		    clockAnim.restart();
		    _setSprite(128,163,97,103);
		}
    	break;
    case 2:
    	if(timeAnim > delai){
		    _cptStatic +=1;
		    clockAnim.restart();
		    _setSprite(233,163,94,103);
		}
    	break;
    case 3:
    	if(timeAnim > delai){
		    _cptStatic +=1;
		    clockAnim.restart();
		    _setSprite(335,163,94,103);
		}
    	break;
    case 4:
    	if(timeAnim > delai){
		    _cptStatic +=1;
		    clockAnim.restart();
		    _setSprite(437,163,93,103);
		}
    	break;
    case 5:
    	if(timeAnim > delai){
		    _cptStatic +=1;
		    clockAnim.restart();
		    _setSprite(538,163,92,103);
		}
    	break;
    case 6:
    	if(timeAnim > delai){
		    _cptStatic=0;
		    clockAnim.restart();
		    _setSprite(638,163,91,103);
		}
    	break;
    }
}

void Dhalsim::avancer(sf::Clock& clockAnim)
{
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    int deplacement=30;
    switch (_cptAvancer)
    {
    case 0:
    	_posY=_scene.getBottom()-_tailleSprite.y;
		setPosition(_posX,_posY);
    	if(timeAnim > delai){
		    _cptAvancer +=1;
		    clockAnim.restart();
    		_setSprite(24,284,75,101);
    		_posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 1:
    	if(timeAnim > delai){
		    _cptAvancer +=1;
		    clockAnim.restart();
		    _setSprite(107,284,68,101);
		    _posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 2:
    	if(timeAnim > delai){
		    _cptAvancer +=1;
		    clockAnim.restart();
		    _setSprite(183,284,61,101);
		    _posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 3:
    	if(timeAnim > delai){
		    _cptAvancer +=1;
		    clockAnim.restart();
		    _setSprite(252,284,58,101);
		    _posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 4:
    	if(timeAnim > delai){
		    _cptAvancer +=1;
		    clockAnim.restart();
		    _setSprite(318,284,67,101);
		    _posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 5:
    	if(timeAnim > delai){
		    _cptAvancer +=1;
		    clockAnim.restart();
		    _setSprite(393,284,67,101);
		    _posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 6:
    	if(timeAnim > delai){
		    _cptAvancer+=1;
		    clockAnim.restart();
		    _setSprite(468,284,63,101);
		    _posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 7:
    	if(timeAnim > delai){
		    _cptAvancer=0;
		    clockAnim.restart();
		    _setSprite(539,284,66,101);
		    _posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    }
	keepInWalls();
}


void Dhalsim::reculer(sf::Clock& clockAnim)
{
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    int deplacement=30;
    switch (_cptReculer)
    {
    case 0:
    	_posY=_scene.getBottom()-_tailleSprite.y;
		setPosition(_posX,_posY);
    	if(timeAnim > delai){
		    _cptReculer +=1;
		    clockAnim.restart();
    		_setSprite(614,282,69,103);
    		_posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 1:
    	if(timeAnim > delai){
		    _cptReculer +=1;
		    clockAnim.restart();
		    _setSprite(691,282,63,103);
		    _posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 2:
    	if(timeAnim > delai){
		    _cptReculer +=1;
		    clockAnim.restart();
		    _setSprite(762,282,60,103);
		    _posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 3:
    	if(timeAnim > delai){
		    _cptReculer +=1;
		    clockAnim.restart();
			_setSprite(830,282,63,103);
			_posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 4:
    	if(timeAnim > delai){
		    _cptReculer +=1;
		    clockAnim.restart();
			_setSprite(901,282,62,103);
			_posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 5:
    	if(timeAnim > delai){
		    _cptReculer +=1;
		    clockAnim.restart();
		    _setSprite(971,282,57,103);
		    _posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 6:
    	if(timeAnim > delai){
		    _cptReculer+=1;
		    clockAnim.restart();
			_setSprite(1036,282,60,103);
			_posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 7:
    	if(timeAnim > delai){
		    _cptReculer=0;
		    clockAnim.restart();
			_setSprite(1104,282,63,103);
			_posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    }
	keepInWalls();
}