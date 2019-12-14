#include "../IncludeManager.h"

using namespace std;

Ryu::Ryu(int orientation,const Scene& s)
{
	SCALE=4.2;
	_orientation=-orientation;
	_scene=s;
	_cptStatic=0;_cptAvancer=0;_cptReculer=0;_cptSauter=0;_cptApparition=0;_cptAction=0;_cptAccroupi=0;

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
    
    if(_orientation==-1)
    {
		_hurtbox.setScale(-1,1);
		_hitbox.setScale(-1,1);
	}
}


bool Ryu::prendCoup(sf::Clock& clockAnim,bool& enCours,sf::Sprite& effet)
{
	bool fini=false;
	_cptSauter=0;
	_cptStatic=0;
	effet.setTextureRect(sf::IntRect(0,0,0,0));
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
    		setSprite(1,4859,69,92);
    		_posX-=10*SCALE*_orientation;
    		_posY+=6*SCALE;
    		break;
    	case 1:
    		clockAnim.restart();
    		_cptAction++;
    		setSprite(71,4857,70,94);
    		_posX-=10*SCALE*_orientation;
    		break;
    	case 2:
    		clockAnim.restart();
    		_cptAction++;
    		setSprite(142,4858,74,93);
    		_posX-=10*SCALE*_orientation;
    		break;
    	case 3:
    		clockAnim.restart();
    		_cptAction=0;
    		setSprite(220,4857,70,94);
    		fini=true;
    		enCours=false;
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

void Ryu::statique(sf::Clock& clockAnim,Personnage& ennemi)
{
    sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=150;
    
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

    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.1);
    _hurtbox.setSize(sf::Vector2f(60*SCALE,_tailleSprite.y*0.9));
    rotate(ennemi);
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
    	_posY+=6*SCALE;
    	_sprite.setPosition(_posX,_posY);
    }
    _hurtbox.setSize(sf::Vector2f(0,0));
    keepInWalls();
}

bool Ryu::finGarde(sf::Clock& clockAnim)
{
	bool fini=false;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    setSprite(5,538,63,89);
    if(timeAnim>delai*3)
    	fini=true;
    return fini;
}

void Ryu::avancer(sf::Clock& clockAnim,Personnage& ennemi)
{
	_cptStatic=0;
	_posY=_scene.getBottom()-_tailleSprite.y;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    int deplacement=55;
	
	if(timeAnim>delai)
	{
	    switch (_cptAvancer)
	    {
	    case 0:
			_sprite.setPosition(_posX,_posY);
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
    _hurtbox.setPosition(_posX,_posY);
    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.7,_tailleSprite.y));
    rotate(ennemi);
	keepInWalls();
}


void Ryu::reculer(sf::Clock& clockAnim)
{
	_posY=_scene.getBottom()-_tailleSprite.y;
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    int deplacement=50;
    
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
    _hurtbox.setPosition(_posX,_posY);
    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.7,_tailleSprite.y));
	keepInWalls();
}

bool Ryu::sauter(sf::Clock& clockAnim,sf::Clock& clockAttente)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacement=125;
    bool fini=false;

    if(_cptSauter==0)
    {
    	clockAttente.restart();
	    _cptSauter++;
	    setSprite(1207,829,63,89);

	    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y));
	    _hurtbox.setPosition(_posX,_posY);
    }else if(timeAnim>delai)
    {
	    switch(_cptSauter)
	    {
	    case 1:
		    clockAnim.restart();
		    _cptSauter++;
		    _posY-=deplacement;
		    setSprite(722,818,62,108);

		    _hurtbox.setPosition(_posX,_posY);
	    	break;
	    case 2:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(791,775,64,88);
		    _posY-=deplacement;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.8));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	break;
	    case 3:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(861,748,61,70);
		    _posY-=deplacement;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.7));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.3);
	    	break;
	    case 4:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(925,739,61,65);

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.4);
	    	break;
	    case 5:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(1000,750,64,86);
		    _posY+=deplacement;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.7));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.3);
	    	break;
	    case 6:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(1071,765,62,116);
		    _posY+=deplacement;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.8));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	break;
	    case 7:
		    clockAnim.restart();
		    _cptSauter=0;
		    setSprite(1207,829,63,89);
		    _posY+=deplacement;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.9));
		    _hurtbox.setPosition(_posX,_posY);
		    fini=true;
	    	break;
	    }
	}
	_sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}


bool Ryu::sauterAvant(sf::Clock& clockAnim,Personnage& ennemi)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacementY=150,deplacementX=30*_orientation;
    bool fini=false;
    
    if(timeAnim > delai)
    {
	    switch(_cptSauter)
	    {
	    case 0:
		    clockAnim.restart();
		    _cptSauter++;
			setSprite(1207,829,63,89);

			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y));
			_hurtbox.setPosition(_posX,_posY);
	    	break;
	    case 1:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(1278,818,62,108);
    		_posX+=deplacementX;_posY-=deplacementY;

		    _hurtbox.setPosition(_posX,_posY);
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
    		_posX+=deplacementX;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.4);
	    	break;
	    case 5:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(1573,768,115,52);
    		_posX+=deplacementX*4;_posY+=deplacementY;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.4);
	    	break;
	    case 6:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(1689,747,70,94);
    		_posX+=deplacementX*2;_posY+=deplacementY;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.4);
	    	break;
	    case 7:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(1071,765,62,116);
    		_posX+=deplacementX;_posY+=deplacementY;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y));
		    _hurtbox.setPosition(_posX,_posY);
	    	break;
	    case 8:
		    clockAnim.restart();
		    _cptSauter++;
			setSprite(1207,829,63,89);
			_cptSauter=0;
			fini=true;
			_hurtbox.setPosition(_posX,_posY);
	    	break;
	    }
	}
	_sprite.setPosition(_posX,_posY);
    rotate(ennemi);
    keepInWalls();
    return fini;
}

bool Ryu::sauterArriere(sf::Clock& clockAnim)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacementY=150,deplacementX=30*_orientation;
    bool fini=false;
    
    if(timeAnim > delai)
    {
	    switch(_cptSauter)
	    {
	    case 0:
		    clockAnim.restart();
		    _cptSauter++;
    		setSprite(1207,829,63,89);

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
    		_posY=_scene.getBottom()-_tailleSprite.y;
			_sprite.setPosition(_posX,_posY);
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
    			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.7));
    			_hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.3);
    		}
    	}
    }
}


bool Ryu::punch(sf::Clock& clockAnim,sf::RectangleShape hurtboxEnnemi,bool& prendCoup, Player& ennemi)
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
		    setSprite(3,1319,74,94);
		    _posY+=4*SCALE;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y));
		    _hurtbox.setPosition(_posX,_posY);
			break;
		case 1:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(80,1318,102,95);
		    _hitbox.setSize(sf::Vector2f(16*SCALE,39*SCALE));
		    _hitbox.setPosition(_posX+58*SCALE*_orientation,_posY+SCALE);
			break;
		case 2:
		    _cptAction++;
		    clockAnim.restart();
		    setSprite(185,1319,74,94);
		    _posY+=1*SCALE;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
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

	if(collisioncoup(hurtboxEnnemi))
	{
		prendCoup=true;
		ennemi.setDegats(10);
	}
	_sprite.setPosition(_posX,_posY);
	keepInWalls();
	return fini;
}

bool Ryu::sautPunch(sf::Clock& clockAnim,sf::RectangleShape hurtboxEnnemi,bool& prendCoup, Player& ennemi)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacement=125;
    bool fini=false;
    
    if(_cptSauter==0)
    {
	    _cptSauter++;
	    setSprite(1207,829,63,89);

	    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y));
	    _hurtbox.setPosition(_posX,_posY);
    }else if(timeAnim>delai)
    {
	    switch(_cptSauter)
	    {
	    case 1:
		    clockAnim.restart();
		    _cptSauter++;
		    _posY-=deplacement;
		    setSprite(722,818,62,108);

		    _hurtbox.setPosition(_posX,_posY);
	    	break;
	    case 2:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(791,775,64,88);
		    _posY-=deplacement;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.8));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	break;
	    case 3:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(153,1893,55,73);
		    _posY-=deplacement;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.7));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.3);
	    	break;
	    case 4:
	    	if(timeAnim>delai*3)
	    	{
	    		clockAnim.restart();
	    		_cptSauter++;

	    		setSprite(284,1893,99,72);
	    		_hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	}
	    	break;
	    case 5:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(1000,750,64,86);
		    _posY+=deplacement;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.7));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.3);
	    	break;
	    case 6:
		    clockAnim.restart();
		    _cptSauter++;
		    setSprite(1071,765,62,116);
		    _posY+=deplacement;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.8));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	break;
	    case 7:
		    clockAnim.restart();
		    _cptSauter=0;
		    setSprite(1207,829,63,89);
		    _posY+=deplacement;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.9));
		    _hurtbox.setPosition(_posX,_posY);
		    fini=true;
	    	break;
	    }
	}

	if(collisioncoup(hurtboxEnnemi))
	{
		prendCoup=true;
		ennemi.setDegats(10);
	}

	_sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}


bool Ryu::kick(sf::Clock& clockAnim,sf::RectangleShape hurtboxEnnemi,bool& prendCoup, Player& ennemi)
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
		    _posY+=4*SCALE;

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.95,_tailleSprite.y*0.9));
    		_hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.1);
			break;
		case 1:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(566,2559,65,94);
		    
			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.95,_tailleSprite.y));
    		_hurtbox.setPosition(_posX,_posY);
			break;
		case 2:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(656,2563,118,90);
		    _posY+=4*SCALE;
		    
			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.4,_tailleSprite.y*0.9));
    		_hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.1);
    		_hitbox.setSize(sf::Vector2f(39*SCALE,22*SCALE));
		    _hitbox.setPosition(_posX+87*SCALE*_orientation,_posY+51*SCALE);
			break;
		case 3:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(775,2559,65,94);

		    _hitbox.setSize(sf::Vector2f(0,0));
		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.95,_tailleSprite.y));
    		_hurtbox.setPosition(_posX,_posY);
			break;
		case 4:
		    _cptAction =0;
		    clockAnim.restart();
		    setSprite(867,2559,65,94);
		    fini=true;
			break;
		}
	}

	if(collisioncoup(hurtboxEnnemi))
	{
		prendCoup=true;
		ennemi.setDegats(10);
	}
	_sprite.setPosition(_posX,_posY);
	keepInWalls();
	return fini;	
}

bool Ryu::sautKick(sf::Clock& clockAnim,sf::RectangleShape hurtboxEnnemi,bool& prendCoup, Player& ennemi)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacement=125;
    bool fini=false;
    
    if(_cptSauter==0)
    {
	    _cptSauter++;
	    setSprite(1207,829,63,89);

	    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y));
	    _hurtbox.setPosition(_posX,_posY);
    }else if(timeAnim>delai)
    {
	    switch(_cptSauter)
	    {
	    case 1:
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(1,3039,71,110);
    		_posX+=2*_orientation;
    		_posY-=deplacement;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.9));
    		_hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.1);
	    	break;
	    case 2:
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(75,3036,61,87);
    		_posX+=8*_orientation;
    		_posY-=deplacement;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.9));
    		_hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.1);
	    	break;
	    case 3:
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(148,3025,54,68);
    		_posX-=8*_orientation;
    		_posY-=deplacement;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.9));
    		_hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.1);
    		_hitbox.setSize(sf::Vector2f(30*SCALE,17*SCALE));
		    _hitbox.setPosition(_posX+27*SCALE*_orientation,_posY+41*SCALE);
	    	break;
	    case 4:
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(228,3022,59,77);

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.3,_tailleSprite.y*0.9));
    		_hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.1);
    		_hitbox.setSize(sf::Vector2f(49*SCALE,26*SCALE));
		    _hitbox.setPosition(_posX+50*SCALE*_orientation,_posY+25*SCALE);
	    	break;
	    case 5:
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(298,3013,59,98);
    		_posY+=deplacement;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.9));
    		_hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.1);
    		_hitbox.setSize(sf::Vector2f(0,0));
	    	break;
	    case 6:
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(366,3020,93,107);
    		_posX-=35*_orientation;
    		_posY+=deplacement;
    		
    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.4,_tailleSprite.y*0.9));
    		_hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.1);
    		fini=true;
	    	break;
	    case 7:
    		clockAnim.restart();
    		_cptSauter++;
    		setSprite(472,3036,61,102);
    		_posY+=deplacement;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.4,_tailleSprite.y*0.9));
    		_hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.1);
    		fini=true;
	    	break;
	    case 8:
    		clockAnim.restart();
    		_cptSauter=0;
    		setSprite(538,3057,63,89);

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.4,_tailleSprite.y*0.9));
    		_hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.1);
    		fini=true;
	    	break;
	    }
	}

	if(collisioncoup(hurtboxEnnemi))
	{
		prendCoup=true;
		ennemi.setDegats(10);
	}
	_sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}



bool Ryu::SP(sf::Clock& clockAnim,sf::Sprite& bouleFeu,sf::RectangleShape hurtboxEnnemi,bool& prendCoup, Player& ennemi)
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
		    _cptAction=1;
		    clockAnim.restart();
		    setSprite(10,3493,74,90);
		    bouleFeu.setPosition(500,500);
		    _posY+=8*SCALE;

		    bouleFeu.setTexture(_texture);
			bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
			break;
		case 1:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(97,3498,91,85);
		    _posY+=5*SCALE;
			break;
		case 2:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(190,3503,96,80);
		    _posY+=5*SCALE;
			break;
		case 3:
		    _cptAction ++;
		    clockAnim.restart();
		    setSprite(294,3506,114,77);
		    _posY+=3*SCALE;

			bouleFeu.setTextureRect(sf::IntRect(1012,5713,286,205));
			bouleFeu.setScale(_orientation,1);
			bouleFeu.setPosition(_posX+(_tailleSprite.x*0.7*_orientation),_posY);
			break;
		}
	}

	if(_cptAction>3 && _cptAction<8)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(1365,5713,279,218));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY);
	}else if(_cptAction>7 && _cptAction<12)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(1710,5708,283,214));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY);
	}else if(_cptAction>11 && _cptAction<16)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(2057,5704,284,218));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY);
	}else if(_cptAction>15 && _cptAction<20)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(1012,5713,286,205));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY);
		if(_cptAction==20)
			_cptAction=4;
	}


	if( (_orientation==1 && bouleFeu.getPosition().x>=_scene.getRightLimit()) || (_orientation==-1 && bouleFeu.getPosition().x<=_scene.getLeftLimit()) )
	{
		bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
		fini=true;
		_cptAction=0;
	}
	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x,_tailleSprite.y));
    _hurtbox.setPosition(_posX,_posY);

    _hitbox.setSize(sf::Vector2f(bouleFeu.getGlobalBounds().width,bouleFeu.getGlobalBounds().height));
	_hitbox.setPosition(bouleFeu.getPosition().x,bouleFeu.getPosition().y);

	if(collisioncoup(hurtboxEnnemi))
	{
		prendCoup=true;
		ennemi.setDegats(30);
		bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
		fini=true;
		_cptAction=0;
	}
	_sprite.setPosition(_posX,_posY);
	keepInWalls();
	return fini;
}