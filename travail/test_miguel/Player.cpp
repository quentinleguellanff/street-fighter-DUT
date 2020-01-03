#include "IncludeManager.h"
#include "Player.h"
#include <string>

using namespace std;

Player::Player(int n,sf::RenderWindow& window)
{
	_PV=100;

	_posHorizontale=0;
	_posVerticale=0;
	_action=-1;
	_derniereAction=-1;
	_actionFini=true;

	_barrePV.setSize(sf::Vector2f(_PV*8,50));

	if(n==1)
	{
		_barrePV.setPosition(sf::Vector2f(20,20));
	}else
	{
		_barrePV.setScale(-1,1);
		_barrePV.setPosition(sf::Vector2f(window.getSize().x-20,20));
	}
}

void Player::setChampion(Personnage* perso)
{
	_champion=perso;
}

Personnage* Player::getChampion()
{
	return _champion;
}

sf::Sprite Player::getEffet()
{
	return _effet;
}

void Player::_resetAttributs()
{
	_posHorizontale=0;
	_posVerticale=0;
	_action=-1;
	_derniereAction=-1;
	_actionFini=true;
	_prendCoup=0;
}

void Player::recuperationCommandesP1(Player& ennemi)    // Commandes pour le player 1
{
	_resetAttributs();

	bool avancer=false,reculer=false, accroupi=false, saut=false,sautAvant=false,sautArriere=false,garde=false,punch=false,kick=false,SP1=false;

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
		reculer=sf::Keyboard::isKeyPressed(sf::Keyboard::Q);  	// touche pour reculer:    Q
		avancer=sf::Keyboard::isKeyPressed(sf::Keyboard::D);  	// touche pour avancer:    D
		saut=sf::Keyboard::isKeyPressed(sf::Keyboard::Z);	  	// touche pour sauter:     Z
		accroupi=sf::Keyboard::isKeyPressed(sf::Keyboard::S);	// touche pour accroupir:  S
		punch=sf::Keyboard::isKeyPressed(sf::Keyboard::A);	  	// touche pour puncher:    A
		kick=sf::Keyboard::isKeyPressed(sf::Keyboard::E);	  	// touche pour kicker:     E
		SP1=sf::Keyboard::isKeyPressed(sf::Keyboard::R);		// touche pour spécial 1:  R
	}
	
	gestionDesCommandes(ennemi,avancer,reculer,accroupi,saut,sautAvant,sautArriere,garde,punch,kick,SP1);	
}

void Player::recuperationAttaquesP1()
{
	if(_posHorizontale==0 && _posVerticale==1 && _action==-1)
	{
		bool punch=false,kick=false;
		if (sf::Joystick::isConnected(0))   // Commandes pour manette
		{
			punch=sf::Joystick::isButtonPressed(0, 0);
			kick=sf::Joystick::isButtonPressed(0, 1);
		}else
		{
			punch=sf::Keyboard::isKeyPressed(sf::Keyboard::A);	  	
			kick=sf::Keyboard::isKeyPressed(sf::Keyboard::E);
		}
		if(punch)
			_action=1;
		else if(kick)
			_action=2;
	}	
}


void Player::recuperationCommandesP2(Player& ennemi)    // Commandes pour le player 2
{
	_resetAttributs();

	bool avancer=false,reculer=false, accroupi=false, saut=false,sautAvant=false,sautArriere=false,garde=false,punch=false,kick=false,SP1=false;

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
		avancer=sf::Keyboard::isKeyPressed(sf::Keyboard::Right);  	// touche pour reculer:    Right
		reculer=sf::Keyboard::isKeyPressed(sf::Keyboard::Left);  	// touche pour avancer:    Left
		saut=sf::Keyboard::isKeyPressed(sf::Keyboard::Up);	  		// touche pour sauter:     Up
		accroupi=sf::Keyboard::isKeyPressed(sf::Keyboard::Down);	// touche pour accroupir:  Down
		punch=sf::Keyboard::isKeyPressed(sf::Keyboard::P);	  		// touche pour puncher:    P
		kick=sf::Keyboard::isKeyPressed(sf::Keyboard::M);	  		// touche pour kicker:     M
		SP1=sf::Keyboard::isKeyPressed(sf::Keyboard::L);			// touche pour spécial 1:  L

	}
	gestionDesCommandes(ennemi,avancer,reculer,accroupi,saut,sautAvant,sautArriere,garde,punch,kick,SP1);	
}

void Player::recuperationAttaquesP2()
{
	if(_posHorizontale==0 && _posVerticale==1 && _action==-1)
	{
		bool punch=false,kick=false;
		if (sf::Joystick::isConnected(1))   // Commandes pour manette
		{
			punch=sf::Joystick::isButtonPressed(0, 0);
			kick=sf::Joystick::isButtonPressed(0, 1);
		}else
		{
			punch=sf::Keyboard::isKeyPressed(sf::Keyboard::P);	  	
			kick=sf::Keyboard::isKeyPressed(sf::Keyboard::M);
		}
		if(punch)
			_action=1;
		else if(kick)
			_action=2;
	}	
}

void Player::gestionDesCommandes(Player& ennemi,bool avancer, bool reculer, bool accroupi, bool saut, bool sautAvant, bool sautArriere, bool garde, bool punch, bool kick, bool SP1 )
{
	if(punch && (avancer || reculer))
	{
		punch=true;
		avancer=false;
		reculer=false;
	}else if(kick && (avancer || reculer))
	{
		kick=true;
		avancer=false;
		reculer=false;
	}else if(SP1 && (avancer || reculer || saut))
	{
		SP1=true;
		avancer=false;
		reculer=false;
		saut=false;
	}

	if(sautAvant)
	{
		_posHorizontale=1;
		_posVerticale=1;
	}else if (sautArriere)
	{
		_posHorizontale=-1;
		_posVerticale=1;	
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

	if(ennemi.getAction()>0 && _champion->getOrientation()==_posHorizontale)
		_action=0;
	else if(punch)
		_action=1;
	else if(kick)
		_action=2;
	else if(SP1)
		_action=3;
	else
		_action=-1;
}

bool Player::lancerApparition()
{
	return _champion->apparition(_clockAnim,_effet);
}

bool Player::lancerActions(Player& jEnnemi)
{
	if(_prendCoup!=0)
	{
		if(_action==0)
		{
			_actionFini=_champion->parade(_clockAnim,&_prendCoup,_effet);
		}else
		{
			if(_prendCoup>0)
				setDegats(_prendCoup);
			_posHorizontale==0;_posVerticale==0;_action=-1;
			_actionFini=_champion->prendCoup(_clockAnim,&_prendCoup,_effet);
		}
	}

	else if(_action!=_derniereAction && _derniereAction==0 && _posVerticale==0)
		_actionFini=_champion->finGarde(_clockAnim);
	else if(_etaitAccroupi && _posVerticale!=-1)
		_actionFini=_champion->seLever(_clockAnim);

	else if(_action==0)
		_champion->garde(_clockAnim);

	else if(_action==1)
		_actionFini=_champion->punch(_clockAnim,*jEnnemi.getChampion(),jEnnemi.getPrendCoup());

	else if(_action==2)
		_actionFini=_champion->kick(_clockAnim,*jEnnemi.getChampion(),jEnnemi.getPrendCoup());

	else if(_action==3)
		_actionFini=_champion->SP(_clockAnim,_effet,*jEnnemi.getChampion(),jEnnemi.getPrendCoup(),son);

	else if(_posHorizontale==1 && _posVerticale==1)
	{
		if(_champion->getOrientation()==-1)
			_actionFini=_champion->sauterAvant(_clockAnim,*jEnnemi.getChampion());
		else
			_actionFini=_champion->sauterArriere(_clockAnim,*jEnnemi.getChampion());
	}

	else if(_posHorizontale==-1 && _posVerticale==1)
	{
		if(_champion->getOrientation()==-1)
			_actionFini=_champion->sauterArriere(_clockAnim,*jEnnemi.getChampion());
		else
			_actionFini=_champion->sauterAvant(_clockAnim,*jEnnemi.getChampion());
	}
	
	else if(_posHorizontale==1)
	{
		if(_champion->getOrientation()==-1)
			_champion->avancer(_clockAnim,*jEnnemi.getChampion());
		else
			_champion->reculer(_clockAnim);
	}

	else if(_posHorizontale==-1)
	{
		if(_champion->getOrientation()==-1)
			_champion->reculer(_clockAnim);
		else
			_champion->avancer(_clockAnim,*jEnnemi.getChampion());
	}

	else if(_posVerticale==1)
		_actionFini=_champion->sauter(_clockAnim,_action,*jEnnemi.getChampion(),jEnnemi.getPrendCoup());

	else if(_posVerticale==-1)
		_champion->accroupi(_clockAnim,_action==0);

	else
		_champion->statique(_clockAnim,*jEnnemi.getChampion());

	if(_posVerticale!=-1)
		_champion->resetCptAccroupi();

	if( !(_action!=_derniereAction && _derniereAction==0) || _actionFini==true)
		_derniereAction=_action;

	if(_actionFini==true)
		_etaitAccroupi=(_posVerticale==-1);

	return _actionFini;
}

bool Player::finPartie()
{
	_posVerticale=0;_posHorizontale=0;_action=-1;
	_effet.setTextureRect(sf::IntRect(0,0,0,0));
	if(_PV>0)
		return _champion->victoire(_clockAnim,son);
	else
		return _champion->mort(_clockAnim);
}

int Player::getAction()
{
	return _action;
}

int Player::getPV()
{
	return _PV;
}

void Player::resetPV()
{
	_PV=100;
}

void Player::setDegats(int degats)
{
	_PV-=degats;
}

sf::RectangleShape Player::getBarrePV()
{
	if(_PV>66)
		_barrePV.setFillColor(sf::Color(0,250,0));
	else if(_PV>33)
		_barrePV.setFillColor(sf::Color(255,165,0));
	else 
		_barrePV.setFillColor(sf::Color(255,0,0));

	if(_PV>0)
		_barrePV.setSize(sf::Vector2f(_PV*8,50));
	else
		_barrePV.setSize(sf::Vector2f(0,50));

	return _barrePV;
}

int* Player::getPrendCoup()
{
	return &_prendCoup;
}

void Player::setPrendCoup(int n)
{
	_prendCoup=n;
}