#include "IncludeManager.h"
#include "Player.h"
#include <string>
#include <vector>

using namespace std;

Player::Player(int n,sf::RenderWindow& window)
{
	_PV=100;
	_energie=10;

	for(int i=0;i<2;i++)
	{
		sf::Clock temp;
		_clockAnim.push_back(temp);
	}

	_posHorizontale=0;
	_posVerticale=0;
	_action=-1;
	_derniereAction=-1;
	_actionFini=true;

	for(int i=0;i<=11;i++)
		_tabActions.push_back(false);


	_barrePV.setSize(sf::Vector2f(_PV*8,50));

	if(n==1)
	{
		_barrePV.setPosition(sf::Vector2f(20,20));
	}else
	{
		_barrePV.setScale(-1,1);
		_barrePV.setPosition(sf::Vector2f(window.getSize().x-20,20));
	}


	for(int i=0;i<4;i++)
	{
		sf::RectangleShape temp;
		_barresEnergie.push_back(temp);
	}

	if(n==1)
	{
		_barresEnergie[0].setPosition(sf::Vector2f(20,window.getSize().y-50));
		for(int i=1;i<4;i++)
			_barresEnergie[i].setPosition(sf::Vector2f(_barresEnergie[i-1].getPosition().x+55*2,window.getSize().y-50));
	}else
	{
		for(int i=0;i<4;i++)
			_barresEnergie[i].setScale(-1,1);

		_barresEnergie[0].setPosition(sf::Vector2f(window.getSize().x-20,window.getSize().y-50));
		for(int i=1;i<4;i++)
			_barresEnergie[i].setPosition(sf::Vector2f(_barresEnergie[i-1].getPosition().x-55*2,window.getSize().y-50));
	}
}

void Player::resetPlayer()
{
	resetAttributs();
	_prendCoup=0;
}

void Player::resetAttributs()
{
	_posHorizontale=0;
	_posVerticale=0;
	_action=-1;
	_derniereAction=-1;
	_actionFini=true;

	for(int i=0;i<=11;i++)
		_tabActions[i]=false;
}

void Player::setChampion(Personnage* perso)
{
	_champion=perso;
	resetPlayer();
}

Personnage* Player::getChampion()
{
	return _champion;
}

sf::Sprite Player::getEffet()
{
	return _effet;
}


void Player::recuperationCommandesP1(Player& ennemi)    // Commandes pour le player 1
{
	resetAttributs();

	if (sf::Joystick::isConnected(0))   // Commandes pour manette
	{
		/* gestion des attaques */
		_tabActions[9] =(sf::Joystick::isButtonPressed(0, 0) || sf::Joystick::isButtonPressed(0, 1));
		_tabActions[7] =(sf::Joystick::isButtonPressed(0, 2) || sf::Joystick::isButtonPressed(0, 3));   // touche pour mettre un coup de poing
		
		joystick0_axisZ =sf::Joystick::getAxisPosition(0, sf::Joystick::Z);   // touche pour super punch
		joystick0_axisR =sf::Joystick::getAxisPosition(0, sf::Joystick::R);	 // touche pour super kick
		_tabActions[10] =joystick0_axisZ > 40 || joystick0_axisR>40;

		_tabActions[8]=(sf::Joystick::isButtonPressed(0, 4) || sf::Joystick::isButtonPressed(0, 5));

		if( ( (joystick0_axisX > 40 || joystick0_axisX < -40) && joystick0_axisY > 40) &&  (sf::Joystick::isButtonPressed(0, 2) || sf::Joystick::isButtonPressed(0, 3)) )
			_tabActions[11] =true;

		/* gestion des deplacements */
		joystick0_axisX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		joystick0_axisY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		//cout<<"x : "<<joystick0_axisX<<"\t y : "<<joystick0_axisY<<endl;
		if( (joystick0_axisX > 40) && (joystick0_axisY < 70 && joystick0_axisY > -55) )
			_tabActions[0] =true;
		else if( (joystick0_axisX < -40) && (joystick0_axisY < 70 && joystick0_axisY > -40) )
			_tabActions[1] =true;
		else if( (joystick0_axisX>-80 && joystick0_axisX<80) && (joystick0_axisY<-40) )
			_tabActions[3] =true;
		else if( (joystick0_axisX<=100 && joystick0_axisX>=80) && (joystick0_axisY<-40) )
		{
			_tabActions[0] =true;
			_tabActions[3] =true;
		}	
		else if( (joystick0_axisX>=-100 && joystick0_axisX<=-80) && (joystick0_axisY<-40) )
		{
			_tabActions[1] =true;
			_tabActions[3] =true;
		}
		else if( (joystick0_axisX>-80 && joystick0_axisX<80) && (joystick0_axisY>40) )
			_tabActions[2] =true;

	}else   // Commandes clavier au cas ou manette absent
	{
		_tabActions[1] =sf::Keyboard::isKeyPressed(sf::Keyboard::Q);  	// touche pour reculer:    Q
		_tabActions[0] =sf::Keyboard::isKeyPressed(sf::Keyboard::D);  	// touche pour avancer:    D
		_tabActions[3] =sf::Keyboard::isKeyPressed(sf::Keyboard::Z);	  	// touche pour sauter:     Z
		_tabActions[2] =sf::Keyboard::isKeyPressed(sf::Keyboard::S);	// touche pour accroupir:  S
		_tabActions[7] =sf::Keyboard::isKeyPressed(sf::Keyboard::A);	  	// touche pour puncher:    A
		_tabActions[9] =sf::Keyboard::isKeyPressed(sf::Keyboard::E);	  	// touche pour kicker:     E
		_tabActions[11] =sf::Keyboard::isKeyPressed(sf::Keyboard::R);		// touche pour spécial 1:  R
	}

	gestionDesCommandes(ennemi);
}

void Player::recuperationAttaquesP1()
{
	if(_posHorizontale==0 && _posVerticale==1 && _action==-1)
	{
		if (sf::Joystick::isConnected(0))   // Commandes pour manette
		{
			_tabActions[7]=(sf::Joystick::isButtonPressed(0, 2) || sf::Joystick::isButtonPressed(0, 3));
			_tabActions[9]=(sf::Joystick::isButtonPressed(0, 0) || sf::Joystick::isButtonPressed(0, 1));
		}else
		{
			_tabActions[7]=sf::Keyboard::isKeyPressed(sf::Keyboard::A);	  	
			_tabActions[9]=sf::Keyboard::isKeyPressed(sf::Keyboard::E);
		}
		if(_tabActions[7])
			_action=1;
		else if(_tabActions[9])
			_action=2;
	}	
}


void Player::recuperationCommandesP2(Player& ennemi)    // Commandes pour le player 2
{
	resetAttributs();

	if (sf::Joystick::isConnected(1))   // Commandes pour manette
	{
		/* gestion des attaques */
		_tabActions[9] =(sf::Joystick::isButtonPressed(1, 0) || sf::Joystick::isButtonPressed(1, 1));
		_tabActions[7] =(sf::Joystick::isButtonPressed(1, 2) || sf::Joystick::isButtonPressed(1, 3));   // touche pour mettre un coup de poing
		
		joystick1_axisZ =sf::Joystick::getAxisPosition(1, sf::Joystick::Z);   // touche pour super punch
		joystick1_axisR =sf::Joystick::getAxisPosition(1, sf::Joystick::R);	 // touche pour super kick
		_tabActions[10] =joystick1_axisZ > 40 || joystick1_axisR>40;

		_tabActions[8]=(sf::Joystick::isButtonPressed(1, 4) || sf::Joystick::isButtonPressed(1, 5));

		if( ( (joystick1_axisX > 40 || joystick1_axisX < -40) && joystick1_axisY > 40) &&  (sf::Joystick::isButtonPressed(1, 2) || sf::Joystick::isButtonPressed(1, 3)) )
			_tabActions[11] =true;

		/* gestion des deplacements */
		joystick1_axisX = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
		joystick1_axisY = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);
		//cout<<"x : "<<joystick0_axisX<<"\t y : "<<joystick0_axisY<<endl;
		if( (joystick1_axisX > 40) && (joystick1_axisY < 70 && joystick1_axisY > -55) )
			_tabActions[0] =true;
		else if( (joystick1_axisX < -40) && (joystick1_axisY < 70 && joystick1_axisY > -40) )
			_tabActions[1] =true;
		else if( (joystick1_axisX>-80 && joystick1_axisX<80) && (joystick1_axisY<-40) )
			_tabActions[3] =true;
		else if( (joystick1_axisX<=100 && joystick1_axisX>=80) && (joystick1_axisY<-40) )
		{
			_tabActions[0] =true;
			_tabActions[3] =true;
		}	
		else if( (joystick1_axisX>=-100 && joystick1_axisX<=-80) && (joystick1_axisY<-40) )
		{
			_tabActions[1] =true;
			_tabActions[3] =true;
		}
		else if( (joystick1_axisX>-80 && joystick1_axisX<80) && (joystick1_axisY>40) )
			_tabActions[2] =true;

	}else   // Commandes clavier au cas ou manette absent
	{
		_tabActions[0]=sf::Keyboard::isKeyPressed(sf::Keyboard::Right);  	// touche pour _tabActions[1]:    Right
		_tabActions[1]=sf::Keyboard::isKeyPressed(sf::Keyboard::Left);  	// touche pour _tabActions[0]:    Left
		_tabActions[3]=sf::Keyboard::isKeyPressed(sf::Keyboard::Up);	  		// touche pour sauter:     Up
		_tabActions[2]=sf::Keyboard::isKeyPressed(sf::Keyboard::Down);	// touche pour accroupir:  Down
		_tabActions[7]=sf::Keyboard::isKeyPressed(sf::Keyboard::P);	  		// touche pour puncher:    P
		_tabActions[9]=sf::Keyboard::isKeyPressed(sf::Keyboard::M);	  		// touche pour kicker:     M
		_tabActions[11]=sf::Keyboard::isKeyPressed(sf::Keyboard::L);			// touche pour spécial 1:  L

	}
	
	gestionDesCommandes(ennemi);
}

void Player::recuperationAttaquesP2()
{
	if(_posHorizontale==0 && _posVerticale==1 && _action==-1)
	{
		if (sf::Joystick::isConnected(1))   // Commandes pour manette
		{
			_tabActions[7]=(sf::Joystick::isButtonPressed(1, 2) || sf::Joystick::isButtonPressed(1, 3));
			_tabActions[9]=(sf::Joystick::isButtonPressed(1, 0) || sf::Joystick::isButtonPressed(1, 1));
		}else
		{
			_tabActions[7]=sf::Keyboard::isKeyPressed(sf::Keyboard::P);	  	
			_tabActions[9]=sf::Keyboard::isKeyPressed(sf::Keyboard::M);
		}
		if(_tabActions[7])
			_action=1;
		else if(_tabActions[9])
			_action=2;
	}	
}

void Player::gestionDesCommandes(Player& ennemi)
{
	if(_tabActions[7] && (_tabActions[0] || _tabActions[1]))
	{
		_tabActions[7]=true;
		_tabActions[0]=false;
		_tabActions[1]=false;
	}else if(_tabActions[8] && (_tabActions[0] || _tabActions[1]))
	{
		_tabActions[9]=true;
		_tabActions[0]=false;
		_tabActions[1]=false;
	}else if(_tabActions[8] && (_tabActions[0] || _tabActions[1]))
	{
		_tabActions[9]=true;
		_tabActions[0]=false;
		_tabActions[1]=false;
	}else if(_tabActions[10] && (_tabActions[0] || _tabActions[1]))
	{
		_tabActions[10]=true;
		_tabActions[0]=false;
		_tabActions[1]=false;
	}else if(_tabActions[11] && (_tabActions[0] || _tabActions[1] || _tabActions[2] || _tabActions[3]))
	{
		_tabActions[11]=true;
		_tabActions[0]=false;
		_tabActions[1]=false;
		_tabActions[2]=false;
		_tabActions[3]=false;
	}

	if(_tabActions[0] && _tabActions[3])
	{
		_posHorizontale=1;
		_posVerticale=1;
	}else if (_tabActions[1] && _tabActions[3])
	{
		_posHorizontale=-1;
		_posVerticale=1;	
	}



	/* Gestion des attributs */

	if(_tabActions[0])
		_posHorizontale=1;
	else if(_tabActions[1])
		_posHorizontale=-1;
	else
		_posHorizontale=0;


	if(_tabActions[3])
		_posVerticale=1;
	else if(_tabActions[2])
		_posVerticale=-1;
	else 
		_posVerticale=0;

	if(ennemi.getAction()>0 && _champion->getOrientation()==_posHorizontale)
		_action=0;
	else if(_tabActions[11])
		_action=5;
	else if(_tabActions[7])
		_action=1;
	else if(_tabActions[8])
		_action=2;
	else if(_tabActions[9])
		_action=3;
	else if(_tabActions[10])
		_action=4;
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

	else if(_etaitAccroupi && _posVerticale!=-1)
		_actionFini=_champion->seLever(_clockAnim);

	else if(_action==0)
		_champion->garde(_clockAnim);

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

	else if(_action==1)
		_actionFini=_champion->punch(_clockAnim,*jEnnemi.getChampion(),jEnnemi.getPrendCoup());

	else if(_action==2)
		_actionFini=_champion->punchSP(_clockAnim,_effet,*jEnnemi.getChampion(),jEnnemi.getPrendCoup(),son);

	else if(_action==3)
		_actionFini=_champion->kick(_clockAnim,*jEnnemi.getChampion(),jEnnemi.getPrendCoup());

	else if(_action==4)
		_actionFini=_champion->kickSP(_clockAnim,*jEnnemi.getChampion(),jEnnemi.getPrendCoup());

	else if(_action==5)
		_actionFini=_champion->SP(_clockAnim,_effet,*jEnnemi.getChampion(),jEnnemi.getPrendCoup(),son);

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

void Player::afficherEnergie(sf::RenderWindow& window)
{
	if(_energie==100)
	{
		for(int i=0;i<4;i++)
		{
			_barresEnergie[i].setOutlineColor(sf::Color(0,250,0));
			_barresEnergie[i].setFillColor(sf::Color(10,255,255));
		}
	}else if(_energie>50)
	{
		for(int i=0;i<4;i++)
		{
			_barresEnergie[i].setOutlineColor(sf::Color(15,5,107));
			_barresEnergie[i].setFillColor(sf::Color(10,255,255));
		}
	}else
	{
		for(int i=0;i<4;i++)
		{
			_barresEnergie[i].setOutlineThickness(2.f);
			_barresEnergie[i].setOutlineColor(sf::Color(15,5,107));
			_barresEnergie[i].setFillColor(sf::Color(18,164,202));
		}
	}

	if(_energie<25)
	{
		_barresEnergie[0].setSize(sf::Vector2f(_energie*4,30));
		for(int i=1;i<4;i++)
		{
			_barresEnergie[i].setSize(sf::Vector2f(49*2,30));
			_barresEnergie[i].setFillColor(sf::Color(0,0,0,0));
		}
	}else if(_energie<50)
	{
		_barresEnergie[0].setSize(sf::Vector2f(49*2,30));
		_barresEnergie[1].setSize(sf::Vector2f((_energie-24)*4,30));
		for(int i=2;i<4;i++)
			_barresEnergie[i].setSize(sf::Vector2f(0,0));
	}else if(_energie<75)
	{
		_barresEnergie[0].setSize(sf::Vector2f(49*2,30));
		_barresEnergie[1].setSize(sf::Vector2f(49*2,30));
		_barresEnergie[2].setSize(sf::Vector2f((_energie-49)*4,30));
	
		_barresEnergie[3].setSize(sf::Vector2f(0,0));
	}else
	{
		_barresEnergie[0].setSize(sf::Vector2f(49*2,30));
		_barresEnergie[1].setSize(sf::Vector2f(49*2,30));
		_barresEnergie[2].setSize(sf::Vector2f(49*2,30));
		_barresEnergie[3].setSize(sf::Vector2f((_energie-74)*4,30));
	}

	for(int i=0;i<4;i++)
		window.draw(_barresEnergie[i]);
}


int* Player::getPrendCoup()
{
	return &_prendCoup;
}

void Player::setPrendCoup(int n)
{
	_prendCoup=n;
}

int Player::getPC()
{
	return _prendCoup;
}