#include "Ryu.h"
#include "Personnage.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace std;

Ryu::Ryu(int orientation)
{
    _orientation = orientation;
    if (!_Texture.loadFromFile("sprite/sprite_ryu.png"))//load de la texture du personnage
    {
        cout << "erreur" << endl;
    }
    _spritePerso.setTexture(_Texture);
    _scale = 3.5;
    _spritePerso.setScale(_scale*_orientation,_scale);
    _posX = 20.f;
    cout << _posY << endl;

    _cptanimstatic = 0;
    _cptanimavancer = 0;


    //_hurtbox.setScale(_scale*_orientation,_scale);

}

void Ryu::debout(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi){
    _cptanimjump = 0;
    _posY = 900-40-_spritePerso.getGlobalBounds().height -10;
    sf::Time elapsed = _clockanim.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    if(timeanim > 70)
    {
        switch (_cptanimstatic)
	    {
	    case 0:
		    _cptanimstatic ++;
		    _clockanim.restart();
    		setSprite(2,433,66,98);
    		//_posY=40-_tailleSprite.y;
			//_spritePerso.setPosition(_posX,40-_tailleSprite.y);
	    	break;
	    case 1:
		    _cptanimstatic ++;
            _clockanim.restart();
		    setSprite(71,433,66,98);
	    	break;
	    case 2:
		    _cptanimstatic ++;
            _clockanim.restart();
		    setSprite(140,433,66,98);
	    	break;
	    case 3:
            _cptanimstatic ++;
		    _clockanim.restart();
		    setSprite(209,433,66,98);
	    	break;
	    case 4:
            _cptanimstatic ++;
		    _clockanim.restart();
		    setSprite(279,433,64,98);
	    	break;
	    case 5:
		    _cptanimstatic=0;
		    _clockanim.restart();
		    setSprite(347,433,66,98);
	    	break;
	    }
	}
    _hurtbox.setPosition(_spritePerso.getPosition().x,_spritePerso.getPosition().y);
    _hurtbox.setSize(sf::Vector2f(_spritePerso.getGlobalBounds().width,_spritePerso.getGlobalBounds().height));
    ResteDansFenetre();
    _spritePerso.setPosition(_posX,_posY);
    window.draw(_spritePerso);
    window.draw(_hurtbox);
}

void Ryu::avancer(sf::RenderWindow& window,sf::RectangleShape hurtboxEnnemi){
    //_posY=_scene.getBottom()-_tailleSprite.y;
	sf::Time elapsed1 = _clockanim.getElapsedTime();
    int timeAnim = elapsed1.asMilliseconds();

    sf::Time elapsed2 = _clockmove.getElapsedTime();
    int timeMove = elapsed2.asMilliseconds();
    //setSprite(5,634,63,96);
    _vitesseX = 15 * _orientation;
    //collision(hurtboxEnnemi);
    if(timeMove > 30){
         //ResteDansFenetre();
        _spritePerso.setPosition(_spritePerso.getPosition().x+15,_spritePerso.getPosition().y);
        _clockmove.restart();
    }

    int delai=70;
    int deplacement=60;
    if(timeAnim>80)
	{
	    switch (_cptanimavancer)
	    {
	    case 0:
		    _cptanimavancer ++;
		    _clockanim.restart();
    		setSprite(5,634,63,96);
	    	break;
	    case 1:
		    _cptanimavancer ++;
		    _clockanim.restart();
		    setSprite(70,634,69,96);
	    	break;
	    case 2:
		    _cptanimavancer ++;
		    _clockanim.restart();
		    setSprite(144,634,68,96);
	    	break;
	    case 3:
		    _cptanimavancer ++;
		    _clockanim.restart();
		    setSprite(222,634,59,96);
	    	break;
	    case 4:
		    _cptanimavancer ++;
		    _clockanim.restart();
		    setSprite(296,634,54,96);
	    	break;
	    case 5:
            _cptanimavancer = 0;
            _clockanim.restart();
            setSprite(364,634,56,93);
            break;
	    }
	}

	//_sprite.setPosition(_posX,_posY);
    //_hurtbox.setPosition(_posX+_tailleSprite.x*0.2*_orientation,_posY+_tailleSprite.y*0.1);
    //_hurtbox.setSize(sf::Vector2f(_tailleSprite.x*0.6,_tailleSprite.y*0.9));
    //rotate(champEnnemi);

	//ResteDansFenetre();

    window.draw(_spritePerso);


}

Ryu::Ryu(){}

Ryu::~Ryu()
{
    //dtor
}
