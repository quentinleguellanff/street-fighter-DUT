#include "../IncludeManager.h"

using namespace std;

Dhalsim::Dhalsim(int orientation,const Scene& s)
{
	SCALE=4;
	_orientation=-orientation;
	_scene=s;
	_cptStatic=0;_cptAvancer=0;_cptReculer=0;_cptSauter=0;_cptApparition=0;_cptAction=0;_cptAccroupi=0;_cptPrendCoup=0;

	if (!_texture.loadFromFile("sprites/sprite_dhalsim.png"))
	{
	    std::cout<<"Erreur au chargement du sprite";
	}
	_sprite.setTexture(_texture);
	_sprite.scale(_orientation*SCALE,SCALE);
	setSprite(24,32,51,115);

	_icone.setTexture(_texture);
	_icone.setTextureRect(sf::IntRect(990,6490,97,104));

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


bool Dhalsim::victoire(std::vector<sf::Clock>& clockAnim,sf::Music& son)
{
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    bool fini=false;
    _hitbox.setSize(sf::Vector2f(0,0));

	if(timeAnim>delai)
	{
	    switch (_cptApparition)
	    {
	    case 0:	
		    _cptApparition ++;
		    clockAnim[0].restart();
			setSprite(24,5634,50,126);

			_hurtbox.setSize(sf::Vector2f(0,0));

			if (!son.openFromFile("musique/Dhalsim/dhalsim_victoire.ogg"))
		        std::cout<<"erreur musique";
			son.play();
	    	break;
	    case 1:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(82,5634,50,126);
	    	break;
	    case 2:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(140,5634,56,126);
	    	break;
	    case 3:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(204,5634,60,126);
	    	break;
	    case 4:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(272,5634,65,126);
	    	break;
	    case 5:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(345,5634,63,126);
	    	break;
	    case 6:
		    _cptApparition++;
		    clockAnim[0].restart();
		    setSprite(417,5634,64,126);
		    break;
		}

		_posY=_scene.getBottom()-_tailleSprite.y;
		_sprite.setPosition(_posX,_posY);
	}

	if(_cptApparition==7 && timeAnim>2000)
	{
		clockAnim[0].restart();
		_cptApparition=0;
		fini=true;
	}

	keepInWalls();
	return fini;
}

bool Dhalsim::mort(std::vector<sf::Clock>& clockAnim)
{
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=100,deplacementX=_scene.getRightLimit()/15;
    bool fini=false;
    _hitbox.setSize(sf::Vector2f(0,0));

	if(timeAnim>delai)
	{
	    switch (_cptApparition)
	    {
	    case 0:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(102,5112,90,111);
		    _hurtbox.setSize(sf::Vector2f(0,0));
		    _posX-=deplacementX*_orientation;
	    	break;
	    case 1:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(200,5112,93,111);
		    _posX-=deplacementX*_orientation;
	    	break;
	    case 2:
		    _cptApparition++;
		    clockAnim[0].restart();
		    setSprite(301,5112,130,111);
		    _posX-=deplacementX*_orientation;
	    	break;
	    case 3:
		    _cptApparition++;
		    clockAnim[0].restart();
		    setSprite(439,5112,127,111);
	    	break;
	    case 4:
		    _cptApparition++;
		    clockAnim[0].restart();
		    setSprite(300,5328,141,39);
	    	break;
	    
		}

		if(_cptApparition >=3)
			_posY=_scene.getBottom()-_tailleSprite.y;
		_sprite.setPosition(_posX,_posY);

	}

	if(_cptApparition==5 && timeAnim>2000)
	{
		clockAnim[0].restart();
		_cptApparition=0;
		fini=true;
	}


	keepInWalls();
	return fini;
}

bool Dhalsim::parade(std::vector<sf::Clock>& clockAnim,int* degats,sf::Sprite& effet)
{
	bool fini=false;
	_cptSauter=0;_cptAction=0;
	effet.setTextureRect(sf::IntRect(0,0,0,0));
	_hurtbox.setSize(sf::Vector2f(0,0));

	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=120;

    if(_cptPrendCoup==0)
    {
    	//setSprite(24,4996,85,100);
    	_cptPrendCoup++;
    	_posX-=25*SCALE*_orientation;
    }else if(timeAnim > delai)
    {
		if(_cptPrendCoup==1)
		{
			clockAnim[0].restart();
			_cptPrendCoup++;
    		_posX-=25*SCALE*_orientation;
		}else{
			clockAnim[0].restart();
			_cptPrendCoup=0;
			fini=true;
			*degats=0;
		}
    }

    _sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}

bool Dhalsim::prendCoup(std::vector<sf::Clock>& clockAnim,int* degats,sf::Sprite& effet)
{
	*degats=-1;
	bool fini=false;
	_cptSauter=0;_cptAction=0;
	effet.setTextureRect(sf::IntRect(0,0,0,0));
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    _hurtbox.setSize(sf::Vector2f(0,0));
    _gardebox.setSize(sf::Vector2f(0,0));
    
    if(timeAnim > delai)
    {
    	switch(_cptPrendCoup)
    	{
    	case 0:
    		clockAnim[0].restart();
    		_cptPrendCoup++;
    		setSprite(24,4996,85,100);
    		_posX-=10*SCALE*_orientation;
    		break;
    	case 1:
    		clockAnim[0].restart();
    		_cptPrendCoup++;
    		setSprite(117,4996,90,100);
    		_posX-=10*SCALE*_orientation;
    		break;
    	case 2:
    		clockAnim[0].restart();
    		_cptPrendCoup++;
    		setSprite(215,4996,93,100);
    		_posX-=10*SCALE*_orientation;
    		break;
    	case 3:
    		clockAnim[0].restart();
    		_cptPrendCoup++;
    		setSprite(117,4996,90,100);
    		break;
    	case 4:
    		clockAnim[0].restart();
    		_cptPrendCoup=0;
    		setSprite(24,163,96,103);
    		fini=true;
    		*degats=0;
    		break;
    	}
    }
    _posY=_scene.getBottom()-_tailleSprite.y;
    _sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}


bool Dhalsim::apparition(std::vector<sf::Clock>& clockAnim,sf::Sprite& bandeau)
{
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    bool fini=false;
    int delai=200;
    
   	if(_cptApparition==0)
   	{
   		bandeau.setTexture(_texture);
	    bandeau.setTextureRect(sf::IntRect(0,0,0,0));
	    bandeau.setScale(_orientation*SCALE,SCALE);
	    bandeau.setPosition(_posX-(_tailleSprite.x*_orientation),_posY);

		setSprite(24,32,51,115);
		_cptApparition ++;
   	}else if(timeAnim>delai)
   	{
	   	switch(_cptApparition)
		{
		case 1:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(83,32,52,115);
		    _posX-=1*SCALE*_orientation;
			_sprite.setPosition(_posX,_posY);
			break;
		case 2:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(143,32,53,115);
		    _posX-=1*SCALE*_orientation;
			_sprite.setPosition(_posX,_posY);    
			break;
		case 3:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(204,32,59,115);
		    _posX-=6*SCALE*_orientation;
			_sprite.setPosition(_posX,_posY);
		    bandeau.setTextureRect(sf::IntRect(462, 70,78,77));
			break;
		case 4:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(271,32,64,115);
		    _posX-=5*SCALE*_orientation;
			_sprite.setPosition(_posX,_posY);
			bandeau.setTextureRect(sf::IntRect(542, 70,78,77));
			break;
		case 5:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(343,32,58,115);
		    _posX+=6*SCALE*_orientation;
			_sprite.setPosition(_posX,_posY);
		    bandeau.setTextureRect(sf::IntRect(622, 70,78,77));
			break;
		case 6:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(409,32,51,115);
		    _posX+= 13*SCALE*_orientation;
			_sprite.setPosition(_posX,_posY);
			bandeau.setPosition(_posX-(_tailleSprite.x*_orientation),_posY);
			break;
		}
	}

	if(_cptApparition>=7)
	{
		_cptApparition++;
		bandeau.setPosition(_posX-((_tailleSprite.x+_cptApparition*3)*_orientation),_posY+_cptApparition);
	}
	if(_cptApparition==70)
	{
		bandeau.setTextureRect(sf::IntRect(0,0,0,0));
		_cptApparition=0;
		fini=true;
	}

	
	return fini;
}

void Dhalsim::statique(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi)
{
    sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=150;
    
    if(timeAnim>delai)
    {
	    switch (_cptStatic)
	    {
	    case 0:
		    _cptStatic ++;
		    clockAnim[0].restart();
    		setSprite(24,163,96,103);
    		_posY=_scene.getBottom()-_tailleSprite.y;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 1:
		    _cptStatic ++;
		    clockAnim[0].restart();
		    setSprite(128,163,97,103);
	    	break;
	    case 2:
		    _cptStatic ++;
		    clockAnim[0].restart();
		    setSprite(233,163,94,103);
	    	break;
	    case 3:
		    _cptStatic ++;
		    clockAnim[0].restart();
		    setSprite(335,163,94,103);
	    	break;
	    case 4:
		    _cptStatic ++;
		    clockAnim[0].restart();
		    setSprite(437,163,93,103);
	    	break;
	    case 5:
		    _cptStatic ++;
		    clockAnim[0].restart();
		    setSprite(538,163,92,103);
	    	break;
	    case 6:
		    _cptStatic=0;
		    clockAnim[0].restart();
		    setSprite(638,163,91,103);
	    	break;
	    }
	}

	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.4,_tailleSprite.y*0.9));
	_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
	_hitbox.setSize(sf::Vector2f(0,0));
	_gardebox.setSize(sf::Vector2f(0,0));

    rotate(champEnnemi);
    int n=0;
    collision(champEnnemi,n);
    keepInWalls();
}


void Dhalsim::garde(std::vector<sf::Clock>& clockAnim)
{
	_cptStatic=0;
	_posY=_scene.getBottom()-_tailleSprite.y;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    if(timeAnim>delai)
    {
    	clockAnim[0].restart();
    	setSprite(125,4747,63,100);
    	_gardebox.setSize(sf::Vector2f(_tailleSprite.x*0.2,_tailleSprite.y));
    	_gardebox.setPosition(_posX+_tailleSprite.x*0.8*_orientation,_posY);
    }

}

void Dhalsim::avancer(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi)
{
	_posY=_scene.getBottom()-_tailleSprite.y;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    int deplacement=40;
	
	collision(champEnnemi,deplacement);
	
	if(deplacement==0)
    {
    	statique(clockAnim,champEnnemi);
    }else if(timeAnim>delai)
	{
	    switch (_cptAvancer)
	    {
	    case 0:
			_sprite.setPosition(_posX,_posY);
		    _cptAvancer ++;
		    clockAnim[0].restart();
    		setSprite(24,284,75,101);
    		_posX+=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 1:
		    _cptAvancer ++;
		    clockAnim[0].restart();
		    setSprite(107,284,68,101);
		    _posX+=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 2:
		    _cptAvancer ++;
		    clockAnim[0].restart();
		    setSprite(183,284,61,101);
		    _posX+=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 3:
		    _cptAvancer ++;
		    clockAnim[0].restart();
		    setSprite(252,284,58,101);
		    _posX+=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 4:
		    _cptAvancer ++;
		    clockAnim[0].restart();
		    setSprite(318,284,67,101);
		    _posX+=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 5:
			    _cptAvancer ++;
			    clockAnim[0].restart();
			    setSprite(393,284,67,101);
			    _posX+=_orientation*deplacement;
				_sprite.setPosition(_posX,_posY);
	    	break;
	    case 6:
		    _cptAvancer++;
		    clockAnim[0].restart();
		    setSprite(468,284,63,101);
		    _posX+=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 7:
		    _cptAvancer=0;
		    clockAnim[0].restart();
		    setSprite(539,284,66,101);
		    _posX+=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    }
	}
	collision(champEnnemi,deplacement);
    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y));
	_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY);
    rotate(champEnnemi);
	keepInWalls();
}


void Dhalsim::reculer(std::vector<sf::Clock>& clockAnim)
{
	_posY=_scene.getBottom()-_tailleSprite.y;
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    int deplacement=40;
    
    if(timeAnim > delai)
    {
	    switch (_cptReculer)
	    {
	    case 0:
			_sprite.setPosition(_posX,_posY);
		    _cptReculer ++;
		    clockAnim[0].restart();
    		setSprite(614,282,69,103);
    		_posX-=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 1:
		    _cptReculer ++;
		    clockAnim[0].restart();
		    setSprite(691,282,63,103);
		    _posX-=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 2:
		    _cptReculer ++;
		    clockAnim[0].restart();
		    setSprite(762,282,60,103);
		    _posX-=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 3:
		    _cptReculer ++;
		    clockAnim[0].restart();
			setSprite(830,282,63,103);
			_posX-=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 4:
		    _cptReculer ++;
		    clockAnim[0].restart();
			setSprite(901,282,62,103);
			_posX-=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 5:
		    _cptReculer ++;
		    clockAnim[0].restart();
		    setSprite(971,282,57,103);
		    _posX-=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 6:
		    _cptReculer++;
		    clockAnim[0].restart();
			setSprite(1036,282,60,103);
			_posX-=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 7:
		    _cptReculer=0;
		    clockAnim[0].restart();
			setSprite(1104,282,63,103);
			_posX-=_orientation*deplacement;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    }
	}
	_gardebox.setSize(sf::Vector2f(0,0));
    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y));
	_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY);
	keepInWalls();
}


bool Dhalsim::sauter(std::vector<sf::Clock>& clockAnim,int& lancerAttaque,Personnage& champEnnemi,int* degats)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacement=_scene.getBottom()/7;
    bool fini=false;

    if(lancerAttaque!=-1)
    {
    	bool enAttaque=false;

		if(lancerAttaque==1)
			enAttaque=sautPunch(clockAnim,champEnnemi,degats);
    	else if(lancerAttaque==2) 		
    		enAttaque=sautKick(clockAnim,champEnnemi,degats);

    	if(enAttaque)
    	{
    		lancerAttaque=-1;
    		if(_cptSauter<4)
    			_cptSauter=7-_cptSauter;
    	}
    	
    }else
    {

	    if(_cptSauter==0)
	    {
		    _cptSauter++;
		    setSprite(974,1705,50,126);
	    }else if(_cptSauter==8)
	    {
	    	clockAnim[0].restart();
	    	_cptSauter=0;
	    	fini=true;
	    }else if(timeAnim>delai)
	    {
		    collisionsaut(champEnnemi,deplacement);
		    switch(_cptSauter)
		    {
		    case 1:
			    clockAnim[0].restart();
			    _cptSauter++;
			    _posY-=deplacement;
		    	break;
		    case 2:
			    clockAnim[0].restart();
			    _cptSauter++;
			    setSprite(1084,1730,57,101);
			    _posY-=deplacement;
		    	break;
		    case 3:
			    clockAnim[0].restart();
			    _cptSauter++;
			    setSprite(1148,1744,60,87);
			    _posY-=deplacement;
		    	break;
		    case 4:
			    clockAnim[0].restart();
			    _cptSauter++;
			    setSprite(1148,1744,60,87);
		    	break;
		    case 5:
			    clockAnim[0].restart();
			    _cptSauter++;
			    setSprite(1148,1744,60,87);
			    _posY+=deplacement;
		    	break;
		    case 6:
			    clockAnim[0].restart();
			    _cptSauter++;
			    setSprite(1084,1730,57,101);
			    _posY+=deplacement;
		    	break;
		    case 7:
			    clockAnim[0].restart();
			    _cptSauter++;
			    setSprite(974,1705,50,126);
			    _posY+=deplacement;
		    	break;
		    }
		    _sprite.setPosition(_posX,_posY);
		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.8));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
		}
	}

    keepInWalls();
    return fini;
}


bool Dhalsim::sauterAvant(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacementY=_scene.getBottom()/7,deplacementX=50*_orientation;
    bool fini=false;
    
    if(timeAnim > delai)
    {
    	collisionsaut(champEnnemi,deplacementX);
	    switch(_cptSauter)
	    {
	    case 0:
		    clockAnim[0].restart();
		    _cptSauter++;
			setSprite(108,1720,68,111);

			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
	    	break;
	    case 1:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(108,1720,68,111);
    		_posX+=deplacementX;_posY-=deplacementY;

    		_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
	    	break;
	    case 2:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(254,1756,68,75);
    		_posX+=deplacementX*2;_posY-=deplacementY;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	break;
	    case 3:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(330,1785,80,46);
    		_posX+=deplacementX;_posY-=deplacementY;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	break;
	    case 4:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(418,1770,79,61);
    		_posX+=deplacementX;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	break;
	    case 5:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(505,1770,57,61);
    		_posX+=deplacementX*4;_posY+=deplacementY;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	break;
	    case 6:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(570,1784,103,47);
    		_posX+=deplacementX*2;_posY+=deplacementY;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	break;
	    case 7:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(108,1720,68,111);
    		_posX+=deplacementX;_posY+=deplacementY;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);	
	    	break;
	    case 8:
		    clockAnim[0].restart();
		    setSprite(24,1720,82,111);
		    _cptSauter=0;
			fini=true;

			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
	    	break;
	    }

	    _sprite.setPosition(_posX,_posY);
	}

    rotate(champEnnemi);
    keepInWalls();
    return fini;
}

bool Dhalsim::sauterArriere(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacementY=_scene.getBottom()/7,deplacementX=50*_orientation;
    bool fini=false;
    
    if(timeAnim > delai)
    {
	    collisionsaut(champEnnemi,deplacementX);
	    switch(_cptSauter)
	    {
	    case 0:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(108,1720,68,111);

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
	    	break;
	    case 1:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(108,1720,68,111);
    		_posX-=deplacementX;_posY-=deplacementY;

    		_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
	    	break;
	    case 2:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(570,1784,103,47);
    		_posX-=deplacementX*2;_posY-=deplacementY;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	break;
	    case 3:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(505,1770,57,61);
    		_posX-=deplacementX;_posY-=deplacementY;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	break;
	    case 4:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(418,1770,79,61);
    		_posX-=deplacementX;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	break;
	    case 5:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(330,1785,80,46);
    		_posX-=deplacementX*4;_posY+=deplacementY;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	break;
	    case 6:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(254,1756,68,75);
    		_posX-=deplacementX*2;_posY+=deplacementY;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.6));
		    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.2);
	    	break;
	    case 7:
		    clockAnim[0].restart();
		    _cptSauter++;
    		setSprite(108,1720,68,111);
    		_posX-=deplacementX;_posY+=deplacementY;

    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
	    	break;
	    case 8:
		    clockAnim[0].restart();
		    _cptSauter=0;
			setSprite(24,1720,82,111);
			fini=true;

			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
	    	break;
	    }

	    _sprite.setPosition(_posX,_posY);
	}

    keepInWalls();
    return fini;
}

void Dhalsim::accroupi(std::vector<sf::Clock>& clockAnim,bool garde)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=35;
    if(_cptAccroupi==0)
    {
    	if(timeAnim>delai)
    	{
    		clockAnim[0].restart();
    		_cptAccroupi++;
    		setSprite(24,1424,82,95);
    		_posY=_scene.getBottom()-_tailleSprite.y;
			_sprite.setPosition(_posX,_posY);
			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y));
			_hurtbox.setPosition(_posX,_posY);
    	}
    }else if(_cptAccroupi==1)
    {
    	if(timeAnim>delai)
    	{
    		clockAnim[0].restart();
    		_cptAccroupi++;
    		setSprite(114,1424,61,95);
    		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.9));
    		_hurtbox.setPosition(_posX+_tailleSprite.x*0.1,_posY+_tailleSprite.y*0.1);
    	}
    }else
    {
    	if(timeAnim>delai)
    	{
    		clockAnim[0].restart();
    		if(garde==true)
	    	{
	    		setSprite(263,4776,59,71);
	    	}else
    			setSprite(183,1424,60,95);
    	}
    }
}


bool Dhalsim::punch(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi, int* degats)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    bool fini=false;
	
    if(timeAnim > delai)
    {
		switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(24,419,82,117);
		    
		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.8));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
			break;
		case 1:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(114,419,74,117);
			break;
		case 2:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(197,419,108,117);
		    _hitbox.setSize(sf::Vector2f(40*SCALE,20*SCALE));
		    _hitbox.setPosition(_posX+68*SCALE*_orientation,_posY+56*SCALE);
			break;
		case 3:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(313,419,108,117);
			break;
		case 4:
		    _cptAction =0;
		    clockAnim[0].restart();
		    setSprite(429,419,75,117);
		    fini=true;
		    _hitbox.setSize(sf::Vector2f(0,0));
			break;
		}
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=10;

		if(champEnnemi.getPosX()==_scene.getRightLimit())
			_posX-=25*SCALE*_orientation;
	}

	keepInWalls();
	return fini;
}

bool Dhalsim::sautPunch(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi,int* degats)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacement=125;
    bool fini=false;
    
    if(timeAnim>delai)
    {
	    switch(_cptAction)
	    {
	    case 0:
	    	_cptAction ++;
		    clockAnim[0].restart();
		    setSprite(896,1847,69,95);

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
			break;
		case 1:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(973,1847,58,95);
			break;
		case 2:
			_cptAction ++;
			clockAnim[0].restart();
			setSprite(1039,1847,105,95);

			_hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.4,_tailleSprite.y*0.5));
			_hitbox.setPosition(_posX+_tailleSprite.x*0.6*_orientation,_posY+_tailleSprite.y*0.2);
			break;
		case 3:
		    _cptAction=0;
		    clockAnim[0].restart();
		    setSprite(973,1847,58,95);
		    fini=true;

		    _hitbox.setSize(sf::Vector2f(0,0));
			break;
	    }
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=10;

		if(champEnnemi.getPosX()==_scene.getRightLimit())
			_posX-=25*SCALE*_orientation;
	}

    keepInWalls();
    return fini;
}

bool Dhalsim::punchSP(std::vector<sf::Clock>& clockAnim,sf::Sprite& inutile,Personnage& champEnnemi, int* degats,sf::Music& son)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=30;
    bool fini=false;
	
    if(timeAnim > delai)
    {
		switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(24,660,86,92);

		    _posX+=2*SCALE*_orientation;
			break;
		case 1:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(118,665,95,87);
			break;
		case 2:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(221,688,143,64);
			break;
		case 3:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(372,688,271,64);

		    _hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.3));
		    _hitbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.1);
			break;
		case 4:
			if(timeAnim>delai*4)
			{
			    _cptAction++;
			    clockAnim[0].restart();
			    setSprite(651,688,143,64);
			    _hitbox.setSize(sf::Vector2f(0,0));
			}
			break;
		case 5:
		    _cptAction++;
		    clockAnim[0].restart();
		    setSprite(802,688,147,64);
			break;
		case 6:
		    _cptAction++;
		    clockAnim[0].restart();
		    setSprite(957,671,96,81);
			break;
		case 7:
		    _cptAction++;
		    clockAnim[0].restart();
		    setSprite(1061,665,95,87);
			break;
		case 8:
		    _cptAction++;
		    clockAnim[0].restart();
		    setSprite(1164,663,86,89);
			break;
		case 9:
		    _cptAction++;
		    clockAnim[0].restart();
		    setSprite(1258,660,84,92);
			break;
		case 10:
			_cptAction=0;
		    clockAnim[0].restart();
		    setSprite(24,163,96,103);
		    fini=true;
		    _posX+=2*SCALE*_orientation;
			break;
		}
		_posY=_scene.getBottom()-_tailleSprite.y;
		_sprite.setPosition(_posX,_posY);
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=10;

		if(champEnnemi.getPosX()==_scene.getRightLimit())
			_posX-=25*SCALE*_orientation;
	}

	return fini;
}

bool Dhalsim::kick(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi, int* degats)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    bool fini=false;

    if(timeAnim > delai)
    {
		switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(24,768,77,113);
		
		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.8));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
			break;
		case 1:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(109,768,56,113);
		    _posX+= 18*SCALE*_orientation;
			break;
		case 2:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(173,768,126,113);
		    _posX-=8*SCALE*_orientation;

    		_hitbox.setSize(sf::Vector2f(39*SCALE,22*SCALE));
		    _hitbox.setPosition(_posX+87*SCALE*_orientation,_posY+51*SCALE);
			break;
		case 3:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(307,768,122,113);
			break;
		case 4:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(437,768,56,113);
		    _posX+=8*SCALE*_orientation;

    		_hitbox.setSize(sf::Vector2f(0,0));
			break;
		case 5:
		    _cptAction =0;
		    clockAnim[0].restart();
		    setSprite(501,768,77,113);
		    _posX-=18*SCALE*_orientation;
		    fini=true;
			break;
		}
		_sprite.setPosition(_posX,_posY);
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=10;

		if(champEnnemi.getPosX()==_scene.getRightLimit())
			_posX-=25*SCALE*_orientation;
	}

	keepInWalls();
	return fini;	
}

bool Dhalsim::sautKick(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi, int* degats)
{
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=80,deplacement=_scene.getBottom()/6;
    bool fini=false;
    
	if(timeAnim>delai)
    {
	    switch(_cptAction)
	    {
	    case 0:
	    	_cptAction ++;
		    clockAnim[0].restart();
		    setSprite(601,2319,53,110);

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
			break;
	    case 1:
	    	_cptAction ++;
		    clockAnim[0].restart();
		    setSprite(662,2319,63,110);
			break;
		case 2:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(733,2319,99,110);

		    _hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.3));
		    _hitbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.25);
			break;
		case 3:
			_cptAction =0;
			clockAnim[0].restart();
			setSprite(840,2319,70,110);
			fini=true;

			_hitbox.setSize(sf::Vector2f(0,0));
			break;
	    }
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=10;

		if(champEnnemi.getPosX()==_scene.getRightLimit())
			_posX-=25*SCALE*_orientation;
	}
	
    keepInWalls();
    return fini;
}

bool Dhalsim::kickSP(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi, int* degats)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    bool fini=false;
	
    if(timeAnim > delai)
    {
		switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(24,1165,77,113);

		    _posX+=2*SCALE*_orientation;
			break;
		case 1:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(109,1159,97,119);
			break;
		case 2:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(214,1173,56,105);
			break;
		case 3:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(278,1173,126,105);
			break;
		case 4:
			_cptAction++;
			clockAnim[0].restart();
			setSprite(412,1173,232,105);

			_hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.3));
		    _hitbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY);
			break;
		case 5:
		    if(timeAnim>delai*2)
			{	
		    	_cptAction++;
			    clockAnim[0].restart();
			    setSprite(652,1173,126,105);

			    _hitbox.setSize(sf::Vector2f(0,0));
			}
			break;
		case 6:
		    _cptAction++;
		    clockAnim[0].restart();
		    setSprite(924,1173,56,105);
			break;
		case 7:
		    _cptAction++;
		    clockAnim[0].restart();
		    setSprite(988,1173,100,105);
			break;
		case 8:
			_cptAction=0;
		    clockAnim[0].restart();
		    setSprite(24,163,96,103);
		    fini=true;
		    _posX+=2*SCALE*_orientation;
			break;
		}
		_posY=_scene.getBottom()-_tailleSprite.y;
		_sprite.setPosition(_posX,_posY);
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=10;

		if(champEnnemi.getPosX()==_scene.getRightLimit())
			_posX-=25*SCALE*_orientation;
	}

	return fini;
}

bool Dhalsim::SP(std::vector<sf::Clock>& clockAnim,sf::Sprite& bouleFeu,Personnage& champEnnemi, int* degats,sf::Music& son)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    bool fini=false;
    
    if(timeAnim > delai)
    {
	    switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(24,3233,76,120);
		    _posX-=10*SCALE*_orientation;

		    if (!son.openFromFile("musique/Dhalsim/yoga_fire.ogg"))
		        std::cout<<"erreur musique";
			son.play();

		    bouleFeu.setPosition(10,10);
		    bouleFeu.setTexture(_texture);
			bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
			break;
		case 1:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(108,3233,81,120);
		    _posX-=6*SCALE*_orientation;
			break;
		case 2:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(197,3233,58,120);
		    _posX+=28*SCALE*_orientation;
			break;
		case 3:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(263,3233,92,120);
		    _posX-=4*SCALE*_orientation;
			
			bouleFeu.setTextureRect(sf::IntRect(357,3355,38,25));
			bouleFeu.setScale(_orientation*SCALE,SCALE);
			bouleFeu.setPosition(_posX+(_tailleSprite.x*_orientation/2),_posY+(_tailleSprite.y/3));
			break;
		}
		_sprite.setPosition(_posX,_posY);
	}

	if(_cptAction>=4 && _cptAction<8)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(310,3355,39,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>7 && _cptAction<11)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(263,3355,39,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>10 && _cptAction<15)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(217,3355,38,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>14 && _cptAction<20)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(167,3355,42,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>19 && _cptAction<24)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(119,3355,40,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>23 && _cptAction<28)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(71,3355,40,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}else if(_cptAction>27)
	{
		_cptAction ++;
		bouleFeu.setTextureRect(sf::IntRect(24,3355,39,25));
		bouleFeu.setPosition(bouleFeu.getPosition().x+20*_orientation,_posY+(_tailleSprite.y/2));
	}

	if( (_orientation==1 && bouleFeu.getPosition().x>=_scene.getRightLimit()) || (_orientation==-1 && bouleFeu.getPosition().x<=_scene.getLeftLimit()) )
	{
		bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
		fini=true;
		_cptAction=0;
	}


	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.8));
	_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);

    _hitbox.setSize(sf::Vector2f(bouleFeu.getGlobalBounds().width,bouleFeu.getGlobalBounds().height));
	_hitbox.setPosition(bouleFeu.getPosition().x,bouleFeu.getPosition().y);

	if(collisioncoup(champEnnemi))
	{
		*degats=30;

		if(champEnnemi.getPosX()==_scene.getRightLimit())
			_posX-=25*SCALE*_orientation;

		bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
		fini=true;
		_cptAction=0;
	}

	keepInWalls();
	return fini;
}