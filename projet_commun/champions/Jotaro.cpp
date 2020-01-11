#include "../IncludeManager.h"

using namespace std;

Jotaro::Jotaro(int orientation)
{
    _cptStatic=0;_cptAvancer=0;_cptReculer=0;_cptSauter=0;_cptApparition=0;_cptAction=0;_cptAccroupi==0;_cptGarde=0;_cptSP=0;_cptPrendCoup=0;
    SCALE=3.7;
	_orientation=-orientation;
    _icone.setTexture(_texture);
	_icone.setTextureRect(sf::IntRect(3081,7499,115,104));
    if (!_texture.loadFromFile("sprites/sprite_jotaro.png"))
	{
	    std::cout<<"Erreur au chargement du sprite";
	}
	_sprite.setTexture(_texture);
	_sprite.scale(_orientation*SCALE,SCALE);
	setSprite(24,32,51,115);

	_hurtbox.setFillColor(sf::Color(255,255,255,0));
    _hurtbox.setOutlineColor(sf::Color::Green);
    _hurtbox.setOutlineThickness(4);

    _hitbox.setFillColor(sf::Color(255,255,255,0));
    _hitbox.setOutlineColor(sf::Color::Red);
    _hitbox.setOutlineThickness(4);

    _gardebox.setFillColor(sf::Color(255,255,255,0));
    _gardebox.setOutlineColor(sf::Color::Blue);
    _gardebox.setOutlineThickness(4);

}
void Jotaro::setTout(const Scene& s)
{
	_scene=s;


	if(_orientation==1)
		_posX=100.f;
	else
		_posX=_scene.getRightLimit()-100.f;

	_posY=_scene.getBottom()-_tailleSprite.y;
	_sprite.setPosition(_posX,_posY);
	keepInWalls();


    if(_orientation==-1)
    {
		_hurtbox.setScale(-1,1);
		_hitbox.setScale(-1,1);
	}
}


void Jotaro::ajouterTexture(int n1, int n2, int i1, int i2)
{
	vector<int> temp{};
	temp.push_back(n1);
	temp.push_back(n2);
	temp.push_back(i1);
	temp.push_back(i2);

	_tabSP.push_back(temp);

}

void Jotaro::resetTexture()
{
	while(!_tabSP.empty())
	{
		_tabSP.pop_back();
	}
}

bool Jotaro::victoire(std::vector<sf::Clock>& clockAnim,sf::Music& son)
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
			setSprite(21,6791,82,117);

			_hurtbox.setSize(sf::Vector2f(0,0));

			if (!son.openFromFile("musique/Jotaro/jotaro_victoire.ogg"))
		        std::cout<<"erreur musique";
			son.play();
	    	break;
	    case 1:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(114,6791,74,117);
	    	break;
	    case 2:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(200,6793,63,115);
	    	break;
	    case 3:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(276,6793,70,115);
	    	break;
	    case 4:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(356,6793,73,115);
	    	break;
	    case 5:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(441,6793,67,115);
	    	break;
	    case 6:
		    _cptApparition++;
		    clockAnim[0].restart();
		    setSprite(521,6793,61,116);
		    break;
		}

		_posY=_scene.getBottom()-_tailleSprite.y;
		_sprite.setPosition(_posX,_posY);
	}

	if(_cptApparition==7 && timeAnim>4000)
	{
		clockAnim[0].restart();
		_cptApparition=0;
		fini=true;
	}

	keepInWalls();
	return fini;
}

bool Jotaro::mort(std::vector<sf::Clock>& clockAnim)
{
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=100,deplacementX=_scene.getRightLimit()/12;
    bool fini=false;
    _hitbox.setSize(sf::Vector2f(0,0));

	if(timeAnim>delai)
	{
	    switch (_cptApparition)
	    {
	    case 0:
		    _cptApparition ++;
		    clockAnim[0].restart();
			setSprite(617,6355,91,96);

			_hurtbox.setSize(sf::Vector2f(0,0));
	    	break;
	    case 1:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(160,5836,148,80);
		    _posX-=deplacementX*_orientation;
	    	break;
	    case 2:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(475,5830,148,68);
		    _posX-=deplacementX*_orientation;
	    	break;
	    case 3:
		    _cptApparition ++;
		    clockAnim[0].restart();
		    setSprite(1204,6384,124,68);
		    _posX-=deplacementX*_orientation;
	    	break;
	    case 4:
		    _cptApparition++;
		    clockAnim[0].restart();
		    setSprite(1806,6405,137,44);
	    	break;
	    case 5:
		    _cptApparition++;
		    clockAnim[0].restart();
		    setSprite(1955,6417,140,35);
	    	break;
	    case 6:
		    _cptApparition++;
		    clockAnim[0].restart();
		    setSprite(2106,6424,144,28);
	    	break;
	    case 7:
		    _cptApparition++;
		    clockAnim[0].restart();
		    setSprite(2264,6425,143,27);
	    	break;
	    }

	    if(_cptApparition>3)
	    	_posY=_scene.getBottom()-_tailleSprite.y;
		_sprite.setPosition(_posX,_posY);
	}

	if(_cptApparition==8 && timeAnim>2000)
	{
		clockAnim[0].restart();
		_cptApparition=0;
		fini=true;
	}

	keepInWalls();
	return fini;
}

bool Jotaro::parade(std::vector<sf::Clock>& clockAnim,int* degats,sf::Sprite& effet)
{
	bool fini=false;
	_cptSauter=0;_cptAction=0;_cptGarde=0;
	effet.setTextureRect(sf::IntRect(0,0,0,0));
	_hurtbox.setSize(sf::Vector2f(0,0));

	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=120;

    if(_cptPrendCoup==0)
    {
    	setSprite(642,4999,126,117);
    	_cptPrendCoup++;
    	_posX-=25*SCALE*_orientation;
    	_posY=_scene.getBottom()-_tailleSprite.y;
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

bool Jotaro::prendCoup(std::vector<sf::Clock>& clockAnim,int* degats,sf::Sprite& effet,int& energie)
{
	*degats=-1;
	bool fini=false;
	_cptSauter=0;_cptAction=0;
	effet.setTextureRect(sf::IntRect(0,0,0,0));
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    _hurtbox.setSize(sf::Vector2f(0,0));
    if(timeAnim > delai)
    {
    	switch(_cptPrendCoup)
    	{
    	case 0:
    		clockAnim[0].restart();
    		_cptPrendCoup++;
    		setSprite(1168,5354,89,108);
    		_posX-=11*SCALE*_orientation;
    		_posY+=9*SCALE;
    		_gardebox.setSize(sf::Vector2f(0,0));

    		energie+=5;
    		break;
    	case 1:
    		clockAnim[0].restart();
    		_cptPrendCoup++;
    		setSprite(1269,5354,111,108);
    		_posX-=10*SCALE*_orientation;
    		break;
    	case 2:
    		clockAnim[0].restart();
    		_cptPrendCoup++;
    		setSprite(1858,5371,123,88);
    		_posY+=20*SCALE;
    		_posX-=10*SCALE*_orientation;
    		break;
    	case 3:
    		clockAnim[0].restart();
    		_cptPrendCoup++;
    		setSprite(1391,5354,88,108);
    		break;
    	case 4:
    		clockAnim[0].restart();
    		_cptPrendCoup=0;
    		setSprite(4,6,64,117);
    		fini=true;
    		*degats=0;
    		break;
    	}
    }
    keepInWalls();
    _sprite.setPosition(_posX,_posY);
    return fini;
}



bool Jotaro::apparition(std::vector<sf::Clock>& clockAnim,sf::Sprite& starPlat)
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
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=120;
    bool fini =false;

    if(_cptApparition<=10 && timeAnim>delai)
    {
    	switch(_cptApparition)
    	{
    	case 0:
    		clockAnim[0].restart();
    		_cptApparition++;
    		setSprite(18,1403,82,134);
    		_posX-=18*SCALE*_orientation;
    		break;
    	case 1:
    		clockAnim[0].restart();
    		_cptApparition++;
    		setSprite(112,1403,87,134);
    		_posX-=2*SCALE*_orientation;
    		break;
    	case 2:
    		clockAnim[0].restart();
    		_cptApparition++;
    		setSprite(209,1403,101,134);
    		_posX-=2*SCALE*_orientation;
    		break;
    	case 3:
    		clockAnim[0].restart();
    		_cptApparition++;
    		setSprite(318,1403,101,134);

    		break;
    	case 4:
    		clockAnim[0].restart();
    		_cptApparition++;
    		setSprite(428,1403,157,134);
    		break;
    	case 5:
    		clockAnim[0].restart();
    		_cptApparition++;
    		setSprite(597,1403,137,134);
    		_posX+=21*SCALE*_orientation;
    		break;
    	case 6:
    		clockAnim[0].restart();
    		_cptApparition++;
    		setSprite(748,1403,132,134);
    		break;
    	case 7:
    		clockAnim[0].restart();
    		_cptApparition++;
    		setSprite(892,1403,127,134);
    		break;
    		clockAnim[0].restart();
    		_cptApparition++;
    		setSprite(1030,1403,121,134);
    		break;
    	case 8:
    		clockAnim[0].restart();
    		_cptApparition++;
    		setSprite(1168,1403,120,134);
    		_posX+=1*SCALE*_orientation;
    		break;
    	case 9:
    		clockAnim[0].restart();
    		_cptApparition++;
    		setSprite(1030,1403,121,134);
    		_posX-=1*SCALE*_orientation;
    		break;
    	case 10:
    		clockAnim[0].restart();
    		_cptApparition++;
    		setSprite(3050,4837,69,117);
    		_posY+=17*SCALE;
    		starPlat.setTexture(_texture);
    		starPlat.setScale(_orientation*SCALE,SCALE);
			starPlat.setPosition(_posX+(_tailleSprite.x*_orientation),_scene.getBottom()-_tabSP[0][3]*SCALE);
			starPlat.setTextureRect(sf::IntRect(_tabSP[0][0],_tabSP[0][1],_tabSP[0][2],_tabSP[0][3]));
    		break;
    	}
    	_sprite.setPosition(_posX,_posY);
    }
    else if(_cptApparition>10 && timeAnim>delai/3)
    {
    	clockAnim[0].restart();
    	_cptApparition++;
		starPlat.setTextureRect(sf::IntRect(_tabSP[_cptApparition-11][0],_tabSP[_cptApparition-11][1],_tabSP[_cptApparition-11][2],_tabSP[_cptApparition-11][3]));
		if(_cptApparition==34)
		{
			fini=true;
			_SPChargee=false;
			_cptApparition=0;
			starPlat.setTextureRect(sf::IntRect(0,0,0,0));
			resetTexture();
		}
    }

    keepInWalls();
    return fini;
}

void Jotaro::statique(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi)
{
    sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=120;

	if(timeAnim>delai)
	{
	    switch (_cptStatic)
	    {
	    case 0:
		    _cptStatic ++;
		    clockAnim[0].restart();
			setSprite(4,6,64,117);
	    	break;
	    case 1:
		    _cptStatic ++;
		    clockAnim[0].restart();
		    setSprite(80,6,64,117);
	    	break;
	    case 2:
		    _cptStatic ++;
		    clockAnim[0].restart();
		    setSprite(155,6,64,117);
	    	break;
	    case 3:
		    _cptStatic ++;
		    clockAnim[0].restart();
		    setSprite(232,6,66,117);
	    	break;
	    case 4:
		    _cptStatic ++;
		    clockAnim[0].restart();
		    setSprite(310,6,69,117);
	    	break;
	    case 5:
		    _cptStatic ++;
		    clockAnim[0].restart();
		    setSprite(390,6,67,117);
	    	break;
	    case 6:
		    _cptStatic++;
		    clockAnim[0].restart();
		    setSprite(467,6,64,117);
		    break;
	    case 7:
		    _cptStatic=0;
		    clockAnim[0].restart();
		    setSprite(541,6,64,117);
	    	break;
	    }
	    _posY=_scene.getBottom()-_tailleSprite.y;
    	_sprite.setPosition(_posX,_posY);
	}


    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
   	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
   	_hitbox.setSize(sf::Vector2f(0,0));
   	_gardebox.setSize(sf::Vector2f(0,0));

    rotate(champEnnemi);
    int n=0;
    collision(champEnnemi,n);
    keepInWalls();
}


void Jotaro::garde(std::vector<sf::Clock>& clockAnim)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    if(timeAnim>delai)
    {
    	clockAnim[0].restart();
    	setSprite(269,4991,108,125);

    	if(_gardebox.getSize()==sf::Vector2f(0,0))
    		_posX-=30*SCALE*_orientation;

    	_gardebox.setSize(sf::Vector2f(_tailleSprite.x*0.2,_tailleSprite.y));
    	_gardebox.setPosition(_posX+_tailleSprite.x*0.8*_orientation,_posY);
    }
    _posY=_scene.getBottom()-_tailleSprite.y;
    _sprite.setPosition(_posX,_posY);
    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
   	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
}

void Jotaro::avancer(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi)
{
	_posY=_scene.getBottom()-_tailleSprite.y;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=60;
    int deplacement=45;

    collision(champEnnemi,deplacement);

	if(deplacement==0)
    {
    	statique(clockAnim,champEnnemi);
    }else if(timeAnim>delai)
    {
	    switch (_cptAvancer)
	    {
	    case 0:

		    _cptAvancer ++;
		    clockAnim[0].restart();
			setSprite(4,858,67,115);
			_posX+=_orientation*deplacement;
	    	break;
	    case 1:
		    _cptAvancer ++;
		    clockAnim[0].restart();
		    setSprite(92,858,59,115);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 2:
		    _cptAvancer ++;
		    clockAnim[0].restart();
		    setSprite(174,858,47,115);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 3:
		    _cptAvancer ++;
		    clockAnim[0].restart();
		    setSprite(247,858,48,115);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 4:
		    _cptAvancer ++;
		    clockAnim[0].restart();
		    setSprite(316,858,53,115);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 5:
		    _cptAvancer ++;
		    clockAnim[0].restart();
		    setSprite(387,858,70,115);
		    _posX+=_orientation*deplacement;

	    	break;
	    case 6:
		    _cptAvancer++;
		    clockAnim[0].restart();
		    setSprite(473,858,77,115);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 7:
		    _cptAvancer++;
		    clockAnim[0].restart();
		    setSprite(564,858,72,115);
		    _posX+=_orientation*deplacement;
	    	break;
	    case 8:
		    _cptAvancer++;
		    clockAnim[0].restart();
		    setSprite(658,858,69,115);
		    _posX+=_orientation*deplacement;
			break;
		case 9:
		    _cptAvancer++;
		    clockAnim[0].restart();
		    setSprite(746,858,62,115);
		    _posX+=_orientation*deplacement;
			break;
		case 10:
		    _cptAvancer++;
		    clockAnim[0].restart();
		    setSprite(825,858,47,115);
		    _posX+=_orientation*deplacement;
			break;
		case 11:
		    _cptAvancer++;
		    clockAnim[0].restart();
		    setSprite(897,858,52,115);
		    _posX+=_orientation*deplacement;
			break;
		case 12:
		    _cptAvancer++;
		    clockAnim[0].restart();
		    setSprite(961,858,58,115);
		    _posX+=_orientation*deplacement;
			break;
		case 13:
		    _cptAvancer++;
		    clockAnim[0].restart();
		    setSprite(1124,858,76,115);
		    _posX+=_orientation*deplacement;
			break;
		case 14:
		    _cptAvancer=0;
		    clockAnim[0].restart();
		    setSprite(1209,858,72,115);
		    _posX+=_orientation*deplacement;
			break;
	    }
	    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
   		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
   		_sprite.setPosition(_posX,_posY);
	}

    rotate(champEnnemi);
	keepInWalls();
}


void Jotaro::reculer(std::vector<sf::Clock>& clockAnim)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=60, deplacement=30;
    if(timeAnim>delai)
    {
		switch (_cptReculer)
		{
		case 0:
		    _cptReculer ++;
		    clockAnim[0].restart();
			setSprite(1413,858,76,115);
			_posX-=_orientation*deplacement;
			break;
		case 1:
		    _cptReculer ++;
		    clockAnim[0].restart();
		    setSprite(1499,858,75,115);
		    _posX-=_orientation*deplacement;
			break;
		case 2:
		    _cptReculer ++;
		    clockAnim[0].restart();
		    setSprite(1583,858,58,115);
		    _posX-=_orientation*deplacement;
			break;
		case 3:
		    _cptReculer ++;
		    clockAnim[0].restart();
			setSprite(1656,858,52,115);
			_posX-=_orientation*deplacement;
			break;
		case 4:
		    _cptReculer ++;
		    clockAnim[0].restart();
			setSprite(1723,858,46,115);
			_posX-=_orientation*deplacement;
			break;
		case 5:
		    _cptReculer ++;
		    clockAnim[0].restart();
		    setSprite(1782,858,59,115);
		    _posX-=_orientation*deplacement;
			break;
		case 6:
		    _cptReculer++;
		    clockAnim[0].restart();
			setSprite(1854,858,59,115);
			_posX-=_orientation*deplacement;
			break;
		case 7:
		    _cptReculer++;
		    clockAnim[0].restart();
			setSprite(1931,858,72,115);
			_posX-=_orientation*deplacement;
			break;
		case 8:
		    _cptReculer++;
		    clockAnim[0].restart();
		    setSprite(2016,858,77,115);
		    _posX-=_orientation*deplacement;
			break;
		case 9:
		    _cptReculer++;
		    clockAnim[0].restart();
		    setSprite(2105,858,70,115);
		    _posX-=_orientation*deplacement;
			break;
		case 10:
		    _cptReculer++;
		    clockAnim[0].restart();
		    setSprite(2186,858,53,115);
		    _posX-=_orientation*deplacement;
			break;
		case 11:
		    _cptReculer++;
		    clockAnim[0].restart();
		    setSprite(2253,858,48,115);
		    _posX-=_orientation*deplacement;
			break;
		case 12:
		    _cptReculer++;
		    clockAnim[0].restart();
		    setSprite(2314,858,47,115);
		    _posX-=_orientation*deplacement;
			break;
		case 13:
		    _cptReculer++;
		    clockAnim[0].restart();
		    setSprite(2374,858,56,115);
		    _posX-=_orientation*deplacement;
			break;
		case 14:
		    _cptReculer++;
		    clockAnim[0].restart();
		    setSprite(2443,858,67,115);
		    _posX-=_orientation*deplacement;
			break;
		case 15:
		    _cptReculer=0;
		    clockAnim[0].restart();
		    setSprite(2523,858,72,115);
		    _posX-=_orientation*deplacement;
			break;
		}
		_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
   		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
   		_gardebox.setSize(sf::Vector2f(0,0));
   		_posY=_scene.getBottom()-_tailleSprite.y;
   		_sprite.setPosition(_posX,_posY);
	}
	keepInWalls();
}


bool Jotaro::sauter(std::vector<sf::Clock>& clockAnim,int& lancerAttaque,Personnage& champEnnemi,int* degats,int& energie)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacement=_scene.getBottom()/11;
    bool fini=false;

    if(lancerAttaque!=-1)
    {
    	bool enAttaque=false;

		if(lancerAttaque==1)
			enAttaque=sautPunch(clockAnim,champEnnemi,degats,energie);
    	else if(lancerAttaque==2)
    		enAttaque=sautKick(clockAnim,champEnnemi,degats,energie);

    	if(enAttaque)
    	{
    		lancerAttaque=-1;
    		if(_cptSauter<5)
    			_cptSauter=11-_cptSauter;
    	}

    }else
    {
	    if(_cptSauter==0)
	    {
		    _cptSauter++;
		    setSprite(2,1101,97,153);
		    _posX-=25*SCALE*_orientation;
		    _posY=_scene.getBottom()-_tailleSprite.y;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.3);
	   		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.6));
	    }
	    else if(timeAnim > delai)
	   	{
		    collisionsaut(champEnnemi,deplacement);

			switch(_cptSauter)
		    {
		    case 1:
			    clockAnim[0].restart();
			    _cptSauter++;
			    setSprite(109,1137,57,127);
			    _posX+=25*SCALE*_orientation;
			    _posY-=deplacement;

		    	_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.3);
		    	break;
		    case 2:
			    clockAnim[0].restart();
			    _cptSauter++;
			    setSprite(183,1143,90,117);
			    _posX-=13*SCALE*_orientation;
			    _posY-=deplacement;

			    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.3);
		    	break;
		    case 3:
			    clockAnim[0].restart();
			    _cptSauter++;
			    setSprite(281,1147,88,99);
			    _posY-=deplacement;

			    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.3);
	   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.6));
		    	break;
		    case 4:
			    clockAnim[0].restart();
			    _cptSauter++;
			    setSprite(383,1145,80,83);
			    _posY-=deplacement;

			    _hurtbox.setPosition(_posX+_tailleSprite.x*0.3*_orientation,_posY+_tailleSprite.y*0.2);
	   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.5));
		    	break;
		    case 5:
			    clockAnim[0].restart();
			    _cptSauter++;
			    setSprite(480,1142,85,79);

			    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.2);
	   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.65,_tailleSprite.y*0.5));
		    	break;
		    case 6:
			    clockAnim[0].restart();
			    _cptSauter++;
			    setSprite(576,1124,99,112);
			    _posX-=8*SCALE*_orientation;
			    _posY+=deplacement;

			    _hurtbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.3);
	   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.5));
		    	break;
		    case 7:
			    clockAnim[0].restart();
			    _cptSauter++;
			    setSprite(682,1114,101,142);
			    _posY+=deplacement;

			    _hurtbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.3);
	   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.5));
		    	break;
		    case 8:
			    clockAnim[0].restart();
			    _cptSauter++;
			    setSprite(682,1114,101,142);
			    _posY+=deplacement;

			    _hurtbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.3);
	   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.6));
		    	break;
		    case 9:
		    	clockAnim[0].restart();
		    	_cptSauter++;
		    	setSprite(793,1121,111,138);
			    _posY+=deplacement;

			    _hurtbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.3);
	   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.6));
		    	break;
		    case 10:
		    	clockAnim[0].restart();
		    	_cptSauter++;
		    	setSprite(914,1111,125,153);
			    _posY+=deplacement;

			    _hurtbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.3);
	   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.6));
				break;
			case 11:
			    clockAnim[0].restart();
				setSprite(4,6,64,117);
			    _posX+=23*SCALE*_orientation;
			    _cptSauter=0;
			    fini=true;
			    _posY=_scene.getBottom()-_tailleSprite.y;
		    	break;
		    }

	   		_sprite.setPosition(_posX,_posY);
		}
	}

    keepInWalls();
    return fini;
}


bool Jotaro::sauterAvant(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacementY=_scene.getBottom()/9,deplacementX=80*_orientation;
    bool fini=false;

    if(_cptSauter==0)
    {
    	_cptSauter++;
	    setSprite(2,1101,97,153);
	    _posY=_scene.getBottom()-_tailleSprite.y;

	    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.3);
   		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.6));
    }else if(timeAnim>delai)
    {
	    collisionsaut(champEnnemi,deplacementX);

	    switch(_cptSauter)
	    {
	    case 1:
		    clockAnim[0].restart();
		    _cptSauter++;
		    setSprite(109,1111,57,153);
		    _posY-=deplacementY;
		    _posX+=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.3);
	    	break;
	    case 2:
		    clockAnim[0].restart();
		    _cptSauter++;
		    setSprite(183,1111,90,153);
		    _posY-=deplacementY;
		    _posX+=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.3);
	    	break;
	    case 3:
		    clockAnim[0].restart();
		    _cptSauter++;
		    setSprite(281,1111,88,153);
		    _posY-=deplacementY;
		    _posX+=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.3);
   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.6));
	    	break;
	    case 4:
		    clockAnim[0].restart();
		    _cptSauter++;
		    setSprite(383,1111,80,153);
		    _posY-=deplacementY;
		    _posX+=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.3*_orientation,_posY+_tailleSprite.y*0.2);
   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.5));
	    	break;
	    case 5:
		    clockAnim[0].restart();
		    _cptSauter++;
		    setSprite(480,1111,85,153);

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.2);
   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.65,_tailleSprite.y*0.5));
	    	break;
	    case 6:
		    clockAnim[0].restart();
		    _cptSauter++;
		    setSprite(576,1111,99,153);
		    _posY+=deplacementY;
		    _posX+=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.3);
   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.5));
	    	break;
	    case 7:
		    clockAnim[0].restart();
		    _cptSauter++;
		    setSprite(682,1111,101,153);
		    _posY+=deplacementY;
		    _posX+=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.3);
   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.5));
	    	break;
	    case 8:
	    	clockAnim[0].restart();
	    	_cptSauter++;
	    	setSprite(793,1111,111,153);
		    _posY+=deplacementY;
		    _posX+=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.3);
   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.6));
	    	break;
	    case 9:
	    	clockAnim[0].restart();
	    	_cptSauter++;
	    	setSprite(914,1111,125,153);
		    _posY+=deplacementY;
		    _posX+=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.3);
   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.6));
			break;
		case 10:
		    clockAnim[0].restart();
			setSprite(4,6,64,117);
		    _posX+=23*SCALE*_orientation;
		    _cptSauter=0;
		    fini=true;
		    _posY=_scene.getBottom()-_tailleSprite.y;
	    	break;
	    }
	    _sprite.setPosition(_posX,_posY);
	}

    rotate(champEnnemi);
    keepInWalls();
    return fini;
}

bool Jotaro::sauterArriere(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacementY=_scene.getBottom()/9,deplacementX=70*_orientation;
    bool fini=false;

    if(_cptSauter==0)
    {
    	_cptSauter++;
	    setSprite(2,1101,97,153);
	    _posY=_scene.getBottom()-_tailleSprite.y;

	    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.3);
   		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.6));
    }else if( timeAnim>delai)
    {
	    collisionsaut(champEnnemi,deplacementX);

	    switch(_cptSauter)
	    {
	    case 1:
		    clockAnim[0].restart();
		    _cptSauter++;
		    setSprite(109,1111,57,153);
		    _posY-=deplacementY;
		    _posX-=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.3);
	    	break;
	    case 2:
		    clockAnim[0].restart();
		    _cptSauter++;
		    setSprite(183,1111,90,153);
		    _posY-=deplacementY;
		    _posX-=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.3);
	    	break;
	    case 3:
		    clockAnim[0].restart();
		    _cptSauter++;
		    setSprite(281,1111,88,153);
		    _posY-=deplacementY;
		    _posX-=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.3);
   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.6));
	    	break;
	    case 4:
		    clockAnim[0].restart();
		    _cptSauter++;
		    setSprite(383,1111,80,153);
		    _posY-=deplacementY;
		    _posX-=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.3*_orientation,_posY+_tailleSprite.y*0.2);
   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.5));
	    	break;
	    case 5:
		    clockAnim[0].restart();
		    _cptSauter++;
		    setSprite(480,1111,85,153);

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.2);
   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.65,_tailleSprite.y*0.5));
	    	break;
	    case 6:
		    clockAnim[0].restart();
		    _cptSauter++;
		    setSprite(576,1111,99,153);
		    _posY+=deplacementY;
		    _posX-=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.3);
   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.5));
	    	break;
	    case 7:
		    clockAnim[0].restart();
		    _cptSauter++;
		    setSprite(682,1111,101,153);
		    _posY+=deplacementY;
		    _posX-=deplacementX;

	    	_hurtbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.3);
   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.5));
	    	break;
	    case 8:
	    	clockAnim[0].restart();
	    	_cptSauter++;
	    	setSprite(793,1111,111,153);
		    _posY+=deplacementY;
		    _posX-=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.3);
   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.6));
	    	break;
	    case 9:
	    	clockAnim[0].restart();
	    	_cptSauter++;
	    	setSprite(914,1111,125,153);
		    _posY+=deplacementY;
		    _posX-=deplacementX;

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.3);
   			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.6));
			break;
		case 10:
		    clockAnim[0].restart();
			setSprite(4,6,64,117);
		    _posX+=23*SCALE*_orientation;
		    _cptSauter=0;
		    fini=true;
		    _posY=_scene.getBottom()-_tailleSprite.y;
	    	break;
	    }

   		_sprite.setPosition(_posX,_posY);
	}

    keepInWalls();
    return fini;
}

void Jotaro::accroupi(std::vector<sf::Clock>& clockAnim,bool garde)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    if(timeAnim>delai)
    {
	    if(_cptAccroupi==0)
	    {
    		clockAnim[0].restart();
    		_cptAccroupi++;
    		setSprite(914,743,97,102);
    		_posY=_scene.getBottom()-_tailleSprite.y;
    		_posX-=25*SCALE;
	    }else if(_cptAccroupi==1)
	    {
    		clockAnim[0].restart();
    		_cptAccroupi++;
    		setSprite(1026,743,91,102);
    		_posX+=14*SCALE;
	    }else if(_cptAccroupi==2)
	    {
    		clockAnim[0].restart();
    		_cptAccroupi++;
    		setSprite(1128,743,104,102);
	    }else if(_cptAccroupi==3)
	    {
    		clockAnim[0].restart();
    		_cptAccroupi++;
    		setSprite(1245,743,89,102);
    		_posX+=4*SCALE;
	    }else if(_cptAccroupi==4)
	    {
    		clockAnim[0].restart();
    		_cptAccroupi++;
    		setSprite(1348,743,95,102);
    		_posX-=3*SCALE;
	    }else if(_cptAccroupi==5)
	    {
    		clockAnim[0].restart();
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
	    	clockAnim[0].restart();
    		if(garde==true)
	    	{
	    		setSprite(1922,5033,112,83);
	    	}else
    			_cptAccroupi=5;
	    }
	}
	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.7));
    _hurtbox.setPosition(_posX,_posY+_tailleSprite.y*0.3);
    _sprite.setPosition(_posX,_posY);
}

bool Jotaro::seLever(std::vector<sf::Clock>& clockAnim)
{
	_cptAccroupi=0;
	bool fini=false;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    if(timeAnim>delai)
    {
	    switch(_cptAction)
	    {
	    case 0:
	    	clockAnim[0].restart();
	    	_cptAction++;
	    	setSprite(2186,725,90,118);
	    	_posX+=1*SCALE*_orientation;
	    	break;
	    case 1:
	    	clockAnim[0].restart();
	    	_cptAction++;
	    	setSprite(2290,725,90,118);
	    	_posX-=1*SCALE*_orientation;
	    	break;
	    case 2:
	    	clockAnim[0].restart();
	    	_cptAction++;
	    	setSprite(2392,725,71,118);
	    	_posX+=12*SCALE*_orientation;
	    	break;
	    case 3:
	    	clockAnim[0].restart();
	    	_cptAction++;
	    	setSprite(2471,725,76,118);
	    	_posX-=6*SCALE*_orientation;
	    	break;
	    case 4:
	    	clockAnim[0].restart();
	    	_cptAction=0;
	    	setSprite(4,6,64,117);
	    	_posX+=6*SCALE*_orientation;
	    	fini=true;
	    	break;
	    }
   	}
   	_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
	_sprite.setPosition(_posX,_posY);
   	keepInWalls();
   	return fini;
}

bool Jotaro::punch(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi, int* degats,int& energie)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    bool fini=false;
	if(timeAnim>delai)
	{
		switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(6,2106,88,115);

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
	   		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
			break;
		case 1:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(102,2106,117,115);
			break;
		case 2:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(227,2106,119,115);
			break;
		case 3:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(359,2106,152,115);
		    _hitbox.setSize(sf::Vector2f(49*SCALE,23*SCALE));
		    _hitbox.setPosition(_posX+_tailleSprite.x*0.66*_orientation,_posY+18*SCALE);
			break;
		case 4:
		    _cptAction++;
		    clockAnim[0].restart();
		    setSprite(519,2106,110,114);
		    _posY+=2*SCALE*_orientation;
		    _hitbox.setSize(sf::Vector2f(0,0));
			break;
		case 5:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(637,2106,134,114);
			break;
		case 6:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(776,2106,132,114);
			break;
		case 7:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(915,2106,107,114);
			break;
		case 8:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(1031,2106,71,115);
			break;
		case 9:
		    _cptAction =0;
		    clockAnim[0].restart();
		    setSprite(4,6,64,117);
		    fini=true;
			break;
		}
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=10;
		energie+=10;

		if(champEnnemi.getPosX()==_scene.getRightLimit())
			_posX-=25*SCALE*_orientation;
	}

	_sprite.setPosition(_posX,_posY);
	keepInWalls();
	return fini;
}

bool Jotaro::sautPunch(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi,int* degats,int& energie)
{
	return sautKick(clockAnim,champEnnemi,degats,energie);
}

bool Jotaro::punchSP(std::vector<sf::Clock>& clockAnim,sf::Sprite& starPlat,Personnage& champEnnemi, int* degats,sf::Music& son,int& energie)
{
	if(energie<25)
		return true;

	if(!_SPChargee)
	{
		ajouterTexture(1751,4643,112,128);ajouterTexture(1870,4643,108,128);ajouterTexture(2157,4643,161,128);ajouterTexture(2467,4643,127,128);
		ajouterTexture(2762,4643,219,128);ajouterTexture(3128,4643,218,128);ajouterTexture(3634,4643,129,128);
		_SPChargee=true;
	}
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    bool fini=false;
	if(timeAnim>delai)
	{
	    switch (_cptAction)
		{
		case 0:
			    _cptAction ++;
			    clockAnim[0].restart();
			    setSprite(13,4649,76,117);

			    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
		   		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));

			    starPlat.setTexture(_texture);
			    starPlat.setScale(_orientation*SCALE,SCALE);
				starPlat.setPosition(_posX+(_tailleSprite.x/2*_orientation),_posY);
			break;
		case 1:
			    _cptAction ++;
			    clockAnim[0].restart();
			    setSprite(101,4649,122,117);
			break;
		case 2:
			    _cptAction ++;
			    clockAnim[0].restart();
			    setSprite(228,4649,118,117);
			break;
		case 3:
			    _cptAction ++;
			    clockAnim[0].restart();
			    setSprite(357,4649,113,117);
			break;
		case 4:
			    _cptAction ++;
			    clockAnim[0].restart();
			    setSprite(477,4649,113,117);
			break;
		case 5:
			    _cptAction ++;
			    clockAnim[0].restart();
			    setSprite(598,4649,106,117);
			break;
		case 13:
			    _cptAction ++;
			    clockAnim[0].restart();
			    setSprite(1064,4649,75,117);
			break;
		case 14:
			    _cptAction ++;
			    clockAnim[0].restart();
			    setSprite(1145,4649,74,117);
			break;
		case 15:
			    _cptAction =0;
			    clockAnim[0].restart();
			    fini=true;
			    _SPChargee=false;

			    energie-=25;
			    resetTexture();
			break;
		}

		if(_cptAction>5 && _cptAction<13)
		{
			clockAnim[0].restart();
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

	if(collisioncoup(champEnnemi))
	{
		*degats=20;

		if(champEnnemi.getPosX()==_scene.getRightLimit())
			_posX-=25*SCALE*_orientation;
	}

	return fini;
}


bool Jotaro::kick(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi, int* degats,int& energie)
{
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=50;
    bool fini=false;

	if(timeAnim>delai)
	{
		switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(1322,2103,74,118);

		    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
			break;
		case 1:
			if(timeAnim > delai*1.5){
			    _cptAction ++;
			    clockAnim[0].restart();
			    setSprite(1414,2103,76,118);
			    _posX-=9*SCALE*_orientation;

			}
			break;
		case 2:
			if(timeAnim > delai*1.5){
			    _cptAction ++;
			    clockAnim[0].restart();
			    setSprite(1507,2103,89,118);
			    _posX-=5*SCALE*_orientation;

			}
			break;
		case 3:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(1612,2103,130,118);
		    _posX-=8*SCALE*_orientation;

		    _hitbox.setSize(sf::Vector2f(72*SCALE,28*SCALE));
		    _hitbox.setPosition(_posX+58*SCALE*_orientation,_posY+72*SCALE);
			break;
		case 4:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(1758,2103,124,118);
		    _posX-=2*SCALE*_orientation;
			break;
		case 5:
		    _cptAction++;
		    clockAnim[0].restart();
		    setSprite(1893,2103,112,118);
		    _posX+=1*SCALE*_orientation;
		    _hitbox.setSize(sf::Vector2f(0,0));
			break;
		case 6:
		    _cptAction++;
		    clockAnim[0].restart();
		    setSprite(2018,2103,104,118);
		    _posX+=1*SCALE*_orientation;
			break;
		case 7:
		    _cptAction++;
		    clockAnim[0].restart();
		    setSprite(2131,2103,71,118);
		    _posX+=17*SCALE*_orientation;
			break;
		case 8:
		    _cptAction++;
		    clockAnim[0].restart();
		    setSprite(2215,2103,76,118);
		    _posX-=6*SCALE*_orientation;
			break;
		case 9:
		    _cptAction =0;
		    clockAnim[0].restart();
		    setSprite(4,6,64,117);
		    _posX+=11*SCALE*_orientation;
		    fini=true;
			break;
		}
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=15;
		energie+=10;

		if(champEnnemi.getPosX()==_scene.getRightLimit())
			_posX-=25*SCALE*_orientation;
	}

    _sprite.setPosition(_posX,_posY);
	keepInWalls();
	return fini;
}

bool Jotaro::sautKick(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi, int* degats,int& energie)
{
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70,deplacement=_scene.getBottom()/6;
    bool fini=false;

	if(timeAnim>delai)
    {
	    switch(_cptAction)
	    {
	    case 0:
	    	_cptAction ++;
		    clockAnim[0].restart();
		    setSprite(3123,2127,77,95);

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
			break;
	    case 1:
	    	_cptAction ++;
		    clockAnim[0].restart();
		    setSprite(3208,2127,89,93);
			break;
		case 2:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(3304,2116,130,95);

		    _hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.3));
			_hitbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.7);
			break;
		case 3:
			_cptAction =0;
			clockAnim[0].restart();
			setSprite(3695,2134,105,83);
			fini=true;

			_hitbox.setSize(sf::Vector2f(0,0));
			break;
	    }
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=10;
		energie+=10;

		if(champEnnemi.getPosX()==_scene.getRightLimit())
			_posX-=25*SCALE*_orientation;
	}

    keepInWalls();
    return fini;
}

bool Jotaro::kickSP(std::vector<sf::Clock>& clockAnim,Personnage& champEnnemi, int* degats,int& energie)
{
	if(energie<25)
		return true;

	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=40;
    bool fini=false;
	if(timeAnim>delai)
	{
		switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(13,2465,89,118);

		    _posX-=6*SCALE*_orientation;
			break;
		case 1:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(110,2468,101,115);
			break;
		case 2:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(217,2467,138,116);
			break;
		case 3:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(361,2467,151,116);
		    break;
		case 4:
		    _cptAction++;
		    clockAnim[0].restart();
		    setSprite(521,2474,176,109);

		    _hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.5,_tailleSprite.y*0.3));
			_hitbox.setPosition(_posX+_tailleSprite.x*0.5*_orientation,_posY+_tailleSprite.y*0.6);
			break;
		case 5:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(705,2476,176,107);
			break;
		case 6:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(889,2476,157,107);
			break;
		case 7:
			if(timeAnim>delai*3)
			{
			    _cptAction=0;
			    clockAnim[0].restart();
			    setSprite(1553,2476,154,107);
			    fini=true;

			    _hitbox.setSize(sf::Vector2f(0,0));
			    energie-=25;
			}
			break;
		}
		_posY=_scene.getBottom()-_tailleSprite.y;
		_sprite.setPosition(_posX,_posY);

		_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
		_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
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


bool Jotaro::SP(std::vector<sf::Clock>& clockAnim,sf::Sprite& starPlat,Personnage& champEnnemi, int* degats,sf::Music& son,int& energie)
{
	if(energie<50)
		return true;

	if(!_SPChargee)
	{
		ajouterTexture(671,3724,100,135);ajouterTexture(875,3724,142,135);ajouterTexture(1025,3724,185,135);ajouterTexture(1219,3724,169,135);
		ajouterTexture(1395,3724,184,135);ajouterTexture(1586,3724,176,135);ajouterTexture(1768,3724,158,135);ajouterTexture(1933,3724,150,135);
		ajouterTexture(2091,3724,165,135);ajouterTexture(2264,3724,164,135);ajouterTexture(2436,3724,163,135);ajouterTexture(2607,3724,151,135);
		ajouterTexture(2765,3724,195,135);ajouterTexture(2968,3724,187,135);ajouterTexture(3162,3724,168,135);ajouterTexture(3339,3724,140,135);
		ajouterTexture(3485,3724,138,135);ajouterTexture(3630,3724,179,135);ajouterTexture(3816,3724,170,135);ajouterTexture(3995,3724,166,135);
		ajouterTexture(4170,3724,175,135);ajouterTexture(4354,3724,174,135);ajouterTexture(4536,3724,171,135);ajouterTexture(4714,3724,155,135);
		_SPChargee=true;
		if (!son.openFromFile("musique/Jotaro/jotaro_SP.ogg"))
		        std::cout<<"erreur musique";
		son.play();
	}
	_cptStatic=0;
	sf::Time elapsed = clockAnim[0].getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delai=70;
    bool fini=false;

	if(timeAnim>delai && _cptAction<6)
	{
	    switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(21,3742,75,116);
		    starPlat.setTexture(_texture);
			break;
		case 1:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(106,3742,100,116);
			break;
		case 2:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(216,3742,113,116);
			break;
		case 3:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(338,3742,113,116);
			break;
		case 4:
		    _cptAction ++;
		    clockAnim[0].restart();
		    setSprite(459,3742,108,116);

			starPlat.setTextureRect(sf::IntRect(_tabSP[_cptAction-4][0],_tabSP[_cptAction-4][1],_tabSP[_cptAction-4][2],_tabSP[_cptAction-4][3]));
			starPlat.setScale(_orientation*SCALE,SCALE);
			starPlat.setPosition(_posX+(_tailleSprite.x/2*_orientation),_scene.getBottom()-_tabSP[_cptAction-4][3]*SCALE);
			break;
		case 5:
		    _cptAction ++;
		    clockAnim[0].restart();
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
		clockAnim[0].restart();
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
				_cptSP=0;
				energie-=50;
				resetTexture();
			}else
			{
				_cptAction=8;
			}
		}
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=10;

		if(champEnnemi.getPosX()==_scene.getRightLimit())
			_posX-=25*SCALE*_orientation;
	}

	_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
	return fini;
}
