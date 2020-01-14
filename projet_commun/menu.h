/**
 * \file menu.h
 * \brief Classe Menu
 * \author Team La Bagarre
 *
 * Classe permettant la gestion des différents menus
 */


#ifndef MENU_H
#define MENU_H

#include "IncludeManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

using namespace std ;

class MenuPrincipal {
private:

    /**
   * \attribute int _selection
   * \brief Etat de la sélection
   *
   * 0 si "Jouer" , 1 si "Commandes" et 2 si "Quitter"
   */
    int _selection;

    /**
   * \attribute sf::Font font
   * \brief Police utilisée pour le titre
   *
   * Police du titre "La Bagarre" sur le menu principal
   */
    sf::Font font;

    /**
   * \attribute sf::Texture textureCase
   * \brief Texture des boutons
   *
   *  Texture des boutons "JOUER, COMMANDES, QUITTER"
   */
    sf::Texture textureCase;

    /**
   * \attribute sf::Texture menuFond;
   * \brief Texture du fond du menu
   *
   *  Texture du fond du menu
   */
    sf::Texture menuFond;

    /**
   * \attribute sf::Sprite spriteFond
   * \brief Sprite d'arrière plan du menu
   *
   *  Sprite d'arrière plan du menu
   */
    sf::Sprite spriteFond;

    /**
   * \attribute sf::Sprite spriteMenu[6]
   * \brief Tableau de sprites des boutons du menu
   *
   *  3 sprites pour "JOUER, COMMANDES, QUITTER" sélectionnés + 3 sprites pour "JOUER, COMMANDES, QUITTER" non-sélectionnés
   */
    sf::Sprite spriteMenu[6];

    /**
   * \attribute sf::Sprite spriteMenux[3]
   * \brief Tableau de sprites des boutons du menu affiché
   *
   *  Sprites remplacés par la sélection courrante
   */
    sf::Sprite spriteMenux[3];
    sf::Sprite sfond;
    sf::Vector2f position;
    sf::Text titre;

    float joystick0_axisX;
    float joystick0_axisY;
    sf::Clock clockAttente;

    sf::Music _effetSon;
public:
    MenuPrincipal();
    MenuPrincipal (float width, float height);
    ~MenuPrincipal();

    void draw(sf::RenderWindow& window);
    void bouger(int&,sf::Event, sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    };


class MenuSelection {
private:

    sf::Texture textureVS;
    sf::Sprite spriteVS;

    sf::Font fontMenu;

    sf::Texture menuFond;
    sf::Sprite spriteFond;

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

    float joystick0_axisX;
    float joystick0_axisY;
    sf::Clock clockAttente;

    sf::Music _effetSon;

public :
    MenuSelection();
    MenuSelection(sf::RenderWindow&);
    void draw(sf::RenderWindow &window);

    void persoSuivant_P1(int&,sf::RenderWindow&);
    void persoPrecedent_P1(int&,sf::RenderWindow&);

    void persoSuivant_P2(int&,sf::RenderWindow&);
    void persoPrecedent_P2(int&,sf::RenderWindow&);

    void bouger(sf::Event,sf::RenderWindow&);
    int validationPerso(sf::Event event,int&,int&);

    void reset(sf::RenderWindow&);
    void initValidationPerso();
};

class MenuCommandes {
    private:
    sf::Texture texturej1;
    sf::Texture texturej2;
    sf::Sprite spriteCommandes[2];
    sf::Vector2f position;
    sf::Font fontCommandes;
    sf::Text retour;
    sf::Text j1;
    sf::Text j2;
    sf::Texture menuFond;
    sf::Sprite spriteFond;
    sf::RectangleShape ligneDelim;


    public:
        MenuCommandes();
        MenuCommandes(sf::RenderWindow&);
        void retourMenu(int& selecEcran,sf::Event event);
        void draw(sf::RenderWindow &window);
};

class MenuBackground {
    private:
        int selection;
        sf::Texture bg[6];
        sf::Sprite spritebg[6];
        sf::RectangleShape rect[6];
        sf::Vector2f position;
        sf::Font fontBackground;
        sf::Text retour;
        sf::Text titre;
        sf::Texture menuFond;
        sf::Sprite spriteFond;

    public:
        MenuBackground();
        MenuBackground(sf::RenderWindow&);
        void retourMenu2(int& selecEcran,sf::Event event, MenuSelection& m,sf::RenderWindow&);
        void draw(sf::RenderWindow &window);
        void bouger(sf::Event,sf::RenderWindow &window);
        void moveRight();
        void moveLeft();
        void selectionner(sf::Event event, sf::RenderWindow& window,int& selecEcran, Scene& s,sf::Music&);
        void valider(sf::RenderWindow& window,int& selecEcran, Scene& s,sf::Music&);


};

#endif // MENU_H
