/**
 * \file menu.h
 * \brief Classes MenuPrincipal, MenuSelection, MenuCommandes, MenuBackground
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

    sf::Sprite sfond;
    sf::Vector2f position;

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
   * \attribute sf::Clock clockAttenteBoutton
   * \brief Temps d'attente entre chaque déplacement d'option avec le bouton
   *
   *  Attente afin de ne pas défiler les options du menu à une trop grande vitesse
   */
	sf::Clock clockAttente;


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
	   * \attribute sf::Text annulerChoixJ1
	   * \brief Texte d'annulation du choix de personnage
	   *
	   * Texte d'annulation du choix de personnage pour le joueur 1
	   */
		sf::Text annulerChoixJ1;

		/**
	   * \attribute sf::Text annulerChoixJ2
	   * \brief Texte d'annulation du choix de personnage
	   *
	   * Texte d'annulation du choix de personnage pour le joueur 2
	   */
		sf::Text annulerChoixJ2;

		/**
	   * \attribute sf::Texture texturePersos
	   * \brief Texture des personnages
	   *
	   * Texture des personnages affichés pour la sélection
	   */
		sf::Texture texturePersos;

		/**
	   * \attribute sf::Sprite spriteP1
	   * \brief Sprite pour le joueur 1
	   *
	   * Sprite pour la sélection du joueur 1
	   */
		sf::Sprite spriteP1;

		/**
	   * \attribute sf::Sprite spriteP2
	   * \brief Sprite pour le joueur 2
	   *
	   * Sprite pour la sélection du joueur 2
	   */
		sf::Sprite spriteP2;

		/**
	   * \attribute sf::Texture menuFond
	   * \brief Texture du fond du menu
	   *
	   * Texture du fond du menu
	   */
		sf::Texture menuFond;

		/**
	   * \attribute sf::Sprite spriteFond
	   * \brief Sprite du fond du menu
	   *
	   * Sprite du fond du menu
	   */
		sf::Sprite spriteFond;

		/**
	   * \attribute sf::Clock clockAttenteJoystick
	   * \brief Sprite du fond du menu
	   *
	   * Sprite du fond du menu
	   */
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
	   * \attribute int hauteurPerso
	   * \brief Hauteur de l'affichage des personnages
	   *
	   * Hauteur de l'affichage des personnages
	   */
		int hauteurPerso;

		/**
	   * \attribute int hauteurTexte
	   * \brief Hauteur de l'affichage des textes
	   *
	   * Hauteur de l'affichage des textes
	   */
		int hauteurTexte;

		/**
	   * \attribute int etatPersoJ1 = 0
	   * \brief Personnage à afficher pour le joueur 1
	   *
	   * Personnage 1 = etat 0, Personnage 2 = etat 1 ...
	   */
		int etatPersoJ1 = 0;

		/**
	   * \attribute int etatPersoJ2 = 1
	   * \brief Personnage à afficher pour le joueur 2
	   *
	   * Personnage 1 = etat 0, Personnage 2 = etat 1 ...
	   */
		int etatPersoJ2 = 1;

		/**
	   * \attribute int choixJ1 = -1
	   * \brief Choix du personnage pour le joueur 1
	   *
	   * ChoixJ1 = -1 => pas de selection, choixJ1 = 2 => Personnage 1 selectionné
	   */
		int choixJ1 = -1;

		/**
	   * \attribute int choixJ2 = -1
	   * \brief Choix du personnage pour le joueur 2
	   *
	   * ChoixJ2 = -1 => pas de selection, choixJ2 = 2 => Personnage 1 selectionné
	   */
		int choixJ2 = -1;


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
	   * \attribute sf::Music _effetSon
	   * \brief Son de sélection
	   *
	   *  Son de sélection d'une option du menu.
	   */
		sf::Music _effetSon;

	public :

		/**
	   * \fn MenuSelection()
	   * \brief Constructeur de MenuSelection
	   *
	   *  Constructeur de MenuSelection
	   */
		MenuSelection();

		/**
	   * \fn MenuSelection(sf::RenderWindow&)
	   * \brief Constructeur de MenuSelection avec la gestion de la fenêtre en paramètre
	   *
	   *  Constructeur de MenuSelection avec la gestion de la fenêtre en paramètre
	   */
		MenuSelection(sf::RenderWindow&);

		/**
	   * \fn void draw(sf::RenderWindow &window)
	   * \brief Gestion des affichages du menu
	   *
	   *  Gestion des affichages du menu (draw)
	   */
		void draw(sf::RenderWindow &window);

		/**
	   * \fn void persoSuivant_P1(int&,sf::RenderWindow&)
	   * \brief Passer au personnage suivant pour le joueur 1
	   *
	   *  Passer au personnage suivant pour le joueur 1
	   */
		void persoSuivant_P1(int&,sf::RenderWindow&);

		/**
	   * \fn void persoPrecedent_P1(int&,sf::RenderWindow&)
	   * \brief Passer au personnage précédent pour le joueur 1
	   *
	   *  Passer au personnage précédent pour le joueur 1
	   */
		void persoPrecedent_P1(int&,sf::RenderWindow&);

		/**
	   * \fn void persoSuivant_P2(int&,sf::RenderWindow&)
	   * \brief Passer au personnage suivant pour le joueur 2
	   *
	   *  Passer au personnage suivant pour le joueur 2
	   */
		void persoSuivant_P2(int&,sf::RenderWindow&);

		/**
	   * \fn void persoPrecedent_P1(int&,sf::RenderWindow&)
	   * \brief Passer au personnage précédent pour le joueur 2
	   *
	   *  Passer au personnage précédent pour le joueur 2
	   */
		void persoPrecedent_P2(int&,sf::RenderWindow&);

		/**
	   * \fn void bouger(sf::Event,sf::RenderWindow&)
	   * \brief Pression des touches
	   *
	   * Pression des touches pour passer au personnage suivant/précédent
	   */
		void bouger(sf::Event,sf::RenderWindow&);

		/**
	   * \fn int validationPerso(sf::Event event,int&,int&)
	   * \brief Valider les personnages
	   *
	   * Valider les personnages
	   */
		int validationPerso(sf::Event event,int&,int&);

		/**
	   * \fn void reset(sf::RenderWindow&)
	   * \brief Réinitialiser les paramètres pour une deuxieme selection
	   *
	   *  Reinitialiser les paramètres pour une deuxième selection après un combat ou après un retour au menu principal.
	   */
		void reset(sf::RenderWindow&);

		/**
	   * \fn void resetClock()
	   * \brief Réinitialiser les horloges
	   *
	   *  Reinitialiser les horloges pour l'attente boutons et joystick.
	   */
		void resetClock();

		/**
	   * \fn void initValidationPerso()
	   * \brief Initialiser l'état de sélection du joueur 2
	   *
	   *  Initialiser l'état de sélection du joueur 2 à -1 pour une annuler la sélection courante
	   */
		void initValidationPerso();
};

class MenuCommandes {
    private:
		/**
	   * \attribute sf::Texture texturej1
	   * \brief Texture pour affichage des commandes du joueur 1
	   *
	   *  Texture pour affichage des commandes du joueur 1
	   */
		sf::Texture texturej1;

		/**
	   * \attribute sf::Texture texturej2
	   * \brief Texture pour affichage des commandes du joueur 2
	   *
	   *  Texture pour affichage des commandes du joueur 2
	   */
		sf::Texture texturej2;

		/**
	   * \attribute sf::Sprite spriteCommandes[2]
	   * \brief Sprites pour l'affichage des commandes
	   *
	   *  Sprites pour l'affichage des commandes
	   */
		sf::Sprite spriteCommandes[2];

		/**
	   * \attribute sf::Font fontCommandes
	   * \brief Police pour les textes du menu commande
	   *
	   *  Police pour les textes du menu commande
	   */
		sf::Font fontCommandes;

		/**
	   * \attribute sf::Font fontCommandes
	   * \brief Texte pour afficher la commande de retour
	   *
	   *  Instructions pour le retour au menu principal
	   */
		sf::Text retour;

		/**
	   * \attribute sf::Text j1
	   * \brief Texte "Joueur 1"
	   *
	   *  Texte "Joueur 1" au-dessus des commandes
	   */
		sf::Text j1;

		/**
	   * \attribute sf::Text j2
	   * \brief Texte "Joueur 2"
	   *
	   *  Texte "Joueur 2" au-dessus des commandes
	   */
		sf::Text j2;

		/**
	   * \attribute sf::Texture menuFond
	   * \brief Texture du fond du menu
	   *
	   *  Texture du fond du menu
	   */
		sf::Texture menuFond;

		/**
	   * \attribute sf::Texture menuFond
	   * \brief Sprite du fond du menu
	   *
	   *  Sprite du fond du menu
	   */
		sf::Sprite spriteFond;

		/**
	   * \attribute sf::RectangleShape ligneDelim
	   * \brief Ligne de délimitation
	   *
	   *  Ligne de délimitation entre les commandes J1 et J2
	   */
		sf::RectangleShape ligneDelim;

		/**
	   * \attribute sf::Clock clockAttenteBoutton
	   * \brief Temps d'attente entre chaque déplacement d'option avec le bouton
	   *
	   *  Attente afin de ne pas défiler les options du menu à une trop grande vitesse
	   */
		sf::Clock clockAttenteBoutton;

    public:

		/**
	   * \fn MenuCommandes()
	   * \brief Constructeur du MenuCommandes
	   *
	   *  Constructeur du MenuCommandes
	   */
		MenuCommandes();

		/**
	   * \fn MenuCommandes(sf::RenderWindow&)
	   * \brief Constructeur du MenuCommandes
	   *
	   *  Constructeur du MenuCommandes avec la gestion de fenêtre en paramètre
	   */
		MenuCommandes(sf::RenderWindow&);

		/**
	   * \fn void retourMenu(int& selecEcran,sf::Event event)
	   * \brief Retourner au menu principal
	   *
	   *  Retourner au menu principal
	   */
        void retourMenu(int& selecEcran,sf::Event event);

		/**
	   * \fn void draw(sf::RenderWindow& window)
	   * \brief Affichages du menu de commandes
	   *
	   * Gestion des affichages (draw) du menu de commandes
	   */
        void draw(sf::RenderWindow &window);
};


class MenuBackground {
    private:
		/**
	   * \attribute int selection
	   * \brief Numero de la map sélectionnée
	   *
	   * Numero de la map sélectionnée
	   */
        int selection;

		/**
	   * \attribute sf::Texture bg[6]
	   * \brief Textures des aperçus des maps
	   *
	   * Textures des aperçus des maps
	   */
        sf::Texture bg[6];

		/**
	   * \attribute sf::Sprite spritebg[6]
	   * \brief Sprites des aperçus des maps
	   *
	   * Sprites des aperçus des maps
	   */
        sf::Sprite spritebg[6];

		/**
	   * \attribute sf::RectangleShape rect[6]
	   * \brief Rectangle des sélections de maps
	   *
	   * Permet de situer la sélection courante de la map
	   */
        sf::RectangleShape rect[6];

		/**
	   * \attribute sf::Font fontBackground
	   * \brief Police des textes du menu
	   *
	   * Police des textes du menu
	   */
        sf::Font fontBackground;

		/**
	   * \attribute sf::Text retour
	   * \brief Texte pour le retour au menu précédent
	   *
	   * Texte pour le retour au menu de sélection de personnages
	   */
        sf::Text retour;

		/**
	   * \attribute sf::Text titre
	   * \brief Titre du menu
	   *
	   * Titre du menu
	   */
        sf::Text titre;

		/**
	   * \attribute sf::Texture menuFond
	   * \brief Texture du fond du menu
	   *
	   * Texture du fond du menu
	   */
        sf::Texture menuFond;

		/**
	   * \attribute sf::Sprite spriteFond
	   * \brief Sprite du fond du menu
	   *
	   * Sprite du fond du menu
	   */
        sf::Sprite spriteFond;

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

    public:
		/**
	   * \fn MenuBackground()
	   * \brief Constructeur du menu de maps
	   *
	   * Constructeur du menu de maps
	   */
        MenuBackground();

		/**
	   * \fn MenuBackground(sf::RenderWindow&)
	   * \brief Constructeur du menu de maps
	   *
	   * Constructeur du menu de maps avec la gestion de fenêtre en paramètre
	   */
        MenuBackground(sf::RenderWindow&);

		/**
	   * \fn void retourMenu2(int& selecEcran,sf::Event event, MenuSelection& m,sf::RenderWindow&)
	   * \brief Retour au menu de sélection de personnages
	   *
	   * Retour au menu de sélection de personnages
	   */
        void retourMenu2(int& selecEcran,sf::Event event, MenuSelection& m,sf::RenderWindow&);

		/**
	   * \fn void draw(sf::RenderWindow& window)
	   * \brief Affichages du menu de commandes
	   *
	   * Gestion des affichages (draw) du menu de commandes
	   */
        void draw(sf::RenderWindow &window);

		/**
		* \fn void bouger(sf::Event,sf::RenderWindow &window)
		* \brief Sélection des options
		*
		* Permet de déplacer la sélection pour choisir une option
		*/
        void bouger(sf::Event,sf::RenderWindow &window);

		/**
		* \fn void moveRight()
		* \brief Déplacer à droite (changement d'option)
	    *
	    * Permet de déplacer la sélection pour sélectionner une option à droite
	    */
        void moveRight();

		/**
		* \fn void moveLeft()
		* \brief Déplacer à gauche (changement d'option)
	    *
	    * Permet de déplacer la sélection pour sélectionner une option à gauche
	    */
        void moveLeft();

		/**
		* \fn void selectionner(sf::Event event, sf::RenderWindow& window,int& selecEcran, Scene& s,sf::Music&)
		* \brief Sélectionner une map
	    *
	    * Permet de sélectionner une map
	    */
        void selectionner(sf::Event event, sf::RenderWindow& window,int& selecEcran, Scene& s,sf::Music&);

		/**
		* \fn void valider(sf::RenderWindow& window,int& selecEcran, Scene& s,sf::Music&)
		* \brief Valider une map
	    *
	    * Permet de valider la map sélectionnée et la charger
	    */
        void valider(sf::RenderWindow& window,int& selecEcran, Scene& s,sf::Music&);


};

/**
* \fn bool appuiBouttonManette(int joueur,int numBoutton,sf::Clock& clockAttente)
* \brief Détecte l'appui sur un bouton de la manette
*
* Détecte l'appui sur un bouton de la manette
*/
bool appuiBouttonManette(int joueur,int numBoutton,sf::Clock& clockAttente);

#endif // MENU_H
