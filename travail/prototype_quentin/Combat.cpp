#include "Combat.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"
#include "joueur.h"

Combat::Combat(Joueur& joueur1, Joueur& joueur2,sf::RectangleShape& sol)
{
    _joueur1 = joueur1;
    _joueur2 = joueur2;
    _sol = sol;
}

Combat::~Combat()
{
    //dtor
}

bool Combat::partie(sf::RenderWindow& window,bool& toucheJ1, bool& toucheJ2){

            window.clear();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                _joueur1.antiSpam(event);
                _joueur2.antiSpam(event);
            }

            _joueur1.recupCommande();
            _joueur2.recupCommande();

            _joueur1.saut(window,_joueur2.getHurtbox(),_joueur2.getEtat());
            _joueur2.saut(window,_joueur1.getHurtbox(),_joueur1.getEtat());

            _joueur1.statique(window,_joueur2.getHurtbox());
            _joueur2.statique(window,_joueur1.getHurtbox());

            _joueur1.avancedroite(window,_joueur2.getHurtbox());
            _joueur2.avancedroite(window,_joueur1.getHurtbox());

            _joueur1.avancegauche(window,_joueur2.getHurtbox());
            _joueur2.avancegauche(window,_joueur1.getHurtbox());

            _joueur1.prendCoup(toucheJ1,window);
            _joueur2.prendCoup(toucheJ2,window);

            _joueur1.coupDePoing(_joueur2.getHurtbox(),toucheJ2,window);
            _joueur2.coupDePoing(_joueur1.getHurtbox(),toucheJ1,window);

            //window.draw(_joueur1.getHitbox());
            //window.draw(_joueur2.getHitbox());
            window.draw(_sol);
            window.draw(_joueur1.getBarreVie());
            window.draw(_joueur2.getBarreVie());
            //window.draw(_joueur1.getHurtbox());
            //window.draw(_joueur2.getHurtbox());
            window.display();
            return true;
}
