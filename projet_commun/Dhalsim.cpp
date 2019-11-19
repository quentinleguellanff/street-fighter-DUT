#include "Dhalsim.h"
#include "Scene.h"

using namespace std;

Dhalsim::Dhalsim(int orientation,const Scene& s)
{
	_orientation=-orientation;
	_scene=s;
	_cptStatic=0;_cptAvancer=0;_cptReculer=0;_cptSauter=0;_cptApparition=0;_cptAction=0;_cptAccroupi==0;

	if (!_texture.loadFromFile("sprites/sprite_dhalsim.png"))
	{
	    std::cout<<"Erreur au chargement du sprite";
	}
	setTexture(_texture);
	scale(_orientation*SCALE,SCALE);
	setSprite(24,32,51,115);

	if(_orientation==1)
		_posX=100.f;
	else
		_posX=_scene.getRightLimit()-100.f;

	_posY=_scene.getBottom()-_tailleSprite.y;
	setPosition(_posX,_posY);
	keepInWalls();
}

void Dhalsim::setSprite(int n1, int n2, int i1, int i2)
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


void Dhalsim::rotate(const sf::Sprite& ennemi)
{
	if( (getScale().x==SCALE && _posX> ennemi.getPosition().x) || (getScale().x==SCALE*-1 && _posX< ennemi.getPosition().x) )
	{
		_orientation=_orientation*-1;
		_posX=_posX-_tailleSprite.x*_orientation;
		setPosition(_posX,_posY);
		setScale(_orientation*SCALE,SCALE);
	}
}

/*
void Dhalsim::rotate(sf::Clock& clockAnim,const sf::Sprite& _ennemi)
{
	
    bool fini=false;
    int delai=70;
	if( (getScale().x==SCALE && _posX> _ennemi.getPosition().x) || (getRotation()==360 && _posX< _ennemi.getPosition().x) )
	{
		sf::Time elapsed = clockAnim.getElapsedTime();
		int timeAnim = elapsed.asMilliseconds();
		if(_cptAction==0)
		{
			if(timeAnim > delai){
				cout<<"bienvenue"<<endl;
			    clockAnim.restart();
				_cptAction ++;
			    setSprite(737,163,65,103);
			}
		}else if (_cptAction==1)
		{
			if(timeAnim > delai){
			    clockAnim.restart();
			    _cptAction ++;
			    setSprite(810,163,63,103);
			}
		}else if(_cptAction==2)
		{
			if(timeAnim > delai){
			    clockAnim.restart();
			    _cptAction=0;
			    _orientation=-_orientation;
			    setSprite(881,163,93,103);
			    scale(_orientation*SCALE,SCALE);
			    fini=true;
			}
		}
		
	}
}*/


/* ANIMATIONS */

void Dhalsim::reset()
{
	//setSprite(409,32,51,115);
	_cptSauter=0;_cptApparition=0;_cptAction=0;
	_posY=_scene.getBottom()-_tailleSprite.y;
	setPosition(_posX,_posY);
}

void Dhalsim::resetAccroupi()
{
	_cptAccroupi=0;
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

		setSprite(24,32,51,115);
		_cptApparition +=1;
		break;
	case 1:
		if(timeAnim > delai){
		    _cptApparition +=1;
		    clockAnim.restart();
		    setSprite(83,32,52,115);
		    _posX-=1*SCALE*_orientation;
			setPosition(_posX,_posY);
		}
		break;
	case 2:
		if(timeAnim > delai){
		    _cptApparition +=1;
		    clockAnim.restart();
		    setSprite(143,32,53,115);
		    _posX-=1*SCALE*_orientation;
			setPosition(_posX,_posY);    
		}
		break;
	case 3:
		if(timeAnim > delai){
		    _cptApparition +=1;
		    clockAnim.restart();
		    setSprite(204,32,59,115);
		    _posX-=6*SCALE*_orientation;
			setPosition(_posX,_posY);
		    bandeau.setTextureRect(sf::IntRect(462, 70,78,77));
		}
		break;
	case 4:
		if(timeAnim > delai){
		    _cptApparition +=1;
		    clockAnim.restart();
		    setSprite(271,32,64,115);
		    _posX-=5*SCALE*_orientation;
			setPosition(_posX,_posY);
			bandeau.setTextureRect(sf::IntRect(542, 70,78,77));
		}
		break;
	case 5:
		if(timeAnim > delai){
		    _cptApparition +=1;
		    clockAnim.restart();
		    setSprite(343,32,58,115);
		    _posX+=6*SCALE*_orientation;
			setPosition(_posX,_posY);
		    bandeau.setTextureRect(sf::IntRect(622, 70,78,77));
		}
		break;
	case 6:
		if(timeAnim > delai){
		    _cptApparition +=1;
		    clockAnim.restart();
		    setSprite(409,32,51,115);
		    _posX+=13*SCALE*_orientation;
			setPosition(_posX,_posY);
			bandeau.setPosition(_posX-(_tailleSprite.x*_orientation),_posY);
		}
		break;
	}
	if(_cptApparition>=7)
	{
		_cptApparition++;
		bandeau.setPosition(_posX-((_tailleSprite.x+_cptApparition*3)*_orientation),_posY+_cptApparition);
	}
	if(_cptApparition==70)
	{
		bandeau.setTextureRect(sf::IntRect(0,0,0,0));
		fini=true;
	}

	
	return fini;
}

void Dhalsim::statique(sf::Clock& clockAnim,const sf::Sprite& ennemi)
{
    //_cptAvancer=0;_cptReculer=0;_cptSauter=0;_cptApparition=0;_cptAccroupi=0;
    sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=150;
    switch (_cptStatic)
    {
    case 0:
    	if(timeAnim > delai){
		    _cptStatic +=1;
		    clockAnim.restart();
    		setSprite(24,163,96,103);
    		_posY=_scene.getBottom()-_tailleSprite.y;
			setPosition(_posX,_posY);
		}
    	break;
    case 1:
    	if(timeAnim > delai){
		    _cptStatic +=1;
		    clockAnim.restart();
		    setSprite(128,163,97,103);
		}
    	break;
    case 2:
    	if(timeAnim > delai){
		    _cptStatic +=1;
		    clockAnim.restart();
		    setSprite(233,163,94,103);
		}
    	break;
    case 3:
    	if(timeAnim > delai){
		    _cptStatic +=1;
		    clockAnim.restart();
		    setSprite(335,163,94,103);
		}
    	break;
    case 4:
    	if(timeAnim > delai){
		    _cptStatic +=1;
		    clockAnim.restart();
		    setSprite(437,163,93,103);
		}
    	break;
    case 5:
    	if(timeAnim > delai){
		    _cptStatic +=1;
		    clockAnim.restart();
		    setSprite(538,163,92,103);
		}
    	break;
    case 6:
    	if(timeAnim > delai){
		    _cptStatic=0;
		    clockAnim.restart();
		    setSprite(638,163,91,103);
		}
    	break;
    }
    rotate(ennemi);
}


void Dhalsim::garde(sf::Clock& clockAnim)
{
	_cptStatic=0;
	_posY=_scene.getBottom()-_tailleSprite.y;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    if(timeAnim>delai)
    {
    	clockAnim.restart();
    	setSprite(125,4747,63,100);
    }
}


void Dhalsim::avancer(sf::Clock& clockAnim,const sf::Sprite& ennemi)
{
	_cptStatic=0;
	_posY=_scene.getBottom()-_tailleSprite.y;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    int deplacement=30;
    switch (_cptAvancer)
    {
    case 0:
		setPosition(_posX,_posY);
    	if(timeAnim > delai){
		    _cptAvancer +=1;
		    clockAnim.restart();
    		setSprite(24,284,75,101);
    		_posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 1:
    	if(timeAnim > delai){
		    _cptAvancer +=1;
		    clockAnim.restart();
		    setSprite(107,284,68,101);
		    _posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 2:
    	if(timeAnim > delai){
		    _cptAvancer +=1;
		    clockAnim.restart();
		    setSprite(183,284,61,101);
		    _posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 3:
    	if(timeAnim > delai){
		    _cptAvancer +=1;
		    clockAnim.restart();
		    setSprite(252,284,58,101);
		    _posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 4:
    	if(timeAnim > delai){
		    _cptAvancer +=1;
		    clockAnim.restart();
		    setSprite(318,284,67,101);
		    _posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 5:
    	if(timeAnim > delai){
		    _cptAvancer +=1;
		    clockAnim.restart();
		    setSprite(393,284,67,101);
		    _posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 6:
    	if(timeAnim > delai){
		    _cptAvancer+=1;
		    clockAnim.restart();
		    setSprite(468,284,63,101);
		    _posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 7:
    	if(timeAnim > delai){
		    _cptAvancer=0;
		    clockAnim.restart();
		    setSprite(539,284,66,101);
		    _posX+=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    }
    rotate(ennemi);
	keepInWalls();
}


void Dhalsim::reculer(sf::Clock& clockAnim)
{
	_posY=_scene.getBottom()-_tailleSprite.y;
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    int deplacement=30;
    switch (_cptReculer)
    {
    case 0:
		setPosition(_posX,_posY);
    	if(timeAnim > delai){
		    _cptReculer +=1;
		    clockAnim.restart();
    		setSprite(614,282,69,103);
    		_posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 1:
    	if(timeAnim > delai){
		    _cptReculer +=1;
		    clockAnim.restart();
		    setSprite(691,282,63,103);
		    _posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 2:
    	if(timeAnim > delai){
		    _cptReculer +=1;
		    clockAnim.restart();
		    setSprite(762,282,60,103);
		    _posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 3:
    	if(timeAnim > delai){
		    _cptReculer +=1;
		    clockAnim.restart();
			setSprite(830,282,63,103);
			_posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 4:
    	if(timeAnim > delai){
		    _cptReculer +=1;
		    clockAnim.restart();
			setSprite(901,282,62,103);
			_posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 5:
    	if(timeAnim > delai){
		    _cptReculer +=1;
		    clockAnim.restart();
		    setSprite(971,282,57,103);
		    _posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 6:
    	if(timeAnim > delai){
		    _cptReculer+=1;
		    clockAnim.restart();
			setSprite(1036,282,60,103);
			_posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    case 7:
    	if(timeAnim > delai){
		    _cptReculer=0;
		    clockAnim.restart();
			setSprite(1104,282,63,103);
			_posX-=_orientation*deplacement;
			setPosition(_posX,_posY);
		}
    	break;
    }
	keepInWalls();
}

bool Dhalsim::sauter(sf::Clock& clockAnim)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacement=125;
    bool fini=false;

    switch(_cptSauter)
    {
    case 0:
	    _cptSauter+=1;
	    setSprite(974,1705,50,126);
    	break;
    case 1:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter+=1;
		    _posY-=deplacement;
		    setPosition(_posX,_posY);
		}
    	break;
    case 2:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter+=1;
		    setSprite(1084,1705,57,126);
		    _posY-=deplacement;
		    setPosition(_posX,_posY);
		}
    	break;
    case 3:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter+=1;
		    setSprite(1148,1705,60,126);
		    _posY-=deplacement;
		    setPosition(_posX,_posY);
		}
    	break;
    case 4:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter+=1;
		    setSprite(1216,1705,65,126);
		}
    	break;
    case 5:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter+=1;
		    setSprite(1148,1705,60,126);
		    _posY+=deplacement;
		    setPosition(_posX,_posY);
		}
    	break;
    case 6:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter+=1;
		    setSprite(1084,1705,57,126);
		    _posY+=deplacement;
		    setPosition(_posX,_posY);
		}
    	break;
    case 7:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter+=1;
		    setSprite(974,1705,50,126);
		    _posY+=deplacement;
		    setPosition(_posX,_posY);
		}
    	break;
    case 8:
    	clockAnim.restart();
    	_cptSauter=0;
    	fini=true;
    	//reset();
    	break;
    }
    keepInWalls();
    return fini;
}


bool Dhalsim::sauterAvant(sf::Clock& clockAnim,const sf::Sprite& ennemi)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacementY=150,deplacementX=30*_orientation;
    bool fini=false;
    switch(_cptSauter)
    {
    case 0:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(108,1720,68,111);
    	}
    	break;
    case 1:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(108,1720,68,111);
    		_posX+=deplacementX;_posY-=deplacementY;
		    setPosition(_posX,_posY);
    	}
    	break;
    case 2:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(254,1720,68,111);
    		_posX+=deplacementX*2;_posY-=deplacementY;
		    setPosition(_posX,_posY);
    	}
    	break;
    case 3:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(330,1720,80,111);
    		_posX+=deplacementX;_posY-=deplacementY;
		    setPosition(_posX,_posY);
    	}
    	break;
    case 4:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(418,1720,79,111);
    		_posX+=deplacementX;
		    setPosition(_posX,_posY);
    	}
    	break;
    case 5:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(505,1720,57,111);
    		_posX+=deplacementX*4;_posY+=deplacementY;
		    setPosition(_posX,_posY);
    	}
    	break;
    case 6:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(570,1720,103,111);
    		_posX+=deplacementX*2;_posY+=deplacementY;
		    setPosition(_posX,_posY);
    	}
    	break;
    case 7:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(108,1720,68,111);
    		_posX+=deplacementX;_posY+=deplacementY;
		    setPosition(_posX,_posY);
    	}
    	break;
    case 8:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
			setSprite(108,1720,68,111);
			_cptSauter=0;
			fini=true;
			reset();
		}
    	break;
    }
    rotate(ennemi);
    keepInWalls();
    return fini;
}

bool Dhalsim::sauterArriere(sf::Clock& clockAnim)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacementY=150,deplacementX=30*_orientation;
    bool fini=false;
    switch(_cptSauter)
    {
    case 0:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(108,1720,68,111);
    	}
    	break;
    case 1:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(108,1720,68,111);
    		_posX-=deplacementX;_posY-=deplacementY;
		    setPosition(_posX,_posY);
    	}
    	break;
    case 2:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(570,1720,103,111);
    		_posX-=deplacementX*2;_posY-=deplacementY;
		    setPosition(_posX,_posY);
    	}
    	break;
    case 3:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(505,1720,57,111);
    		_posX-=deplacementX;_posY-=deplacementY;
		    setPosition(_posX,_posY);
    	}
    	break;
    case 4:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(418,1720,79,111);
    		_posX-=deplacementX;
		    setPosition(_posX,_posY);
    	}
    	break;
    case 5:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(330,1720,80,111);
    		_posX-=deplacementX*4;_posY+=deplacementY;
		    setPosition(_posX,_posY);
    	}
    	break;
    case 6:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(254,1720,68,111);
    		_posX-=deplacementX*2;_posY+=deplacementY;
		    setPosition(_posX,_posY);
    	}
    	break;
    case 7:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(108,1720,68,111);
    		_posX-=deplacementX;_posY+=deplacementY;
		    setPosition(_posX,_posY);
    	}
    	break;
    case 8:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
			setSprite(108,1720,68,111);
			_cptSauter=0;
			fini=true;
			reset();
		}
    	break;
    }
    keepInWalls();
    return fini;
}

void Dhalsim::accroupi(sf::Clock& clockAnim,bool garde)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=35;
    if(_cptAccroupi==0)
    {
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		_cptAccroupi++;
    		setSprite(24,1424,82,95);
    		_posY=_scene.getBottom()-_tailleSprite.y;
			setPosition(_posX,_posY);
    	}
    }else if(_cptAccroupi==1)
    {
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		_cptAccroupi++;
    		setSprite(114,1424,61,95);
    	}
    }else
    {
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		if(garde==true)
	    	{
	    		setSprite(263,4776,59,71);
	    	}else
    			setSprite(183,1424,60,95);
    	}
    }
}


bool Dhalsim::punch(sf::Clock& clockAnim)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    bool fini=false;
	switch (_cptAction)
	{
	case 0:
		if(timeAnim > delai){
		    _cptAction +=1;
		    clockAnim.restart();
		    setSprite(24,419,82,117);
		}
		break;
	case 1:
		if(timeAnim > delai){
		    _cptAction +=1;
		    clockAnim.restart();
		    setSprite(114,419,74,117);
		}
		break;
	case 2:
		if(timeAnim > delai){
		    _cptAction +=1;
		    clockAnim.restart();
		    setSprite(197,419,108,117);
		}
		break;
	case 3:
		if(timeAnim > delai){
		    _cptAction +=1;
		    clockAnim.restart();
		    setSprite(313,419,108,117);
		}
		break;
	case 4:
		if(timeAnim > delai){
		    _cptAction =0;
		    clockAnim.restart();
		    setSprite(429,419,75,117);
		    fini=true;
		}
		break;
	}
	keepInWalls();
	return fini;
}

bool Dhalsim::sautPunch(sf::Clock& clockAnim)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacement=125;
    bool fini=false;
    switch(_cptSauter)
    {
    case 0:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(974,1705,50,126);
		    _posY-=deplacement;
		    setPosition(_posX,_posY);
		}
    	break;
    case 1:
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(396,1857,96,85);
    		_posY-=deplacement/2;
    		setPosition(_posX,_posY);
    	}
    	break;
    case 2:
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(500,1857,76,85);
    	}
    	break;
    case 3:
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(584,1864,116,76);
    	}
    	break;
    case 4:
    	if(timeAnim>delai*3)
    	{
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(500,1857,76,85);
    	}
    	break;
    case 5:
    	if(timeAnim>delai)
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(396,1857,96,85);
    		_posY+=deplacement/2;
    		setPosition(_posX,_posY);
    	}
    	break;
    case 6:
    	if(timeAnim > delai){
		    clockAnim.restart();
		    _cptSauter=0;
		    setSprite(974,1705,50,126);
		    _posY+=deplacement;
		    setPosition(_posX,_posY);
		    fini=true;
		}
    	break;
    }
    keepInWalls();
    return fini;
}


bool Dhalsim::kick(sf::Clock& clockAnim)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    bool fini=false;
	switch (_cptAction)
	{
	case 0:
		if(timeAnim > delai){
		    _cptAction +=1;
		    clockAnim.restart();
		    setSprite(24,768,77,113);
		}
		break;
	case 1:
		if(timeAnim > delai){
		    _cptAction +=1;
		    clockAnim.restart();
		    setSprite(109,768,56,113);
		    _posX+=18*SCALE*_orientation;
			setPosition(_posX,_posY);
		}
		break;
	case 2:
		if(timeAnim > delai){
		    _cptAction +=1;
		    clockAnim.restart();
		    setSprite(173,768,126,113);
		    _posX-=8*SCALE*_orientation;
			setPosition(_posX,_posY);
		}
		break;
	case 3:
		if(timeAnim > delai){
		    _cptAction +=1;
		    clockAnim.restart();
		    setSprite(307,768,122,113);
		}
		break;
	case 4:
		if(timeAnim > delai){
		    _cptAction +=1;
		    clockAnim.restart();
		    setSprite(437,768,56,113);
		    _posX+=8*SCALE*_orientation;
			setPosition(_posX,_posY);
		}
		break;
	case 5:
		if(timeAnim > delai){
		    _cptAction =0;
		    clockAnim.restart();
		    setSprite(501,768,77,113);
		    _posX-=18*SCALE*_orientation;
			setPosition(_posX,_posY);
		    fini=true;
		}
		break;
	}
	keepInWalls();
	return fini;	
}

bool Dhalsim::sautKick(sf::Clock& clockAnim)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacement=125;
    bool fini=false;
    switch(_cptSauter)
    {
    case 0:
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(464,2319,62,110);
    		_posX+=33*_orientation;
    		setPosition(_posX,_posY);
    	}
    	break;
    case 1:
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(534,2319,59,110);
    		_posX+=2*_orientation;
    		_posY-=deplacement;
    		setPosition(_posX,_posY);
    	}
    	break;
    case 2:
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(601,2319,53,110);
    		_posX+=8*_orientation;
    		_posY-=deplacement;
    		setPosition(_posX,_posY);
    	}
    	break;
    case 3:
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(662,2319,63,110);
    		_posX-=8*_orientation;
    		setPosition(_posX,_posY);
    	}
    	break;
    case 4:
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(733,2319,99,110);
    		_posY+=deplacement;
    		setPosition(_posX,_posY);
    	}
    	break;
    case 5:
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(840,2319,70,110);
    		_posY+=deplacement;
    		setPosition(_posX,_posY);
    	}
    	break;
    case 6:
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		_cptSauter=0;
    		setSprite(918,2319,74,110);
    		_posX-=35*_orientation;
    		setPosition(_posX,_posY);
    		fini=true;
    	}
    	break;
    }
    keepInWalls();
    return fini;
}



bool Dhalsim::SP1(sf::Clock& clockAnim,sf::Sprite& bouleFeu)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    bool fini=false;
    switch (_cptAction)
	{
	case 0:
		if(timeAnim > delai){
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(24,3233,76,120);
		    _posX-=10*SCALE*_orientation;
			setPosition(_posX,_posY);
		}
		break;
	case 1:
		if(timeAnim > delai){
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(108,3233,81,120);
		    _posX-=6*SCALE*_orientation;
			setPosition(_posX,_posY);
		}
		break;
	case 2:
		if(timeAnim > delai){
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(197,3233,58,120);
		    _posX+=28*SCALE*_orientation;
			setPosition(_posX,_posY);
		}
		break;
	case 3:
		if(timeAnim > delai){
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(263,3233,92,120);
		    _posX-=4*SCALE*_orientation;
			setPosition(_posX,_posY);
			bouleFeu.setTextureRect(sf::IntRect(357,3355,38,25));
			bouleFeu.setScale(_orientation*SCALE,SCALE);
			bouleFeu.setPosition(_posX+(_tailleSprite.x*_orientation),_posY+(_tailleSprite.y/3));
		}
		break;
	}

	if(_cptAction>=4 && _cptAction<8)
	{
		_cptAction +=1;
		bouleFeu.setTextureRect(sf::IntRect(310,3355,39,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>7 && _cptAction<11)
	{
		_cptAction +=1;
		bouleFeu.setTextureRect(sf::IntRect(263,3355,39,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>10 && _cptAction<15)
	{
		_cptAction +=1;
		bouleFeu.setTextureRect(sf::IntRect(217,3355,38,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>14 && _cptAction<20)
	{
		_cptAction +=1;
		bouleFeu.setTextureRect(sf::IntRect(167,3355,42,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>19 && _cptAction<24)
	{
		_cptAction +=1;
		bouleFeu.setTextureRect(sf::IntRect(119,3355,40,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>23 && _cptAction<28)
	{
		_cptAction +=1;
		bouleFeu.setTextureRect(sf::IntRect(71,3355,40,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>27)
	{
		_cptAction +=1;
		bouleFeu.setTextureRect(sf::IntRect(24,3355,39,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}

	if( (_orientation==1 && bouleFeu.getPosition().x>=_scene.getRightLimit()) || (_orientation==-1 && bouleFeu.getPosition().x<=_scene.getLeftLimit()) )
	{
		bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
		bouleFeu.setPosition(_posX+(_tailleSprite.x*_orientation),_posY+(_tailleSprite.y/2));
		fini=true;
		_cptAction=0;
	}
	keepInWalls();
	return fini;
}