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
   *  Sprites remplacés par la sélection courante et affiché (draw)
   */
    sf::Sprite spriteMenux[3];

    /**
   * \attribute sf::Text titre
   * \brief Texte du titre du jeu
   *
   *  Titre "La Bagarre"
   */
    sf::Text titre;

    /**
   * \attribute  float joystick0_axisX
   * \brief Position en x du joystick gauche (0)
   *
   *  Position en x du joystick gauche (0)
   */
    float joystick0_axisX;


    /**
   * \attribute  float joystick0_axisY
   * \brief Position en y du joystick gauche (0)
   *
   *  Position en y du joystick gauche (0)
   */
    float joystick0_axisY;


    /**
   * \attribute sf::Clock clockAttenteJoystick
   * \brief Temps d'attente entre chaque déplacement d'option avec le joystick
   *
   *  Attente afin de ne pas défiler les options du menu à une trop grande vitesse
   */
    sf::Clock clockAttenteJoystick;
	
	
    /**
   * \attribute sf::Clock clockAttenteBoutton
   * \brief Temps d'attente entre chaque déplacement d'option avec le bouton
   *
   *  Attente afin de ne pas défiler les options du menu à une trop grande vitesse
   */
    sf::Clock clockAttenteBoutton;

    /**
   * \attribute sf::Music _effetSon
   * \brief Son de sélection
   *
   *  Son de sélection d'une option du menu.
   */
    sf::Music _effetSon;

public:
    /**
   * \fn MenuPrincipal()
   * \brief Constructeur MenuPrincipal()
   *
   * Constructeur du Menu Principal
   */
    MenuPrincipal();

    /**
   * \fn MenuPrincipal (float width, float height)
   * \brief Constructeur MenuPrincipal(float width, float height)
   *
   * Constructeur du Menu Principal avec en paramètre la largeur et hauteur de la fenêtre
   */
    MenuPrincipal (float width, float height);

    /**
   * \fn ~MenuPrincipal()
   * \brief Destructeur MenuPrincipal
   *
   * Destructeur du Menu Principal
   */
    ~MenuPrincipal();

    /**
   * \fn void draw(sf::RenderWindow& window)
   * \brief Affichages du menu principal
   *
   * Gestion des affichages (draw) du menu principal
   */
    void draw(sf::RenderWindow& window);

    /**
   * \fn  void bouger(int&,sf::Event, sf::RenderWindow& window)
   * \brief Sélection des options
   *
   * Permet de descendre et monter pour choisir une option
   */
    void bouger(int&,sf::Event, sf::RenderWindow& window);

    /**
   * \fn void moveUp()
   * \brief Monter (changement d'option)
   *
   * Permet de monter pour sélectionner une option au-dessus
   */
    void moveUp();

    /**
   * \fn void moveDown()
   * \brief Descendre (changement d'option)
   *
   * Permet de descendre pour sélectionner une option en-dessous
   */
    void moveDown();

    };


class MenuSelection {
private:

    /**
   * \attribute sf::Texture textureVS
   * \brief Texture image VS
   *
   *  Texture image VS entre les deux personnages
   */
    sf::Texture textureVS;

    /**
   * \attribute sf::Sprite spriteVS
   * \brief Sprite VS
   *
   *  Sprite de l'image VS entre les deux personnages
   */
    sf::Sprite spriteVS;

    /**
   * \attribute sf::Font fontMenu
   * \brief Police du menu sélection
   *
   *  Sprite d'arrière plan du menu
   */
    sf::Font fontMenu;

    /**
   * \attribute sf::Text titre
   * \brief Titre du menu de sélection
   *
   * Texte : "sélection des personnages"
   */
    sf::Text titre;

    /**
   * \attribute sf::Text j1
   * \brief Texte du menu de selection pour le joueur 1
   *
   * Texte : "JOUEUR 1"
   */
    sf::Text j1;

    /**
   * \attribute sf::Text j2
   * \brief Texte du menu de selection pour le joueur 2
   *
   * Texte : "JOUEUR 2"
   */
    sf::Text j2;

    /**
   * \attribute sf::Text nomPersoJ1
   * \brief Nom du personnage J1
   *
   * Texte pour le nom du personnage sélectionné par le joueur 1
   */
    sf::Text nomPersoJ1;

    /**
   * \attribute sf::Text nomPersoJ2
   * \brief Nom du personnage J2
   *
   * Texte pour le nom du personnage sélectionné par le joueur 2
   */
    sf::Text nomPersoJ2;

    /**
   * \attribute f::Text annulerChoixJ1
   * \brief Nom du personnage J2
   *
   * Texte pour le nom du personnage sélectionné par le joueur 2
   */
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
    void resetClock();
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
		sf::Clock clockAttenteBoutton;

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

    float joystick0_axisX;
    float joystick0_axisY;
    sf::Clock clockAttenteJoystick;
    sf::Clock clockAttenteBoutton;

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

bool appuiBouttonManette(int joueur,int numBoutton,sf::Clock& clockAttente);

#endif // MENU_H
