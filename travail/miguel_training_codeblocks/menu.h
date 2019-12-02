#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

const int nbcase=3;

class Menu {
private:

    int _selection;
    sf::Font font;
    sf::Text menu[nbcase];
    bool _monter;
    bool _descendre;
    float joystick0_axisX;
	float joystick0_axisY;
    sf::Texture textureCase;
    sf::Clock clockAttente;
public:

    Menu (float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void bouger(int&,sf::Event);
    void moveUp();
    void moveDown();
    };

#endif // MENU_H
