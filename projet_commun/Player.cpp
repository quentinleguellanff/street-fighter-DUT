#include "Player.h"
#include <string>

using namespace std;

Player::Player(int n)
{
	_numPlayer=n;
}

void Player::_resetAttributs()
{
	_posHorizontale=0;
	_posVerticale=0;
	_action=0;
}

void Player::recuperationCommandesP1()    // Commandes pour le player 1
{
	_resetAttributs();

	bool avancer=false,reculer=false, accroupi=false, saut=false,sautAvant=false,sautArriere=false,punch=false,kick=false;

	if (sf::Joystick::isConnected(0))   // Commandes pour manette
	{
		punch=sf::Joystick::isButtonPressed(0, 0);   // touche pour puncher: A
		kick=sf::Joystick::isButtonPressed(0, 1);	 // touche pour kicker:  B
		joystick0_axisX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		joystick0_axisY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		//cout<<"x : "<<joystick0_axisX<<"\t y : "<<joystick0_axisY<<endl;
		if( (joystick0_axisX > -40 && joystick0_axisX < 40) && (joystick0_axisY > -40 && joystick0_axisY < 40))  // Gestion du joystick gauche
		{
			avancer=false;
			reculer=false;
			saut=false;
			sautAvant=false;
			sautArriere=false;
		}
		else if( (joystick0_axisX > 40) && (joystick0_axisY < 45 && joystick0_axisY > -25) )
			avancer=true;
		else if( (joystick0_axisX < -40) && (joystick0_axisY < 45 && joystick0_axisY > -25) )
			reculer=true;
		else if( (joystick0_axisX>-40 && joystick0_axisX<40) && (joystick0_axisY<-40) )
			saut=true;
		else if( (joystick0_axisX<=95 && joystick0_axisX>=40) && (joystick0_axisY<-40) )
		{
			saut=true;
			avancer=true;
		}	
		else if( (joystick0_axisX>=-95 && joystick0_axisX<=-40) && (joystick0_axisY<-40) )
		{
			saut=true;
			reculer=true;
		}
		else if( (joystick0_axisX>-40 && joystick0_axisX<40) && (joystick0_axisY>40) )
			accroupi=true;
	}else   // Commandes clavier au cas ou manette absent
	{
		avancer=sf::Keyboard::isKeyPressed(sf::Keyboard::D);  	// touche pour avancer:    D
		reculer=sf::Keyboard::isKeyPressed(sf::Keyboard::Q);  	// touche pour reculer:    Q
		saut=sf::Keyboard::isKeyPressed(sf::Keyboard::Z);	  	// touche pour sauter:     Z
		accroupi=sf::Keyboard::isKeyPressed(sf::Keyboard::S);	// touche pour accroupir:  S
		punch=sf::Keyboard::isKeyPressed(sf::Keyboard::A);	  	// touche pour puncher:    A
		kick=sf::Keyboard::isKeyPressed(sf::Keyboard::E);	  	// touche pour kicker:     E
	
		if(avancer && reculer)
		{
			avancer=false;
			reculer=false;
		}

	}
	if(kick && punch)
	{
		kick=false;
		punch=false;
	}
	else if(punch && (avancer || reculer || saut))  // A garder tant que 1 seul punch créé
	{
		punch=true;
		avancer=false;
		reculer=false;
		saut=false;
	}else if(kick && (avancer || reculer || saut))  // A garder tant que 1 seul kick créé
	{
		kick=true;
		avancer=false;
		reculer=false;
		saut=false;
	}

	/* Gestion des attributs */

	if(avancer)
		_posHorizontale=1;
	else if(reculer)
		_posHorizontale=-1;
	else
		_posHorizontale=0;


	if(saut)
		_posVerticale=1;
	else if(accroupi)
		_posVerticale=-1;
	else 
		_posVerticale=0;


	if(punch)
		_action=1;
	else if(kick)
		_action=2;
	else
		_action=0;
}

void Player::recuperationCommandesP2()    // Commandes pour le player 2
{
	_resetAttributs();

	bool avancer=false,reculer=false, accroupi=false, saut=false,sautAvant=false,sautArriere=false,punch=false,kick=false;

	if (sf::Joystick::isConnected(1))   // Commandes pour manette
	{
		punch=sf::Joystick::isButtonPressed(0, 0);   // touche pour puncher: A
		kick=sf::Joystick::isButtonPressed(0, 1);	 // touche pour kicker:  B
		joystick1_axisX = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
		joystick1_axisY = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);
		//cout<<"x : "<<joystick1_axisX<<"\t y : "<<joystick1_axisY<<endl;
		if( (joystick1_axisX > -40 && joystick1_axisX < 40) && (joystick1_axisY > -40 && joystick1_axisY < 40))  // Gestion du joystick gauche
		{
			avancer=false;
			reculer=false;
			saut=false;
			sautAvant=false;
			sautArriere=false;
		}
		else if( (joystick1_axisX > 40) && (joystick1_axisY < 45 && joystick1_axisY > -25) )
			reculer=true;
		else if( (joystick1_axisX < -40) && (joystick1_axisY < 45 && joystick1_axisY > -25) )
			avancer=true;
		else if( (joystick1_axisX>-40 && joystick1_axisX<40) && (joystick1_axisY<-40) )
			saut=true;
		else if( (joystick1_axisX<=95 && joystick1_axisX>=40) && (joystick1_axisY<-40) )
		{
			saut=true;
			reculer=true;
		}	
		else if( (joystick0_axisX>=-95 && joystick0_axisX<=-40) && (joystick0_axisY<-40) )
		{
			saut=true;
			avancer=true;
		}
		else if( (joystick0_axisX>-40 && joystick0_axisX<40) && (joystick0_axisY>40) )
			accroupi=true;
	}else   // Commandes clavier au cas ou manette absent
	{
		avancer=sf::Keyboard::isKeyPressed(sf::Keyboard::Left);  	// touche pour avancer:    Left
		reculer=sf::Keyboard::isKeyPressed(sf::Keyboard::Right);  	// touche pour reculer:    Right
		saut=sf::Keyboard::isKeyPressed(sf::Keyboard::Up);	  		// touche pour sauter:     Up
		accroupi=sf::Keyboard::isKeyPressed(sf::Keyboard::Down);	// touche pour accroupir:  Down
		punch=sf::Keyboard::isKeyPressed(sf::Keyboard::P);	  		// touche pour puncher:    P
		kick=sf::Keyboard::isKeyPressed(sf::Keyboard::M);	  		// touche pour kicker:     M
	
		if(avancer && reculer)
		{
			avancer=false;
			reculer=false;
		}

	}
	if(kick && punch)
	{
		kick=false;
		punch=false;
	}
	else if(punch && (avancer || reculer || saut))  // A garder tant que 1 seul punch créé
	{
		punch=true;
		avancer=false;
		reculer=false;
		saut=false;
	}else if(kick && (avancer || reculer || saut))  // A garder tant que 1 seul kick créé
	{
		kick=true;
		avancer=false;
		reculer=false;
		saut=false;
	}

	/* Gestion des attributs */

	if(avancer)
		_posHorizontale=1;
	else if(reculer)
		_posHorizontale=-1;
	else
		_posHorizontale=0;


	if(saut)
		_posVerticale=1;
	else if(accroupi)
		_posVerticale=-1;
	else 
		_posVerticale=0;


	if(punch)
		_action=1;
	else if(kick)
		_action=2;
	else
		_action=0;
}


int Player::getPosHorizontale()
{
	return _posHorizontale;
}

int Player::getPosVerticale()
{
	return _posVerticale;
}

int Player::getAction()
{
	return _action;
}