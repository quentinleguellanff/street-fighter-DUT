#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML test");

    //sol
    sf::RectangleShape sol(sf::Vector2f(1200.f,50.f));
    sol.setFillColor(sf::Color::White);
    sol.setPosition(sf::Vector2f(0.f,750.f));

    //mur gauche
    sf::RectangleShape murGauche(sf::Vector2f(100.f, 750.f));
    murGauche.setOutlineColor(sf::Color::Red);
    murGauche.setOutlineThickness(4.0);
    murGauche.setFillColor(sf::Color::Black);
    murGauche.setPosition(sf::Vector2f(0.f,0.f));

    //mur droite
    sf::RectangleShape murDroite(sf::Vector2f(100.f, 750.f));
    murDroite.setOutlineColor(sf::Color::Red);
    murDroite.setOutlineThickness(4.0);
    murDroite.setFillColor(sf::Color::Black);
    murDroite.setPosition(sf::Vector2f(1100.f,0.f));

    sf::Clock clock;
    sf::Time Time;

    int a = 4;
    int i = 130;

    sf::Texture texture;
    if (!texture.loadFromFile("Sprite_perso1.png"))
    {
        cout << "Erreur : chargement de texture" << endl;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sprite.setTextureRect(sf::IntRect(4, 875, 121, 201));
    sprite.setPosition(sf::Vector2f(250.f, 540.f));
    sprite.scale(sf::Vector2f(-1,1));


    sf::Sprite coup;
    coup.setTexture(texture);

    coup.setTextureRect(sf::IntRect(4, 2275, 121, 201));
    coup.scale(sf::Vector2f(-1,1));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        //Retour à gauche
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
             if(sprite.getGlobalBounds().intersects(murDroite.getGlobalBounds())) {
                sprite.move(sf::Vector2f(0.f, 0.f));
            }
            else{
                sprite.move(sf::Vector2f(1.f, 0.f));
                if(clock.getElapsedTime().asMilliseconds() > 150)
                {
                    cout << a << endl;
                    sprite.setTextureRect(sf::IntRect(a, 875, 121, 201));
                    a = a+i;
                    clock.restart();
                }
                if(a > 1565) a = 4;
            }
        }

        //Déplacement à droite
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(sprite.getGlobalBounds().intersects(murGauche.getGlobalBounds())) {
                sprite.move(sf::Vector2f(0.f, 0.f));
            }
            else{
                sprite.move(sf::Vector2f(-1.f, 0.f));
            }
        }

        //Coup de poing
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            a = 4;
            coup.setPosition(sprite.getPosition());
            if(sprite.getGlobalBounds().intersects(murDroite.getGlobalBounds())) {
                sprite.move(sf::Vector2f(0.f, 0.f));
            }
            else{
                if(clock.getElapsedTime().asMilliseconds() > 150)
                {
                    coup.setTextureRect(sf::IntRect(a, 2275, 121, 201));
                    a = a+i;
                    clock.restart();
                }
                if(a > 1565) a = 4;
            }

        }


        window.draw(sol);
        window.draw(murGauche);
        window.draw(murDroite);
        window.draw(sprite);
        window.display();
        window.clear();

    }
    return 0;
}
