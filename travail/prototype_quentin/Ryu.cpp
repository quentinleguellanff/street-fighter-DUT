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
    cout << "position du sol en y " << _sol.getPosition().y << endl;
    _cptanimstatic = 0;
    _cptanimavancer = 0;
    _cptAnimCoupPoing = 0;
    _cptanimprendcoup = 0;
    _cptanimjump = 0;
    _vsaut = -75;
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
    if(timeanim > 70)
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

    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();
    //_spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _vitesseX = 30 * _orientation;
    ResteDansFenetre();
    collision(hurtboxEnnemi);
    if(timeMove > 20){

         switch (_cptanimavancer)
	    {
	    case 0:
	        deplacer(_vitesseX);
	        _clockmove.restart();
	    	break;
	    case 1:
	        deplacer(_vitesseX);
            _clockmove.restart();
	    	break;
	    case 2:
	        deplacer(_vitesseX);
            _clockmove.restart();
	    	break;
	    case 3:
	        deplacer(_vitesseX);
            _clockmove.restart();
	    	break;
        case 4:
	        deplacer(_vitesseX);
            _clockmove.restart();
	    	break;
        case 5:
	        deplacer(_vitesseX);
            _clockmove.restart();
	    	break;
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
    cout << _spritePerso.getPosition().y + _spritePerso.getGlobalBounds().height +7 << endl;
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
    _vitesseX = -15 * _orientation;
    ResteDansFenetre();
    if(timeMove > 20){
         switch (_cptanimavancer)
	    {
	    case 0:
            deplacer(_vitesseX);
            _clockmove.restart();
	    	break;
	    case 1:
		    deplacer(_vitesseX);
            _clockmove.restart();
	    	break;
	    case 2:
		    deplacer(_vitesseX);
            _clockmove.restart();
	    	break;
	    case 3:
	        deplacer(_vitesseX);
            _clockmove.restart();
	    	break;
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
    int v_grav = 6;
    _vitesseX = 20;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeAnim = elapsed.asMilliseconds();
    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();

    if(timeMove > 20){
        _vsaut += v_grav;
        _spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y+_vsaut);
        _clockmove.restart();
    }
    if(timeAnim > 80){
	    switch (_cptanimjump)
	    {
            case 0:
		    _cptanimjump ++;
		    _clockanim.restart();
    		setSprite(651,829,63,89);
    		//_spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y+23);
	    	break;
	    case 1:
		    _cptanimjump ++;
            setSprite(714,818,70,108);
		    _clockanim.restart();
		    //_spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y-50);
	    	break;
	    case 2:
            _cptanimjump ++;
    		setSprite(791,775,64,88);
		    _clockanim.restart();
	    	break;
        case 3:
		    _cptanimjump ++;
            setSprite(861,748,61,70);
		    _clockanim.restart();
	    	break;
        case 4:
		    _cptanimjump ++;
            setSprite(925,739,61,65);
		    _clockanim.restart();
	    	break;
        case 5:
		    _cptanimjump ++;
            setSprite(1000,750,64,86);
		    _clockanim.restart();
	    	break;
        case 6:
            _cptanimjump ++;
            setSprite(1071,765,62,115);
            //_spritePerso.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
		    _clockanim.restart();
		    cout << _spritePerso.getPosition().y + _spritePerso.getGlobalBounds().height + _vsaut << endl;
		    cout << _vsaut << endl;
		    //if(_spritePerso.getPosition().y + _spritePerso.getGlobalBounds().height + _vsaut*5 >= _sol.getPosition().y){
            //    _cptanimjump ++;
		    //}
	    	break;
        case 7:
		    _cptanimjump =0;
		    setSprite(2,433,66,98);
		    _spritePerso.setPosition(_spritePerso.getPosition().x,_sol.getPosition().y-_spritePerso.getGlobalBounds().height);
		    _clockanim.restart();
            _vsaut = -75;
		    return false;
	    	break;
	    }
    }
    window.draw(_spritePerso);
    return true;
}

Ryu::Ryu(){}

Ryu::~Ryu()
{
    //dtor
}
