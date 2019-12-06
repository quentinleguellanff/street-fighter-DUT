#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"
#include "joueur.h"

using namespace std;

int main()
{
    const int LONGUEUR = 960;
    const int LARGEUR = 1280;
    sf::RenderWindow window(sf::VideoMode(LARGEUR,LONGUEUR), "prototype");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    bool combat = true;
    bool fincombat = false;

    //affichage du sol a une position donnée
    sf::RectangleShape sol(sf::Vector2f(1280.f, 100.f));
    sol.setPosition(0.f,860.f);
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

            joueur1.prendCoup(clockanim,joueur1.prendcoup,window);
            joueur2.prendCoup(clockanim2,joueur2.prendcoup,window);

            joueur1.statique(clockanim,window);
            joueur2.statique(clockanim2,window);

            joueur1.avancedroite(clockanim,clockmove,window);
            joueur2.avancedroite(clockanim2,clockmove2,window);

            joueur1.avancegauche(clockanim,clockmove,window);
            joueur2.avancegauche(clockanim2,clockmove2,window);

            joueur1.coupDePoing(clockanim,joueur2.getHurtbox(),joueur2.prendcoup,window);
            joueur2.coupDePoing(clockanim2,joueur1.getHurtbox(),joueur1.prendcoup,window);


            //window.draw(joueur1.getHurtbox());
            //window.draw(joueur2.getHurtbox());
            //window.draw(joueur1.getHitbox());
            //window.draw(joueur2.getHitbox());
            window.draw(sol);
            window.draw(joueur1.getBarreVie());
            window.draw(joueur2.getBarreVie());
            window.display();
        }
        if(fincombat){
            window.clear();
            window.display();
        }

    }
    return 0;
}
