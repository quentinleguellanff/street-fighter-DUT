/**
 * \file menu.h
 * \brief Classe GestionFenetre
 * \author Team La Bagarre
 *
 * Classe permettant la gestion entre les différents modes du jeu.
 *
 */

#ifndef GESTIONFENETRE_H
#define GESTIONFENETRE_H

#include "IncludeManager.h"
#include "Player.h"
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class GestionFenetre
{
private:
    /**
    * \attribute sf::RenderWindow window
    * \brief fenêtre de jeu
    *
    * Création de la fenêtre, gestion de la taille, gestion du nombre de fps et de la visibilité de la souris.
    */
    sf::RenderWindow window;

    /**
    * \attribute Scene scene
    * \brief décor de fond du combat
    *
    * Gestion des décors définis dans la classe Scene.
    */
    Scene scene;
    /**
    * \attribute int selecEcran
    * \brief indice de sélection de la phase de jeu à lancer/afficher
    *
    * Gestion entre les différents menu et les combats. Chaque menu ainsi que le combat ont une valeur selecEcran différente.
    */
    int selecEcran;

    /**
    * \attribute MenuPrincipal* menuPrinc
    * \brief déclaration du menu principal
    *
    * Menu principal et sa gestion.
    */
    MenuPrincipal* menuPrinc;

    /**
    * \attribute MenuCommandes* menuCommandes
    * \brief déclaration de la page des commandes
    *
    * Menu commandes et sa gestion.
    */
    MenuCommandes* menuCommandes;

    /**
    * \attribute MenuSelection* menuSel
    * \brief déclaration du menu personnage
    *
    * Menu de selection des personnages et sa gestion.
    */
    MenuSelection* menuSel;

    /**
    * \attribute MenuBackground* menuBackground
    * \brief déclaration du menu des décors de combat
    *
    * Menu de selection du décor de jeu et sa gestion.
    */
    MenuBackground* menuBackground;


    /**
    * \attribute sf::Texture readyF
    * \brief Texture d'animation de début de combat
    *
    * Affichage au début du combat: "Ready" puis "Fight".
    */
    sf::Texture readyF;

    /**
    * \attribute sf::Sprite readyFight
    * \brief Sprite d'animation de début de combat
    *
    * Affichage au début du combat: "Ready" puis "Fight".
    */
    sf::Sprite readyFight;

    /**
    * \attribute sf::Clock clockReadyFight
    * \brief Horloge début de combat
    *
    * Décompte 1 seconde puis enlève le sprite "Fight" affiché à l'écran
    */
    sf::Clock clockReadyFight;

    /**
    * \attribute Player* joueur1
    * \brief appelle la classe Player
    *
    * Creation d'un joueur1, objet de la classe Player
    */
    Player* joueur1;
    /**
    * \attribute Player* joueur2
    * \brief appelle la classe Player
    *
    * Creation d'un joueur2, objet de la classe Player
    */
    Player* joueur2;

    /**
    * \attribute int selecChamp_P1
    * \brief selection champion(personnage choisi)
    *
    * Variable permettant de sauvergarder le choix du personnage pour paramétrer l'appel de la fonction des personnages (Greg, Ryu...)
    * Gestion des personnages pour le joueur 1
    */
    int selecChamp_P1;

    /**
    * \attribute int selecChamp_P2
    * \brief selection champion(personnage choisi)
    *
    * Variable permettant de sauvergarder le choix du personnage pour paramétrer l'appel des sous-classes de Personnage (Greg, Ryu...)
    * Gestion des personnages pour le joueur 2
    */
    int selecChamp_P2;

    /**
    * \attribute Personnage* champion_P1
    * \brief utilisation de la classe Personnage
    *
    * gestion des personnages
    */
    Personnage* champion_P1;

    /**
    * \attribute Personnage* champion_P2
    * \brief utilisation de la classe Personnage
    *
    * gestion des personnages
    */
    Personnage* champion_P2;

    /**
    * \attribute std::vector<bool> _tabActionCombat
    * \brief tableau de booléen pour les conditions d'animation
    *
    * Permet la gestion du combat: animation des personnages début du combat, permission d'action, animation de fin du combat.
    *  0-apparitionsFinies_P1
    *  1-apparitionsFinies_P2
    *  2-actionFini_P1
    *  3-actionFini_P2
    *  4-animationFinLancee
    *  5-animationFin_P1
    *  6-animationFin_P2
    */
    std::vector<bool> _tabActionCombat;

    /**
    * \attribute Music musique
    * \brief musique du jeu
    *
    * Gestion des musiques en fonction du mode de jeu.
    */
    sf::Music musique;

public:

    /**
    * \fn GestionFenetre()
    * \brief constructeur de l'objet de gestion de la fenêtre
    *
    */
    GestionFenetre();

    /**
    * \fn 	~GestionFenetre(){}
    * \brief destructeur de l'objet de gestion de la fenêtre
    *
    */
    ~GestionFenetre() {};

    /**
    * \fn sf::RenderWindow& getWindow()
    * \brief accesseur de la fenêtre
    *
    * Accesseur de la fenêtre pour l'appeler dans le main
    */
    sf::RenderWindow& getWindow();

    /**
    * \fn void action()
    * \brief détermine quelle gestion de mode utiliser
    *
    * Méthode de gestion des différentes méthodes utilisées pour les différents modes du jeu (menu, combat).
    */
    void action();

    /**
    * \fn void gestionMenuPrinc(sf::Event&)
    * \brief gestion du menu principale
    *
    * Méthode de gestion des différentes méthodes utilisées pour le menu principal
    */
    void gestionMenuPrinc(sf::Event&);

    /**
    * \fn void gestionSelecPerso(sf::Event&)
    * \brief gestion du menu de selection des personnages
    *
    * Méthode de gestion des différentes méthodes utilisées pour le menu selection des personnages
    */
    void gestionSelecPerso(sf::Event&);

    /**
    * \fn void gestionMenuCommande(sf::Event&)
    * \brief gestion du menu des commandes
    *
    * Méthode de gestion des différentes méthodes utilisées pour le menu commande
    */
    void gestionMenuCommande(sf::Event&);

    /**
    * \fn void gestionSelecScene(sf::Event&)
    * \brief gestion du menu des scènes
    *
    * Méthode de gestion des différentes méthodes utilisées pour le menu des décors
    */
    void gestionSelecScene(sf::Event&);

    /**
    * \fn void combat(sf::Event&)
    * \brief gestion du combat
    *
    * Méthode de gestion du combat et des méthodes utilisées pour le combat
    */
    void combat(sf::Event&);

    /**
    * \fn void finCombat()
    * \brief gestion fin de combat
    *
    * Méthode de gestion des différentes méthodes utilisées pour la fin de combat et la réinitialisation des valeurs pour recommencer un nouveau combat.
    */
    void finCombat();

    /**
    * \fn void affichageCombat()
    * \brief gestion des affichages du combat
    *
    * Méthode de gestion des différentes méthodes utilisées pour afficher les personnages, les barres de vie et d'énergie et des effets.
    */
    void affichageCombat();
};

#endif
