#include "IncludeManager.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

int main()
{
	/* Gestion de la fenetre */
	sf::RenderWindow window;
	//window.create(sf::VideoMode(1920,1080),"la Bagarre",sf::Style::Fullscreen);
	window.create(sf::VideoMode(1920,1080),"la Bagarre");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(0);

	/* Création de la scene */
	Scene fond(window,1);

	/* Création des horloges pour les animations */
	sf::Clock clockAnim_P1;
	sf::Clock clockAttente_P1;
	sf::Clock clockAnim_P2;
	sf::Clock clockAttente_P2;

	/* Création des deux champions */
	Jotaro champion_P1(-1,fond);
	Dhalsim champion_P2(1,fond);

	/* Création des sprites pour les effets */
	sf::Sprite effet_P1;
	sf::Sprite effet_P2;

	/* Création des 2 classes Player */
	Player joueur1(1);
	Player joueur2(2);

	/* Création des variables pour les actions à effectuer */
	bool apparitionsFinies_P1=false,apparitionsFinies_P2=false,actionFini_P1=true,actionFini_P2=true,etaitAccroupi_P1=false,etaitAccroupi_P2=false;
	int deplacementX_P1, deplacementY_P1, action_P1, derniereAction_P1=-1;
	int deplacementX_P2, deplacementY_P2, action_P2, derniereAction_P2=-1;

	/* Déclarations pour le menu */
	int selecEcran=1;
	bool peutmonter = true, peutdescendre = true;
	sf::Texture menufond;
    if(!menufond.loadFromFile("background/menu.png")){
        std::cout<<"erreur fond"<<endl;
    }
    sf::Sprite spritemenu;
    spritemenu.setTexture(menufond);
	Menu menu(window.getSize().x, window.getSize().y);

	/* Ouverture de la fenetre */
	while(window.isOpen())
	{
		window.clear();
		sf::Event event;

		sf::Time elapsedAttente_P1 = clockAttente_P1.getElapsedTime();
    	int timeAttente_P1 = elapsedAttente_P1.asMilliseconds();

    	sf::Time elapsedAttente_P2 = clockAttente_P2.getElapsedTime();
    	int timeAttente_P2 = elapsedAttente_P2.asMilliseconds();

		
    	if (selecEcran==0)
    	{
            while (window.pollEvent(event))
                menu.bouger(selecEcran,event);            
	        
	        window.draw(spritemenu);
	        menu.draw(window);
	        window.display();
        }

        else if(selecEcran==1)
        {
			if(!apparitionsFinies_P1 || !apparitionsFinies_P2)
			{
				if(!apparitionsFinies_P1)
					apparitionsFinies_P1=champion_P1.apparition(clockAnim_P1,effet_P1);
				if(!apparitionsFinies_P2)
					apparitionsFinies_P2=champion_P2.apparition(clockAnim_P2,effet_P2);
			}
			else
			{
				/* Récuperation des actions à effectuer */
				if(actionFini_P1)
				{
					champion_P1.reset();
					joueur1.recuperationCommandesP1();
					deplacementX_P1=joueur1.getPosHorizontale();deplacementY_P1=joueur1.getPosVerticale();action_P1=joueur1.getAction();
				}else if(actionFini_P1==false && timeAttente_P1<150)
				{
					joueur1.recuperationAttaquesP1();
					action_P1=joueur1.getAction();
				}
				if(actionFini_P2)
				{	
					champion_P2.reset();
					joueur2.recuperationCommandesP2();
					deplacementX_P2=joueur2.getPosHorizontale();deplacementY_P2=joueur2.getPosVerticale();action_P2=joueur2.getAction();
				}else if(actionFini_P2==false && timeAttente_P2<150)
				{
					joueur2.recuperationAttaquesP2();
					action_P2=joueur2.getAction();
				}

				/* Lancement des animations Player 1*/

				if(action_P1!=derniereAction_P1 && derniereAction_P1==0 && deplacementY_P1==0)
					actionFini_P1=champion_P1.finGarde(clockAnim_P1);
				else if(etaitAccroupi_P1 && deplacementY_P1!=-1)
					actionFini_P1=champion_P1.seLever(clockAnim_P1);
				else if(deplacementX_P1==1 && deplacementY_P1==1)
				{
					if(champion_P1.getOrientation()==-1)
						actionFini_P1=champion_P1.sauterAvant(clockAnim_P1,champion_P2);
					else
						actionFini_P1=champion_P1.sauterArriere(clockAnim_P1);
				}
				else if(deplacementX_P1==-1 && deplacementY_P1==1)
				{
					if(champion_P1.getOrientation()==-1)	
						actionFini_P1=champion_P1.sauterArriere(clockAnim_P1);
					else
						actionFini_P1=champion_P1.sauterAvant(clockAnim_P1,champion_P2);
				}
				else if(deplacementY_P1==1 && action_P1==2)
					actionFini_P1=champion_P1.sautKick(clockAnim_P1);

				else if(deplacementY_P1==1 && action_P1==1)
					actionFini_P1=champion_P1.sautPunch(clockAnim_P1);

				else if(deplacementX_P1==1)
				{
					if(champion_P1.getOrientation()==-1)	
						champion_P1.avancer(clockAnim_P1,champion_P2);
					else 
						champion_P1.reculer(clockAnim_P1);
				}
				else if(deplacementX_P1==-1)
				{
					if(champion_P1.getOrientation()==-1)
						champion_P1.reculer(clockAnim_P1);
					else
						champion_P1.avancer(clockAnim_P1,champion_P2);
				}
				else if(deplacementY_P1==1)
					actionFini_P1=champion_P1.sauter(clockAnim_P1,clockAttente_P1);

				else if(deplacementY_P1==-1)
					champion_P1.accroupi(clockAnim_P1,action_P1==0);

				else if(action_P1==0)
					champion_P1.garde(clockAnim_P1);

				else if(action_P1==1)
					actionFini_P1=champion_P1.punch(clockAnim_P1);

				else if(action_P1==2)
					actionFini_P1=champion_P1.prendCoup(clockAnim_P1);

				else if(action_P1==3)
					actionFini_P1=champion_P1.SP(clockAnim_P1,effet_P1);

				else
					champion_P1.statique(clockAnim_P1,champion_P2);

				if(deplacementY_P1!=-1)
					champion_P1.resetAccroupi();

				if( !(action_P1!=derniereAction_P1 && derniereAction_P1==0) || actionFini_P1==true)
					derniereAction_P1=action_P1;

				if(actionFini_P1==true)
					etaitAccroupi_P1=(deplacementY_P1==-1);

				/* Lancement des animations Player 2*/

				if(derniereAction_P2!=action_P2 && derniereAction_P2==0 && deplacementY_P2==0)
					actionFini_P2=champion_P2.finGarde(clockAnim_P2);

				else if(deplacementX_P2==1 && deplacementY_P2==1)
				{
					if(champion_P2.getOrientation()==1)	
						actionFini_P2=champion_P2.sauterAvant(clockAnim_P2,champion_P1);
					else
						actionFini_P2=champion_P2.sauterArriere(clockAnim_P2);
				}
				else if(deplacementX_P2==-1 && deplacementY_P2==1)
				{
					if(champion_P2.getOrientation()==1)	
						actionFini_P2=champion_P2.sauterArriere(clockAnim_P2);
					else
						actionFini_P2=champion_P2.sauterAvant(clockAnim_P2,champion_P1);
				}
				else if(deplacementY_P2==1 && action_P2==2)
					actionFini_P2=champion_P2.sautKick(clockAnim_P2);

				else if(deplacementY_P2==1 && action_P2==1)
					actionFini_P2=champion_P2.sautPunch(clockAnim_P2);

				else if(deplacementX_P2==1)
				{
					if(champion_P2.getOrientation()==1)
						champion_P2.avancer(clockAnim_P2,champion_P1);
					else
						champion_P2.reculer(clockAnim_P2); 
				}
				else if(deplacementX_P2==-1)
				{
					if(champion_P2.getOrientation()==1)	
						champion_P2.reculer(clockAnim_P2);
					else
						champion_P2.avancer(clockAnim_P2,champion_P1);
				}
				else if(deplacementY_P2==1)
					actionFini_P2=champion_P2.sauter(clockAnim_P2,clockAttente_P2);

				else if(deplacementY_P2==-1)
					champion_P2.accroupi(clockAnim_P2,action_P2==0);

				else if(action_P2==0)
					champion_P2.garde(clockAnim_P2);

				else if(action_P2==1)
					actionFini_P2=champion_P2.prendCoup(clockAnim_P2);

				else if(action_P2==2)
					actionFini_P2=champion_P2.kick(clockAnim_P2);

				else if(action_P2==3)
					actionFini_P2=champion_P2.SP(clockAnim_P2,effet_P2);

				else
					champion_P2.statique(clockAnim_P2,champion_P1);

				if(deplacementY_P2!=-1)
					champion_P2.resetAccroupi();

				if( !(action_P1!=derniereAction_P2 && derniereAction_P2==0) || actionFini_P2==true)
					derniereAction_P2=action_P2;
			}

			/* Gestion de la fermeture de la fenetre */
			while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }


	        window.draw(fond.getSprite());
	        window.draw(fond.getSol());

	        window.draw(champion_P1);
	        window.draw(effet_P1);
	        window.draw(champion_P1.getHurtbox());
	        window.draw(champion_P1.getHitbox());

	        window.draw(champion_P2);
	        window.draw(effet_P2);
	        window.draw(champion_P2.getHurtbox());
	        window.draw(champion_P2.getHitbox());

	        window.display();

	    }else if(selecEcran==-1)
	    {
	    	window.close();
	    }
	}
}