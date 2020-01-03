#include "../IncludeManager.h"

using namespace std;

Ryu::Ryu(int orientation,const Scene& s)
{
	SCALE=4.2;
	_orientation=-orientation;
	_scene=s;
	_cptStatic=0;_cptAvancer=0;_cptReculer=0;_cptSauter=0;_cptApparition=0;_cptAction=0;_cptAccroupi=0;_cptPrendCoup=0;

	if (!_texture.loadFromFile("sprites/sprite_ryu.png"))
	{
	    std::cout<<"Erreur au chargement du sprite";
	}
	_sprite.setTexture(_texture);
	_sprite.scale(_orientation*SCALE,SCALE);

	if(_orientation==1)
		_posX=100.f;
	else
		_posX=_scene.getRightLimit()-100.f;

	_posY=_scene.getBottom()-_tailleSprite.y;
	_sprite.setPosition(_posX,_posY);
	keepInWalls();

	_hurtbox.setFillColor(sf::Color(255,255,255,0));
    _hurtbox.setOutlineColor(sf::Color::Green);
    _hurtbox.setOutlineThickness(4);

    _hitbox.setFillColor(sf::Color(255,255,255,0));
    _hitbox.setOutlineColor(sf::Color::Red);
    _hitbox.setOutlineThickness(4);

    _gardebox.setFillColor(sf::Color(255,255,255,0));
    _gardebox.setOutlineColor(sf::Color::Blue);
    _gardebox.setOutlineThickness(4);
    
    if(_orientation==-1)
    {
		_hurtbox.setScale(-1,1);
		_hitbox.setScale(-1,1);
	}
}

bool Ryu::victoire(sf::Clock& clockAnim,sf::Music& son)
{
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=120;
    bool fini=false;
    _hitbox.setSize(sf::Vector2f(0,0));

	if(timeAnim>delai)
	{
	    switch (_cptApparition)
	    {
	    case 0:	
		    _cptApparition ++;
		    clockAnim.restart();
			setSprite(5,5254,63,89);

			_hurtbox.setSize(sf::Vector2f(0,0));
	    	break;
	    case 1:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(75,5251,60,92);
	    	break;
	    case 2:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(144,5244,62,99);
	    	break;
	    case 3:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(213,5225,62,118);
	    	break;
		}

		_posY=_scene.getBottom()-_tailleSprite.y;
		_sprite.setPosition(_posX,_posY);
	}

	if(_cptApparition==4 && timeAnim>2000)
	{
		clockAnim.restart();
		_cptApparition=0;
		fini=true;
	}

	keepInWalls();
	return fini;
}

bool Ryu::mort(sf::Clock& clockAnim)
{
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=100;
    bool fini=false;
    _hitbox.setSize(sf::Vector2f(0,0));

	if(timeAnim>delai)
	{
	    switch (_cptApparition)
	    {
	    case 0:	
		    _cptApparition ++;
		    clockAnim.restart();
			setSprite(1,4763,65,87);

			_hurtbox.setSize(sf::Vector2f(0,0));
	    	break;
	    case 1:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(1,4965,80,77);
	    	break;
	    case 2:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(82,4961,105,44);
	    	break;
	    case 3:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(188,4975,73,65);
	    	break;
	    case 4:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(278,4980,120,46);
	    	break;
	    case 5:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(399,5024,125,41);
	    	break;
	    case 6:
		    _cptApparition++;
		    clockAnim.restart();
		    setSprite(526,5004,124,53);
		    break;
		case 7:
		    _cptApparition++;
		    clockAnim.restart();
		    setSprite(651,5025,123,41);
		    break;
		case 8:
		    _cptApparition++;
		    clockAnim.restart();
		    setSprite(775,5024,133,34);
		    break;
		}

		_posY=_scene.getBottom()-_tailleSprite.y;
		_sprite.setPosition(_posX,_posY);
	}

	if(_cptApparition==9 && timeAnim>2000)
	{
		clockAnim.restart();
		_cptApparition=0;
		fini=true;
	}

	keepInWalls();
	return fini;
}


bool Ryu::parade(sf::Clock& clockAnim,int* degats,sf::Sprite& effet)
{
	bool fini=false;
	_cptSauter=0;_cptAction=0;
	effet.setTextureRect(sf::IntRect(0,0,0,0));
	_hurtbox.setSize(sf::Vector2f(0,0));

	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=120;

    if(_cptPrendCoup==0)
    {
    	setSprite(70,4659,68,91);
    	_cptPrendCoup++;
    	_posX-=25*SCALE*_orientation;
    }else if(timeAnim > delai)
    {
		if(_cptPrendCoup==1)
		{
			clockAnim.restart();
			_cptPrendCoup++;
    		_posX-=25*SCALE*_orientation;
		}else{
			clockAnim.restart();
			_cptPrendCoup=0;
			fini=true;
			*degats=0;
		}
    }

    _sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}


bool Ryu::prendCoup(sf::Clock& clockAnim,int* degats,sf::Sprite& effet)
{
	*degats=-1;
	bool fini=false;
	_cptSauter=0;_cptAction=0;
	effet.setTextureRect(sf::IntRect(0,0,0,0));
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    _hurtbox.setSize(sf::Vector2f(0,0));
    if(timeAnim > delai)
    {
    	switch(_cptPrendCoup)
    	{
    	case 0:
    		clockAnim.restart();
    		_cptPrendCoup++;
    		setSprite(1,4859,69,92);
    		_posX-=1*SCALE*_orientation;
    		_posY+=6*SCALE;
    		break;
    	case 1:
    		clockAnim.restart();
    		_cptPrendCoup++;
    		setSprite(1,4859,69,92);
    		_posX+=1*SCALE*_orientation;
    		break;
    	case 2:
    		clockAnim.restart();
    		_cptPrendCoup++;
    		setSprite(71,4857,70,94);
    		_posX-=16*SCALE*_orientation;
    		break;
    	case 3:
    		clockAnim.restart();
    		_cptPrendCoup++;
    		setSprite(142,4858,74,93);
    		_posX-=16*SCALE*_orientation;
    		break;
    	case 4:
    		clockAnim.restart();
    		_cptPrendCoup=0;
    		setSprite(220,4857,70,94);
    		_posX-=16*SCALE*_orientation;
    		fini=true;
    		*degats=0;
    		break;
    	}
    }
    _sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}


bool Ryu::apparition(sf::Clock& clockAnim,sf::Sprite& inutile)
{
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    bool fini=false;
    int delai=200;
    
   	if(_cptApparition==0)
   	{
		setSprite(9,225,61,104);
		_cptApparition ++;
   	}else if(timeAnim>delai)
   	{
	   	switch(_cptApparition)
		{
		case 1:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(80,225,61,104);
			break;
		case 2:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(152,225,67,104);
			break;
		case 3:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(227,225,70,104);
			break;
		case 4:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(306,225,64,104);
			break;
		case 5:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(379,225,61,104);
			break;
		case 6:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(449,225,61,104);
			break;
		case 7:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(519,225,61,104);
			break;
		case 8:
		    _cptApparition ++;
		    clockAnim.restart();
		    setSprite(589,225,61,104);
			break;
		case 9:
		    _cptApparition=0;
		    clockAnim.restart();
		    setSprite(654,225,68,104);
			fini=true;
			break;
		}
	}
	keepInWalls();
	return fini;
}

void Ryu::statique(sf::Clock& clockAnim,Personnage& champEnnemi)
{
    sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    if(timeAnim>delai)
    {
	    switch (_cptStatic)
	    {
	    case 0:
		    _cptStatic ++;
		    clockAnim.restart();
    		setSprite(2,433,66,98);
    		_posY=_scene.getBottom()-_tailleSprite.y;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 1:
		    _cptStatic ++;
		    clockAnim.restart();
		    setSprite(71,433,66,98);
	    	break;
	    case 2:
		    _cptStatic ++;
		    clockAnim.restart();
		    setSprite(140,433,66,98);
	    	break;
	    case 3:
		    _cptStatic ++;
		    clockAnim.restart();
		    setSprite(209,433,66,98);
	    	break;
	    case 4:
		    _cptStatic ++;
		    clockAnim.restart();
		    setSprite(279,433,64,98);
	    	break;
	    case 5:
		    _cptStatic=0;
		    clockAnim.restart();
		    setSprite(347,433,66,98);
	    	break;
	    }
	}

	_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
   	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
	
	int n=0;
	collision(champEnnemi,n);
    rotate(champEnnemi);
    keepInWalls();
}


void Ryu::garde(sf::Clock& clockAnim)
{
	_cptStatic=0;
	_posY=_scene.getBottom()-_tailleSprite.y;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    if(timeAnim>delai)
    {
    	clockAnim.restart();
    	setSprite(3,4658,65,92);
    	_gardebox.setSize(sf::Vector2f(_tailleSprite.x*0.2,_tailleSprite.y));
    	_gardebox.setPosition(_posX+_tailleSprite.x*0.8*_orientation,_posY);
    }
    _posY=_scene.getBottom()-_tailleSprite.y;
    _sprite.setPosition(_posX,_posY);
    keepInWalls();
}

bool Ryu::finGarde(sf::Clock& clockAnim)
{
	bool fini=false;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    setSprite(5,538,63,89);
    _gardebox.setSize(sf::Vector2f(0,0));
    if(timeAnim>delai*3)
    	fini=true;
    keepInWalls();
    return fini;
}

void Ryu::avancer(sf::Clock& clockAnim,Personnage& champEnnemi)
{
	_posY=_scene.getBottom()-_tailleSprite.y;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    int deplacement=60;

    collision(champEnnemi,deplacement);
	
	if(deplacement==0)
    {
    	statique(clockAnim,champEnnemi);
    }else if(timeAnim>delai)
	{
	    switch (_cptAvancer)
	    {
	    case 0:
	    	_cptStatic=0;
		    _cptAvancer ++;
		    clockAnim.restart();
    		setSprite(5,634,63,96);
    		_posX+=_orientation*deplacement;
	    	break;
	    case 1:
		    _cptAvancer ++;
		    clockAnim.restart();
		    setSprite(70,634,69,96);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 2:
		    _cptAvancer ++;
		    clockAnim.restart();
		    setSprite(144,634,68,96);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 3:
		    _cptAvancer ++;
		    clockAnim.restart();
		    setSprite(222,634,59,96);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 4:
		    _cptAvancer ++;
		    clockAnim.restart();
		    setSprite(296,634,54,96);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 5:
		    _cptAvancer =0;
		    clockAnim.restart();
		    setSprite(428,634,63,96);
		    _posX+=_orientation*deplacement;
	    	break;
	    }
	}
	
	_sprite.setPosition(_posX,_posY);
    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
    rotate(champEnnemi);
    
	keepInWalls();
}


void Ryu::reculer(sf::Clock& clockAnim)
{
	_posY=_scene.getBottom()-_tailleSprite.y;
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    int deplacement=45;
    
    if(timeAnim > delai)
    {
	    switch (_cptReculer)
	    {
	    case 0:
			_sprite.setPosition(_posX,_posY);
		    _cptReculer ++;
		    clockAnim.restart();
    		setSprite(5,634,63,96);
    		_posX-=_orientation*deplacement;
	    	break;
	    case 1:
		    _cptReculer ++;
		    clockAnim.restart();
		    setSprite(497,634,61,96);
		    _posX-=_orientation*deplacement;
	    	break;
	    case 2:
		    _cptReculer ++;
		    clockAnim.restart();
		    setSprite(565,634,54,96);
		    _posX-=_orientation*deplacement;
	    	break;
	    case 3:
		    _cptReculer ++;
		    clockAnim.restart();
			setSprite(633,634,54,96);
			_posX-=_orientation*deplacement;
	    	break;
	    case 4:
		    _cptReculer=0;
		    clockAnim.restart();
			setSprite(428,634,63,96);
			_posX-=_orientation*deplacement;
	    	break;
	    }
	}
	_sprite.setPosition(_posX,_posY);
    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
	keepInWalls();
}


bool Ryu::sauter(sf::Clock& clockAnim,int& lancerAttaque,Personnage& champEnnemi,int* degats)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacement=_scene.getBottom()/6;
    bool fini=false;

    if(lancerAttaque!=-1)
    {
    	bool enAttaque=false;
		int directionEnCours=0;
    	
    	if(_cptSauter<1)
    	{
			directionEnCours=1;
		}
		else if(_cptSauter<4)
			directionEnCours=2;
		else
			directionEnCours=3;

		if(lancerAttaque==1)
			enAttaque=sautPunch(clockAnim,champEnnemi,degats,directionEnCours);
    	else if(lancerAttaque==2) 		
    		enAttaque=sautKick(clockAnim,champEnnemi,degats,directionEnCours);

    	if(_cptSauter>4)
    	{
    		fini=enAttaque;
    	}else
    	{
    		fini=false;
    		if(enAttaque)
    			lancerAttaque=-1;
    	}
    	
    	if(enAttaque || lancerAttaque==-1)
    	{
    		_cptSauter=5;
    		if(_cptSauter>7)
    			_cptSauter=7;
    	}

    	if(fini)
    		_cptSauter=0;

    }else
    {
	    if(_cptSauter==0)
	    {
		    _cptSauter++;
		    setSprite(1207,829,63,89);
		    _posY=_scene.getBottom()-_tailleSprite.y;
	    }else if(timeAnim>delai)
	    {
		    collisionsaut(champEnnemi,deplacement);
		    switch(_cptSauter)
		    {
		    case 1:
			    clockAnim.restart();
			    _cptSauter++;
			    _posY-=deplacement;
			    setSprite(722,818,62,108);
		    	break;
		    case 2:
			    clockAnim.restart();
			    _cptSauter++;
			    setSprite(791,775,64,88);
			    _posY-=deplacement;
		    	break;
		    case 3:
			    clockAnim.restart();
			    _cptSauter++;
			    setSprite(861,748,61,70);
			    _posY-=deplacement;
		    	break;
		    case 4:
			    clockAnim.restart();
			    _cptSauter++;
			    setSprite(861,748,61,70);
		    	break;
		    case 5:
			    clockAnim.restart();
			    _cptSauter++;
			    setSprite(1000,750,64,86);
			    _posY+=deplacement;
		    	break;
		    case 6:
			    clockAnim.restart();
			    _cptSauter++;
			    setSprite(1071,765,62,116);
			    _posY+=deplacement;
		    	break;
		    case 7:
			    clockAnim.restart();
			    _cptSauter=0;
			    setSprite(1207,829,63,89);
			    _posY+=deplacement;
			    _posY=_scene.getBottom()-_tailleSprite.y;
			    fini=true;
		    	break;
		    }
		}
	}
	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
	_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);	

	_sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}


bool Ryu::sauterAvant(sf::Clock& clockAnim,Personnage& champEnnemi)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacementY=_scene.getBottom()/6,deplacementX=50*_orientation;
    bool fini=false;

    
    
    if(timeAnim > delai)
    {
	    collisionsaut(champEnnemi,deplacementX);
	    switch(_cptSauter)
	    {
	    case 0:
		    clockAnim.restart();
		    _cptSauter++;
			setSprite(1207,829,63,89);
			_posY=_scene.getBottom()-_tailleSprite.y;

			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
	    	break;
	    case 1:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(1278,818,62,108);
    		_posX+=deplacementX;_posY-=deplacementY;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
	    	break;
	    case 2:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(1348,794,61,106);
    		_posX+=deplacementX*2;_posY-=deplacementY;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.4);
	    	break;
	    case 3:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(1410,760,93,46);
    		_posX+=deplacementX;_posY-=deplacementY;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.4);
	    	break;
	    case 4:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(1510,737,55,77);
    		_posX+=deplacementX*4;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.4);
	    	break;
	    case 5:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(1573,768,115,52);
    		_posX+=deplacementX*2;_posY+=deplacementY;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.4);
	    	break;
	    case 6:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(1689,747,70,94);
    		_posX+=deplacementX*3;_posY+=deplacementY;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.4);
	    	break;
	    case 7:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(1071,765,62,116);
    		_posX+=deplacementX;_posY+=deplacementY;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);	
	    	break;
	    case 8:
		    clockAnim.restart();
		    _cptSauter++;
			setSprite(1207,829,63,89);
			_posY=_scene.getBottom()-_tailleSprite.y;

			_cptSauter=0;
			fini=true;
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
			rotate(champEnnemi);
	    	break;
	    }
	}

	_sprite.setPosition(_posX,_posY);

    keepInWalls();
    return fini;
}

bool Ryu::sauterArriere(sf::Clock& clockAnim,Personnage& champEnnemi)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacementY=150,deplacementX=40*_orientation;
    bool fini=false;

    
    if(timeAnim > delai)
    {
	    collisionsaut(champEnnemi,deplacementX);
	    switch(_cptSauter)
	    {
	    case 0:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(1207,829,63,89);
    		_posY=_scene.getBottom()-_tailleSprite.y;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y));
    		_hurtbox.setPosition(_posX,_posY);
	    	break;
	    case 1:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(7,775,64,88);
    		_posX-=deplacementX;_posY-=deplacementY;

		    _hurtbox.setPosition(_posX,_posY);
	    	break;
	    case 2:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(72,747,70,94);
    		_posX-=deplacementX*2;_posY-=deplacementY;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.4);
	    	break;
	    case 3:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(161,768,115,52);
    		_posX-=deplacementX;_posY-=deplacementY;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.4);
	    	break;
	    case 4:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(282,737,55,77);
    		_posX-=deplacementX;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.4);
	    	break;
	    case 5:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(346,760,93,46);
    		_posX-=deplacementX*4;_posY+=deplacementY;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.4);
	    	break;
	    case 6:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(447,794,61,106);
    		_posX-=deplacementX*2;_posY+=deplacementY;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.4);
	    	break;
	    case 7:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(515,806,62,116);
    		_posX-=deplacementX;_posY+=deplacementY;
		    
		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y));
		    _hurtbox.setPosition(_posX,_posY);
	    	break;
	    case 8:
		    clockAnim.restart();
		    _cptSauter++;
			setSprite(582,829,63,89);
			_posY=_scene.getBottom()-_tailleSprite.y;
			_cptSauter=0;
			fini=true;
			_hurtbox.setPosition(_posX,_posY);
	    	break;
	    }
	}
	_sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}

void Ryu::accroupi(sf::Clock& clockAnim,bool garde)
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
    		setSprite(73,555,62,72);
			
			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y));
			_hurtbox.setPosition(_posX,_posY);
    	}
    }else
    {
    	if(timeAnim>delai)
    	{
    		clockAnim.restart();
    		if(garde==true)
	    		setSprite(212,4685,64,65);
	    	else
    		{
    			setSprite(142,562,62,65);
    			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.9));
    			_hurtbox.setPosition(_posX+_tailleSprite.x*0.1,_posY+_tailleSprite.y*0.1);
    		}
    	}
    }
    _posY=_scene.getBottom()-_tailleSprite.y;
    _sprite.setPosition(_posX,_posY);
}


bool Ryu::punch(sf::Clock& clockAnim,Personnage& champEnnemi,int* degats)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    bool fini=false;
	
    if(timeAnim > delai)
    {
		switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(3,1319,74,94);

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);	
			break;
		case 1:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(80,1318,102,95);
		    _hitbox.setSize(sf::Vector2f(40*SCALE,20*SCALE));
		    _hitbox.setPosition(_posX+60*SCALE*_orientation,_posY+10*SCALE);
			break;
		case 2:
		    _cptAction++;
		    clockAnim.restart();
		    setSprite(185,1319,74,94);

		    _hitbox.setSize(sf::Vector2f(0,0));
			break;
		case 3:
			_cptAction=0;
			clockAnim.restart();
			setSprite(2,433,66,98);
			fini=true;
			break;
		}
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=10;
		cout<<"je l'ai touché: "<<*degats<<endl;
	}
	_posY=_scene.getBottom()-_tailleSprite.y;
    _sprite.setPosition(_posX,_posY);
	keepInWalls();
	return fini;
}

bool Ryu::sautPunch(sf::Clock& clockAnim,Personnage& champEnnemi,int* degats,int directionY)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacement=125;
    bool fini=false;
    
    if(timeAnim>delai)
    {
	    switch(_cptAction)
	    {
	    case 0:
	    	_cptAction ++;
		    clockAnim.restart();
		    setSprite(150,1794,55,73);

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
			break;
		case 1:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(206,1794,74,79);

		    _hitbox.setSize(sf::Vector2f(80*SCALE,22*SCALE));
		    _hitbox.setPosition(_posX+36*SCALE*_orientation,_posY);
			break;
		case 2:
			_cptAction =0;
			clockAnim.restart();
			setSprite(281,1794,98,72);
			fini=true;

			_hitbox.setSize(sf::Vector2f(0,0));
			break;
	    }

	    switch(directionY)
	    {
	    case 1:
	    	_posY-=deplacement;	    	
	    	break;
	    case 2:
	    	if(_cptAction==1)
	    		_posY-=deplacement;
	    	break;
	    case 3:
	    	if(_cptAction>0)
	    		_posY+=deplacement;
	    	break;
	    }

	    _sprite.setPosition(_posX,_posY);
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=10;
	}

    keepInWalls();
    return fini;
}


bool Ryu::kick(sf::Clock& clockAnim,Personnage& champEnnemi,int* degats)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=90;
    bool fini=false;

    if(timeAnim > delai)
    {
		switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(497,2559,67,94);

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);	
			break;
		case 1:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(566,2559,65,94);
			break;
		case 2:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(656,2563,118,90);

    		_hitbox.setSize(sf::Vector2f(80*SCALE,22*SCALE));
		    _hitbox.setPosition(_posX+36*SCALE*_orientation,_posY);
			break;
		case 3:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(775,2559,65,94);

		    _hitbox.setSize(sf::Vector2f(0,0));
			break;
		case 4:
		    _cptAction =0;
		    clockAnim.restart();
		    setSprite(867,2559,65,94);
		    fini=true;
			break;
		}
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=10;
	}
	_posY=_scene.getBottom()-_tailleSprite.y;
    _sprite.setPosition(_posX,_posY);
	keepInWalls();
	return fini;	
}

bool Ryu::sautKick(sf::Clock& clockAnim,Personnage& champEnnemi,int* degats,int directionY)
{
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=100,deplacement=_scene.getBottom()/6;
    bool fini=false;
    
	if(timeAnim>delai)
    {
	    switch(_cptAction)
	    {
	    case 0:
	    	_cptAction ++;
		    clockAnim.restart();
		    setSprite(228,3022,58,117);

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
			break;
	    case 1:
	    	_cptAction ++;
		    clockAnim.restart();
		    setSprite(298,3013,59,98);
			break;
		case 2:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(367,3020,92,107);

		    _hitbox.setSize(sf::Vector2f(80*SCALE,22*SCALE));
		    _hitbox.setPosition(_posX+36*SCALE*_orientation,_posY);
			break;
		case 3:
			_cptAction =0;
			clockAnim.restart();
			setSprite(472,3036,61,102);
			fini=true;

			_hitbox.setSize(sf::Vector2f(0,0));
			break;
	    }

	    if(_cptAction!=0)
	    {
		    switch(directionY)
		    {
		    case 1:
		    	_posY-=deplacement;	    	
		    	break;
		    case 2:
		    	if(_cptAction==1)
		    		_posY-=deplacement;
		    	break;
		    case 3:
		    	if(_cptAction>0)
		    		_posY+=deplacement;
		    	break;
		    }
		}    

	    _sprite.setPosition(_posX,_posY);
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=10;
	}
	
    keepInWalls();
    return fini;
}



bool Ryu::SP(sf::Clock& clockAnim,sf::Sprite& bouleFeu,Personnage& champEnnemi,int* degats,sf::Music& son)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    bool fini=false;

    if(timeAnim > delai)
    {
	    switch (_cptAction)
		{
		case 0:
			if (!son.openFromFile("musique/hadouken.ogg"))
		        std::cout<<"erreur musique";
		    son.play();

		    _cptAction++;
		    clockAnim.restart();
		    setSprite(10,3493,74,90);

		    bouleFeu.setPosition(10,10);
		    bouleFeu.setTexture(_texture);
			bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
			break;
		case 1:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(890,3520,91,90);
		    _posX-=1*SCALE*_orientation;
			break;
		case 2:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(986,3520,111,90);
		    _posX-=20*SCALE*_orientation;
			break;
		case 3:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(742,3630,115,90);
		    _posX-=4*SCALE*_orientation;
		    break;
		case 4:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(993,3630,117,90);
		    _posX-=2*SCALE*_orientation;
		    break;
		case 5:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(1124,3636,98,85);
		    _posX+=20*SCALE*_orientation;
		    break;
		case 6:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(1229,3635,119,86);
		    _posX+=2*SCALE*_orientation;

			bouleFeu.setTextureRect(sf::IntRect(1130,5745,240,171));
			bouleFeu.setScale(_orientation,1);
			bouleFeu.setPosition(_posX+(_tailleSprite.x*0.7*_orientation),_posY);
			break;
		}
	}

	if(_cptAction>6 && _cptAction<11)
	{
		setSprite(400,3605,119,79);
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(1426,5744,231,181));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY);
	}else if(_cptAction>10 && _cptAction<15)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(1713,5742,234,176));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY);
	}else if(_cptAction>14 && _cptAction<19)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(2003,5738,234,178));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY);
	}else if(_cptAction>18 && _cptAction<23)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(1130,5745,240,171));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY);
		if(_cptAction==23)
			_cptAction=7;
	}


	if( (_orientation==1 && bouleFeu.getPosition().x>=_scene.getRightLimit()) || (_orientation==-1 && bouleFeu.getPosition().x<=_scene.getLeftLimit()) )
	{
		bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
		fini=true;
		_cptAction=0;
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=30;
		bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
		fini=true;
		_cptAction=0;
	}

	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
	_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);	

    _hitbox.setSize(sf::Vector2f(bouleFeu.getGlobalBounds().width,bouleFeu.getGlobalBounds().height));
	_hitbox.setPosition(bouleFeu.getPosition().x,bouleFeu.getPosition().y);

	
	_posY=_scene.getBottom()-_tailleSprite.y;
    _sprite.setPosition(_posX,_posY);
	keepInWalls();
	return fini;
}