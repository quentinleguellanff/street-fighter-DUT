#include "Ken.h"

using namespace std;

Ken::Ken()
{
    //ctor
}

Ken::Ken(int orientation,sf::RectangleShape& sol){
    _orientation = orientation;
    if (!_Texture.loadFromFile("sprite/sprite_Ken.png"))//load de la texture du personnage
    {
        cout << "erreur" << endl;
    }
    _spritePerso.setTexture(_Texture);
    _scale = 3.5;
    _spritePerso.setScale(_scale*_orientation,_scale);
    _hurtbox.setScale(_orientation,1);
    _hitbox.setSize(sf::Vector2f(12.f,12.f));
    _posX = 600.f;
    _sol = sol;
    //cout << "position du sol en y " << _sol.getPosition().y << endl;
    _cptanimstatic = 0;
    _cptanimavancer = 0;
    _cptAnimCoupPoing = 0;
    _cptanimprendcoup = 0;
    _cptanimjump = 0;
    _vsaut = -40;
    setSprite(24,32,66,98);
    if(orientation == 1){
        _spritePerso.setPosition(20.f,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
    }
    else{
        _spritePerso.setPosition(1420.f,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
    }
    _hurtbox.setScale(_orientation,1);
    _hitbox.setScale(_scale*_orientation,_scale);


}

void Ken::debout(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi)
{
    _cptanimjump = 0;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    if(timeanim > 100)
    {
        _cptanimstatic++;
        _clockanim.restart();
    }
    switch (_cptanimstatic)
    {
    case 0:
        setSprite(24,32,66,98);
        break;
    case 1:
        setSprite(98,32,66,98);
        break;
    case 2:
        setSprite(171,32,66,98);
        break;
    case 3:
        setSprite(246,32,66,98);
        break;
    case 4:
        setSprite(392,32,66,98);
        break;
    case 5:
        _cptanimstatic=0;
        //setSprite(347,433,66,98);
        break;
    }
    _spritePerso.setPosition(_spritePerso.getPosition().x,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
    _hurtbox.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width,_spritePerso.getGlobalBounds().height));
    ResteDansFenetre();
    window.draw(_spritePerso);
    //window.draw(_hurtbox);
}

void Ken::avancer(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi){
    if(_cptanimavancer > 5){
        _cptanimavancer = 0;
    }
	sf::Time elapsed1 = _clockanim.getElapsedTime();
    int timeAnim = elapsed1.asMilliseconds();

    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();
    _vitesseX = 12 * _orientation;
    ResteDansFenetre();
    collision(hurtboxEnnemi);
    if(timeMove > 10){
        deplacer(_vitesseX);
        _clockmove.restart();
    }
    if(timeAnim>50){
        _cptanimavancer ++;
        _clockanim.restart();
    }

    int delai=70;
    int deplacement=60;
	    switch (_cptanimavancer)
	    {
	    case 0:
            if(timeAnim>20){
                _cptanimavancer ++;
                _clockanim.restart();
            }
    		setSprite(24,146,63,96);
	    	break;
	    case 1:
		    setSprite(95,146,70,96);
	    	break;
	    case 2:
		    setSprite(173,146,69,96);
	    	break;
	    case 3:
		    setSprite(242,146,67,96);
	    	break;
	    case 4:
		    setSprite(308,146,62,96);
	    	break;
	    case 5:
            setSprite(370,146,64,96);
            break;
	    }
    _spritePerso.setPosition(_spritePerso.getPosition().x,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width,_spritePerso.getGlobalBounds().height));
    _spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _hurtbox.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    window.draw(_spritePerso);
    window.draw(_hurtbox);
}

void Ken::reculer(sf::RenderWindow& window){
    if(_cptanimavancer > 5){
        _cptanimavancer = 0;
    }
    sf::Time elapsed1 = _clockanim.getElapsedTime();
    int timeAnim = elapsed1.asMilliseconds();

    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();
    _vitesseX = -10 * _orientation;
    ResteDansFenetre();
    //collision(hurtboxEnnemi);
    if(timeMove > 10){
        if(_cptanimavancer < 6){
            deplacer(_vitesseX);
	        _clockmove.restart();
        }
    }
    if(timeAnim>50){
        _cptanimavancer ++;
        _clockanim.restart();
    }
    	    switch (_cptanimavancer)
	    {
	    case 0:
            if(timeAnim>20){
                _cptanimavancer ++;
                _clockanim.restart();
            }
    		setSprite(442,146,62,96);
	    	break;
	    case 1:
		    setSprite(512,146,63,96);
	    	break;
	    case 2:
		    setSprite(582,146,54,96);
	    	break;
	    case 3:
		    setSprite(644,146,54,96);
	    	break;
	    case 4:
		    setSprite(706,146,61,96);
	    	break;
	    case 5:
            setSprite(774,146,63,96);
            break;
	    }
    _spritePerso.setPosition(_spritePerso.getPosition().x,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width,_spritePerso.getGlobalBounds().height+7));
    _spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _hurtbox.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    window.draw(_spritePerso);

}

bool Ken::coupDePoing(sf::RectangleShape hurtboxEnnemi,bool& touche,sf::RenderWindow& window){
    sf::Time elapsed1 = _clockanim.getElapsedTime();
    int timeAnim = elapsed1.asMilliseconds();

    if(timeAnim>40)
	{
	    switch (_cptAnimCoupPoing)
	    {
	    case 0:
		    _cptAnimCoupPoing ++;
		    _clockanim.restart();
    		setSprite(30,263,78,98);
	    	break;
	    case 1:
		    _cptAnimCoupPoing ++;
		    _clockanim.restart();
		    setSprite(116,263,107,98);
            _hitbox.setPosition(_spritePerso.getPosition().x+90*_scale*_orientation,_spritePerso.getPosition().y+14*_scale);
            if(collisioncoup(hurtboxEnnemi)){
                touche = true;
            }
	    	break;
	    case 2:
		    _cptAnimCoupPoing ++;
		    _clockanim.restart();
    		setSprite(231,263,77,98);
	    	break;
        case 3:
            _cptAnimCoupPoing = 0;
            setSprite(316,263,66,98);
            _clockanim.restart();
            return false;
	    }
	}
	_spritePerso.setPosition(_spritePerso.getPosition().x,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width,_spritePerso.getGlobalBounds().height));
    //_spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _hurtbox.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _hitbox.setPosition(_spritePerso.getPosition().x+90*_scale*_orientation,_spritePerso.getPosition().y+14*_scale);
	window.draw(_spritePerso);
	//window.draw(_hurtbox);
	window.draw(_hitbox);
	return true;


}

void Ken::prendCoup(bool& touche,sf::RenderWindow& window){
    sf::Time elapsed1 = _clockanim.getElapsedTime();
    int timeAnim = elapsed1.asMilliseconds();

    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();

    _vitesseX = -20 * _orientation;
    ResteDansFenetre();
    if(timeMove > 20){
         switch (_cptanimprendcoup)
	    {
	    case 1:
		    deplacer(_vitesseX);
            _clockmove.restart();
	    	break;
	    case 2:
		    deplacer(_vitesseX);
            _clockmove.restart();
	    	break;
	    }
    }

    if(timeAnim>70)
	{
	    switch (_cptanimprendcoup)
	    {
	    case 0:
		    _cptanimprendcoup ++;
		    _clockanim.restart();
    		setSprite(24,3287,70,92);
	    	break;
	    case 1:
		    _cptanimprendcoup ++;
            setSprite(101,3287,73,92);
		    _clockanim.restart();
	    	break;
	    case 2:
		    _cptanimprendcoup ++;
    		setSprite(24,3287,70,92);
		    _clockanim.restart();
	    	break;
        case 3:
		    _cptanimprendcoup = 0;
		    _clockanim.restart();
		    touche = false;
	    	break;
	    }
	}
	_spritePerso.setPosition(_spritePerso.getPosition().x,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
	window.draw(_spritePerso);
	_hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width,_spritePerso.getGlobalBounds().height));
    //_spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _hurtbox.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
	window.draw(_hurtbox);
}

bool Ken::sauter(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi){
    float v_grav = 1.7;
    _vitesseX = 20;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();

    if(timeMove > 10){
        _vsaut += v_grav;
        collisionsaut(hurtboxEnnemi);
        _spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y+_vsaut);
        _clockmove.restart();
    }
    if(timeAnim > 70){
        if(_cptanimjump < 6)
            _cptanimjump++;
        _clockanim.restart();
    }
    switch (_cptanimjump)
    {
        case 0:
            if(timeAnim > 20){
                 _cptanimjump ++;
                 _clockanim.restart();
            }
        setSprite(24,1227,63,89);
        break;
    case 1:
        setSprite(95,1208,62,108);
        break;
    case 2:
        setSprite(817,1228,64,88);
        break;
    case 3:
        setSprite(889,1246,61,70);
        break;
    case 4:
        setSprite(958,1251,61,65);
        break;
    case 5:
        setSprite(1027,1230,64,86);
        break;
    case 6:
        setSprite(676,1202,62,114);
        if(_spritePerso.getPosition().y + _spritePerso.getGlobalBounds().height + _vsaut >= _sol.getPosition().y){
            _cptanimjump ++;
        }
        break;
    case 7:
        _cptanimjump =0;
        setSprite(24,1227,63,89);
        _spritePerso.setPosition(_spritePerso.getPosition().x,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
        _vsaut = -40;
        return false;
        break;
    }
    window.draw(_spritePerso);
    return true;
}

bool Ken::sauterAvancer(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi){
     float v_grav = 1.7;
    _vitesseX = 15*_orientation;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();

    if(timeMove > 10){
        _vsaut += v_grav;
        ResteDansFenetre();
        collisionsaut(hurtboxEnnemi);
        _spritePerso.setPosition(_spritePerso.getPosition().x+_vitesseX,_spritePerso.getPosition().y+_vsaut);
        _hurtbox.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
        _clockmove.restart();
    }
    if(timeAnim > 70){
        if(_cptanimjump < 8 && _cptanimjump != 2){
            if(_cptanimjump == 1)
                _spritePerso.setPosition(_spritePerso.getPosition().x+25*_orientation,_spritePerso.getPosition().y-5);
            _cptanimjump++;
            _clockanim.restart();
        }

        if(_cptanimjump == 4){
            _spritePerso.setPosition(_spritePerso.getPosition().x-100*_orientation,_spritePerso.getPosition().y+50);
        }
        else if(_cptanimjump == 5){
            _spritePerso.setPosition(_spritePerso.getPosition().x+100*_orientation,_spritePerso.getPosition().y-50);
        }
        else if(_cptanimjump == 6){
            _spritePerso.setPosition(_spritePerso.getPosition().x-140*_orientation,_spritePerso.getPosition().y+100);
        }
        else if(_cptanimjump == 7){
            _spritePerso.setPosition(_spritePerso.getPosition().x+70*_orientation,_spritePerso.getPosition().y-70);
        }
    }
    switch (_cptanimjump)
    {
        case 0:
            if(timeAnim > 20){
                 _cptanimjump ++;
                 _clockanim.restart();
            }
        setSprite(24,1227,63,89);
        break;
    case 1:
        setSprite(95,1208,62,108);
        break;
    case 2:
        setSprite(161,1208,61,108);
            if(timeAnim > 200){
                 _cptanimjump ++;
                 _clockanim.restart();
            }
        break;
    case 3:
        setSprite(230,1229,60,87);
        break;
    case 4:
        setSprite(298,1268,98,48);
        break;
    case 5:
        setSprite(403,1239,59,77);
        break;
    case 6:
        setSprite(470,1258,115,58);
        break;
    case 7:
        setSprite(593,1222,79,94);
        break;
    case 8:
        setSprite(676,1202,62,114);
        if(_spritePerso.getPosition().y + _spritePerso.getGlobalBounds().height + _vsaut >= _sol.getPosition().y){
            _cptanimjump ++;
        }
        break;
    case 9:
        _cptanimjump =0;
        setSprite(24,1227,63,89);
        _spritePerso.setPosition(_spritePerso.getPosition().x+45*_orientation,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
        if(_spritePerso.getPosition().x + _spritePerso.getGlobalBounds().width > 1440){
            _spritePerso.setPosition(1440- _spritePerso.getGlobalBounds().width,_spritePerso.getPosition().y);
        }
        else if(_spritePerso.getPosition().x <= _spritePerso.getGlobalBounds().width){
             _spritePerso.setPosition(_spritePerso.getGlobalBounds().width,_spritePerso.getPosition().y);
        }
        cout << _spritePerso.getPosition().x << endl;
        _vsaut = -40;
        return false;
        break;
    }
    window.draw(_spritePerso);
    window.draw(_hurtbox);
    return true;
}

bool Ken::sauterArriere(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi){
float v_grav = 1.7;
    _vitesseX = -15*_orientation;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();

    if(timeMove > 10){
        _vsaut += v_grav;
        ResteDansFenetre();
        collisionsaut(hurtboxEnnemi);
        _spritePerso.setPosition(_spritePerso.getPosition().x+_vitesseX,_spritePerso.getPosition().y+_vsaut);
        _hurtbox.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
        _clockmove.restart();
    }
    if(timeAnim > 70){
        if(_cptanimjump < 8){
            if(_cptanimjump == 1)
                _spritePerso.setPosition(_spritePerso.getPosition().x+25*_orientation,_spritePerso.getPosition().y-5);
            _cptanimjump++;
            _clockanim.restart();
        }
        if(_cptanimjump == 2){
            _spritePerso.setPosition(_spritePerso.getPosition().x-100*_orientation,_spritePerso.getPosition().y);
        }
        else if(_cptanimjump == 3){
            _spritePerso.setPosition(_spritePerso.getPosition().x-50*_orientation,_spritePerso.getPosition().y+50);
        }
        else if(_cptanimjump == 4){
            _spritePerso.setPosition(_spritePerso.getPosition().x+100*_orientation,_spritePerso.getPosition().y-50);
        }
        else if(_cptanimjump == 5){
            _spritePerso.setPosition(_spritePerso.getPosition().x-50*_orientation,_spritePerso.getPosition().y+50);
        }
        else if(_cptanimjump == 6){
            _spritePerso.setPosition(_spritePerso.getPosition().x+75*_orientation,_spritePerso.getPosition().y-50);
        }
        else if(_cptanimjump == 7){
            _spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y-30);
        }
    }
    switch (_cptanimjump)
    {
        case 0:
            if(timeAnim > 20){
                 _cptanimjump ++;
                 _clockanim.restart();
            }
        setSprite(651,829,63,89);
        break;
    case 1:
        setSprite(791,775,64,88);
        break;
    case 2:
        setSprite(1689,747,72,94);
        break;
    case 3:
        setSprite(1565,768,123,52);
        break;
    case 4:
        setSprite(1510,736,55,78);
        break;
    case 5:
        setSprite(1410,759,93,47);
        break;
    case 6:
        setSprite(1488,927,61,90);
        break;
    case 7:
        setSprite(518,982,61,107);
        break;
    case 8:
        setSprite(1071,765,62,115);
        if(_spritePerso.getPosition().y + _spritePerso.getGlobalBounds().height + _vsaut >= _sol.getPosition().y){
            _cptanimjump ++;
        }
        break;
    case 9:
        _cptanimjump =0;
        setSprite(2,433,66,98);
        if(_spritePerso.getPosition().x + _spritePerso.getGlobalBounds().width > 1440){
            _spritePerso.setPosition(1440,_spritePerso.getPosition().y);
        }
        else if(_spritePerso.getPosition().x < 0){
             _spritePerso.setPosition(0,_spritePerso.getPosition().y);
        }
        _spritePerso.setPosition(_spritePerso.getPosition().x,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
        _vsaut = -40;
        return false;
        break;
    }
    window.draw(_spritePerso);
    window.draw(_hurtbox);
    return true;
}

void Ken::seBaisser(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi){
}
Ken::~Ken()
{
    //dtor
}
