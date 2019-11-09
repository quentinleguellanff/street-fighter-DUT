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

    sf::Clock clock;
    sf::Time Time;

    sf::Texture texture;
    if (!texture.loadFromFile("Sprite_perso1.png"))
    {
        cout << "Erreur : chargement de texture" << endl;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sprite.setTextureRect(sf::IntRect(4, 875, 121, 201));
    sprite.setPosition(sf::Vector2f(120.f, 540.f));


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
             sprite.move(sf::Vector2f(1.f, 0.f));
        }

         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            sprite.move(sf::Vector2f(-1.f, 0.f));
        }

        window.draw(sol);
        window.draw(murGauche);
        window.draw(sprite);
        window.display();
        window.clear();
    }

    return 0;
}
