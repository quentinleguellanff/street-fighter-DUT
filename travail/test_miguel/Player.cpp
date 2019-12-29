#include "IncludeManager.h"
#include <string>

using namespace std;

Player::Player(int n,sf::RenderWindow& window)
{
	_numPlayer=n;
	_PV=100;

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

void Player::_resetAttributs()
{
	_posHorizontale=0;
	_posVerticale=0;
	_action=0;
}

void Player::recuperationCommandesP1()    // Commandes pour le player 1
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
		garde=sf::Keyboard::isKeyPressed(sf::Keyboard::C);	  	// touche pour protection: C   
		punch=sf::Keyboard::isKeyPressed(sf::Keyboard::A);	  	// touche pour puncher:    A
		kick=sf::Keyboard::isKeyPressed(sf::Keyboard::E);	  	// touche pour kicker:     E
		SP1=sf::Keyboard::isKeyPressed(sf::Keyboard::R);		// touche pour spécial 1:  R
	}
	
	gestionDesCommandes(avancer,reculer,accroupi,saut,sautAvant,sautArriere,garde,punch,kick,SP1);	
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


void Player::recuperationCommandesP2()    // Commandes pour le player 2
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
		reculer=sf::Keyboard::isKeyPressed(sf::Keyboard::Right);  	// touche pour reculer:    Right
		avancer=sf::Keyboard::isKeyPressed(sf::Keyboard::Left);  	// touche pour avancer:    Left
		saut=sf::Keyboard::isKeyPressed(sf::Keyboard::Up);	  		// touche pour sauter:     Up
		accroupi=sf::Keyboard::isKeyPressed(sf::Keyboard::Down);	// touche pour accroupir:  Down
		garde=sf::Keyboard::isKeyPressed(sf::Keyboard::O);	  		// touche pour protection: O   
		punch=sf::Keyboard::isKeyPressed(sf::Keyboard::P);	  		// touche pour puncher:    P
		kick=sf::Keyboard::isKeyPressed(sf::Keyboard::M);	  		// touche pour kicker:     M
		SP1=sf::Keyboard::isKeyPressed(sf::Keyboard::L);			// touche pour spécial 1:  L

	}
	gestionDesCommandes(avancer,reculer,accroupi,saut,sautAvant,sautArriere,garde,punch,kick,SP1);	
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

void Player::gestionDesCommandes(bool avancer, bool reculer, bool accroupi, bool saut, bool sautAvant, bool sautArriere, bool garde, bool punch, bool kick, bool SP1 )
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

	if(garde)
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

/*void Player::lancerActions(Personnage& monPerso,Personnage& persoEnnemi,Player& jEnnemi)
{
	if(_prendCoup)
	{
		_posHorizontale==0;_posVerticale==0;_action=-1;
		_actionFini=monPerso.prendCoup(_clockAnim,_prendCoup,_effet);
	}
	else if(_action!=_derniereAction && _derniereAction==0 && _posVerticale==0)
		_actionFini=monPerso.finGarde(_clockAnim);
	else if(_etaitAccroupi && _posVerticale!=-1)
		_actionFini=monPerso.seLever(_clockAnim);
	else if(_posHorizontale==1 && _posVerticale==1)
	{
		if(monPerso.getOrientation()==-1)
			_actionFini=monPerso.sauterAvant(_clockAnim,*persoEnnemi);
		else
			_actionFini=monPerso.sauterArriere(_clockAnim,*persoEnnemi);
	}
	else if(_posHorizontale==-1 && _posVerticale==1)
	{
		if(monPerso.getOrientation()==-1)
			_actionFini=monPerso.sauterArriere(_clockAnim,*persoEnnemi);
		else
			_actionFini=monPerso.sauterAvant(_clockAnim,*persoEnnemi);
	}
	else if(_posVerticale==1 && _action==2)
	{
		int n;
		_actionFini=monPerso.sautKick(_clockAnim,*persoEnnemi,jEnnemi.getPrendCoup(),jEnnemi,n);
	}
	else if(_posVerticale==1 && _action==1)
		_actionFini=monPerso.sautPunch(_clockAnim,*persoEnnemi,jEnnemi.getPrendCoup(),jEnnemi);

	else if(_posHorizontale==1)
	{
		if(monPerso.getOrientation()==-1)
			monPerso.avancer(_clockAnim,*persoEnnemi);
		else
			monPerso.reculer(_clockAnim);
	}
	else if(_posHorizontale==-1)
	{
		if(monPerso.getOrientation()==-1)
			monPerso.reculer(_clockAnim);
		else
			monPerso.avancer(_clockAnim,*persoEnnemi);
	}
	else if(_posVerticale==1)
		_actionFini=monPerso.sauter(_clockAnim,clockAttente,*persoEnnemi);

	else if(_posVerticale==-1)
		monPerso.accroupi(_clockAnim,_action==0);

	else if(_action==0)
		monPerso.garde(_clockAnim);

	else if(_action==1)
		_actionFini=monPerso.punch(_clockAnim,*persoEnnemi,jEnnemi.getPrendCoup(),jEnnemi);

	else if(_action==2)
		_actionFini=monPerso.kick(_clockAnim,*persoEnnemi,jEnnemi.getPrendCoup(),jEnnemi);

	else if(_action==3)
		_actionFini=monPerso.SP(_clockAnim,_effet,*persoEnnemi,jEnnemi.getPrendCoup(),jEnnemi,son);

	else
		monPerso.statique(_clockAnim,*persoEnnemi);

	if(_posVerticale!=-1)
		monPerso.resetCptAccroupi();

	if( !(_action!=_derniereAction && _derniereAction==0) || _actionFini==true)
		_derniereAction=_action;

	if(_actionFini==true)
		_etaitAccroupi=(_posVerticale==-1);
}*/


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

bool Player::getPrendCoup()
{
	return _prendCoup;
}