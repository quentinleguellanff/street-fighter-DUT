#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"
#include "joueur.h"
#include "collisionmanager.h"

using namespace std;

int main()
{
    const int LONGUEUR = 900;
    const int LARGEUR = 1440;
    sf::RenderWindow window(sf::VideoMode(LARGEUR,LONGUEUR), "prototype");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    bool combat = true;
    bool fincombat = false;
    bool toucheJ1 = false;
    bool toucheJ2 = false;

    //affichage du sol a une position donnée
    sf::RectangleShape sol(sf::Vector2f(window.getSize().x, 40.f));
    sf::RectangleShape fenetrecollision(sf::Vector2f(window.getSize()));
    //effetcoup.setFillColor(sf::Color::White);
    sol.setPosition(0.f,window.getSize().y-sol.getSize().y);
    sol.setFillColor(sf::Color(255,0,0,130));

    //horloge permettant de récuperer le temps
    sf::Clock clockanim;
    sf::Clock clockmove;

    sf::Clock clockanim2;
    sf::Clock clockmove2;

    //CREATION DE DEUX INSTANCES DE LA CLASSE BROLY
    Broly Brolytest(-1);
    Broly Brolytest2(1);



    Joueur joueur1(1,Brolytest);
    Joueur joueur2(2,Brolytest2);

    collisionmanager collision;

    while (window.isOpen())
    {
        if(combat){
            // GESTION DES EVENEMENTS
            window.clear();

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                joueur1.antiSpam(event);
                joueur2.antiSpam(event);
            }

            joueur1.recupCommande();
            joueur2.recupCommande();

            joueur1.saut(window,joueur2.getHurtbox(),joueur2.getEtat());
            joueur2.saut(window,joueur1.getHurtbox(),joueur1.getEtat());

            joueur1.statique(window,joueur2.getHurtbox());
            joueur2.statique(window,joueur1.getHurtbox());

            joueur1.avancedroite(window,joueur2.getHurtbox());
            joueur2.avancedroite(window,joueur1.getHurtbox());

            joueur1.avancegauche(window,joueur2.getHurtbox());
            joueur2.avancegauche(window,joueur1.getHurtbox());

            joueur1.prendCoup(toucheJ1,window);
            joueur2.prendCoup(toucheJ2,window);

            joueur1.coupDePoing(joueur2.getHurtbox(),toucheJ2,window);
            joueur2.coupDePoing(joueur1.getHurtbox(),toucheJ1,window);

            //collision.collisionpersonnage(joueur1,joueur2);

            if(toucheJ2 || toucheJ1){
                //window.draw(effetcoup);
            }

            //window.draw(joueur1.getHurtbox());
            //window.draw(joueur2.getHurtbox());
            window.draw(joueur1.getHitbox());
            window.draw(joueur2.getHitbox());
            window.draw(sol);
            window.draw(joueur1.getBarreVie());
            window.draw(joueur2.getBarreVie());
            window.draw(joueur1.getHurtbox());
            window.draw(joueur2.getHurtbox());
            window.display();
        }
        if(fincombat){
            window.clear();
            window.display();
        }

    }
    return 0;
}
