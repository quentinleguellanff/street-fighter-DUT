#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <SFML/Graphics.hpp>

const int nbcase=3;
class Menu {
private:

    int _selection;
    sf::Font font;
    sf::Text menu[nbcase];

public:

    Menu (float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getSelection();
    };
class cScreen
{
public :
    virtual int Run (sf::RenderWindow &App) = 0;
};
#endif // FONCTION_H_INCLUDED
