#include "Player.h"
#include "Scene.h"
#include "Dhalsim.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

int main()
{
	/* Gestion de la fenetre */
	sf::RenderWindow window;
	window.create(sf::VideoMode(1920,1080),"la Bagarre");
	//window.create(sf::VideoMode(1920,1080),"la Bagarre",sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	//window.setMouseCursorVisible(0);

	/* Création de la scene */
	Scene fond(window,1);

	/* Création des horloges pour les animations */
	sf::Clock clockAnim_P1;
	sf::Clock clockAnim_P2;

	/* Création des deux champions */
	Dhalsim champion_P1(-1,fond);
	Dhalsim champion_P2(1,fond);

	/* Création des sprites pour les effets */
	sf::Sprite effet_P1;
	sf::Sprite effet_P2;

	/* Création des 2 classes Player */
	Player joueur1(1);
	Player joueur2(2);

	/* Création des variables pour les actions à effectuer */
	bool apparitionsFinies=false,chargementFini=false;
	int deplacementX_P1, deplacementY_P1, action_P1;
	int deplacementX_P2, deplacementY_P2, action_P2;

	/* Ouverture de la fenetre */
	while(window.isOpen())
	{
		window.clear();
		sf::Event event;


		if(!apparitionsFinies)
		{
			apparitionsFinies=champion_P1.apparition(clockAnim_P1,effet_P1);
			apparitionsFinies=champion_P2.apparition(clockAnim_P2,effet_P2);
		}
		else
		{
			/* Récuperation des actions à effectuer */
			joueur1.recuperationCommandesP1();
			joueur2.recuperationCommandesP2();
			deplacementX_P1=joueur1.getPosHorizontale();deplacementY_P1=joueur1.getPosVerticale();action_P1=joueur1.getAction();
			deplacementX_P2=joueur2.getPosHorizontale();deplacementY_P2=joueur2.getPosVerticale();action_P2=joueur2.getAction();
			cout<<deplacementX_P1<<endl;

			/* Lancement des animations (avec 2 threads?)*/
			if(deplacementX_P1==1)
				champion_P1.avancer(clockAnim_P1);
			else if(deplacementX_P1==-1)
				champion_P1.reculer(clockAnim_P1);
			else
				champion_P1.statique(clockAnim_P1);

			if(deplacementX_P2==1)
				champion_P2.avancer(clockAnim_P2);
			else if(deplacementX_P2==-1)
				champion_P2.reculer(clockAnim_P2);
			else
				champion_P2.statique(clockAnim_P2);

			/* Gestion de la fermeture de la fenetre */
		}

		
		while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.draw(fond.getSprite());
        window.draw(fond.getSol());
        window.draw(champion_P1);
        window.draw(effet_P1);
        window.draw(champion_P2);
        window.draw(effet_P2);
        window.display();

	}
}