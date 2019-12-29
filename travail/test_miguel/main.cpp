#include "IncludeManager.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

using namespace std;

int main()
{
	/* Gestion de la fenetre */
	sf::RenderWindow window;
	window.create(sf::VideoMode(),"la Bagarre",sf::Style::Fullscreen);
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

	/* Variable de création des deux champions */
	int selecChamp_P1=-1,selecChamp_P2=-1;	//variables destinées à la selection du champion
	Personnage* champion_P1;
	Personnage* champion_P2;

	/* Création des sprites pour les effets */
	sf::Sprite effet_P1;
	sf::Sprite effet_P2;

	/* Création des 2 classes Player */
	Player joueur1(1,window);
	Player joueur2(2,window);

	/* Création des variables pour les actions à effectuer */
	bool apparitionsFinies_P1=false,apparitionsFinies_P2=false,actionFini_P1=true,actionFini_P2=true,etaitAccroupi_P1=false,etaitAccroupi_P2=false;
	bool prendCoup_P1=false,prendCoup_P2=false;
	int deplacementX_P1, deplacementY_P1, action_P1, derniereAction_P1=-1;
	int deplacementX_P2, deplacementY_P2, action_P2, derniereAction_P2=-1;

	/* Déclarations pour le menu */
	int selecEcran=0;


    MenuPrincipal menuPrinc(window.getSize().x, window.getSize().y);

    /* Déclaration menu selection */
    MenuSelection menuSel(window);
    sf::Event eventS;

    /* Déclaration menu commandes */
    MenuCommandes menuCommandes;

    /* Musique */
	sf::Music musique;
    if (!musique.openFromFile("musique/musicBagarre.ogg")){
            std::cout<<"erreur musique";
    }
    musique.setVolume(0.f) ;
    musique.play();
    musique.setLoop(true);

    /* Effets musicaux champions */
    sf::Music son_P1;
    sf::Music son_P2;

	/* Ouverture de la fenetre */
	while(window.isOpen())
	{
		window.clear();
		sf::Event event;

		/* initialisation des timers pour permettre entre la demande du saut et de l'attaque en l'air */
		sf::Time elapsedAttente_P1 = clockAttente_P1.getElapsedTime();
    	int timeAttente_P1 = elapsedAttente_P1.asMilliseconds();

    	sf::Time elapsedAttente_P2 = clockAttente_P2.getElapsedTime();
    	int timeAttente_P2 = elapsedAttente_P2.asMilliseconds();


    	if (selecEcran==0)	//menu principal
    	{
            while (window.pollEvent(event))
                menuPrinc.bouger(selecEcran,event, window);

	        menuPrinc.draw(window);
	        window.display();
        }

        else if(selecEcran==1) //menu de selection des personnages
        {
            while (window.pollEvent(eventS))
	        {
	            if (eventS.type == sf::Event::Closed)
	                window.close();
                    menuSel.bouger(eventS,window);
                    selecEcran = menuSel.validationPerso(eventS,selecChamp_P1,selecChamp_P2);
	        }

            window.clear();
            menuSel.draw(window);
	        window.display();

	        if(selecChamp_P1==0)
	        {
	        	champion_P1=new Jotaro(-1,fond);
	        }else if(selecChamp_P1==1)
	        {
	        	champion_P1=new Dhalsim(-1,fond);
	        }else if(selecChamp_P1==2)
	        {
	        	champion_P1=new Ryu(-1,fond);
	        }

	        if(selecChamp_P2==0)
	        {
	        	champion_P2= new Jotaro(1,fond);
	        }else if(selecChamp_P2==1)
	        {
	        	champion_P2=new Dhalsim(1,fond);
	        }else if(selecChamp_P2==2)
	        {
	        	champion_P2=new Ryu(1,fond);
	        }


        }else if(selecEcran==3)
        {
            while (window.pollEvent(event))
                menuCommandes.retourMenu(selecEcran,event);
            menuCommandes.draw(window);
            window.display();
        }else if(selecEcran==2)	//lancement du combat
        {
        	/* lancement des animations de début de combat */
			if(!apparitionsFinies_P1 || !apparitionsFinies_P2)
			{
				if(!apparitionsFinies_P1)
					apparitionsFinies_P1=champion_P1->apparition(clockAnim_P1,effet_P1);
				if(!apparitionsFinies_P2)
					apparitionsFinies_P2=champion_P2->apparition(clockAnim_P2,effet_P2);
			}
			else
			{
				/* Récuperation des actions à effectuer */
				if(actionFini_P1)
				{
					joueur1.recuperationCommandesP1();
					deplacementX_P1=joueur1.getPosHorizontale();deplacementY_P1=joueur1.getPosVerticale();action_P1=joueur1.getAction();
				}else if(actionFini_P1==false && timeAttente_P1<150)
				{
					joueur1.recuperationAttaquesP1();
					action_P1=joueur1.getAction();
				}
				if(actionFini_P2)
				{
					joueur2.recuperationCommandesP2();
					deplacementX_P2=joueur2.getPosHorizontale();deplacementY_P2=joueur2.getPosVerticale();action_P2=joueur2.getAction();
				}else if(actionFini_P2==false && timeAttente_P2<150)
				{
					joueur2.recuperationAttaquesP2();
					action_P2=joueur2.getAction();
				}

				/* Lancement des animations Player 1*/

				//joueur1.lancerActions(*champion_P1,*champion_P2,joueur2);

				/* Lancement des animations Player 2*/

				if(prendCoup_P2)
				{
					deplacementX_P2==0;deplacementY_P2==0;action_P2=-1;
					actionFini_P2=champion_P2->prendCoup(clockAnim_P2,prendCoup_P2,effet_P2);
				}
				else if(derniereAction_P2!=action_P2 && derniereAction_P2==0 && deplacementY_P2==0)
					actionFini_P2=champion_P2->finGarde(clockAnim_P2);

				else if(deplacementX_P2==1 && deplacementY_P2==1)
				{
					if(champion_P2->getOrientation()==1)
						actionFini_P2=champion_P2->sauterAvant(clockAnim_P2,*champion_P1);
					else
						actionFini_P2=champion_P2->sauterArriere(clockAnim_P2,*champion_P1);
				}
				else if(deplacementX_P2==-1 && deplacementY_P2==1)
				{
					if(champion_P2->getOrientation()==1)
						actionFini_P2=champion_P2->sauterArriere(clockAnim_P2,*champion_P1);
					else
						actionFini_P2=champion_P2->sauterAvant(clockAnim_P2,*champion_P1);
				}
				else if(deplacementY_P2==1 && action_P2==2)
				{
					int n;
					actionFini_P2=champion_P2->sautKick(clockAnim_P2,*champion_P1,prendCoup_P1,joueur1,n);
				}
				else if(deplacementY_P2==1 && action_P2==1)
					actionFini_P2=champion_P2->sautPunch(clockAnim_P2,*champion_P1,prendCoup_P1,joueur1);

				else if(deplacementX_P2==1)
				{
					if(champion_P2->getOrientation()==1)
						champion_P2->avancer(clockAnim_P2,*champion_P1);
					else
						champion_P2->reculer(clockAnim_P2);
				}
				else if(deplacementX_P2==-1)
				{
					if(champion_P2->getOrientation()==1)
						champion_P2->reculer(clockAnim_P2);
					else
						champion_P2->avancer(clockAnim_P2,*champion_P1);
				}
				else if(deplacementY_P2==1)
					actionFini_P2=champion_P2->sauter(clockAnim_P2,clockAttente_P2,*champion_P1);

				else if(deplacementY_P2==-1)
					champion_P2->accroupi(clockAnim_P2,action_P2==0);

				else if(action_P2==0)
					champion_P2->garde(clockAnim_P2);

				else if(action_P2==1)
					actionFini_P2=champion_P2->punch(clockAnim_P2,*champion_P1,prendCoup_P1,joueur1);

				else if(action_P2==2)
					actionFini_P2=champion_P2->kick(clockAnim_P2,*champion_P1,prendCoup_P1,joueur1);

				else if(action_P2==3)
					actionFini_P2=champion_P2->SP(clockAnim_P2,effet_P2,*champion_P1,prendCoup_P1,joueur1,son_P2);

				else
					champion_P2->statique(clockAnim_P2,*champion_P1);

				if(deplacementY_P2!=-1)
					champion_P2->resetCptAccroupi();

				if( !(action_P1!=derniereAction_P2 && derniereAction_P2==0) || actionFini_P2==true)
					derniereAction_P2=action_P2;
			}

			/* Gestion de la fermeture de la fenetre */
			while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }

	        /* renvoi sur le menu principal car fin de partie */
	        if(actionFini_P1 && actionFini_P2 && (joueur1.getPV()<=0 || joueur2.getPV()<=0)) 
	        {
	        	selecEcran=0;
	        	joueur1.resetPV();
	        	joueur2.resetPV();
	        	menuSel.reset();
	        }	


	        /* affichage des élements graphiques */
	        window.draw(fond.getSprite());
	        //window.draw(fond.getSol());

	        window.draw(joueur1.getBarrePV());
	        window.draw(joueur2.getBarrePV());

	        window.draw(champion_P1->getSprite());
	        window.draw(effet_P1);
	        window.draw(champion_P1->getHurtbox());
	        window.draw(champion_P1->getHitbox());

	        window.draw(champion_P2->getSprite());
	        window.draw(effet_P2);
	        window.draw(champion_P2->getHurtbox());
	      	//window.draw(champion_P2->getHitbox());

	        window.display();
	    }else if(selecEcran==-1) //fermuture de la fenetre
	    {
	    	window.close();
	    }
	}
}

