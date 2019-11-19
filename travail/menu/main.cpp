#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include"menu.h"
#include "Broly.h"
using namespace std;


int main()
{
    const int LONGUEUR = 960;
    const int LARGEUR = 1280;
    sf::RenderWindow window(sf::VideoMode(LARGEUR,LONGUEUR), "prototype");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    Menu menu(window.getSize().x, window.getSize().y);
    int go=0;


    //affichage du sol a une position donne
    sf::RectangleShape sol(sf::Vector2f(1280.f, 100.f));
    sol.setPosition(0.f,860.f);
    sol.setFillColor(sf::Color(255,0,0,130));

    //horloge permettant de rcuperer le temps
    sf::Clock clockanim;
    sf::Clock clockmove;

    sf::Clock clockanim2;
    sf::Clock clockmove2;

    //CREATION D'UNE INSTANCE DE LA CLASSE BROLY
    Broly Brolytest(-1);
    Broly Brolytest2(1);


    sf::RectangleShape hitbox1(sf::Vector2f(Brolytest.getLocalBounds().width,Brolytest.getLocalBounds().height*2));
    hitbox1.setFillColor(sf::Color(255,255,255,0));
    hitbox1.setOutlineThickness(5);
    hitbox1.setOutlineColor(sf::Color::Blue);
    hitbox1.setPosition(Brolytest.getPosition().x,Brolytest.getPosition().y);
    cout << "taille de la hitbox " << Brolytest.getLocalBounds().width*2 << "   " << Brolytest.getLocalBounds().height*2 << endl;
    cout << "position de la hitbox " << Brolytest.getPosition().x << "   " << Brolytest.getPosition().y << endl;

    sf::RectangleShape hitboxpoing(sf::Vector2f(46.f,44.f));
    hitboxpoing.setFillColor(sf::Color(255,255,255,0));
    hitboxpoing.setOutlineThickness(5);
    hitboxpoing.setOutlineColor(sf::Color::Red);

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

            Joueur1 = Brolytest;
            moveright = false;
            moveleft = false;
            moveright2 = false;
            moveleft2 = false;



    while (window.isOpen()&& (go==0))
    {

        sf::Event event;
        sf::Music music;
        if (!music.openFromFile("Enregistrement.ogg")){
        std::cout<<"pb";} // erreur
        music.setVolume(50);
        music.play();
        while (window.pollEvent(event) ){

            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    menu.moveUp();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            menu.moveDown();
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && (menu.getSelection()==0)){
            go=1;
            }
        window.clear();
        menu.draw(window);
        window.display();}
    }

    while (window.isOpen()&& (go==1))
    {
    window.clear();

            sf::Event event;
            while (window.pollEvent(event)){

                if (event.type == sf::Event::Closed){
                    window.close();
                }
                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Numpad1){
                    peutcoup = true;
                }
                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A){
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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if(!(Brolytest.getPosition().x + Brolytest.getLocalBounds().width*2 + 10 > LARGEUR)){
                    moveright = true;
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if(!(Brolytest.getPosition().x - 10 < 0)){
                    moveleft = true;
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                saut = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)){
                    if(peutcoup){
                        coupPoing = true;
                    }
            }

            if(moveright){
                sf::Time elapsed = clockmove.getElapsedTime();
                int timemove = elapsed.asMilliseconds();
                int v_x = +15;
                if(timemove > 20){
                    Joueur1.setPosition(Joueur1.getPosition().x+v_x,Joueur1.getPosition().y);
                    clockmove.restart();
                }
                Brolytest.setPosition(Joueur1.getPosition());
                Brolytest.avancer(clockanim);
                saut = false;
            }
            if(moveleft){

                sf::Time elapsed = clockmove.getElapsedTime();
                int timemove = elapsed.asMilliseconds();
                int v_x = -15;
                if(timemove > 20){
                    Joueur1.setPosition(Joueur1.getPosition().x+v_x,Joueur1.getPosition().y);
                    clockmove.restart();
                }
                Brolytest.setPosition(Joueur1.getPosition());
                Brolytest.reculer(clockanim);
                saut = false;
            }
            if(!moveright && !moveleft && !saut && !coupPoing){
                Brolytest.debout(clockanim);
                hitbox1.setPosition(Brolytest.getPosition().x+64, Brolytest.getPosition().y);
            }
            if(saut){
                Brolytest.sauter(clockanim);
            }
            if(coupPoing){
                peutcoup = false;
                hitboxpoing.setPosition(Brolytest.getPosition().x + 112,Brolytest.getPosition().y+150);
                coupPoing = Brolytest.coupDePoing(clockanim);
                    if(!coupPoing){
                        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))){
                            peutcoup = true;
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
            Joueur2 = Brolytest2;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                if(!(Brolytest2.getPosition().x + Brolytest2.getLocalBounds().width*2 + 10 > LARGEUR)){
                    moveright2 = true;
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                if(!(Brolytest2.getPosition().x - 10 < 0)){
                    moveleft2 = true;
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {
                saut2 = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    if(peutcoup2){
                        coupPoing2 = true;
                    }
            }
            if(moveright2){
                sf::Time elapsed = clockmove2.getElapsedTime();
                int timemove = elapsed.asMilliseconds();
                int v_x = +15;
                if(timemove > 20){
                    Joueur2.setPosition(Joueur2.getPosition().x+v_x,Joueur2.getPosition().y);
                    clockmove2.restart();
                }
                Brolytest2.setPosition(Joueur2.getPosition());
                Brolytest2.reculer(clockanim2);
                saut2 = false;
            }
            if(moveleft2){

                sf::Time elapsed = clockmove2.getElapsedTime();
                int timemove = elapsed.asMilliseconds();
                int v_x = -15;
                if(timemove > 20){
                    Joueur2.setPosition(Joueur2.getPosition().x+v_x,Joueur2.getPosition().y);
                    clockmove2.restart();
                }
                Brolytest2.setPosition(Joueur2.getPosition());
                Brolytest2.avancer(clockanim2);
                saut2 = false;
            }
            if(!moveright2 && !moveleft2 && !saut2){
                Brolytest2.debout(clockanim2);
            }
            if(saut2){
                Brolytest2.sauter(clockanim2);
            }
            if(coupPoing2){
                peutcoup2 = false;
                coupPoing2 = Brolytest2.coupDePoing(clockanim2);
                    if(!coupPoing2){
                        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::A))){
                            peutcoup2 = true;
                        }
                    }
            }


            //AFFICHAGE
            window.draw(Joueur1);
            window.draw(Joueur2);
            window.draw(hitbox1);
            window.draw(hitboxpoing);

            window.draw(sol);
            window.display();
        }
    return 0;
}


