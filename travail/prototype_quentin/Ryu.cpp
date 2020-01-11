#include "Ryu.h"
#include "Personnage.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace std;

Ryu::Ryu(int orientation,sf::RectangleShape& sol)
{
    _orientation = orientation;
    if (!_Texture.loadFromFile("sprite/sprite_ryu.png"))//load de la texture du personnage
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
    setSprite(2,433,66,98);
    if(orientation == 1){
        _spritePerso.setPosition(20.f,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
    }
    else{
        _spritePerso.setPosition(1420.f,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
    }


    _hurtbox.setScale(_orientation,1);
    _hitbox.setScale(_scale*_orientation,_scale);

}

void Ryu::debout(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi){
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
        setSprite(2,433,66,98);
        break;
    case 1:
        setSprite(71,433,66,98);
        break;
    case 2:
        setSprite(140,433,66,98);
        break;
    case 3:
        setSprite(209,433,66,98);
        break;
    case 4:
        setSprite(279,433,64,98);
        break;
    case 5:
        _cptanimstatic=0;
        setSprite(347,433,66,98);
        break;
    }
    _hurtbox.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width,_spritePerso.getGlobalBounds().height));
    ResteDansFenetre();
    window.draw(_spritePerso);
    //window.draw(_hurtbox);
}

void Ryu::avancer(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi){
    //_posY=_scene.getBottom()-_tailleSprite.y;
    if(_cptanimavancer > 5){
        _cptanimavancer = 0;
    }
	sf::Time elapsed1 = _clockanim.getElapsedTime();
    int timeAnim = elapsed1.asMilliseconds();
    //cout << timeAnim << endl;

    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();
    //_spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _vitesseX = 12 * _orientation;
    ResteDansFenetre();
    collision(hurtboxEnnemi);
    if(timeMove > 10){
        if(_cptanimavancer < 6){
            deplacer(_vitesseX);
	        _clockmove.restart();
        }
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
    		setSprite(-3,634,72,96);
	    	break;
	    case 1:
            if(timeAnim>50){
                _cptanimavancer ++;
                _clockanim.restart();
            }
		    setSprite(70,634,69,96);
	    	break;
	    case 2:
            if(timeAnim>50){
                _cptanimavancer ++;
                _clockanim.restart();
            }
		    setSprite(143,634,69,96);
	    	break;
	    case 3:
            if(timeAnim>50){
                _cptanimavancer ++;
                _clockanim.restart();
            }
		    setSprite(212,634,68,96);
	    	break;
	    case 4:
            if(timeAnim>50){
                _cptanimavancer ++;
                _clockanim.restart();
            }
		    setSprite(281,634,69,96);
	    	break;
	    case 5:
            if(timeAnim>50){
                _cptanimavancer ++;
                _clockanim.restart();
            }
            setSprite(350,634,71,96);
            break;
	    }

	//_sprite.setPosition(_posX,_posY);
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width,_spritePerso.getGlobalBounds().height+7));
    _spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _hurtbox.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    //rotate(champEnnemi);
    window.draw(_spritePerso);
    cout << _spritePerso.getPosition().x << endl;
    //cout << _spritePerso.getPosition().y + _spritePerso.getGlobalBounds().height +7 << endl;
    //window.draw(_hurtbox);
}

void Ryu::reculer(sf::RenderWindow& window){
    if(_cptanimavancer > 3){
        _cptanimavancer = 0;
    }
    sf::Time elapsed1 = _clockanim.getElapsedTime();
    int timeAnim = elapsed1.asMilliseconds();

    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();
    _spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _vitesseX = -10 * _orientation;
    ResteDansFenetre();
    if(timeMove > 10){
        if(_cptanimavancer < 4){
            deplacer(_vitesseX);
	        _clockmove.restart();
        }
    }

    if(timeAnim>70)
	{
	    switch (_cptanimavancer)
	    {
	    case 0:
		    _cptanimavancer ++;
		    _clockanim.restart();
    		setSprite(427,634,63,96);
	    	break;
	    case 1:
		    _cptanimavancer ++;
		    _clockanim.restart();
		    setSprite(497,634,61,96);
	    	break;
	    case 2:
		    _cptanimavancer ++;
		    _clockanim.restart();
		    setSprite(564,634,55,96);
	    	break;
	    case 3:
		    _cptanimavancer = 0;
		    _clockanim.restart();
		    setSprite(632,634,55,96);
	    	break;
	    }
	}

    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width,_spritePerso.getGlobalBounds().height+7));
    _hurtbox.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    window.draw(_spritePerso);
    window.draw(_hurtbox);
}

bool Ryu::coupDePoing(sf::RectangleShape hurtboxEnnemi,bool& touche,sf::RenderWindow& window){

    sf::Time elapsed1 = _clockanim.getElapsedTime();
    int timeAnim = elapsed1.asMilliseconds();

    if(timeAnim>40)
	{
	    switch (_cptAnimCoupPoing)
	    {
	    case 0:
		    _cptAnimCoupPoing ++;
		    _clockanim.restart();
    		setSprite(3,1315,74,98);
	    	break;
	    case 1:
		    _cptAnimCoupPoing ++;
		    _clockanim.restart();
		    setSprite(80,1315,102,98);
            _hitbox.setPosition(_spritePerso.getPosition().x+90*_scale*_orientation,_spritePerso.getPosition().y+14*_scale);
            if(collisioncoup(hurtboxEnnemi)){
                touche = true;
            }
	    	break;
	    case 2:
		    _cptAnimCoupPoing ++;
		    _clockanim.restart();
    		setSprite(3,1315,74,98);
	    	break;
        case 3:
            _cptAnimCoupPoing = 0;
            setSprite(2,433,66,98);
            _clockanim.restart();
            return false;
	    }
	}
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width,_spritePerso.getGlobalBounds().height));
    //_spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _hurtbox.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _hitbox.setPosition(_spritePerso.getPosition().x+90*_scale*_orientation,_spritePerso.getPosition().y+14*_scale);
	window.draw(_spritePerso);
	//window.draw(_hurtbox);
	window.draw(_hitbox);
	return true;
}

void Ryu::prendCoup(bool& touche, sf::RenderWindow& window){

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
    		setSprite(574,4752,73,98);
	    	break;
	    case 1:
		    _cptanimprendcoup ++;
            setSprite(325,4752,73,98);
		    _clockanim.restart();
	    	break;
	    case 2:
		    _cptanimprendcoup ++;
    		setSprite(574,4752,73,98);
		    _clockanim.restart();
	    	break;
        case 3:
		    _cptanimprendcoup = 0;
		    _clockanim.restart();
		    touche = false;
	    	break;
	    }
	}
	window.draw(_spritePerso);
	_hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width,_spritePerso.getGlobalBounds().height));
    //_spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _hurtbox.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
	window.draw(_hurtbox);

}

bool Ryu::sauter(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi){
    float v_grav = 1.7;
    _vitesseX = 20;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();

    if(timeMove > 10){
        _vsaut += v_grav;
        _spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y+_vsaut);
        _clockmove.restart();
    }
    if(timeAnim > 100){
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
        setSprite(651,829,63,89);
        break;
    case 1:
        setSprite(714,818,70,108);
        break;
    case 2:
        setSprite(791,775,64,88);
        break;
    case 3:
        setSprite(861,748,61,70);
        break;
    case 4:
        setSprite(925,739,61,65);
        break;
    case 5:
        setSprite(1000,750,64,86);
        break;
    case 6:
        setSprite(1071,765,62,115);
        if(_spritePerso.getPosition().y + _spritePerso.getGlobalBounds().height + _vsaut >= _sol.getPosition().y){
            _cptanimjump ++;
        }
        break;
    case 7:
        _cptanimjump =0;
        setSprite(2,433,66,98);
        _spritePerso.setPosition(_spritePerso.getPosition().x,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
        _vsaut = -40;
        return false;
        break;
    }
    window.draw(_spritePerso);
    return true;
}

bool Ryu::sauterAvancer(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi){
     float v_grav = 1.7;
    _vitesseX = 15;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();

    if(timeMove > 10){
        _vsaut += v_grav;
        ResteDansFenetre();
        _spritePerso.setPosition(_spritePerso.getPosition().x+_vitesseX*_orientation,_spritePerso.getPosition().y+_vsaut);
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
        setSprite(651,829,63,89);
        break;
    case 1:
        setSprite(714,818,70,108);
        break;
    case 2:
        setSprite(1348,794,62,106);
            if(timeAnim > 200){
                 _cptanimjump ++;
                 _clockanim.restart();
            }
        break;
    case 3:
        setSprite(1488,927,61,90);
        break;
    case 4:
        setSprite(1410,759,93,47);
        break;
    case 5:
        setSprite(1510,736,55,78);
        break;
    case 6:
        setSprite(1565,768,123,52);
        break;
    case 7:
        setSprite(1689,747,72,94);
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
        _spritePerso.setPosition(_spritePerso.getPosition().x+45*_orientation,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
        cout << _spritePerso.getPosition().x << endl;
        _vsaut = -40;
        return false;
        break;
    }
    window.draw(_spritePerso);
    //window.draw(_hurtbox);
    return true;
}

bool Ryu::sauterArriere(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi){
     float v_grav = 1.7;
    _vitesseX = -15;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();

    if(timeMove > 10){
        _vsaut += v_grav;
        ResteDansFenetre();
        _spritePerso.setPosition(_spritePerso.getPosition().x+_vitesseX*_orientation,_spritePerso.getPosition().y+_vsaut);
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
        _spritePerso.setPosition(_spritePerso.getPosition().x,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
        cout << _spritePerso.getPosition().x << endl;
        _vsaut = -40;
        return false;
        break;
    }
    window.draw(_spritePerso);
    //window.draw(_hurtbox);
    return true;
}

Ryu::Ryu(){}

Ryu::~Ryu()
{
    //dtor
}
