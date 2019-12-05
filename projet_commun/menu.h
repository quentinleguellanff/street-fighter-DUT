#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std ;
const int nbcase=3;

class Menu {
private:

    int _selection;
    sf::Font font;
    sf::Texture textureCase;
    sf::Texture menuFond;
    sf::Sprite spriteFond;

    sf::Sprite spriteMenu[6];
    sf::Sprite spriteMenux[3];
    sf::Sprite sfond;
    sf::Vector2f position;
    sf::Text titre;

    float joystick0_axisX;
    float joystick0_axisY;
    sf::Clock clockAttente;
public:

    Menu (float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void bouger(int&,sf::Event);
    void moveUp();
    void moveDown();
    };


class MenuSelection {
private:

    sf::Font fontMenu;

    //texte : sélection des personnages
    sf::Text titre;

    //texte : Joueur 1
    sf::Text j1;

    //texte : Joueur 2
    sf::Text j2;

    //texte : Joueur 2
    sf::Text nomPersoJ1;
    //texte : Joueur 2
    sf::Text nomPersoJ2;

    //délimitation entre la zone de selection j1 et j2
    sf::RectangleShape ligneDelim;//(sf::Vector2f(5, 700));

    //texte : annuler choix J1
    sf::Text annulerChoixJ1;

    //texte : annuler choix J2
    sf::Text annulerChoixJ2;

    //texture des champions
    sf::Texture texturePersos;

    //image joueur1
    sf::Sprite spriteP1;

    //image joueur2
    sf::Sprite spriteP2;

    int hauteurPerso;
    
    int hauteurTexte;
    
    bool etat = 0;
    int etatPersoJ1 = 0;
    int etatPersoJ2 = 1;
    int choixJ1 = -1;
    int choixJ2 = -1;

public :
    MenuSelection(sf::RenderWindow&);
    void draw(sf::RenderWindow &window);
    void bouger(sf::Event,sf::RenderWindow&);
    int validationPerso(sf::Event event);
};

#endif // MENU_H
