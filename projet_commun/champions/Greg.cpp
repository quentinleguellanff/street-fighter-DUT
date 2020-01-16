#include "../IncludeManager.h"

using namespace std;

Greg::Greg(int orientation,Scene& s,sf::RenderWindow& window)
{
    double temp=window.getSize().x;
    SCALE=4.2*(temp/1920);
	_orientation=-orientation;
    _cptStatic=0;_cptAvancer=0;_cptReculer=0;_cptSauter=0;_cptApparition=0;_cptAction=0;_cptAccroupi=0;_cptPrendCoup=0;
    _vsaut = -40;

	if (!_texture.loadFromFile("sprites/sprite_greg.png"))
	{
	    std::cout<<"Erreur au chargement du sprite";
	}
	_sprite.setTexture(_texture);
	_sprite.scale(_orientation*SCALE,SCALE);

	_icone.setTexture(_texture);
	_icone.setTextureRect(sf::IntRect(824,5573,124,104));
    _hurtbox.setFillColor(sf::Color(255,255,255,0));
    _hurtbox.setOutlineColor(sf::Color::Green);
    _hurtbox.setOutlineThickness(4);

    _hitbox.setFillColor(sf::Color(255,255,255,0));
    _hitbox.setOutlineColor(sf::Color::Red);
    _hitbox.setOutlineThickness(4);

    _gardebox.setFillColor(sf::Color(255,255,255,0));
    _gardebox.setOutlineColor(sf::Color::Blue);
    _gardebox.setOutlineThickness(4);

    setScene(s);
}


bool Greg::victoire()//ok
{
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delaiAnim=150;
    bool fini=false;
    _hitbox.setSize(sf::Vector2f(0,0));

	if(timeAnim>delaiAnim)
	{
	    switch (_cptApparition)
	    {
	    case 0:
		    _cptApparition ++;
		    _clockAnim.restart();
			setSprite(420,5374,67,94);

			_hurtbox.setSize(sf::Vector2f(0,0));

			if (!_effetSonore.openFromFile("musique/Greg/victoire.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
	    	break;
	    case 1:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(977,5367,67,101);
	    	break;
	    case 2:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(1115,5367,67,101);
	    	break;
	    case 3:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(1253,5367,67,101);
	    	break;
	    case 4:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(1391,5367,67,101);
	    	break;
	    case 5:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(1529,5367,67,101);
	    	break;
	    case 6:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(1667,5367,67,101);
	    	break;
	    case 7:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(1834,5367,116,101);
		    _posX-=49*SCALE*_orientation;
	    	break;
	    case 8:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(2364,5367,67,101);
		    _posX+=49*SCALE*_orientation;
	    	break;
		}

		_posY=_scene.getBottom()-_tailleSprite.y;
		_sprite.setPosition(_posX,_posY);
	}

	if(_cptApparition==9 && timeAnim>1000)
	{
		_clockAnim.restart();
		_cptApparition=0;
		fini=true;
	}

	return fini;
}

bool Greg::mort()//ok
{
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delaiAnim=100,deplacementX=_scene.getRightLimit()/12;
    bool fini=false;
    _hitbox.setSize(sf::Vector2f(0,0));

	if(timeAnim>delaiAnim)
	{
	    switch (_cptApparition)
	    {
	    case 0:
		    _cptApparition ++;
		    _clockAnim.restart();
			setSprite(1,4753,65,97);

			_hurtbox.setSize(sf::Vector2f(0,0));

            if (!_effetSonore.openFromFile("musique/Greg/mort.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
	    	break;
	    case 1:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(1,4965,80,77);

		    _posX-=deplacementX*_orientation;
		    _posY-=11*SCALE;
	    	break;
	    case 2:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(82,4961,105,44);

		    _posX-=deplacementX*_orientation;
	    	break;
	    case 3:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(188,4975,73,65);

		    _posX-=deplacementX*_orientation;
		    break;
	    case 4:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(278,4980,120,46);
	    	break;
	    case 5:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(399,5024,125,41);
	    	break;
		case 6:
		    _cptApparition++;
		    _clockAnim.restart();
		    setSprite(651,5025,123,41);
		    break;
		case 7:
		    _cptApparition++;
		    _clockAnim.restart();
		    setSprite(775,5024,133,34);
		    break;
		}

		if(_cptApparition >=4)
			_posY=_scene.getBottom()-_tailleSprite.y;

		_sprite.setPosition(_posX,_posY);
	}

	if(_cptApparition==8 && timeAnim>2000)
	{
		_clockAnim.restart();
		_cptApparition=0;
		fini=true;
	}

	keepInWalls();
	return fini;
}


bool Greg::parade(int* degats,sf::Sprite& effet)//ok
{
	bool fini=false;
	_cptSauter=0;_cptAction=0;
	effet.setTextureRect(sf::IntRect(0,0,0,0));
	_hurtbox.setSize(sf::Vector2f(0,0));

	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delaiAnim=120;

    if(_cptPrendCoup==0)
    {
    	setSprite(70,4648,68,102);
    	_cptPrendCoup++;
    	//_posX-=25*SCALE*_orientation;
    }else if(timeAnim > delaiAnim)
    {
		if(_cptPrendCoup==1)
		{
			_clockAnim.restart();
			_cptPrendCoup++;
    		//_posX-=25*SCALE*_orientation;
		}else{
			_clockAnim.restart();
			_cptPrendCoup=0;
			fini=true;
			*degats=0;
		}
    }

    sf::Time elapsedDep = _clockMove.getElapsedTime();
    int timeDep = elapsedDep.asMilliseconds();
    int delaiDep=20,deplacement=_scene.getRightLimit()/200*_orientation;

    if(timeDep>delaiDep)
    {
    	_clockMove.restart();
    	_posX-=deplacement;
    	_sprite.setPosition(_posX,_posY);
    }

    keepInWalls();
    return fini;
}


bool Greg::prendCoup(int* degats,sf::Sprite& effet,int& energie)//ok
{
	*degats=-1;
	bool fini=false;
	_cptSauter=0;_cptAction=0;
	effet.setTextureRect(sf::IntRect(0,0,0,0));
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockMove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();
    int delaiAnim=70;
    int deplacement = 20;
    _hurtbox.setSize(sf::Vector2f(0,0));
    _gardebox.setSize(sf::Vector2f(0,0));

    if(timeMove > 20){
         switch (_cptPrendCoup)
	    {
	    case 1:
            _posX -= deplacement * _orientation;
            _clockMove.restart();
	    	break;
	    case 2:
		    _posX -= deplacement * _orientation;
            _clockMove.restart();
	    	break;
	    }
    }


    if(timeAnim > delaiAnim)
    {
    	switch(_cptPrendCoup)
    	{
    	case 0:
    		_clockAnim.restart();
    		_cptPrendCoup++;
            setSprite(574,4742,73,108);
    		//_posX-=1*SCALE*_orientation;
    		//_posY+=6*SCALE;

            if (!_effetSonore.openFromFile("musique/Greg/degat.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();

    		energie+=5;
    		break;
    	case 1:
    		_clockAnim.restart();
    		_cptPrendCoup++;
    		setSprite(325,4742,73,108);
    		//_posX+=1*SCALE*_orientation;
    		break;
    	case 2:
    		_clockAnim.restart();
    		_cptPrendCoup++;
    		setSprite(574,4742,73,108);
    		//_posX-=16*SCALE*_orientation;
    		break;
    	case 3:
    		_cptPrendCoup=0;
		    _clockAnim.restart();
		    fini=true;
		    *degats = 0;
    		//_posX-=16*SCALE*_orientation;
    		break;
    	/*case 4:
    		_clockAnim.restart();
    		_cptPrendCoup=0;
    		setSprite(220,4857,70,94);
    		//_posX-=16*SCALE*_orientation;
    		fini=true;
    		*degats=0;
    		break;*/
    	}
    }
    _sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}


bool Greg::apparition(sf::Sprite& inutile)//ok
{
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    bool fini=false;
    int delaiAnim=200;

   	if(_cptApparition==0)
   	{
		setSprite(9,216,61,113);
		_cptApparition ++;

        if (!_effetSonore.openFromFile("musique/Greg/apparition.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
   	}else if(timeAnim>delaiAnim)
   	{
	   	switch(_cptApparition)
		{
		case 1:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(80,216,61,113);
			break;
		case 2:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(152,216,67,113);
			break;
		case 3:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(227,216,70,113);
			break;
		case 4:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(306,216,64,113);
			break;
		case 5:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(379,216,61,113);
			break;
		case 6:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(449,216,61,113);
			break;
		case 7:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(519,216,61,113);
			break;
		case 8:
		    _cptApparition ++;
		    _clockAnim.restart();
		    setSprite(589,216,61,113);
			break;
		case 9:
		    _cptApparition=0;
		    _clockAnim.restart();
		    setSprite(654,216,68,113);
			fini=true;
			break;
		}
	}
	keepInWalls();
	return fini;
}

void Greg::statique(Personnage& champEnnemi)//ok
{
    sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delaiAnim=50;
    if(timeAnim>delaiAnim)
    {
	    switch (_cptStatic)
	    {
	    case 0:
		    _cptStatic ++;
		    _clockAnim.restart();
    		setSprite(2,360,66,105);
    		_posY=_scene.getBottom()-_tailleSprite.y;
			_sprite.setPosition(_posX,_posY);
	    	break;
	    case 1:
		    _cptStatic ++;
		    _clockAnim.restart();
		    setSprite(71,360,66,105);
	    	break;
	    case 2:
		    _cptStatic ++;
		    _clockAnim.restart();
		    setSprite(140,360,66,105);
	    	break;
	    case 3:
		    _cptStatic ++;
		    _clockAnim.restart();
		    setSprite(209,360,66,105);
	    	break;
	    case 4:
		    _cptStatic ++;
		    _clockAnim.restart();
		    setSprite(279,360,64,105);
	    	break;
	    case 5:
		    _cptStatic=0;
		    _clockAnim.restart();
		    setSprite(347,360,66,105);
	    	break;
	    }
	}

	_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
   	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
   	_hitbox.setSize(sf::Vector2f(0,0));
   	_gardebox.setSize(sf::Vector2f(0,0));

	int n=0;
	collision(champEnnemi,n);
    rotate(champEnnemi);
    keepInWalls();
}


void Greg::garde()
{
	_cptStatic=0;
	_posY=_scene.getBottom()-_tailleSprite.y;
	sf::Time elapsed =
	_clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delaiAnim=70;
    if(timeAnim>delaiAnim)
    {
    	_clockAnim.restart();
    	setSprite(3,4658,65,92);
    	_gardebox.setSize(sf::Vector2f(_tailleSprite.x*0.2,_tailleSprite.y));
    	_gardebox.setPosition(_posX+_tailleSprite.x*0.8*_orientation,_posY);
    }
    _posY=_scene.getBottom()-_tailleSprite.y;
    _sprite.setPosition(_posX,_posY);
    keepInWalls();
}

void Greg::avancer(Personnage& champEnnemi)//ok
{
	_posY=_scene.getBottom()-_tailleSprite.y;
	_cptStatic=0;
	sf::Time elapsed1 = _clockAnim.getElapsedTime();
    int timeAnim = elapsed1.asMilliseconds();
    sf::Time elapsed2 = _clockMove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();
    int delai=70;
    int deplacement=12;

    collision(champEnnemi,deplacement);
    if(_cptAvancer > 5){
        _cptAvancer = 0;
    }

	if(deplacement==0)
    {
    	statique(champEnnemi);
    }

    if(timeMove > 10){
        if(_cptAvancer < 6){
            _posX= _posX+deplacement*_orientation;
	        _clockMove.restart();
        }
    }
    if(timeAnim>50){
        _cptAvancer ++;
        _clockAnim.restart();
    }
    switch (_cptAvancer)
    {
    case 0:
        if(timeAnim>20){
            _cptAvancer ++;
            _clockAnim.restart();
        }
        setSprite(-3,626,72,104);
        break;
    case 1:
        setSprite(70,626,69,104);
        break;
    case 2:
        setSprite(143,626,69,104);
        break;
    case 3:
        setSprite(212,626,68,104);
        break;
    case 4:
        setSprite(281,626,69,104);
        break;
    case 5:
        setSprite(350,626,71,104);
        break;
    }

    _sprite.setPosition(_posX,_posY);
    _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));

    rotate(champEnnemi);

	keepInWalls();
}


void Greg::reculer()//ok
{
    if(_cptReculer > 3){
        _cptReculer = 0;
    }
	_posY=_scene.getBottom()-_tailleSprite.y;
	_cptStatic=0;
	sf::Time elapsed1 = _clockAnim.getElapsedTime();
    int timeAnim = elapsed1.asMilliseconds();
    sf::Time elapsed2 = _clockMove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();
    int delai=70;
    int deplacement=10;

    if(timeMove > 10){
        if(_cptReculer < 4){
            _posX -= deplacement*_orientation;
            _clockMove.restart();
        }
    }
    if(timeAnim > delai)
	{
	    _cptReculer++;
        _clockAnim.restart();
	}

    switch (_cptReculer)
    {
    case 0:
        setSprite(427,624,63,106);
        break;
    case 1:
        setSprite(497,624,61,106);
        break;
    case 2:
        setSprite(564,624,55,106);
        break;
    case 3:
        setSprite(632,624,55,106);
        break;
    }

	    _sprite.setPosition(_posX,_posY);
    	_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
    	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));

    _gardebox.setSize(sf::Vector2f(0,0));

	keepInWalls();
}


bool Greg::sauter(int& lancerAttaque,Personnage& champEnnemi,int* degats,int& energie)//ok
{
    float v_grav = 1.7;
	_cptStatic=0;
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockMove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();

    int delaiAnim=100;
    bool fini=false;

    if(lancerAttaque!=-1)
    {
    	bool enAttaque=false;

		if(lancerAttaque==1)
			enAttaque=sautPunch(champEnnemi,degats,energie);
    	else if(lancerAttaque==2)
    		enAttaque=sautKick(champEnnemi,degats,energie);

    	if(enAttaque)
    	{
    		lancerAttaque=-1;
    		if(_cptSauter<4)
    			_cptSauter=7-_cptSauter;
    	}

    }else
    {
        if(timeMove > 10){
        _vsaut += v_grav;
         _posY += _vsaut;
        _clockMove.restart();
        }
        if(timeAnim > delaiAnim){
            if(_cptSauter < 6)
                _cptSauter++;
            _clockAnim.restart();
        }
        switch (_cptSauter)
        {
        case 0:
            if(timeAnim > 20){
                _cptSauter ++;
                _clockAnim.restart();

                if (!_effetSonore.openFromFile("musique/Greg/saut.ogg"))
                    std::cout<<"erreur musique";
                _effetSonore.play();
            }
            setSprite(651,818,63,100);
            break;
        case 1:
            setSprite(714,809,70,117);
            break;
        case 2:
            setSprite(791,764,64,99);
            break;
        case 3:
            setSprite(861,737,61,81);
            break;
        case 4:
            setSprite(925,729,61,75);
            break;
        case 5:
            setSprite(1000,739,64,97);
            break;
        case 6:
            setSprite(1071,765,62,115);
            if(_posY + _tailleSprite.y + _vsaut >= _scene.getBottom()){
                _cptSauter ++;
            }
            break;
        case 7:
            _cptSauter =0;
            setSprite(2,423,66,108);
            _posY=_scene.getBottom()-_tailleSprite.y;
            _vsaut = -40;
            fini = true;
            break;
        }
    }
	_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
	_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);

	_sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}


bool Greg::sauterAvant(Personnage& champEnnemi)//ok
{
    float v_grav = 1.7;
	_cptStatic=0;
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockMove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();

    int delaiAnim=70;
    int deplacementX=15;
    bool fini=false;

    if(timeMove > 10){
        _vsaut += v_grav;
        _posY += _vsaut;
        collisionsaut(champEnnemi,deplacementX);
        _posX += deplacementX*_orientation;;
        _clockMove.restart();
    }
    if(timeAnim > delaiAnim){
        if(_cptSauter < 8 && _cptSauter != 2){
            if(_cptSauter == 1){
                //_spritePerso.setPosition(_spritePerso.getPosition().x+25*_orientation,_spritePerso.getPosition().y-5);
                _posX += 25*_orientation;
                _posY -= 5;
            }
            _cptSauter++;
            _clockAnim.restart();
        }

        if(_cptSauter == 4){
            //_spritePerso.setPosition(_spritePerso.getPosition().x-100*_orientation,_spritePerso.getPosition().y+50);
            _posX -= 100*_orientation;;
            _posY += 50;
        }
        else if(_cptSauter == 5){
            //_spritePerso.setPosition(_spritePerso.getPosition().x+100*_orientation,_spritePerso.getPosition().y-50);
            _posX += 100*_orientation;;
            _posY -= 50;
        }
        else if(_cptSauter == 6){
            //_spritePerso.setPosition(_spritePerso.getPosition().x-140*_orientation,_spritePerso.getPosition().y+100);
            _posX -= 140*_orientation;;
            _posY += 100;
        }
        else if(_cptSauter == 7){
            _posX += 70*_orientation;;
            _posY -= 70;
            //_spritePerso.setPosition(_spritePerso.getPosition().x+70*_orientation,_spritePerso.getPosition().y-70);
        }
    }
    switch (_cptSauter)
    {
        case 0:
            if(timeAnim > 20){
                 _cptSauter ++;
                 _clockAnim.restart();

                 if (!_effetSonore.openFromFile("musique/Greg/saut.ogg"))
                    std::cout<<"erreur musique";
                _effetSonore.play();
            }
        setSprite(651,820,63,98);
        _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
        _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
        break;
    case 1:
        setSprite(714,811,70,115);
        _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
        _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
        break;
    case 2:
        setSprite(1348,785,62,115);
        _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
        _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
            if(timeAnim > 200){
                 _cptSauter ++;
                 _clockAnim.restart();
            }
        break;
    case 3:
        setSprite(1488,927,65,90);
        _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
        _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
        break;
    case 4:
        setSprite(1410,760,96,46);
        _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
        _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
        break;
    case 5:
        setSprite(1510,737,53,82);
        _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
        _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
        break;
    case 6:
        setSprite(1568,768,120,52);
        _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.4,_tailleSprite.y*0.8));
        _hurtbox.setPosition(_posX+_tailleSprite.x*0.3*_orientation,_posY+_tailleSprite.y*0.1);
        break;
    case 7:
        setSprite(1689,738,70,103);
        _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
        _hurtbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.1);
        break;
    case 8:
        setSprite(1071,765,62,115);
        _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
        _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
        if(_posY + _tailleSprite.y + _vsaut >= _scene.getBottom()){
            _cptSauter ++;
        }
        break;
    case 9:
        _cptSauter =0;
        setSprite(2,423,66,108);
        _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
        _hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
        _posY=_scene.getBottom()-_tailleSprite.y;
        _posX += 45*_orientation;
        _vsaut = -40;
        rotate(champEnnemi);
        fini =  true;
        break;
    }
	_sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}

bool Greg::sauterArriere(Personnage& champEnnemi)//ok
{
	float v_grav = 1.7;
	_cptStatic=0;
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockMove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();

    int delaiAnim=50;
    int deplacementX=15;
    bool fini=false;

    if(timeMove > 10){
        _vsaut += v_grav;
        _posY += _vsaut;
        collisionsaut(champEnnemi,deplacementX);
        _posX -= deplacementX*_orientation;;
        _clockMove.restart();
    }

    if(timeAnim > delaiAnim){
        if(_cptSauter < 8){
            if(_cptSauter == 1){
                //_spritePerso.setPosition(_spritePerso.getPosition().x+25*_orientation,_spritePerso.getPosition().y-5);
                _posX += 25*_orientation;
                _posY -= 5;
            }
            _cptSauter++;
            _clockAnim.restart();
        }
        switch(_cptSauter)
        {
        case 2:
            _posX -= 100*_orientation;
            break;
        case 3:
            _posX -= 50*_orientation;
            _posY += 50;
            break;
        case 4:
            _posX += 100*_orientation;
            _posY -= 50;
            break;
        case 5:
            _posX -= 50*_orientation;
            _posY += 50;
            break;
        case 6:
            _posX += 75*_orientation;
            _posY -= 50;
            break;
        case 7:
            _posY -= 50;
            break;
        }
    }
    switch (_cptSauter)
    {
    case 0:
        if(timeAnim > 20){
             _cptSauter ++;
             _clockAnim.restart();

            if (!_effetSonore.openFromFile("musique/Greg/saut.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
        }
        setSprite(651,818,63,100);
        break;
    case 1:
         setSprite(791,764,64,99);
        break;
    case 2:
        setSprite(1689,738,70,103);
        break;
    case 3:
        setSprite(1568,768,120,52);
        break;
    case 4:
        setSprite(1510,737,53,82);
        break;
    case 5:
        setSprite(1410,759,93,47);
        break;
    case 6:
        setSprite(1488,927,65,90);
        break;
    case 7:
        setSprite(518,982,61,107);
        break;
    case 8:
        setSprite(1071,765,62,115);
        if(_posY + _tailleSprite.y + _vsaut >= _scene.getBottom()){
            _cptSauter ++;
        }
        break;
    case 9:
        _cptSauter =0;
        setSprite(2,423,66,108);
        _posY=_scene.getBottom()-_tailleSprite.y;
        _vsaut = -40;
        rotate(champEnnemi);
        fini = true;
        break;
    }
    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.8));
	_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);

	_sprite.setPosition(_posX,_posY);
    keepInWalls();
    return fini;
}

void Greg::accroupi(bool garde)//ok
{
	_cptStatic=0;
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delaiAnim=35;
    if(_cptAccroupi==0)
    {
    	if(timeAnim>delaiAnim)
    	{
    		_clockAnim.restart();
    		_cptAccroupi++;
    		setSprite(73,530,62,82);

			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.9,_tailleSprite.y));
			_hurtbox.setPosition(_posX,_posY);
    	}
    }else
    {
    	if(timeAnim>delaiAnim)
    	{
    		_clockAnim.restart();
    		if(garde==true)
	    		setSprite(212,4674,64,76);
	    	else
    		{
    			setSprite(142,537,62,75);
    			_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.8,_tailleSprite.y*0.9));
    			_hurtbox.setPosition(_posX+_tailleSprite.x*0.1,_posY+_tailleSprite.y*0.1);
    		}
    	}
    }
    _posY=_scene.getBottom()-_tailleSprite.y;
    _sprite.setPosition(_posX,_posY);
}

bool Greg::punch(Personnage& champEnnemi,int* degats,int& energie)//ok
{
	_cptStatic=0;
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delaiAnim=60;
    bool fini=false;

    if(timeAnim > delaiAnim)
    {
		switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(3,1310,74,102);

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);

            if (!_effetSonore.openFromFile("musique/Greg/coup_poing.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
			break;
		case 1:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(80,1308,102,104);
		    _hitbox.setSize(sf::Vector2f(40*SCALE,20*SCALE));
		    _hitbox.setPosition(_posX+60*SCALE*_orientation,_posY+10*SCALE);
			break;
		case 2:
		    _cptAction++;
		    _clockAnim.restart();
		    setSprite(3,1310,74,102);

		    _hitbox.setSize(sf::Vector2f(0,0));
			break;
		case 3:
			_cptAction=0;
			_clockAnim.restart();
			setSprite(2,360,66,105);
			fini=true;
			break;
		}
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=5;
		energie+=10;

		if(champEnnemi.getPosX()==_scene.getRightLimit())
			_posX-=25*SCALE*_orientation;
	}

	_posY=_scene.getBottom()-_tailleSprite.y;
    _sprite.setPosition(_posX,_posY);
	keepInWalls();
	return fini;
}

bool Greg::sautPunch(Personnage& champEnnemi,int* degats,int& energie)
{
	_cptStatic=0;
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delaiAnim=60,deplacement=125;
    bool fini=false;

    if(timeAnim>delaiAnim)
    {
	    switch(_cptAction)
	    {
	    case 0:
	    	_cptAction ++;
		    _clockAnim.restart();
		    setSprite(150,1794,55,73);

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);

            if (!_effetSonore.openFromFile("musique/Greg/coup_poing.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
			break;
		case 1:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(206,1794,74,79);
			break;
		case 2:
			_cptAction++;
			_clockAnim.restart();
			setSprite(281,1794,98,72);

			_hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.4,_tailleSprite.y*0.5));
			_hitbox.setPosition(_posX+_tailleSprite.x*0.6*_orientation,_posY+_tailleSprite.y*0.2);
			break;
		case 3:
		    _cptAction=0;
		    _clockAnim.restart();
		    setSprite(281,1794,98,72);
		    fini=true;

		    _hitbox.setSize(sf::Vector2f(0,0));
			break;
	    }
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=5;
		energie+=10;

		if(champEnnemi.getPosX()==_scene.getRightLimit())
			_posX-=25*SCALE*_orientation;
	}

    keepInWalls();
    return fini;
}

bool Greg::punchSP(sf::Sprite& inutile,Personnage& champEnnemi, int* degats,int& energie)
{
	if(energie<25)
	{
		energie=-100;
		return true;
	}

	_cptStatic=0;
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delaiAnim=50,deplacement=_tailleSprite.x/2;
    bool fini=false;


    if(timeAnim > delaiAnim)
    {
		collisionsaut(champEnnemi,deplacement);

		switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(8,3795,66,86);

		    _posY=_scene.getBottom()-_tailleSprite.y;
		    if (!_effetSonore.openFromFile("musique/Greg/shoryuken.ogg"))
		        std::cout<<"erreur musique";
			_effetSonore.play();
			break;
		case 1:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(83,3791,78,90);

		    _posY=_scene.getBottom()-_tailleSprite.y;

		    _hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.2,_tailleSprite.y*0.4));
		    _hitbox.setPosition(_posX+_tailleSprite.x*0.8*_orientation,_posY+_tailleSprite.y*0.1);
			break;
		case 2:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(176,3754,62,129);

		    _posX+=deplacement*_orientation;
		    _posY=_scene.getBottom()-_tailleSprite.y;

		    _hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.4,_tailleSprite.y*0.5));
		    _hitbox.setPosition(_posX+_tailleSprite.x*0.6*_orientation,_posY);
			break;
		case 3:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(244,3686,55,121);

		    _posX+=deplacement*_orientation;
		    _posY-=_tailleSprite.y/2;

		    _hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.4,_tailleSprite.y*0.5));
		    _hitbox.setPosition(_posX+_tailleSprite.x*0.6*_orientation,_posY);
			break;
		case 4:
			if(timeAnim>delaiAnim*2)
			{
				_cptAction++;
			    _clockAnim.restart();
			    setSprite(315,3697,61,117);

			    _posX+=deplacement/2*_orientation;
			    _posY+=_tailleSprite.y/10;

			    _hitbox.setSize(sf::Vector2f(0,0));
			}
			break;
		case 5:
		    _cptAction++;
		    _clockAnim.restart();
		    setSprite(380,3779,63,99);

		    _posY=_scene.getBottom()-_tailleSprite.y;
			break;
		case 6:
		    _cptAction=0;
		    _clockAnim.restart();
		    setSprite(2,433,66,98);
		    fini=true;
		    energie-=25;

		    _posY=_scene.getBottom()-_tailleSprite.y;
		    break;
		}

		if( (_orientation==1 && _posX+_tailleSprite.x >= champEnnemi.getPosX()-champEnnemi.getHurtbox().getGlobalBounds().width)
              || (_orientation==-1 && _posX-_tailleSprite.x <= champEnnemi.getPosX()+champEnnemi.getHurtbox().getGlobalBounds().width) )
	    {
	        _posX=champEnnemi.getPosX()-(champEnnemi.getHurtbox().getGlobalBounds().width+_tailleSprite.x+deplacement)*_orientation;
	    }

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

bool Greg::kick(Personnage& champEnnemi,int* degats,int& energie)
{
	_cptStatic=0;
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delaiAnim=70;
    bool fini=false;

    if(timeAnim > delaiAnim)
    {
		switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(497,2550,67,103);

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);

            if (!_effetSonore.openFromFile("musique/Greg/coup_pied.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
			break;
		case 1:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(566,2550,65,103);
			break;
		case 2:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(656,2550,118,103);

    		_hitbox.setSize(sf::Vector2f(80*SCALE,22*SCALE));
		    _hitbox.setPosition(_posX+36*SCALE*_orientation,_posY);
			break;
		case 3:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(775,2550,65,103);

		    _hitbox.setSize(sf::Vector2f(0,0));
			break;
		case 4:
		    _cptAction =0;
		    _clockAnim.restart();
		    setSprite(867,2550,65,103);
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
	_posY=_scene.getBottom()-_tailleSprite.y;
    _sprite.setPosition(_posX,_posY);
	keepInWalls();
	return fini;
}

bool Greg::sautKick(Personnage& champEnnemi,int* degats,int& energie)
{
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delaiAnim=60,deplacement=_scene.getBottom()/6;
    bool fini=false;

	if(timeAnim>delaiAnim)
    {
	    switch(_cptAction)
	    {
	    case 0:
	    	_cptAction ++;
		    _clockAnim.restart();
		    setSprite(228,3022,58,117);

		    _hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
			_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);

            if (!_effetSonore.openFromFile("musique/Greg/coup_pied.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
			break;
	    case 1:
	    	_cptAction ++;
		    _clockAnim.restart();
		    setSprite(298,3013,59,98);
			break;
		case 2:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(367,3020,92,107);

		    _hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.2));
		    _hitbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.35);
			break;
		case 3:
			_cptAction =0;
			_clockAnim.restart();
			setSprite(472,3036,61,102);
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

bool Greg::kickSP(Personnage& champEnnemi, int* degats,int& energie)
{
	if(energie<25)
	{
		energie=-100;
		return true;
	}

	_cptStatic=0;
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delaiAnim=70,deplacementY=_scene.getBottom()/7,deplacementX=50*_orientation;
    bool fini=false;

    if(timeAnim > delaiAnim)
    {
		switch (_cptAction)
		{
		case 0:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(1,3039,71,110);
		    _posY=_scene.getBottom()-_tailleSprite.y;

            if (!_effetSonore.openFromFile("musique/Greg/tatsumaki.ogg"))
                std::cout<<"erreur musique";
            _effetSonore.play();
			break;
		case 1:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(75,3036,61,87);
		    _posY-=deplacementY;
			break;
		case 2:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(148,3025,54,68);
		    _posY-=deplacementY;
			break;
		case 3:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(228,3022,58,77);
		    _posY-=deplacementY/2;
			break;
		case 4:
			_cptAction++;
			_clockAnim.restart();
			setSprite(298,3013,59,98);
			_posY+=deplacementY;
			break;
		case 5:
			_cptAction++;
		    _clockAnim.restart();
		    setSprite(366,3020,93,108);
		    _posY+=deplacementY;

		    _hitbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.3));
			_hitbox.setPosition(_posX+_tailleSprite.x*0.4*_orientation,_posY+_tailleSprite.y*0.4);
			break;
		case 6:
		    _cptAction++;
		    _clockAnim.restart();
		    setSprite(472,3036,61,102);
		    _posY=_scene.getBottom()-_tailleSprite.y;
		    _hitbox.setSize(sf::Vector2f(0,0));
			break;
		case 7:
		    _cptAction=0;
		    _clockAnim.restart();
		    setSprite(538,3057,63,89);
		    fini=true;
		    energie-=25;
		    _posY=_scene.getBottom()-_tailleSprite.y;
			break;
		}
		_posX+=deplacementX;
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

bool Greg::SP(sf::Sprite& bouleFeu,Personnage& champEnnemi,int* degats,int& energie)
{
	if(energie<50)
	{
		energie=-100;
		return true;
	}

	_cptStatic=0;
	sf::Time elapsed = _clockAnim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    int delaiAnim=70;
    bool fini=false;

    if(timeAnim > delaiAnim)
    {
	    switch (_cptAction)
		{
		case 0:
			if (!_effetSonore.openFromFile("musique/Greg/hadouken.ogg"))
		        std::cout<<"erreur musique";
		    _effetSonore.play();

		    _cptAction++;
		    _clockAnim.restart();
		    setSprite(10,3493,74,90);

		    bouleFeu.setPosition(10,10);
		    bouleFeu.setTexture(_texture);
			bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
			break;
		case 1:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(890,3520,91,90);
		    _posX-=1*SCALE*_orientation;
			break;
		case 2:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(986,3520,111,90);
		    _posX-=20*SCALE*_orientation;
			break;
		case 3:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(742,3630,115,90);
		    _posX-=4*SCALE*_orientation;
		    break;
		case 4:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(993,3630,117,90);
		    _posX-=2*SCALE*_orientation;
		    break;
		case 5:
		    _cptAction ++;
		    _clockAnim.restart();
		    setSprite(1124,3636,98,85);
		    _posX+=20*SCALE*_orientation;
		    break;
		case 6:
		    _cptAction ++;
		    _clockAnim.restart();
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
		energie-=50;
		_cptAction=0;
	}

	if(collisioncoup(champEnnemi))
	{
		*degats=30;
		bouleFeu.setTextureRect(sf::IntRect(0,0,0,0));
		fini=true;
		energie-=50;
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
