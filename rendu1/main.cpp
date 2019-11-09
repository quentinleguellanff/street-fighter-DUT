#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::Vector2f position;
    sf::Texture perso;
    sf::Sprite sprite_perso;
    float speed=0.75;


    if (!perso.loadFromFile("broly.png")){
        std::cout << "erreur chargement sprite";
    }

    //POSITION INITIALE
    sprite_perso.setPosition(118,300);
    sprite_perso.setTexture(perso);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //POSITION INITALE
        sprite_perso.setTextureRect(sf::IntRect(2,262,118,200));

        //GAUCHE
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                position= sprite_perso.getPosition();
                sprite_perso.move(-speed,0);
                sprite_perso.setTextureRect(sf::IntRect(2, 873,128,200));
                if (position.x<=0){
                    sprite_perso.setPosition(0,300);}

        }

        //DROITE
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                position= sprite_perso.getPosition();
                sprite_perso.move(speed,0);
                sprite_perso.setTextureRect(sf::IntRect(2, 11437,153,207));
                std::cout << "x:" << position.x<< std::endl;
                std::cout << "y:" << position.y<< std::endl;
                if (position.x>=670){
                    sprite_perso.setPosition(670,300);}
        }

        //COUP DE POING
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                position= sprite_perso.getPosition();
                sprite_perso.setTextureRect(sf::IntRect(440,2960,210,200));
        }


        window.clear(sf::Color::White);
        window.draw(sprite_perso);
        window.display();
}

    return 0;
}
