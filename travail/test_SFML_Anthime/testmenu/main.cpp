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
	//window.create(sf::VideoMode(1920,1080),"la Bagarre");
	window.create(sf::VideoMode(1920,1080),"la Bagarre",sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	//window.setMouseCursorVisible(0);

	/* Création de la scene */
	Scene fond(window,1);

	/* Création des horloges pour les animations */
	sf::Clock clockAnim_P1;
	sf::Clock clockAttente_P1;
	sf::Clock clockAnim_P2;
	sf::Clock clockAttente_P2;
	sf::Clock clockMenu;

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
	bool apparitionsFinies_P1=false,apparitionsFinies_P2=false,actionFini_P1=true,actionFini_P2=true;
	int deplacementX_P1, deplacementY_P1, action_P1;
	int deplacementX_P2, deplacementY_P2, action_P2;

	///MENU SELECTION -------------------------------------------------------------------------------------------------

      if (!fontMenu.loadFromFile("atari.ttf"))
        {
            cout << "ERREUR : chargement de police atari.ttf" << endl;
        }

      if (!perso1.loadFromFile("browli.png"))
        {
            cout << "ERREUR : chargement d'image personnage : browli.png" << endl;
        }

      if (!perso2.loadFromFile("dhalsim.png"))
        {
            cout << "ERREUR : chargement d'image personnage : dhalsim.png" << endl;
        }

      spriteP1J1.setTexture(perso1);
      spriteP1J1.scale(sf::Vector2f(-1.5,1.5));
      spriteP1J1.setPosition(sf::Vector2f(200.f, 500.f));

      spriteP2J1.setTexture(perso2);
      spriteP2J1.scale(sf::Vector2f(1.5,1.5));
      spriteP2J1.setPosition(sf::Vector2f(-350.f, 500.f));

      spriteP1J2.setTexture(perso1);
      spriteP1J2.scale(sf::Vector2f(1.5,1.5));
      spriteP1J2.setPosition(sf::Vector2f(1350.f, 500.f));

      spriteP2J2.setTexture(perso2);
      spriteP2J2.scale(sf::Vector2f(-1.5,1.5));
      spriteP2J2.setPosition(sf::Vector2f(1980.f, 500.f));

    /// -----------------------------------------------------------------------------------------------------------------------

	/* Ouverture de la fenetre */
	while(window.isOpen())
	{
		window.clear();
		sf::Event event;


			while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

       if((choixJ1 == -1) || (choixJ2 == -1)) {
                        //texte : sélection des personnages
                        titre.setFont(fontMenu);
                        titre.setString("Selection des personnages");
                        titre.setCharacterSize(50);
                        titre.setColor(sf::Color::White);
                        titre.setStyle(sf::Text::Bold);
                        titre.setPosition(sf::Vector2f(580,12));

                        //texte : Joueur 1
                        j1.setFont(fontMenu);
                        j1.setString("Joueur 1");
                        j1.setCharacterSize(26);
                        j1.setColor(sf::Color::White);
                        j1.setStyle(sf::Text::Bold);
                        j1.setPosition(sf::Vector2f(350,100));

                        //texte : Joueur 2
                        j2.setFont(fontMenu);
                        j2.setString("Joueur 2");
                        j2.setCharacterSize(26);
                        j2.setColor(sf::Color::White);
                        j2.setStyle(sf::Text::Bold);
                        j2.setPosition(sf::Vector2f(1150,100));

                        //texte : nomPersoJ1
                        nomPersoJ1.setFont(fontMenu);
                        nomPersoJ1.setString("Broly");
                        nomPersoJ1.setCharacterSize(30);
                        nomPersoJ1.setColor(sf::Color::White);
                        nomPersoJ1.setStyle(sf::Text::Bold);
                        nomPersoJ1.setPosition(sf::Vector2f(350,750));

                        //texte : nomPersoJ2
                        nomPersoJ2.setFont(fontMenu);
                        nomPersoJ2.setString("Broly");
                        nomPersoJ2.setCharacterSize(30);
                        nomPersoJ2.setColor(sf::Color::White);
                        nomPersoJ2.setStyle(sf::Text::Bold);
                        nomPersoJ2.setPosition(sf::Vector2f(1150,750));

                         //délimitation entre la zone de selection j1 et j2
                        ligneDelim.setFillColor(sf::Color::White);
                        ligneDelim.setPosition(sf::Vector2f(800,100));


                   if((sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right) && etatPersoJ2 == 0) {
                        etatPersoJ2 = 1;
                        spriteP1J2.move(sf::Vector2f(400,0));
                        spriteP2J2.move(sf::Vector2f(-400,0));
                        }


                    if((sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left) && etatPersoJ2 == 1) {
                        etatPersoJ2 = 0;
                        spriteP2J2.move(sf::Vector2f(400,0));
                        spriteP1J2.move(sf::Vector2f(-400,0));
                    }

                    if((sf::Event::KeyReleased && event.key.code == sf::Keyboard::D) && etatPersoJ1 == 0) {
                        etatPersoJ1 = 1;
                        spriteP1J1.move(sf::Vector2f(-400,0));
                        spriteP2J1.move(sf::Vector2f(400,0));
                    }

                    if((sf::Event::KeyReleased && event.key.code == sf::Keyboard::Q) && etatPersoJ1 == 1) {
                        etatPersoJ1 = 0;
                        spriteP2J1.move(sf::Vector2f(-400,0));
                        spriteP1J1.move(sf::Vector2f(400,0));
                    }

                    switch(etatPersoJ1){
                        case 0: nomPersoJ1.setString("Broly");
                                break;
                        case 1: nomPersoJ1.setString("Dhalsim");
                                break;
                    }

                    switch(etatPersoJ2){
                        case 0: nomPersoJ2.setString("Broly");
                                break;
                        case 1: nomPersoJ2.setString("Dhalsim");
                                break;
                    }

                    //Validation du choix de personage pour Joueur 1
                    if(sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
                        choixJ1 = etatPersoJ1;
                        etat = 1;
                    }

                    if(sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) {
                  //  if(evenkey.key.code(sf::Keyboard::Enter)) {
                        choixJ2 = etatPersoJ2;
                    }

                    window.clear();
                    window.draw(titre);
                    window.draw(j1);
                    window.draw(j2);
                    window.draw(ligneDelim);
                    window.draw(spriteP1J1);
                    window.draw(spriteP2J1);
                    window.draw(spriteP1J2);
                    window.draw(spriteP2J2);
                    window.draw(nomPersoJ1);
                    window.draw(nomPersoJ2);
                    window.display();

       }
       else if(etat == 1) {


		sf::Time elapsedAttente_P1 = clockAttente_P1.getElapsedTime();
    	int timeAttente_P1 = elapsedAttente_P1.asMilliseconds();

    	sf::Time elapsedAttente_P2 = clockAttente_P2.getElapsedTime();
    	int timeAttente_P2 = elapsedAttente_P2.asMilliseconds();

		if(!apparitionsFinies_P1 || !apparitionsFinies_P2)
		{
			if(!apparitionsFinies_P1)
				apparitionsFinies_P1=champion_P1.apparition(clockAnim_P1,effet_P1);
			if(!apparitionsFinies_P2)
				apparitionsFinies_P2=champion_P2.apparition(clockAnim_P2,effet_P2);
		}
		else
		{
			// Récuperation des actions à effectuer
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

			// Lancement des animations Player 1

			if(deplacementX_P1==1 && deplacementY_P1==1)
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
				actionFini_P1=champion_P1.kick(clockAnim_P1);

			else if(action_P1==3)
				actionFini_P1=champion_P1.punchSP(clockAnim_P1,effet_P1);

			else
				champion_P1.statique(clockAnim_P1,champion_P2);

			if(deplacementY_P1!=-1)
				champion_P1.resetAccroupi();

			// Lancement des animations Player 2

			if(deplacementX_P2==1 && deplacementY_P2==1)
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
				actionFini_P2=champion_P2.punch(clockAnim_P2);

			else if(action_P2==2)
				actionFini_P2=champion_P2.kick(clockAnim_P2);

			else if(action_P2==3)
				actionFini_P2=champion_P2.SP(clockAnim_P2,effet_P2);

			else
				champion_P2.statique(clockAnim_P2,champion_P1);

			if(deplacementY_P2!=-1)
				champion_P2.resetAccroupi();

			// Gestion de la fermeture de la fenetre
		}



        window.draw(fond.getSprite());
        window.draw(fond.getSol());
        window.draw(champion_P1);
        window.draw(champion_P2);
        window.draw(effet_P1);
        window.draw(effet_P2);
        window.display();
	}
	}
}
