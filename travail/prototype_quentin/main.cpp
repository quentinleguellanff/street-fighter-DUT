#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"
#include "collision.h"

using namespace std;

int main()
{
    const int LONGUEUR = 960;
    const int LARGEUR = 1280;
    sf::RenderWindow window(sf::VideoMode(LARGEUR,LONGUEUR), "prototype");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    //affichage du sol a une position donnée
    sf::RectangleShape sol(sf::Vector2f(1280.f, 100.f));
    sol.setPosition(0.f,860.f);
    sol.setFillColor(sf::Color(255,0,0,130));

    //horloge permettant de récuperer le temps
    sf::Clock clockanim;
    sf::Clock clockmove;

    sf::Clock clockanim2;
    sf::Clock clockmove2;

    //CREATION D'UNE INSTANCE DE LA CLASSE BROLY
    Broly Brolytest(-1);
    Broly Brolytest2(1);


    bool prendcoup = false;
    bool prendcoup2 = false;




    sf::Sprite Joueur1;
    sf::Sprite Joueur2;

    bool moveright;
    bool moveright2;
    bool moveleft;
    bool moveleft2;
    bool saut = false;
    bool saut2 = false;
    bool peutcoup = true;
    bool peutcoup2 = true;
    bool coupPoing = false;
    bool coupPoing2 = false;

    while (window.isOpen())
    {
        Joueur1 = Brolytest;
        Joueur2 = Brolytest2;
        moveright = false;
        moveleft = false;
        moveright2 = false;
        moveleft2 = false;


        // GESTION DES EVENEMENTS
        window.clear();



        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::M)
            {
                peutcoup = true;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A)
            {
                peutcoup2 = true;
            }
        }
        /*
        ////////////////////COMMANDE JOUEUR 1////////////////
        *
        *
        *
        *
        **/
        if(!prendcoup)
        {
            if(!coupPoing)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    if(!(Brolytest.getPosition().x + Brolytest.getLocalBounds().width*2 + 10 > LARGEUR))
                    {
                        moveright = true;
                    }
                    if(Brolytest.collisioncorps(Brolytest2))
                    {
                        moveright = false;
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    if(!(Brolytest.getPosition().x - 10 < 0))
                    {
                        moveleft = true;
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    saut = true;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                {
                    if(peutcoup && !prendcoup)
                    {
                        coupPoing = true;
                    }
                }
                if(moveright)
                {
                    sf::Time elapsed = clockmove.getElapsedTime();
                    int timemove = elapsed.asMilliseconds();
                    int v_x = +15;
                    if(timemove > 20)
                    {
                        Joueur1.setPosition(Joueur1.getPosition().x+v_x,Joueur1.getPosition().y);
                        clockmove.restart();
                    }
                    Brolytest.setPosition(Joueur1.getPosition());
                    Brolytest.avancer(clockanim);
                    saut = false;
                }
                if(moveleft)
                {

                    sf::Time elapsed = clockmove.getElapsedTime();
                    int timemove = elapsed.asMilliseconds();
                    int v_x = -15;
                    if(timemove > 20)
                    {
                        Joueur1.setPosition(Joueur1.getPosition().x+v_x,Joueur1.getPosition().y);
                        clockmove.restart();
                    }
                    Brolytest.setPosition(Joueur1.getPosition());
                    Brolytest.reculer(clockanim);
                    saut = false;
                }
                if(!moveright && !moveleft && !saut && !coupPoing && !prendcoup)
                {
                    Brolytest.debout(clockanim);

                }
                if(saut)
                {
                    Brolytest.sauter(clockanim);
                }
            }
            if(coupPoing)
            {
                peutcoup = false;
                coupPoing = Brolytest.coupDePoing(clockanim,Brolytest2.gethurtbox(),prendcoup2);
                window.draw(Brolytest.gethitbox());
                /*if(Brolytest.collisioncoup(Brolytest2.gethurtbox())){
                     prendcoup2 = true;
                }
                */
                if(!coupPoing)
                {
                    if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::M)))
                    {
                        peutcoup = true;
                    }
                }
            }
        }
        /*
        ////////////////////COMMANDE JOUEUR 2////////////////
        *
        *
        *
        *
        **/
        if(!prendcoup2)
        {
            if(!coupPoing2)
            {

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    if(!(Brolytest2.gethurtbox().getGlobalBounds().left + Brolytest2.gethurtbox().getLocalBounds().width  > LARGEUR))
                    {
                        moveright2 = true;
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                {
                    if(!(Brolytest2.getPosition().x - 10 < 0))
                    {
                        moveleft2 = true;
                    }
                    if(Brolytest2.collisioncorps(Brolytest))
                    {
                        moveleft2 = false;
                    }

                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                {
                    saut2 = true;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    if(peutcoup2 && !prendcoup2)
                    {
                        coupPoing2 = true;
                    }
                }
                if(moveright2)
                {
                    sf::Time elapsed = clockmove2.getElapsedTime();
                    int timemove = elapsed.asMilliseconds();
                    int v_x = +15;
                    if(timemove > 20)
                    {
                        Joueur2.setPosition(Joueur2.getPosition().x+v_x,Joueur2.getPosition().y);
                        clockmove2.restart();
                    }
                    Brolytest2.setPosition(Joueur2.getPosition());
                    Brolytest2.reculer(clockanim2);
                    saut2 = false;
                }
                if(moveleft2)
                {

                    sf::Time elapsed = clockmove2.getElapsedTime();
                    int timemove = elapsed.asMilliseconds();
                    int v_x = -15;
                    if(timemove > 20)
                    {
                        Joueur2.setPosition(Joueur2.getPosition().x+v_x,Joueur2.getPosition().y);
                        clockmove2.restart();
                    }
                    Brolytest2.setPosition(Joueur2.getPosition());
                    Brolytest2.avancer(clockanim2);
                    saut2 = false;
                }
                if(!moveright2 && !moveleft2 && !saut2 && !coupPoing2 && !prendcoup2)
                {
                    Brolytest2.debout(clockanim2);
                }
                if(saut2)
                {
                    Brolytest2.sauter(clockanim2);
                }
            }

            if(coupPoing2)
            {
                prendcoup2 = false;
                peutcoup2 = false;
                coupPoing2 = Brolytest2.coupDePoing(clockanim2,Brolytest.gethurtbox(),prendcoup);
                window.draw(Brolytest2.gethitbox());
                /*if(Brolytest2.collisioncoup(Brolytest.gethurtbox())){
                    prendcoup = true;
                }
                */
                if(!coupPoing2)
                {
                    if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
                    {
                        peutcoup2 = true;
                    }
                }
            }
        }

        ///////////////INTERACTION//////////////////////
        /* if(prendcoup && prendcoup2){
             prendcoup = Brolytest.prendcoup(clockanim);
             prendcoup2 = Brolytest2.prendcoup(clockanim2);

         }*/

        if(prendcoup)
        {

            if(coupPoing){
                coupPoing = false;
                Brolytest.setPosition(Brolytest.getPosition().x+112*Brolytest.getorientation(),Brolytest.getPosition().y);
                Brolytest.resetcoup();
            }
            Brolytest.prendcoup(clockanim,prendcoup);
            if(!prendcoup){
                peutcoup = true;
            }
        }
        if(prendcoup2)
        {
            if(coupPoing2){
                coupPoing2 = false;
                Brolytest2.setPosition(Brolytest2.getPosition().x+112*Brolytest2.getorientation(),Brolytest2.getPosition().y);
                Brolytest2.resetcoup();
            }
            Brolytest2.prendcoup(clockanim2,prendcoup2);
            if(!prendcoup2){
                peutcoup2 = true;
            }
        }
        cout << " Broly1 touche  : " << prendcoup << endl;
        cout << " Broly2 touche  : " << prendcoup2 << endl;
        //AFFICHAGE
        window.draw(Joueur1);
        window.draw(Joueur2);
        window.draw(Brolytest2.gethurtbox());
        window.draw(Brolytest.gethurtbox());
        window.draw(sol);
        window.display();

    }
    return 0;
}
