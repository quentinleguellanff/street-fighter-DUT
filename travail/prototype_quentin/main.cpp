#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"
#include "joueur.h"
#include "collisionmanager.h"
#include "combat.h"
#include "Personnage.h"
#include "Ryu.h"

using namespace std;

int main()
{
    const int LONGUEUR = 900;
    const int LARGEUR = 1440;
    sf::RenderWindow window(sf::VideoMode(LARGEUR,LONGUEUR), "prototype");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(true);

    bool combatEnCours = true;
    bool fincombat = false;
    bool toucheJ1 = false;
    bool toucheJ2 = false;

    //affichage du sol a une position donn�e
    sf::RectangleShape sol(sf::Vector2f(window.getSize().x, 40.f));
    sf::RectangleShape fenetrecollision(sf::Vector2f(window.getSize()));
    //effetcoup.setFillColor(sf::Color::White);
    sol.setPosition(0.f,window.getSize().y-sol.getSize().y);
    sol.setFillColor(sf::Color(255,0,0,130));

    //horloge permettant de r�cuperer le temps
    sf::Clock clockanim;
    sf::Clock clockmove;

    sf::Clock clockanim2;
    sf::Clock clockmove2;

    //CREATION DE DEUX INSTANCES DE LA CLASSE BROLY
    Broly Brolytest(-1);
    Broly Brolytest2(1);


    Personnage* PersoJ1;
    Personnage* PersoJ2;
    PersoJ1 = new Ryu(1,sol);
    PersoJ2 = new Ryu(-1,sol);

    Joueur joueur1(1,Brolytest,PersoJ1);
    Joueur joueur2(2,Brolytest2,PersoJ2);

    Combat combat(joueur1,joueur2,sol);

    while (window.isOpen())
    {
        if(combatEnCours){
            combat.partie(window,toucheJ1,toucheJ2);
            //window.clear();
            //PersoJ1->debout(window,joueur1.getHurtbox());
            //window.display();
        }
        if(fincombat){
            window.clear();
            window.display();
        }

    }
    return 0;
}
