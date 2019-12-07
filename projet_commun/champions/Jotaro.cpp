#include "../IncludeManager.h"

using namespace std;

Jotaro::Jotaro(int orientation,const Scene& s)
{
	_orientation=-orientation;
	_scene=s;
	_cptStatic=0;_cptAvancer=0;_cptReculer=0;_cptSauter=0;_cptApparition=0;_cptAction=0;_cptAccroupi==0;_cptGarde=0;_cptSP=0;_indexTab=0;

	if (!_texture.loadFromFile("sprites/sprite_jotaro.png"))
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

	_hurtbox.setFillColor(sf::Color(255,255,255,0));
    _hurtbox.setOutlineColor(sf::Color::Green);
    _hurtbox.setOutlineThickness(4);
    
    _hitbox.setFillColor(sf::Color(255,255,255,0));
    _hitbox.setOutlineColor(sf::Color::Red);
    _hitbox.setOutlineThickness(4);

    if(_orientation==-1)
    {
		_hurtbox.setScale(-1,1);
		_hitbox.setScale(-1,1);
	}
}

void Jotaro::setSprite(int n1, int n2, int i1, int i2)
{
	_tailleSprite.x=i1*SCALE;_tailleSprite.y=i2*SCALE;
	setTextureRect(sf::IntRect(n1, n2,i1,i2));
}


void Jotaro::ajouterTexture(int n1, int n2, int i1, int i2)
{
	_tabSP[_indexTab][0]=n1;
	_tabSP[_indexTab][1]=n2;
	_tabSP[_indexTab][2]=i1;
	_tabSP[_indexTab][3]=i2;
	_indexTab++;
}

void Jotaro::resetTexture()
{
	for(int i=0;i<=25;i++)
	{
		_tabSP[i][0]=0;
		_tabSP[i][1]=0;
		_tabSP[i][2]=0;
		_tabSP[i][3]=0;
	}
	_indexTab=0;
}

sf::RectangleShape Jotaro::getHurtbox()
{
	return _hurtbox;
}

sf::RectangleShape Jotaro::getHitbox()
{
	return _hitbox;
}


void Jotaro::keepInWalls()
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


void Jotaro::rotate(const sf::Sprite& ennemi)
{
	if( (getScale().x==SCALE && _posX> ennemi.getPosition().x*0.9) || (getScale().x==SCALE*-1 && _posX< ennemi.getPosition().x*0.9) )
	{
		_orientation=_orientation*-1;
		_posX=_posX-_tailleSprite.x*_orientation;
		setPosition(_posX,_posY);
		setScale(_orientation*SCALE,SCALE);
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

bool Jotaro::prendCoup(sf::Clock& clockAnim,bool& enCours)
{
	bool fini=false;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    _hurtbox.setSize(sf::Vector2f(0,0));
    if(timeAnim > delai)
    {
    	switch(_cptAction)
    	{
    	case 0:
    		clockAnim.restart();
    		_cptAction++;
    		setSprite(1168,5354,89,108);
    		_posX-=11*SCALE*_orientation;
    		_posY+=9*SCALE;
    		break;
    	case 1:
    		clockAnim.restart();
    		_cptAction++;
    		setSprite(1269,5354,111,108);
    		_posX-=10*SCALE*_orientation;
    		break;
    	case 2:
    		clockAnim.restart();
    		_cptAction++;
    		setSprite(1858,5371,123,88);
    		_posY+=20*SCALE;
    		_posX-=10*SCALE*_orientation;
    		break;
    	case 3:
    		clockAnim.restart();
    		_cptAction++;
    		setSprite(1391,5354,88,108);
    		break;
    	case 4:
    		clockAnim.restart();
    		_cptAction=0;
    		setSprite(4,6,64,117);
    		fini=true;
    		enCours=false;
    		break;
    	}
    }
    keepInWalls();
    setPosition(_posX,_posY);
    return fini;
}

int Jotaro::getOrientation() const
{
	return _orientation*-1;
}


/* ANIMATIONS */

void Jotaro::reset()
{
	_posY=_scene.getBottom()-_tailleSprite.y;
    
}

void Jotaro::resetAccroupi()
{
	_cptAccroupi=0;
}

bool Jotaro::collisioncoup(sf::RectangleShape hurtboxEnnemi){

    return _hitbox.getGlobalBounds().intersects(hurtboxEnnemi.getGlobalBounds());
}

bool Jotaro::collisioncorps(sf::RectangleShape hurtboxEnnemi){

    return _hurtbox.getGlobalBounds().intersects(hurtboxEnnemi.getGlobalBounds());
}

bool Jotaro::apparition(sf::Clock& clockAnim,sf::Sprite& starPlat)
{
	if(!_SPChargee)
	{
		ajouterTexture(671,3724,100,135);ajouterTexture(875,3724,142,135);ajouterTexture(1025,3724,185,135);ajouterTexture(1219,3724,169,135);
		ajouterTexture(1395,3724,184,135);ajouterTexture(1586,3724,176,135);ajouterTexture(1768,3724,158,135);ajouterTexture(1933,3724,150,135);
		ajouterTexture(2091,3724,165,135);ajouterTexture(2264,3724,164,135);ajouterTexture(2436,3724,163,135);ajouterTexture(2607,3724,151,135);
		ajouterTexture(2765,3724,195,135);ajouterTexture(2968,3724,187,135);ajouterTexture(3162,3724,168,135);ajouterTexture(3339,3724,140,135);
		ajouterTexture(3485,3724,138,135);ajouterTexture(3630,3724,179,135);ajouterTexture(3816,3724,170,135);ajouterTexture(3995,3724,166,135);
		ajouterTexture(4170,3724,175,135);ajouterTexture(4354,3724,174,135);ajouterTexture(4536,3724,171,135);ajouterTexture(4714,3724,155,135);
		_SPChargee=true;
	}
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=120;
    bool fini =false;
    if(_cptApparition<=10 && timeAnim>delai)
    {
    	switch(_cptApparition)
    	{
    	case 0:
    		clockAnim.restart();
    		_cptApparition++;
    		setSprite(18,1403,82,134);
    		_posX-=18*SCALE*_orientation;
    		break;
    	case 1:
    		clockAnim.restart();
    		_cptApparition++;
    		setSprite(112,1403,87,134);
    		_posX-=2*SCALE*_orientation;
    		break;
    	case 2:
    		clockAnim.restart();
    		_cptApparition++;
    		setSprite(209,1403,101,134);
    		_posX-=2*SCALE*_orientation;
    		break;
    	case 3:
    		clockAnim.restart();
    		_cptApparition++;
    		setSprite(318,1403,101,134);

    		break;
    	case 4:
    		clockAnim.restart();
    		_cptApparition++;
    		setSprite(428,1403,157,134);
    		break;
    	case 5:
    		clockAnim.restart();
    		_cptApparition++;
    		setSprite(597,1403,137,134);
    		_posX+=21*SCALE*_orientation;
    		break;
    	case 6:
    		clockAnim.restart();
    		_cptApparition++;
    		setSprite(748,1403,132,134);
    		break;
    	case 7:
    		clockAnim.restart();
    		_cptApparition++;
    		setSprite(892,1403,127,134);
    		break;
    		clockAnim.restart();
    		_cptApparition++;
    		setSprite(1030,1403,121,134);
    		break;
    	case 8:
    		clockAnim.restart();
    		_cptApparition++;
    		setSprite(1168,1403,120,134);
    		_posX+=1*SCALE*_orientation;
    		break;
    	case 9:
    		clockAnim.restart();
    		_cptApparition++;
    		setSprite(1030,1403,121,134);
    		_posX-=1*SCALE*_orientation;
    		break;
    	case 10:
    		clockAnim.restart();
    		_cptApparition++;
    		setSprite(3050,4837,69,117);
    		_posY+=17*SCALE;
    		starPlat.setTexture(_texture);
    		starPlat.setScale(_orientation*SCALE,SCALE);
			starPlat.setPosition(_posX+(_tailleSprite.x*_orientation),_scene.getBottom()-_tabSP[0][3]*SCALE);
			starPlat.setTextureRect(sf::IntRect(_tabSP[0][0],_tabSP[0][1],_tabSP[0][2],_tabSP[0][3]));
    		break;
    	}  	
    }
    else if(_cptApparition>10 && timeAnim>delai/3)
	    {
	    	clockAnim.restart();
	    	_cptApparition++;
			starPlat.setTextureRect(sf::IntRect(_tabSP[_cptApparition-10][0],_tabSP[_cptApparition-10][1],_tabSP[_cptApparition-10][2],_tabSP[_cptApparition-10][3]));
			if(_cptApparition==34)
			{
				fini=true;
				_SPChargee=false;
				_cptApparition=0;
				starPlat.setTextureRect(sf::IntRect(0,0,0,0));
				resetTexture();
				reset();
			}
	    }

    setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}

void Jotaro::statique(sf::Clock& clockAnim,const sf::Sprite& ennemi)
{
    sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=120;
	if(timeAnim>delai)
	{
	    switch (_cptStatic)
	    {
	    case 0:
		    _posY=_scene.getBottom()-_tailleSprite.y;
			
		    _cptStatic ++;
		    clockAnim.restart();
			setSprite(4,6,64,117);
	    	break;
	    case 1:
		    _cptStatic ++;
		    clockAnim.restart();
		    setSprite(80,6,64,117);
	    	break;
	    case 2:
		    _cptStatic ++;
		    clockAnim.restart();
		    setSprite(155,6,64,117);
	    	break;
	    case 3:
		    _cptStatic ++;
		    clockAnim.restart();
		    setSprite(232,6,66,117);
	    	break;
	    case 4:
			    _cptStatic ++;
			    clockAnim.restart();
			    setSprite(310,6,69,117);
	    	break;
	    case 5:
		    _cptStatic ++;
		    clockAnim.restart();
		    setSprite(390,6,67,117);
	    	break;
	    case 6:
		    _cptStatic++;
		    clockAnim.restart();
		    setSprite(467,6,64,117);
		    break;
	    case 7:
		    _cptStatic=0;
		    clockAnim.restart();
		    setSprite(541,6,64,117);
	    	break;
	    }
	}

    _hurtbox.setPosition(_posX,_posY);
    _hurtbox.setSize(sf::Vector2f(50*SCALE,_tailleSprite.y));
    rotate(ennemi);
    keepInWalls();
}


void Jotaro::garde(sf::Clock& clockAnim)
{
	_cptStatic=0;
	_posY=_scene.getBottom()-_tailleSprite.y;
	
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    if(timeAnim>delai)
	{	
    	if(_cptGarde==0)
    	{
	    	clockAnim.restart();
	    	_cptGarde++;
	    	setSprite(7,4991,110,125);
	    	_posX-=11*SCALE*_orientation;
	    }else if(_cptGarde==1)
	    {
	    	clockAnim.restart();
	    	_cptGarde++;
	    	setSprite(122,4991,139,125);
	    	_posX-=34*SCALE*_orientation;
	    }else if(_cptGarde>1)
	    {
	    	clockAnim.restart();
	    	_cptGarde++;
	    	setSprite(269,4991,108,125);
	    	if(_cptGarde==3)
	    		_posX+=17*SCALE*_orientation;
	    }
	}
	setPosition(_posX,_posY);
}

bool Jotaro::finGarde(sf::Clock& clockAnim)
{
	_cptGarde=0;
	bool fini=false;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    if(timeAnim>delai)
	{
		if(_cptAction==0)
    	{
	    	clockAnim.restart();
	    	_cptAction++;
	    	setSprite(642,4991,126,125);
	    }else if(_cptAction==1)
	    {
	    	clockAnim.restart();
	    	_cptAction++;
	    	setSprite(1043,4991,125,125);
	    }else if(_cptAction==2)
	    {
	    	clockAnim.restart();
	    	_cptAction=0;
	    	setSprite(4,6,64,117);
	    	_posX+=28*SCALE*_orientation;
	    	
	    	fini=true;
	    }
	}
	setPosition(_posX,_posY);
	return fini;
};


void Jotaro::avancer(sf::Clock& clockAnim,const sf::Sprite& ennemi)
{
	_cptStatic=0;
	_posY=_scene.getBottom()-_tailleSprite.y;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=60;
    int deplacement=40;
    if(timeAnim>delai)
    {
	    switch (_cptAvancer)
	    {
	    case 0:
			
		    _cptAvancer ++;
		    clockAnim.restart();
			setSprite(4,858,67,115);
			_posX+=_orientation*deplacement;
	    	break;
	    case 1:
		    _cptAvancer ++;
		    clockAnim.restart();
		    setSprite(92,858,59,115);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 2:
		    _cptAvancer ++;
		    clockAnim.restart();
		    setSprite(174,858,47,115);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 3:
		    _cptAvancer ++;
		    clockAnim.restart();
		    setSprite(247,858,48,115);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 4:
		    _cptAvancer ++;
		    clockAnim.restart();
		    setSprite(316,858,53,115);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 5:
		    _cptAvancer ++;
		    clockAnim.restart();
		    setSprite(387,858,70,115);
		    _posX+=_orientation*deplacement;
			
	    	break;
	    case 6:
		    _cptAvancer++;
		    clockAnim.restart();
		    setSprite(473,858,77,115);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 7:
		    _cptAvancer++;
		    clockAnim.restart();
		    setSprite(564,858,72,115);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 8:
		    _cptAvancer++;
		    clockAnim.restart();
		    setSprite(658,858,69,115);
		    _posX+=_orientation*deplacement;
			break;
		case 9:
		    _cptAvancer++;
		    clockAnim.restart();
		    setSprite(746,858,62,115);
		    _posX+=_orientation*deplacement;
			break;
		case 10:
		    _cptAvancer++;
		    clockAnim.restart();
		    setSprite(825,858,47,115);
		    _posX+=_orientation*deplacement;
			break;
		case 11:
		    _cptAvancer++;
		    clockAnim.restart();
		    setSprite(897,858,52,115);
		    _posX+=_orientation*deplacement;
			break;
		case 12:
		    _cptAvancer++;
		    clockAnim.restart();
		    setSprite(961,858,58,115);
		    _posX+=_orientation*deplacement;
			break;
		case 13:
		    _cptAvancer++;
		    clockAnim.restart();
		    setSprite(1124,858,76,115);
		    _posX+=_orientation*deplacement;
			break;
		case 14:
		    _cptAvancer=0;
		    clockAnim.restart();
		    setSprite(1209,858,72,115);
		    _posX+=_orientation*deplacement;
			break;
	    }
	}
    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y));
    _hurtbox.setPosition(_posX,_posY);
    rotate(ennemi);
    setPosition(_posX,_posY);
	keepInWalls();
}


void Jotaro::reculer(sf::Clock& clockAnim)
{
	_posY=_scene.getBottom()-_tailleSprite.y;
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=60;
    int deplacement=35;
    if(timeAnim>delai)
    {
		switch (_cptReculer)
		{
		case 0:
		    _cptReculer ++;
		    clockAnim.restart();
			setSprite(1413,858,76,115);
			_posX-=_orientation*deplacement;
			break;
		case 1:
		    _cptReculer ++;
		    clockAnim.restart();
		    setSprite(1499,858,75,115);
		    _posX-=_orientation*deplacement;
			break;
		case 2:
		    _cptReculer ++;
		    clockAnim.restart();
		    setSprite(1583,858,58,115);
		    _posX-=_orientation*deplacement;
			break;
		case 3:
		    _cptReculer ++;
		    clockAnim.restart();
			setSprite(1656,858,52,115);
			_posX-=_orientation*deplacement;
			break;
		case 4:
		    _cptReculer ++;
		    clockAnim.restart();
			setSprite(1723,858,46,115);
			_posX-=_orientation*deplacement;
			break;
		case 5:
		    _cptReculer ++;
		    clockAnim.restart();
		    setSprite(1782,858,59,115);
		    _posX-=_orientation*deplacement;
			break;
		case 6:
		    _cptReculer++;
		    clockAnim.restart();
			setSprite(1854,858,59,115);
			_posX-=_orientation*deplacement;
			break;
		case 7:
		    _cptReculer++;
		    clockAnim.restart();
			setSprite(1931,858,72,115);
			_posX-=_orientation*deplacement;
			break;
		case 8:
		    _cptReculer++;
		    clockAnim.restart();
		    setSprite(2016,858,77,115);
		    _posX-=_orientation*deplacement;
			break;
		case 9:
		    _cptReculer++;
		    clockAnim.restart();
		    setSprite(2105,858,70,115);
		    _posX-=_orientation*deplacement;
			break;
		case 10:
		    _cptReculer++;
		    clockAnim.restart();
		    setSprite(2186,858,53,115);
		    _posX-=_orientation*deplacement;
			break;
		case 11:
		    _cptReculer++;
		    clockAnim.restart();
		    setSprite(2253,858,48,115);
		    _posX-=_orientation*deplacement;
			break;
		case 12:
		    _cptReculer++;
		    clockAnim.restart();
		    setSprite(2314,858,47,115);
		    _posX-=_orientation*deplacement;
			break;
		case 13:
		    _cptReculer++;
		    clockAnim.restart();
		    setSprite(2374,858,56,115);
		    _posX-=_orientation*deplacement;
			break;
		case 14:
		    _cptReculer++;
		    clockAnim.restart();
		    setSprite(2443,858,67,115);
		    _posX-=_orientation*deplacement;
			break;
		case 15:
		    _cptReculer=0;
		    clockAnim.restart();
		    setSprite(2523,858,72,115);
		    _posX-=_orientation*deplacement;
			break;
		}
	}
	setPosition(_posX,_posY);
    _hurtbox.setPosition(_posX,_posY);
	keepInWalls();
}

bool Jotaro::sauter(sf::Clock& clockAnim,sf::Clock& clockAttente)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacement=100;
    bool fini=false;

    if(_cptSauter==0)
    {
    	clockAttente.restart();
		    _cptSauter++;
		    setSprite(2,1101,97,153);
		    _posX-=25*SCALE;
		    _posY=_scene.getBottom()-_tailleSprite.y;
    }
    else if(timeAnim > delai)
   	{
	    switch(_cptSauter)
	    {
	    case 1:
			    clockAnim.restart();
			    _cptSauter++;
			    setSprite(109,1111,57,153);
			    _posX+=25*SCALE;
			    _posY-=deplacement;
	    	break;
	    case 2:
			    clockAnim.restart();
			    _cptSauter++;
			    setSprite(183,1111,90,153);
			    _posX-=13*SCALE;
			    _posY-=deplacement;
	    	break;
	    case 3:
			    clockAnim.restart();
			    _cptSauter++;
			    setSprite(281,1111,88,153);
			    _posY-=deplacement;
	    	break;
	    case 4:
			    clockAnim.restart();
			    _cptSauter++;
			    setSprite(383,1111,80,153);
			    _posY-=deplacement;
	    	break;
	    case 5:
			    clockAnim.restart();
			    _cptSauter++;
			    setSprite(480,1111,85,153);
	    	break;
	    case 6:
			    clockAnim.restart();
			    _cptSauter++;
			    setSprite(576,1111,99,153);
			    _posX-=8*SCALE;
			    _posY+=deplacement;
	    	break;
	    case 7:
			    clockAnim.restart();
			    _cptSauter++;
			    setSprite(682,1111,101,153);
			    _posY+=deplacement;
	    	break;
	    case 8:
		    	clockAnim.restart();
		    	_cptSauter++;
		    	setSprite(793,1111,111,153);
			    _posY+=deplacement;
	    	break;
	    case 9:
		    	clockAnim.restart();
		    	_cptSauter++;
		    	setSprite(914,1111,125,153);
			    _posY+=deplacement;
			break;
		case 10:
		    	clockAnim.restart();
		    	_cptSauter++;
		    	setSprite(1043,1111,104,153);
		    	_posX+=8*SCALE;
			break;
		case 11:
		    	clockAnim.restart();
		    	_cptSauter++;
		    	setSprite(1269,1102,91,151);    	
			break;
		case 12:
		    	clockAnim.restart();
		    	_cptSauter++;
		    	setSprite(1372,1102,90,151);
			break;
		case 13:
		    	clockAnim.restart();
		    	_cptSauter++;
		    	setSprite(1476,1102,71,152);  	
			break;
		case 14:
		    	clockAnim.restart();
		    	_cptSauter=0;
		    	setSprite(4,6,64,117);
		    	fini=true;  	
		    	_posX+=8*SCALE;
			break;
	    }
	}

    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.7));
    _hurtbox.setPosition(_posX+_tailleSprite.x*0.4,_posY+_tailleSprite.y*0.25);
    setPosition(_posX,_posY);
    return fini;
}


bool Jotaro::sauterAvant(sf::Clock& clockAnim,const sf::Sprite& ennemi)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacementY=100,deplacementX=35*_orientation;
    bool fini=false;
    if(_cptSauter==0)
    {
    	_cptSauter++;
	    setSprite(2,1101,97,153);
	    _posY=_scene.getBottom()-_tailleSprite.y;
    }else if(timeAnim>delai)
    {
	    switch(_cptSauter)
	    {
	    case 1:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(109,1111,57,153);
		    _posY-=deplacementY;
		    _posX+=deplacementX;
	    	break;
	    case 2:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(183,1111,90,153);
		    _posY-=deplacementY;
		    _posX+=deplacementX;
	    	break;
	    case 3:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(281,1111,88,153);
		    _posY-=deplacementY;
		    _posX+=deplacementX;
	    	break;
	    case 4:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(383,1111,80,153);
		    _posY-=deplacementY;
		    _posX+=deplacementX;
	    	break;
	    case 5:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(480,1111,85,153);
	    	break;
	    case 6:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(576,1111,99,153);
		    _posY+=deplacementY;
		    _posX+=deplacementX;
	    	break;
	    case 7:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(682,1111,101,153);
		    _posY+=deplacementY;
		    _posX+=deplacementX;
	    	break;
	    case 8:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(793,1111,111,153);
		    _posY+=deplacementY;
		    _posX+=deplacementX;
	    	break;
	    case 9:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(914,1111,125,153);
		    _posY+=deplacementY;
		    _posX+=deplacementX;
			break;
		case 10:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(1043,1111,104,153);
			break;
		case 11:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(1269,1102,91,151);    	
			break;
		case 12:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(1372,1102,90,151);	    	
			break;
		case 13:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(1476,1102,71,152);  	
			break;
		case 14:
	    	clockAnim.restart();
	    	_cptSauter=0;
	    	setSprite(1557,1136,76,118);
	    	fini=true;  	    	
			break;
	    }
	}

    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y));
    _hurtbox.setPosition(_posX,_posY);
    setPosition(_posX,_posY);
    rotate(ennemi);
    keepInWalls();
    return fini;
}

bool Jotaro::sauterArriere(sf::Clock& clockAnim)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacementY=100,deplacementX=50*_orientation;
    bool fini=false;

    if(_cptSauter==0)
    {
    	_cptSauter++;
	    setSprite(2,1101,97,153);
	    _posY=_scene.getBottom()-_tailleSprite.y;
    }else if( timeAnim>delai)
    {
	    switch(_cptSauter)
	    {
	    case 1:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(109,1111,57,153);
		    _posY-=deplacementY;
		    _posX-=deplacementX;
	    	break;
	    case 2:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(183,1111,90,153);
		    _posY-=deplacementY;
		    _posX-=deplacementX;
	    	break;
	    case 3:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(281,1111,88,153);
		    _posY-=deplacementY;
		    _posX-=deplacementX;
	    	break;
	    case 4:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(383,1111,80,153);
		    _posY-=deplacementY;
		    _posX-=deplacementX;
	    	break;
	    case 5:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(480,1111,85,153);
	    	break;
	    case 6:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(576,1111,99,153);
		    _posY+=deplacementY;
		    _posX-=deplacementX;
	    	break;
	    case 7:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(682,1111,101,153);
		    _posY+=deplacementY;
		    _posX-=deplacementX;
	    	break;
	    case 8:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(793,1111,111,153);
		    _posY+=deplacementY;
		    _posX-=deplacementX;
	    	break;
	    case 9:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(914,1111,125,153);
		    _posY+=deplacementY;
		    _posX-=deplacementX;
			break;
		case 10:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(1043,1111,104,153);
			break;
		case 11:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(1269,1102,91,151);    	
			break;
		case 12:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(1372,1102,90,151);	    	
			break;
		case 13:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(1476,1102,71,152);  	
			break;
		case 14:
	    	clockAnim.restart();
	    	_cptSauter=0;
	    	setSprite(1557,1136,76,118);
	    	fini=true;  	    	
			break;
	    }
	}

    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y));
    _hurtbox.setPosition(_posX,_posY);
    setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}

void Jotaro::accroupi(sf::Clock& clockAnim,bool garde)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    if(timeAnim>delai)
    {
	    if(_cptAccroupi==0)
	    {	
    		clockAnim.restart();
    		_cptAccroupi++;
    		setSprite(914,743,97,102);
    		_posY=_scene.getBottom()-_tailleSprite.y;
    		_posX-=25*SCALE;
	    }else if(_cptAccroupi==1)
	    {
    		clockAnim.restart();
    		_cptAccroupi++;
    		setSprite(1026,743,91,102);
    		_posX+=14*SCALE;
	    }else if(_cptAccroupi==2)
	    {
    		clockAnim.restart();
    		_cptAccroupi++;
    		setSprite(1128,743,104,102);
	    }else if(_cptAccroupi==3)
	    {
    		clockAnim.restart();
    		_cptAccroupi++;
    		setSprite(1245,743,89,102);
    		_posX+=4*SCALE;
	    }else if(_cptAccroupi==4)
	    {
    		clockAnim.restart();
    		_cptAccroupi++;
    		setSprite(1348,743,95,102);
    		_posX-=3*SCALE;
	    }else if(_cptAccroupi==5)
	    {
    		clockAnim.restart();
    		if(garde==true)
	    	{
	    		setSprite(1783,5033,131,83);
	    		_cptAccroupi++;
	    	}else
	    	{
    			setSprite(1348,743,95,102);
    			_cptGarde=0;
    		}
	    }else
	    {
	    	clockAnim.restart();
    		if(garde==true)
	    	{
	    		setSprite(1922,5033,112,83);
	    	}else
    			_cptAccroupi=5;
	    }
	}
	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.7));
    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.3);
    setPosition(_posX,_posY);
}

bool Jotaro::seLever(sf::Clock& clockAnim)
{
	_cptAccroupi=0;
	bool fini=false;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    if(timeAnim>delai)
    {
	    switch(_cptAction)
	    {
	    case 0:
	    	clockAnim.restart();
	    	_cptAction++;
	    	setSprite(2186,725,90,118);
	    	_posX+=1*SCALE*_orientation;
	    	break;
	    case 1:
	    	clockAnim.restart();
	    	_cptAction++;
	    	setSprite(2290,725,90,118);
	    	_posX-=1*SCALE*_orientation;
	    	break;
	    case 2:
	    	clockAnim.restart();
	    	_cptAction++;
	    	setSprite(2392,725,71,118);
	    	_posX+=12*SCALE*_orientation;
	    	break;
	    case 3:
	    	clockAnim.restart();
	    	_cptAction++;
	    	setSprite(2471,725,76,118);
	    	_posX-=6*SCALE*_orientation;
	    	break;
	    case 4:
	    	clockAnim.restart();
	    	_cptAction=0;
	    	setSprite(4,6,64,117);
	    	_posX+=6*SCALE*_orientation;
	    	fini=true;
	    	break;
	    }
   	}
   	setPosition(_posX,_posY);
   	keepInWalls();
   	return fini;
}

bool Jotaro::punch(sf::Clock& clockAnim,sf::RectangleShape hurtboxEnnemi,bool& prendCoup, Player& ennemi)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    bool fini=false;
	if(timeAnim>delai)
	{
		switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(6,2106,88,115);
			break;
		case 1:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(102,2106,117,115);
			break;
		case 2:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(227,2106,119,115);
			break;
		case 3:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(359,2106,152,115);
		    _hitbox.setSize(sf::Vector2f(49*SCALE,23*SCALE));
		    _hitbox.setPosition(_posX+_tailleSprite.x*0.66*_orientation,_posY+18*SCALE);
			break;
		case 4:
		    _cptAction++;
		    clockAnim.restart();
		    setSprite(519,2106,110,114);
		    _posY+=2*SCALE*_orientation;
		    _hitbox.setSize(sf::Vector2f(0,0));
			break;
		case 5:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(637,2106,134,114);
			break;
		case 6:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(776,2106,132,114);
			break;
		case 7:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(915,2106,107,114);
			break;
		case 8:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(1031,2106,71,115);
			break;
		case 9:
		    _cptAction =0;
		    clockAnim.restart();
		    setSprite(4,6,64,117);
		    fini=true;
			break;
		}
	}

	if(collisioncoup(hurtboxEnnemi))
	{
		prendCoup=true;
		ennemi.setDegats(10);
	}

	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y));
    _hurtbox.setPosition(_posX,_posY);
    setPosition(_posX,_posY);
	keepInWalls();
	return fini;
}

bool Jotaro::sautPunch(sf::Clock& clockAnim,sf::RectangleShape hurtboxEnnemi,bool& prendCoup, Player& ennemi)
{
	return sauter(clockAnim,clockAnim);
}

bool Jotaro::punchSP(sf::Clock& clockAnim,sf::Sprite& starPlat,sf::RectangleShape hurtboxEnnemi,bool& prendCoup, Player& ennemi)
{
	if(!_SPChargee)
	{
		ajouterTexture(1751,4643,112,128);ajouterTexture(1870,4643,108,128);ajouterTexture(2157,4643,161,128);ajouterTexture(2467,4643,127,128);
		ajouterTexture(2762,4643,219,128);ajouterTexture(3128,4643,218,128);ajouterTexture(3634,4643,129,128);
		_SPChargee=true;
	}
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    bool fini=false;
	if(timeAnim>delai)
	{
	    switch (_cptAction)
		{
		case 0:
			    _cptAction ++;
			    clockAnim.restart();
			    setSprite(13,4649,76,117);
			    starPlat.setTexture(_texture);
			    starPlat.setScale(_orientation*SCALE,SCALE);
				starPlat.setPosition(_posX+(_tailleSprite.x/2*_orientation),_posY);
			break;
		case 1:
			    _cptAction ++;
			    clockAnim.restart();
			    setSprite(101,4649,122,117);
			break;
		case 2:
			    _cptAction ++;
			    clockAnim.restart();
			    setSprite(228,4649,118,117);
			break;
		case 3:
			    _cptAction ++;
			    clockAnim.restart();
			    setSprite(357,4649,113,117);
			break;
		case 4:
			    _cptAction ++;
			    clockAnim.restart();
			    setSprite(477,4649,113,117);
			break;
		case 5:
			    _cptAction ++;
			    clockAnim.restart();
			    setSprite(598,4649,106,117);
			break;
		case 13:
			    _cptAction ++;
			    clockAnim.restart();
			    setSprite(1064,4649,75,117);
			break;
		case 14:
			    _cptAction ++;
			    clockAnim.restart();
			    setSprite(1145,4649,74,117);
			break;
		case 15:
			    _cptAction =0;
			    clockAnim.restart();
			    fini=true;
			break;
		}

		if(_cptAction>5 && _cptAction<13)
		{
			clockAnim.restart();
			_cptAction++;
			starPlat.setTextureRect(sf::IntRect(_tabSP[_cptAction-6][0],_tabSP[_cptAction-6][1],_tabSP[_cptAction-6][2],_tabSP[_cptAction-6][3]));
			if(_cptAction==10)
			{
				_hitbox.setSize(sf::Vector2f(95*SCALE,74*SCALE));
				_hitbox.setPosition(starPlat.getPosition().x+124*SCALE*_orientation,starPlat.getPosition().y+51*SCALE);
			}
			if(_cptAction==11)
			{
				_hitbox.setSize(sf::Vector2f(0,0));
			}
		}
	}

	if(collisioncoup(hurtboxEnnemi))
	{
		prendCoup=true;
		ennemi.setDegats(30);
	}

	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.4,_tailleSprite.y));
    _hurtbox.setPosition(_posX,_posY);
	return fini;
}


bool Jotaro::kick(sf::Clock& clockAnim,sf::RectangleShape hurtboxEnnemi,bool& prendCoup, Player& ennemi)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    bool fini=false;
	
	if(timeAnim>delai)
	{
		switch (_cptAction)
		{
		case 0:
			    _cptAction ++;
			    clockAnim.restart();
			    setSprite(1322,2103,74,118);
			break;
		case 1:
			if(timeAnim > delai*1.5){
			    _cptAction ++;
			    clockAnim.restart();
			    setSprite(1414,2103,76,118);
			    _posX-=9*SCALE*_orientation;
			    
			}
			break;
		case 2:
			if(timeAnim > delai*1.5){
			    _cptAction ++;
			    clockAnim.restart();
			    setSprite(1507,2103,89,118);
			    _posX-=5*SCALE*_orientation;
			    
			}
			break;
		case 3:
			    _cptAction ++;
			    clockAnim.restart();
			    setSprite(1612,2103,130,118);
			    _posX-=8*SCALE*_orientation;
			    
			    _hitbox.setSize(sf::Vector2f(72*SCALE,28*SCALE));
			    _hitbox.setPosition(_posX+58*SCALE*_orientation,_posY+72*SCALE);
			break;
		case 4:
			    _cptAction ++;
			    clockAnim.restart();
			    setSprite(1758,2103,124,118);
			    _posX-=2*SCALE*_orientation;		    
			break;
		case 5:
			    _cptAction++;
			    clockAnim.restart();
			    setSprite(1893,2103,112,118);
			    _posX+=1*SCALE*_orientation;
			    _hitbox.setSize(sf::Vector2f(0,0));
			break;
		case 6:
			    _cptAction++;
			    clockAnim.restart();
			    setSprite(2018,2103,104,118);
			    _posX+=1*SCALE*_orientation;
			break;
		case 7:
			    _cptAction++;
			    clockAnim.restart();
			    setSprite(2131,2103,71,118);
			    _posX+=17*SCALE*_orientation;
			break;
		case 8:
			    _cptAction++;
			    clockAnim.restart();
			    setSprite(2215,2103,76,118);
			    _posX-=6*SCALE*_orientation;
			break;
		case 9:
			    _cptAction =0;
			    clockAnim.restart();
			    setSprite(4,6,64,117);
			    _posX+=11*SCALE*_orientation;
			    fini=true;
			break;
		}
	}

	if(collisioncoup(hurtboxEnnemi))
	{
		prendCoup=true;
		ennemi.setDegats(15);
	}

	_hurtbox.setSize(sf::Vector2f(50*SCALE,_tailleSprite.y));
    _hurtbox.setPosition(_posX,_posY);
    setPosition(_posX,_posY);
	keepInWalls();
	return fini;	
}

bool Jotaro::sautKick(sf::Clock& clockAnim,sf::RectangleShape hurtboxEnnemi,bool& prendCoup, Player& ennemi)
{
    _cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50,deplacement=100;
    bool fini=false;
    if(_cptSauter==0)
    {
    	clockAnim.restart();
	    _cptSauter++;
	    setSprite(2,1101,97,153);
	    _posX-=25*SCALE;
	    _posY=_scene.getBottom()-_tailleSprite.y;
    }else if(timeAnim>delai)
    {
	    switch(_cptSauter)
	    {
	    case 1:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(109,1111,57,153);
		    _posX+=25*SCALE;
		    _posY-=deplacement;
	    	break;
	    case 2:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(183,1111,90,153);
		    _posX-=13*SCALE;
		    _posY-=deplacement;
	    	break;
	    case 3:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(281,1111,88,153);
		    _posY-=deplacement;
	    	break;
	    case 4:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(3208,2117,89,106);		    
	    	break;
	    case 5:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(3304,2117,130,106);	
		    _hitbox.setSize(sf::Vector2f(41*SCALE,27*SCALE));
		    _hitbox.setPosition(_posX+89*SCALE*_orientation,_posY+79*SCALE);	    
	    	break;
	    case 6:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(3442,2117,124,106);
	    	_hitbox.setPosition(_posX+80*SCALE*_orientation,_posY+79*SCALE); 	
	    	break;
	    case 7:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(3573,2117,112,106);	    	
			break;
		case 8:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(3695,2117,105,106);
	    	_hitbox.setSize(sf::Vector2f(0,0));
			break;
		case 9:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(682,1111,101,153);
		    _posY+=deplacement;
	    	break;
	    case 10:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(793,1111,111,153);
		    _posY+=deplacement;
	    	break;
	    case 11:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(914,1111,125,153);
		    _posY+=deplacement;
			break;
		case 12:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(1043,1111,104,153);
	    	_posX+=8*SCALE;
			break;
		case 13:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(1269,1102,91,151);    	
			break;
		case 14:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(1372,1102,90,151);
			break;
		case 15:
	    	clockAnim.restart();
	    	_cptSauter++;
	    	setSprite(1476,1102,71,152);  	
			break;
		case 16:
	    	clockAnim.restart();
	    	_cptSauter=0;
	    	setSprite(4,6,64,117);
	    	fini=true;  	
	    	_posX+=8*SCALE;
			break;
	    }
	}

	if(collisioncoup(hurtboxEnnemi))
	{
		prendCoup=true;
		ennemi.setDegats(15);
	}

    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y));
    _hurtbox.setPosition(_posX,_posY);
    setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}


bool Jotaro::SP(sf::Clock& clockAnim,sf::Sprite& starPlat,sf::RectangleShape hurtboxEnnemi,bool& prendCoup, Player& ennemi)
{
	if(!_SPChargee)
	{
		ajouterTexture(671,3724,100,135);ajouterTexture(875,3724,142,135);ajouterTexture(1025,3724,185,135);ajouterTexture(1219,3724,169,135);
		ajouterTexture(1395,3724,184,135);ajouterTexture(1586,3724,176,135);ajouterTexture(1768,3724,158,135);ajouterTexture(1933,3724,150,135);
		ajouterTexture(2091,3724,165,135);ajouterTexture(2264,3724,164,135);ajouterTexture(2436,3724,163,135);ajouterTexture(2607,3724,151,135);
		ajouterTexture(2765,3724,195,135);ajouterTexture(2968,3724,187,135);ajouterTexture(3162,3724,168,135);ajouterTexture(3339,3724,140,135);
		ajouterTexture(3485,3724,138,135);ajouterTexture(3630,3724,179,135);ajouterTexture(3816,3724,170,135);ajouterTexture(3995,3724,166,135);
		ajouterTexture(4170,3724,175,135);ajouterTexture(4354,3724,174,135);ajouterTexture(4536,3724,171,135);ajouterTexture(4714,3724,155,135);
		_SPChargee=true;
	}
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    bool fini=false;
	
	if(timeAnim>delai && _cptAction<6)
	{
	    switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(21,3742,75,116);
		    starPlat.setTexture(_texture);
			break;
		case 1:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(106,3742,100,116);
			break;
		case 2:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(216,3742,113,116);
			break;
		case 3:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(338,3742,113,116);
			break;
		case 4:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(459,3742,108,116);

			starPlat.setTextureRect(sf::IntRect(_tabSP[_cptAction-4][0],_tabSP[_cptAction-4][1],_tabSP[_cptAction-4][2],_tabSP[_cptAction-4][3]));
			starPlat.setScale(_orientation*SCALE,SCALE);
			starPlat.setPosition(_posX+(_tailleSprite.x/2*_orientation),_scene.getBottom()-_tabSP[_cptAction-4][3]*SCALE);
			break;
		case 5:
		    _cptAction ++;
		    clockAnim.restart();
			starPlat.setTextureRect(sf::IntRect(_tabSP[_cptAction-4][0],_tabSP[_cptAction-4][1],_tabSP[_cptAction-4][2],_tabSP[_cptAction-4][3]));
			_hitbox.setSize(sf::Vector2f(110*SCALE,77*SCALE));
			_hitbox.setPosition(starPlat.getPosition().x+65*SCALE*_orientation,starPlat.getPosition().y+18*SCALE);
			break;
		}
	}

	if(timeAnim>delai/3 && _cptAction>5)
	{
		if(_cptAction==8)
		{
			_cptSP++;
		}
		clockAnim.restart();
		_cptAction++;
		starPlat.setTextureRect(sf::IntRect(_tabSP[_cptAction-4][0],_tabSP[_cptAction-4][1],_tabSP[_cptAction-4][2],_tabSP[_cptAction-4][3]));
		if(_cptAction==27)
		{
			if(_cptSP==3)
			{
				_hitbox.setSize(sf::Vector2f(0,0));
				fini=true;
				_SPChargee=false;
				_cptAction=0;
				starPlat.setTextureRect(sf::IntRect(0,0,0,0));
				resetTexture();
				reset();
			}else
			{
				_cptAction=8;
			}
		}
	}

	if(collisioncoup(hurtboxEnnemi))
	{
		prendCoup=true;
		ennemi.setDegats(50);
	}

	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y));
    _hurtbox.setPosition(_posX,_posY);
	return fini;
}