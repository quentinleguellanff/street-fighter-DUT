#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"

using namespace std;

int main()
{
    const int LONGUEUR = 960;
    const int LARGEUR = 1280;
    sf::RenderWindow window(sf::VideoMode(LARGEUR,LONGUEUR), "premiere fenetre");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
    sf::RectangleShape perso(sf::Vector2f(240.f, 400.f));
    sf::RectangleShape mannequin(sf::Vector2f(200.f, 500.f));
    sf::RectangleShape sol(sf::Vector2f(1280.f, 100.f));
    sol.setPosition(0.f,860.f);
    perso.setFillColor(sf::Color::Green);
    sol.setFillColor(sf::Color::Red);
    perso.setPosition(0.f,460.f);
    mannequin.setPosition(1000.f,360.f);
    sf::Texture texture;
    if (!texture.loadFromFile("Brolyspriteok.png"))
    {
    cout << "erreur" << endl;
    }
    //texture.setSmooth(true);
    sf::Sprite sprite;
    sf::Sprite sprite2;
    sf::Sprite spritemannequin;
    sprite.setTexture(texture);
    //sprite.setTextureRect(sf::IntRect(2, 467,120,200));
    sprite.setScale(-2,2); // augmente la taille du sprite -2 pour tourner le personnage vers la droite
    //sprite.setPosition(200.f, 400.f);

    spritemannequin.setTexture(texture);
    spritemannequin.setScale(2,2);
    spritemannequin.setPosition(1000.f,460.f);

    Broly Broly(-1);
    sprite2 = Broly;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setString("0");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(50);
    text.setPosition(640.f,0.f);

    sf::VertexArray point(sf::Points,1);
    point[0].position = sf::Vector2f(10.f,370.f);


    sf::Clock clock;
    sf::Time elapsed1 = clock.restart();
    sf::Clock clockanim;
    sf::Clock clockanim3;
    sf::Clock clockjump;
    sf::Clock clockanim2;
    int i = 0, time = 0;

    bool saut = false;
    bool moveright = false;
    bool moveleft = false;
    bool sautleft = false;
    bool sautright = false;
    bool coup = false;
    bool couppied = false;
    bool restart = false;
    bool peutsauter = true;
    bool peutcoup = true;
    bool peutcouppied = true;

    float v_x = 0;
    float v_saut = -70;
    float v_grav = 6;
    float v_y = v_saut;

    int timeanim;
    int timemove;
    int timeafterjump;
    int spriteanimrightx = 0;
    int spriteanimstatic = 0;
    int spriteanimjump = 0;
    int spriteanimcoup = 0;
    int spriteanimcouppied = 0;

    int cptanimstatic = 0;

    while (window.isOpen())
    {
        window.clear();
        cout << sprite.getLocalBounds().width << endl;
        cout << sprite.getLocalBounds().height << endl;
        spritemannequin.setColor(sf::Color(255,255,255,255));
        //sprite.setTextureRect(sf::IntRect(2, 467,120,200));
        sf::Vector2f positionPerso = perso.getPosition();
        sf::Vector2f taillePerso = perso.getSize();

        sf::Vector2f positionsprite = positionPerso;
        sf::Vector2f taillesprite = taillePerso;
        sprite.setPosition(positionsprite);

        sf::Vector2f tailleSol = sol.getSize();

        sf::Vector2f posMannequin = mannequin.getPosition();
        mannequin.setFillColor(sf::Color::White);

        sf::Event event;
        sf::Time elapsed1 = clock.getElapsedTime();
        time = elapsed1.asSeconds();
        sprite.setOrigin(taillesprite.x/2, 0.f);

          ///////////////////////////////////////////////////////
        sf::Time elapsedjump = clockjump.getElapsedTime();
        timeafterjump = elapsedjump.asMilliseconds();
        /*if(!saut){
            if(!peutsauter){
                if(timeafterjump > 20){
                    peutsauter = true;
                }
            }
        }*/
        cout << peutsauter << "temps : " << timeafterjump << endl;


        while (window.pollEvent(event)){

            if (event.type == sf::Event::Closed){
                window.close();

            }
            if (event.type == sf::Event::KeyReleased){
                moveright = false;
                moveleft = false;
                restart = false;
                spriteanimrightx = 0;
                v_x = 0;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space){
                peutsauter = true;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A){
                peutcoup = true;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Z){
                peutcouppied = true;
            }
        }

        if(!saut && !coup && !couppied && peutsauter){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                saut = true;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sautleft && !sautright){
                    sautleft = true;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sautright && !sautleft){
                    sautright = true;
                }
                if(!restart){
                    clockanim.restart();
                    restart = true;
                }

            }
        }

        if(!coup && !couppied && !saut && !sautleft && !sautright){
             if(peutcoup){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    if(!coup && !couppied){
                        coup = true;
                        moveright = false;
                        moveleft = false;
                        positionPerso.x += 112;
                        positionPerso.y += 20;
                        perso.setPosition(positionPerso);
                        sprite.setPosition(positionPerso);
                    }
                }
             }
             if(peutcouppied){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
                    if(!coup && !couppied){
                        couppied = true;
                        moveright = false;
                        moveleft = false;
                        positionPerso.x += 160;
                        perso.setPosition(positionPerso);
                        sprite.setPosition(positionPerso);
                    }
                }
             }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if(!(positionPerso.x + taillePerso.x + 10 > LARGEUR) && !coup && !couppied && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    //perso.move(5.f,0.f);
                    moveright = true;
                }
                else{
                    moveright = false;
                }
                if(!restart){
                    clockanim.restart();
                    restart = true;
                }
            }
            if(moveright){
                if(!saut){
                    ///////////////// ANIMATION /////////////////////////////
                    sprite.setTextureRect(sf::IntRect(2, 873,128,200));
                    sf::Time elapsed2 = clockanim.getElapsedTime();
                    timeanim = elapsed2.asMilliseconds();
                    sf::Time elapsed3 = clockanim3.getElapsedTime();
                    timemove = elapsed3.asMilliseconds();

                    if(timeanim > 70){
                        spriteanimrightx++;
                        clockanim.restart();
                    }
                    if(spriteanimrightx >= 13){
                        spriteanimrightx = 1;
                    }
                    if(spriteanimrightx >= 1){
                        sprite.setTextureRect(sf::IntRect(2+spriteanimrightx*130, 873,128,200));
                    }
                    ///////////////// DEPLACEMENT /////////////////////////////
                    v_x=15;
                    if(timemove > 20){
                        positionPerso.x += v_x;
                        clockanim3.restart();
                    }
                    perso.setPosition(positionPerso);

                }
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if(!(positionPerso.x - 10 < 0)&& !coup && !couppied && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    //perso.move(-5.f,0.f);
                    moveleft = true;
                }
                else{
                    moveleft =  false;
                }
                if(!restart){
                    clockanim.restart();
                    restart = true;
                }
            }
            if(moveleft){
                if(!saut){
                    ///////////////// ANIMATION /////////////////////////////
                    sprite.setScale(-2,2);
                    sprite.setTextureRect(sf::IntRect(2, 11437,153,207));
                    sf::Time elapsed2 = clockanim.getElapsedTime();
                    timeanim = elapsed2.asMilliseconds();
                    sf::Time elapsed3 = clockanim3.getElapsedTime();
                    timemove = elapsed3.asMilliseconds();

                    if(timeanim > 70){
                        sprite.setTextureRect(sf::IntRect(157, 11437,153,207));
                    }

                    ///////////////// DEPLACEMENT /////////////////////////////
                        v_x=-15;
                    if(timemove > 20){
                        positionPerso.x += v_x;
                        clockanim3.restart();
                    }
                    perso.setPosition(positionPerso);
                }
            }
        }

        if(!moveleft && !moveright && !saut && !coup && !couppied){
                sprite.setTextureRect(sf::IntRect(2+spriteanimstatic*123, 466,121,201));
                spritemannequin.setTextureRect(sf::IntRect(2+spriteanimstatic*123, 466,121,201));
                sf::Time elapsed2 = clockanim.getElapsedTime();
                timeanim = elapsed2.asMilliseconds();
                if(timeanim > 100){
                    spriteanimstatic++;
                    clockanim.restart();
                }
                if(spriteanimstatic >= 10){
                    spriteanimstatic = 0;
                }
                Broly.debout(cptanimstatic,clockanim2);
        }


        if(i != time){
            i+=1;
            text.setString(to_string(i));
        }

        if(saut){
            couppied = false;
            coup = false;
                //sprite.setTextureRect(sf::IntRect(2, 1650,156,208));
            sf::Time elapsed2 = clockanim.getElapsedTime();
            timeanim = elapsed2.asMilliseconds();
            sf::Time elapsed3 = clockanim3.getElapsedTime();
            timemove = elapsed3.asMilliseconds();


            if(timeanim > 100){
                spriteanimjump++;
                clockanim.restart();
            }

            if(spriteanimjump >= 5){
                sprite.setTextureRect(sf::IntRect(2+(5*158), 1650,156,208));
            }
            else{
                sprite.setTextureRect(sf::IntRect(2+spriteanimjump*158, 1650,156,208));
            }
            if(sautleft && !(positionPerso.x <= 0)){
                sautright = false;
                if(timemove > 20){
                    positionPerso.x += -15;
                    clockanim3.restart();
                }
            }
            if(sautright && !(positionPerso.x + taillePerso.x >= LARGEUR)){
                sautleft = false;
                if(timemove > 20){
                    positionPerso.x += 15;
                    clockanim3.restart();
                }
            }
            if(timemove > 20){
                v_y += v_grav;
                positionPerso.y += v_y;
                clockanim3.restart();
            }

            perso.setPosition(positionPerso);
            if(positionPerso.y >= 460){
                saut = false;
                sautleft = false;
                sautright = false;
                restart = false;
                peutsauter = false;
                v_y = v_saut;
                positionPerso.y = 460;
                perso.setPosition(positionPerso);
                spriteanimjump = 0;
                clockjump.restart();
                if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))){
                        peutsauter = true;
                }
            }
        }
        if(coup){
            if(!saut){
                moveright = false;
                moveleft = false;
                sf::Time elapsed2 = clockanim.getElapsedTime();
                timeanim = elapsed2.asMilliseconds();

                    if(timeanim > 30){
                        spriteanimcoup++;
                        clockanim.restart();
                    }

                    if(spriteanimcoup >= 5){
                        spriteanimcoup = 0;
                        positionPerso.x -= 112;
                        positionPerso.y -= 20;
                        perso.setPosition(positionPerso);
                        sprite.setPosition(positionPerso);
                        sprite.setTextureRect(sf::IntRect(2, 466,121,201));
                        coup = false;
                        peutcoup = false;
                        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::A))){
                            peutcoup = true;
                        }
                    }
                    else{
                        sprite.setTextureRect(sf::IntRect(2+spriteanimcoup*179, 2765,177,191));
                    }


            }
        }

        if(couppied){
            if(!saut){
                moveright = false;
                moveleft = false;
                sf::Time elapsed2 = clockanim.getElapsedTime();
                timeanim = elapsed2.asMilliseconds();

                    if(timeanim > 30){
                        spriteanimcouppied++;
                        clockanim.restart();
                    }

                    if(spriteanimcouppied >= 8){
                        spriteanimcouppied = 0;
                        positionPerso.x -= 160;
                        perso.setPosition(positionPerso);
                        sprite.setPosition(positionPerso);
                        sprite.setTextureRect(sf::IntRect(2, 466,121,201));
                        couppied = false;
                        peutcouppied = false;
                        if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))){
                            peutcouppied = true;
                        }

                    }
                    else{
                        sprite.setTextureRect(sf::IntRect(2+spriteanimcouppied*204, 4738,202,203));
                    }


            }
        }

        if(coup && spriteanimcoup == 1 && (sprite.getPosition().x + taillePerso.x > posMannequin.x)){

            spritemannequin.setColor(sf::Color::Blue);
        }
         if(couppied && spriteanimcouppied == 4 && (sprite.getPosition().x + taillePerso.x > posMannequin.x)){

            spritemannequin.setColor(sf::Color::Blue);
        }
        //window.draw(perso);
        window.draw(sol);
        window.draw(text);
        //window.draw(point);
        window.draw(spritemannequin);
        window.draw(sprite);
        //window.draw(sprite2);
        window.draw(Broly);

        window.display();
    }

    return 0;
}

