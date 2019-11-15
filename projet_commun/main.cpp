#include "Player.h"
#include "Scene.h"

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

	/* Création des deux champions */
	//Broly champion_P1(-1);
	//Broly champion_P2(1);

	/* Création des 2 classes Player */
	Player joueur1(1);
	Player joueur2(2);

	/* Création des variables pour les actions à effectuer */
	int deplacementX_P1, deplacementY_P1, action_P1;
	int deplacementX_P2, deplacementY_P2, action_P2;

	/* Ouverture de la fenetre */
	while(window.isOpen())
	{
		window.clear();
		sf::Event event;

		/* Récuperation des actions à effectuer */
		deplacementX_P1=joueur1.getPosHorizontale();deplacementY_P1=joueur1.getPosVerticale();action_P1=joueur1.getAction();
		deplacementX_P2=joueu2.getPosHorizontale();deplacementY_P2=joueur2.getPosVerticale();action_P2=joueur2.getAction();

		/* Lancement des animations (avec 2 threads?)*/

		/* Gestion de la fermeture de la fenetre */
		while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.draw(fond.getSprite());
        window.display();
	}
}