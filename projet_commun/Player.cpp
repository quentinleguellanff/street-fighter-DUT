#include "IncludeManager.h"
#include "Player.h"
#include <string>
#include <vector>

using namespace std;

Player::Player(int n,sf::RenderWindow& window)
{
	_PV=100;
	_energie=0;

	_posHorizontale=0;
	_posVerticale=0;
	_action=-1;
	_derniereAction=-1;
	_actionFini=true;

	for(int i=0;i<=11;i++)
		_tabActions.push_back(false);
	for(int i=0;i<=4;i++)
		_tabPeutAction.push_back(true);

	if (!_textureBI.loadFromFile("background/lifeBar_V2.png"))
	{
	    std::cout<<"Erreur au chargement du sprite";
	}
	_barreInfos.setTexture(_textureBI);

	for(int i=0;i<2;i++)
	{
		sf::RectangleShape temp;
		_barrePV.push_back(temp);
		_barreEnergie.push_back(temp);
	}

	_barrePV[0].setSize(sf::Vector2f(_PV*7.15,40));
	_barreEnergie[0].setSize(sf::Vector2f(276,40));
	_barrePV[0].setFillColor(sf::Color(90,37,37));
	_barreEnergie[0].setFillColor(sf::Color(210,254,254));

	_barreEnergie[1].setFillColor(sf::Color(10,255,255));

	if(n==1)
	{
		_barreInfos.setPosition(sf::Vector2f(0,10));

		for(int i=0;i<2;i++)
		{
			_barrePV[i].setPosition(sf::Vector2f(177,19));
			_barreEnergie[i].setPosition(sf::Vector2f(177,63));
		}
	}else
	{
		_barreInfos.scale(-1,1);
		_barreInfos.setPosition(sf::Vector2f(window.getSize().x,10));

		for(int i=0;i<2;i++)
		{
			_barrePV[i].scale(-1,1);
			_barrePV[i].setPosition(sf::Vector2f(window.getSize().x-177,18));
			_barreEnergie[i].scale(-1,1);
			_barreEnergie[i].setPosition(sf::Vector2f(window.getSize().x-177,63));
		}

	}
}

void Player::resetPlayer()
{
	resetAttributs();
	_prendCoup=0;
	_energie=0;
	_PV=100;
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

	if(_barreInfos.getScale().x==1)
	{
		_portrait=_champion->getIcone();
		_portrait.setPosition(0,10);
	}else
	{

		_portrait=_champion->getIcone();
		_portrait.setPosition(_barreInfos.getPosition().x,10);
		_portrait.scale(-1,1);
	}
}

Personnage* Player::getChampion()
{
	return _champion;
}

sf::Sprite Player::getEffet()
{
	return _effet;
}

void Player::recuperationAttaqueLancee()
{
	for(int i=7;i<_tabActions.size();i++)
	{
		if(_tabActions[i]==true)
			_tabPeutAction[i-7]=false;
	}
}

void Player::peutAttaquerP1(sf::Event& event, sf::RenderWindow& window)
{
    if (sf::Joystick::isConnected(0))   // Commandes pour manette
	{
        if(event.type==sf::Event::JoystickButtonReleased && event.joystickButton.joystickId==0 )
        {
            switch (event.joystickButton.button)
            {
            case 0:
              	_tabPeutAction[2] = true;
              	break;
            case 1:
              	_tabPeutAction[2] = true;
              	break;
            case 2:
                _tabPeutAction[0] = true;
                _tabPeutAction[4] = true;
                break;
            case 3:
              	_tabPeutAction[0] = true;
              	_tabPeutAction[4] = true;
              	break;
            case 4:
            	_tabPeutAction[1] = true;
            	break;
            case 5:
            	_tabPeutAction[1] = true;
            	break;
            }

            if(event.joystickMove.axis==sf::Joystick::Z || event.joystickMove.axis==sf::Joystick::R)
            {
            	if(event.joystickMove.position<10)
            		_tabPeutAction[3] = true;
            }

        }
    }else
    {
    	if(event.type==sf::Event::KeyReleased )
        {
            switch (event.key.code)
            {
            case sf::Keyboard::A :
              	_tabPeutAction[0] = true;
              	break;
            case sf::Keyboard::E :
                _tabPeutAction[2]=true;
                break;
            case sf::Keyboard::R :
              	_tabPeutAction[4] = true;
              	break;
            }
        }
    }
}

void Player::recuperationCommandesP1(Player& ennemi)    // Commandes pour le player 1
{
	resetAttributs();

	if (sf::Joystick::isConnected(0))   // Commandes pour manette
	{
		/* gestion des attaques */
		_tabActions[9] =( (sf::Joystick::isButtonPressed(0, 0) || sf::Joystick::isButtonPressed(0, 1) ) && _tabPeutAction[2]);
		_tabActions[7] =( (sf::Joystick::isButtonPressed(0, 2) || sf::Joystick::isButtonPressed(0, 3) ) && _tabPeutAction[0]);   // touche pour mettre un coup de poing

		joystick0_axisZ =sf::Joystick::getAxisPosition(0, sf::Joystick::Z);   // touche pour super kick
		joystick0_axisR =sf::Joystick::getAxisPosition(0, sf::Joystick::R);	 // touche pour super kick
		_tabActions[10] =( (joystick0_axisZ > 40 || joystick0_axisR>40)  && _tabPeutAction[3]);

		_tabActions[8]=( (sf::Joystick::isButtonPressed(0, 4) || sf::Joystick::isButtonPressed(0, 5))  && _tabPeutAction[1]);

		if( ( (joystick0_axisX > 40 || joystick0_axisX < -40) && joystick0_axisY > 40) &&  (sf::Joystick::isButtonPressed(0, 2) || sf::Joystick::isButtonPressed(0, 3)) && _tabPeutAction[4] )
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
		_tabActions[7] =( sf::Keyboard::isKeyPressed(sf::Keyboard::A) && _tabPeutAction[0]);	  	// touche pour puncher:    A
		_tabActions[9] =( sf::Keyboard::isKeyPressed(sf::Keyboard::E) && _tabPeutAction[2]);	  	// touche pour kicker:     E
		_tabActions[11]=( sf::Keyboard::isKeyPressed(sf::Keyboard::R) && _tabPeutAction[4]);		// touche pour spécial 1:  R
	}
	recuperationAttaqueLancee();
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


void Player::peutAttaquerP2(sf::Event& event, sf::RenderWindow& window)
{
    if (sf::Joystick::isConnected(0))   // Commandes pour manette
	{
        if(event.type==sf::Event::JoystickButtonReleased && event.joystickButton.joystickId==1 )
        {
            switch (event.joystickButton.button)
            {
            case 0:
              	_tabPeutAction[2] = true;
              	break;
            case 1:
              	_tabPeutAction[2] = true;
              	break;
            case 2:
                _tabPeutAction[0] = true;
                _tabPeutAction[4] = true;
                break;
            case 3:
              	_tabPeutAction[0] = true;
              	_tabPeutAction[4] = true;
              	break;
            case 4:
            	_tabPeutAction[1] = true;
            	break;
            case 5:
            	_tabPeutAction[1] = true;
            	break;
            }

            if(event.joystickMove.axis==sf::Joystick::Z || event.joystickMove.axis==sf::Joystick::R)
            {
            	if(event.joystickMove.position<10)
            		_tabPeutAction[3] = true;
            }

        }
    }else
    {
    	if(event.type==sf::Event::KeyReleased )
        {
            switch (event.key.code)
            {
            case sf::Keyboard::P :
              	_tabPeutAction[0] = true;
              	break;
            case sf::Keyboard::M :
                _tabPeutAction[2]=true;
                break;
            case sf::Keyboard::L :
              	_tabPeutAction[4] = true;
              	break;
            }
        }
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
	return _champion->apparition(_effet);
}

bool Player::lancerActions(Player& jEnnemi)
{
	if(_prendCoup!=0)
	{
		if(_action==0)
		{
			_actionFini=_champion->parade(&_prendCoup,_effet);
		}else
		{
			if(_prendCoup>0)
				setDegats(_prendCoup);
			_posHorizontale==0;_posVerticale==0;_action=-1;
			_actionFini=_champion->prendCoup(&_prendCoup,_effet,_energie);
		}
	}

	else if(_etaitAccroupi && _posVerticale!=-1)
		_actionFini=_champion->seLever();

	else if(_action==0)
		_champion->garde();

	else if(_posHorizontale==1 && _posVerticale==1)
	{
		if(_champion->getOrientation()==-1)
			_actionFini=_champion->sauterAvant(*jEnnemi.getChampion());
		else
			_actionFini=_champion->sauterArriere(*jEnnemi.getChampion());
	}

	else if(_posHorizontale==-1 && _posVerticale==1)
	{
		if(_champion->getOrientation()==-1)
			_actionFini=_champion->sauterArriere(*jEnnemi.getChampion());
		else
			_actionFini=_champion->sauterAvant(*jEnnemi.getChampion());
	}

	else if(_posHorizontale==1)
	{
		if(_champion->getOrientation()==-1)
			_champion->avancer(*jEnnemi.getChampion());
		else
			_champion->reculer();
	}

	else if(_posHorizontale==-1)
	{
		if(_champion->getOrientation()==-1)
			_champion->reculer();
		else
			_champion->avancer(*jEnnemi.getChampion());
	}

	else if(_posVerticale==1)
		_actionFini=_champion->sauter(_action,*jEnnemi.getChampion(),jEnnemi.getPrendCoup(),_energie);

	else if(_posVerticale==-1)
		_champion->accroupi(_action==0);

	else if(_action==1)
		_actionFini=_champion->punch(*jEnnemi.getChampion(),jEnnemi.getPrendCoup(),_energie);

	else if(_action==2)
		_actionFini=_champion->punchSP(_effet,*jEnnemi.getChampion(),jEnnemi.getPrendCoup(),son,_energie);

	else if(_action==3)
		_actionFini=_champion->kick(*jEnnemi.getChampion(),jEnnemi.getPrendCoup(),_energie);

	else if(_action==4)
		_actionFini=_champion->kickSP(*jEnnemi.getChampion(),jEnnemi.getPrendCoup(),_energie);

	else if(_action==5)
		_actionFini=_champion->SP(_effet,*jEnnemi.getChampion(),jEnnemi.getPrendCoup(),son,_energie);

	else
		_champion->statique(*jEnnemi.getChampion());

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
		return _champion->victoire(son);
	else
		return _champion->mort();
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

void Player::afficherEnergie(sf::RenderWindow& window)
{
	/* gestion de la barre de points de vie */

	if(_PV>66)
		_barrePV[1].setFillColor(sf::Color(0,250,0));
	else if(_PV>33)
		_barrePV[1].setFillColor(sf::Color(255,165,0));
	else
		_barrePV[1].setFillColor(sf::Color(255,0,0));

	if(_PV<0)
		_PV=0;
	_barrePV[1].setSize(sf::Vector2f(_PV*7.15,38));

	/* gestion de la barre d'energie */

	sf::Time elapsed = _clockPasAssez.getElapsedTime();
    int timePA = elapsed.asMilliseconds();

    if(timePA>200)
		_barreEnergie[0].setFillColor(sf::Color(210,254,254));

	if(_energie>=0 && _energie<=100)
		_sauvegardeEnergie=_energie;

	if(_energie==-100)
	{
		_energie=_sauvegardeEnergie;
		_barreEnergie[0].setFillColor(sf::Color(255,30,30));
		_clockPasAssez.restart();
	}
	/*else if(_energie<0)
		_energie=0;*/
	else if(_energie>100)
		_energie=100;

	_barreEnergie[1].setSize(sf::Vector2f(_energie*2.76,38));

	/* affichage des barres */

	for(int i=0;i<2;i++)
	{
		window.draw(_barrePV[i]);
		window.draw(_barreEnergie[i]);
	}

	window.draw(_barreInfos);
	window.draw(_portrait);
}

void Player::affichageChampion(sf::RenderWindow& window)
{
    window.draw(_champion->getSprite());
    window.draw(_effet);
    //window.draw(_champion->getHurtbox());
    //window.draw(_champion->getHitbox());
	//window.draw(_champion->getGardebox());
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
