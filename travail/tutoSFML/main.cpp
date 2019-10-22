#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    const int LONGUEUR = 960;
    const int LARGEUR = 1280;
    sf::RenderWindow window(sf::VideoMode(LARGEUR,LONGUEUR), "premiere fenetre");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    sf::RectangleShape perso(sf::Vector2f(240.f, 400.f));
    sf::RectangleShape mannequin(sf::Vector2f(200.f, 500.f));
    sf::RectangleShape bras(sf::Vector2f(200.f, 50.f));
    sf::RectangleShape sol(sf::Vector2f(1280.f, 100.f));
    sol.setPosition(0.f,860.f);
    perso.setFillColor(sf::Color::Green);
    sol.setFillColor(sf::Color::Red);
    sf::Vector2f positionrelperso;
    perso.setPosition(0.f,460.f);
    mannequin.setPosition(1000.f,360.f);
    sf::Texture texture;
    if (!texture.loadFromFile("Brolyspriteok.png"))
    {
    cout << "erreur" << endl;
    }
    //texture.setSmooth(true);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    //sprite.setTextureRect(sf::IntRect(2, 467,120,200));
    sprite.setScale(-2,2); // augmente la taille du sprite -2 pour tourner le personnage vers la droite
    sprite.setPosition(200.f, 400.f);


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
    int i = 0, time = 0;
    bool saut = false;
    bool moveright = false;
    bool moveleft = false;
    bool sautleft = false;
    bool sautright = false;
    bool coup = false;
    bool restart = false;

    float v_x = 0;
    float v_saut = -25;
    float v_grav = 0.9;
    float v_y = v_saut;

    int timeanim;
    int spriteanimrightx = 0;
    int spriteanimstatic = 0;


    while (window.isOpen())
    {
        window.clear();
        sprite.setTextureRect(sf::IntRect(2, 467,120,200));
        sf::Vector2f positionPerso = perso.getPosition();
        sf::Vector2f taillePerso = perso.getSize();

        sf::Vector2f positionbras = bras.getPosition();
        sf::Vector2f taillebras = bras.getSize();

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


        /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(!(positionPerso.y - 10 < 0)){
                perso.move(0.f,-10.f);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if(!(positionPerso.y + 10 + taillePerso.y > LONGUEUR - tailleSol.y)){
                perso.move(0.f,10.f);
                cout << positionPerso.y << " ";
            }
        }*/

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(!(positionPerso.x + taillePerso.x + 5 > LARGEUR)){
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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(!(positionPerso.x - 5 < 0)){
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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                if(!saut){
                    saut = true;
                }
                if(moveleft && !sautleft){
                    sautleft = true;
                    saut = true;

                }
                if(moveright && !sautright){
                    sautright = true;
                    saut = true;
                }

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                coup = true;
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();

            }
            if (event.type == sf::Event::KeyReleased){
                moveright = false;
                moveleft = false;
                coup = false;
                restart = false;
                spriteanimrightx = 0;
                v_x = 0;
            }
        }

        if(saut){
                if(sautleft && !(positionPerso.x <= 0)){
                    positionPerso.x += -5;
                }
                if(sautright && !(positionPerso.x + taillePerso.x >= LARGEUR)){
                    positionPerso.x += +5;
                }
            positionPerso.y += v_y;

            v_y += v_grav;

            perso.setPosition(positionPerso);
            if(positionPerso.y >= 460){
                saut = false;
                sautleft = false;
                sautright = false;
                v_y = v_saut;
                positionPerso.y = 460;
                perso.setPosition(positionPerso);
            }
            cout << positionPerso.y << endl;


        }
        if(moveright){
                if(!saut){
                    ///////////////// ANIMATION /////////////////////////////
                    sprite.setTextureRect(sf::IntRect(2, 873,120,200));
                    sf::Time elapsed2 = clockanim.getElapsedTime();
                    timeanim = elapsed2.asMilliseconds();
                    if(timeanim > 70){
                        spriteanimrightx++;
                        clockanim.restart();
                    }
                    if(spriteanimrightx >= 13){
                        spriteanimrightx = 1;
                    }
                    if(spriteanimrightx >= 1){
                        sprite.setTextureRect(sf::IntRect(2+spriteanimrightx*130, 873,120,200));
                    }
                    ///////////////// DEPLACEMENT /////////////////////////////
                    v_x=5;
                    positionPerso.x += v_x;
                    perso.setPosition(positionPerso);

                }
        }
        if(moveleft){
                if(!saut){
                    ///////////////// ANIMATION /////////////////////////////
                    sprite.setScale(-2,2);
                    sprite.setTextureRect(sf::IntRect(2, 11437,153,207));
                    sf::Time elapsed2 = clockanim.getElapsedTime();
                    timeanim = elapsed2.asMilliseconds();
                    if(timeanim > 70){
                        sprite.setTextureRect(sf::IntRect(157, 11437,153,207));
                    }

                    ///////////////// DEPLACEMENT /////////////////////////////
                    v_x=-5;
                    positionPerso.x += v_x;
                    perso.setPosition(positionPerso);
                }
        }

        if(!moveleft && !moveright && !saut){
            ///////////////// ANIMATION /////////////////////////////
                sprite.setTextureRect(sf::IntRect(2+spriteanimstatic*123, 466,121,201));
                sf::Time elapsed2 = clockanim.getElapsedTime();
                timeanim = elapsed2.asMilliseconds();
                if(timeanim > 100){
                    spriteanimstatic++;
                    clockanim.restart();
                }
                if(spriteanimstatic >= 10){
                    spriteanimstatic = 0;
                }
                cout << spriteanimstatic << endl;
        }

        if(i != time){
            i+=1;
            text.setString(to_string(i));
        }

        if(coup){
            positionbras.x = positionPerso.x + taillePerso.x;
            positionbras.y = positionPerso.y + taillePerso.y*1/3;
            bras.setPosition(positionbras);

            window.draw(bras);
        }

        if(coup && (positionbras.x + taillebras.x > posMannequin.x)){

            mannequin.setFillColor(sf::Color::Blue);
        }

        //window.draw(perso);
        window.draw(sol);
        window.draw(text);
        window.draw(point);
        window.draw(mannequin);
        window.draw(sprite);

        window.display();
    }

    return 0;
}
