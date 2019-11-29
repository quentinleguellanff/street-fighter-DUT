#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <SFML/Graphics.hpp>

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
public:

    Menu (float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void bouger();
    void moveUp();
    void moveDown();
    int getSelection();
    void reset();
    bool getMonter();
    bool getDescendre();
    };

#endif // FONCTION_H_INCLUDED
