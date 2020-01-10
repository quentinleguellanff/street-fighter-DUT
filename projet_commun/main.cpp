#include "IncludeManager.h"
#include "Player.h"

#include <iostream>
#include <thread>
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
	sf::Clock clockAttente;
	sf::Clock clockReadyFight;

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


	///sprite affichage ready, fight
	sf::Texture readyF;
    sf::Sprite readyFight;

    if(!readyF.loadFromFile("background/SdHUDAtlas.png")) {
        std::cout<<"erreur background/SdHUDAtlas.png";
    }


	/* Création des variables pour les actions à effectuer */
	bool apparitionsFinies_P1=false,apparitionsFinies_P2=false,actionFini_P1=true,actionFini_P2=true,animationFinLancee=false,animationFin_P1=false,animationFin_P2=false;

	/* Déclarations pour le menu */
	int selecEcran=0;


    MenuPrincipal menuPrinc(window.getSize().x, window.getSize().y);

    /* Déclaration menu selection */
    MenuSelection menuSel(window);
    sf::Event eventS;

    /* Déclaration menu commandes */
    MenuCommandes menuCommandes(window);

    MenuBackground menuBackground(window);

    /* Musique */
	sf::Music musique;
    if (!musique.openFromFile("musique/theme_menu_princ.ogg")){
        std::cout<<"erreur musique";
    }
    musique.setVolume(00.f) ;
    musique.play();
    musique.setLoop(true);


	/* Ouverture de la fenetre */
	while(window.isOpen())
	{
		window.clear();
		sf::Event event;

    	if (selecEcran==0)	//menu principal
    	{
            while (window.pollEvent(event))
                menuPrinc.bouger(selecEcran,event, window);

	        menuPrinc.draw(window);
	        window.display();

	        if(selecEcran==1)
	        {
	        	if (!musique.openFromFile("musique/theme_menu_perso.ogg")){
                    std::cout<<"erreur musique";
	            }
	            musique.play();
	            musique.setLoop(true);
	        }
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

	        if(selecChamp_P1!=-1 && selecChamp_P2!=-1)
	        {
	        	joueur1.setChampion(champion_P1);
	        	joueur2.setChampion(champion_P2);
	        }

	        if(selecEcran==0)
	        {
	        	if (!musique.openFromFile("musique/theme_menu_princ.ogg")){
                    std::cout<<"erreur musique";
	            }
	            musique.play();
	            musique.setLoop(true);

	        }else if(selecEcran==2)
	        {
	        	fond.lancerMusique(musique);
	        }

        }else if(selecEcran==3)
        {
            while (window.pollEvent(event))
                menuCommandes.retourMenu(selecEcran,event);
            menuCommandes.draw(window);
            window.display();
        }else if (selecEcran==4)
        {
            while (window.pollEvent(event))
            {
                menuBackground.retourMenu2(selecEcran,event, menuSel,window);
                menuBackground.bouger(event, window);
                menuBackground.selectionner(event, window, selecEcran, fond/*, champion_P2, champion_P1*/);
            }
    
            menuBackground.draw(window);
            window.display();

        }else if(selecEcran==2)	//lancement du combat
        {
        	/* Gestion de la fermeture de la fenetre */
			while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();

	            joueur1.peutAttaquerP1(event,window);
	            joueur2.peutAttaquerP2(event,window);
	        }

        	/* lancement des animations de début de combat */
			if(!apparitionsFinies_P1 || !apparitionsFinies_P2)
			{
				///
				readyFight.setTexture(readyF);
                readyFight.setPosition(sf::Vector2f(window.getSize().x*0.45,100));
                readyFight.setTextureRect(sf::IntRect(666,435,300,74));

				if(!apparitionsFinies_P1)
					apparitionsFinies_P1=joueur1.lancerApparition();
				if(!apparitionsFinies_P2)
					apparitionsFinies_P2=joueur2.lancerApparition();
                clockReadyFight.restart();

			}else if( (joueur1.getPV()<=0 || joueur2.getPV()<=0) && ( ( joueur1.getChampion()->auSol() && joueur2.getChampion()->auSol() ) || animationFinLancee ) )
	        {
	        	animationFinLancee=true;
	        	if(animationFin_P1==false)
	        		animationFin_P1=joueur1.finPartie();
	        	if(animationFin_P2==false)
	        		animationFin_P2=joueur2.finPartie();

	        	if(animationFin_P1==true && animationFin_P2==true)
	        	{
	        		clockAttente.restart();
		        	apparitionsFinies_P1=false;apparitionsFinies_P2=false;
		        	animationFin_P1=false;animationFin_P2=false;animationFinLancee=false;
		        	actionFini_P1=true;actionFini_P2=true;
		        	selecEcran=0;
		        	joueur1.resetPV();
		        	joueur1.getChampion()->resetHitbox();
		        	joueur2.resetPV();
		        	joueur2.getChampion()->resetHitbox();
		        	menuSel.reset(window);

		        	if (!musique.openFromFile("musique/theme_menu_princ.ogg")){
				        std::cout<<"erreur musique";
				    }
				    musique.setVolume(50.f) ;
				    musique.play();
				    musique.setLoop(true);
		        }
	        }else
			{
                readyFight.setTextureRect(sf::IntRect(0,401,373,107));
                if(clockReadyFight.getElapsedTime().asSeconds() > 1) {
                    readyFight.setTextureRect(sf::IntRect(0,2,0,0));

                }
				/* Récuperation des actions à effectuer */
				if(actionFini_P1)
				{
					joueur1.recuperationCommandesP1(joueur2);
				}else if(actionFini_P1==false)
				{
					joueur1.recuperationAttaquesP1();
				}


				if(actionFini_P2)
				{
					joueur2.recuperationCommandesP2(joueur1);
				}else if(actionFini_P2==false)
				{
					joueur2.recuperationAttaquesP2();
				}
				
				/* Lancement des animations Player 2*/
				actionFini_P2=joueur2.lancerActions(joueur1);

				/* Lancement des animations Player 1*/
				actionFini_P1=joueur1.lancerActions(joueur2);	
				
			}

			/* Gestion de la fermeture de la fenetre */
			while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }

	        /* affichage des élements graphiques */
	        window.draw(fond.getSprite());

	        joueur1.afficherEnergie(window);

	        joueur2.afficherEnergie(window);

	        window.draw(joueur1.getChampion()->getSprite());
	        window.draw(joueur1.getEffet());
	        //window.draw(joueur1.getChampion()->getHurtbox());
	        //window.draw(joueur1.getChampion()->getHitbox());
	    	//window.draw(joueur1.getChampion()->getGardebox());

	        window.draw(joueur2.getChampion()->getSprite());
	        window.draw(joueur2.getEffet());
	        //window.draw(joueur2.getChampion()->getHurtbox());
	      	//window.draw(joueur2.getChampion()->getHitbox());
	      	//window.draw(joueur2.getChampion()->getGardebox());

	      	///
            window.draw(readyFight);
	        window.display();
	    }else if(selecEcran==-1) //fermuture de la fenetre
	    {
	    	window.close();
	    }
	}
}

