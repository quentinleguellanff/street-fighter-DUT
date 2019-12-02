#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <SFML/Graphics.hpp>

class Menu {
public:

    int _selection;
    sf::Texture textureCase;
    sf::Texture fond;
    sf::Font font;
    sf::Sprite spriteMenu[6];
    sf::Sprite spriteMenux[3];
    sf::Sprite sfond;
    sf::Vector2f position;
    sf::Text titre;

    float joystick0_axisX;
	float joystick0_axisY;



    Menu (float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);

    void moveUp();
    void moveDown();
    int getSelection();

    };

#endif // FONCTION_H_INCLUDED
