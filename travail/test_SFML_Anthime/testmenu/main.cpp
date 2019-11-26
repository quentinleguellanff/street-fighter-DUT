#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main() {

    sf::RenderWindow window(sf::VideoMode(1280, 840), "SFML window");

    sf::Font font;

    if (!font.loadFromFile("atari.ttf"))
    {
        cout << "ERREUR : chargement de police atari.ttf" << endl;
    }

    //texte : sélection des personnages
    sf::Text titre;
    titre.setFont(font);
    titre.setString("Selection des personnages");
    titre.setCharacterSize(50);
    titre.setColor(sf::Color::White);
    titre.setStyle(sf::Text::Bold);
    titre.setPosition(sf::Vector2f(430,12));

    //texte : Joueur 1
    sf::Text j1;
    j1.setFont(font);
    j1.setString("Joueur 1");
    j1.setCharacterSize(26);
    j1.setColor(sf::Color::White);
    j1.setStyle(sf::Text::Bold);
    j1.setPosition(sf::Vector2f(270,100));

    //texte : Joueur 2
    sf::Text j2;
    j2.setFont(font);
    j2.setString("Joueur 2");
    j2.setCharacterSize(26);
    j2.setColor(sf::Color::White);
    j2.setStyle(sf::Text::Bold);
    j2.setPosition(sf::Vector2f(950,100));

    //délimitation entre la zone de selection j1 et j2
    sf::RectangleShape ligneDelim(sf::Vector2f(5, 700));
    ligneDelim.setFillColor(sf::Color::White);
    ligneDelim.setPosition(sf::Vector2f(650,100));


    //image perso
    sf::Texture perso1;
    if (!perso1.loadFromFile("browli.png"))
    {
        cout << "ERREUR : chargement d'image personnage : browli.png" << endl;
    }

    sf::Sprite spriteP1J1;
    spriteP1J1.setTexture(perso1);
    spriteP1J1.setPosition(sf::Vector2f(100.f, 200.f));

     //image perso2
    sf::Texture perso2;
    if (!perso2.loadFromFile("dhalsim.png"))
    {
        cout << "ERREUR : chargement d'image personnage : dhalsim.png" << endl;
    }

    sf::Sprite spriteP2J1;
    spriteP2J1.setTexture(perso2);
    spriteP2J1.setPosition(sf::Vector2f(350.f, 200.f));


    //perso pour J2
    sf::Sprite spriteP1J2;
    spriteP1J2.setTexture(perso1);
    spriteP1J2.setPosition(sf::Vector2f(780.f, 200.f));

     //image perso2
    sf::Sprite spriteP2J2;
    spriteP2J2.setTexture(perso2);
    spriteP2J2.setPosition(sf::Vector2f(1050.f, 200.f));

    //cadre selection perso
    sf::Texture cadreSelection;
    if (!cadreSelection.loadFromFile("selection.png"))
    {
        cout << "ERREUR : chargement d'image : selection.png" << endl;
    }

    sf::Sprite spriteCadre;
    spriteCadre.setTexture(cadreSelection);
    spriteCadre.setScale(sf::Vector2f(1.9,1.3));
    spriteCadre.setPosition(sf::Vector2f(60.f, 190.f));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            spriteCadre.setPosition(sf::Vector2f(340.f, 190.f));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            spriteCadre.setPosition(sf::Vector2f(60.f, 190.f));
        }

        window.clear();
        window.draw(titre);
        window.draw(j1);
        window.draw(j2);
        window.draw(ligneDelim);
        window.draw(spriteP1J1);
        window.draw(spriteP2J1);
        window.draw(spriteP1J2);
        window.draw(spriteP2J2);
        window.draw(spriteCadre);
        window.display();
	}
}
