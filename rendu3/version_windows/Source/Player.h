/**
 * \file Player.h
 * \brief Classe Player
 * \author Team La Bagarre
 *
 * Classe permettant la gestion d'un joueur de ses points de vie et d'énergie ainsi que de son champion
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "IncludeManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Player
{
private:

    /**
    * \attribute Personnage* _champion
    * \brief champion du joueur
    *
    * champion dont le joueur aura le contrôle durant le combat
    */
    Personnage* _champion;

    /**
    * \attribute double ratioScale
    * \brief valeur pour adapter les éléments à la fenêtre
    *
    * permet d'adapter les éléments afficher à taille de la fenêtre en se basant sur la largeur de la fenêtre
    */
    double ratioScale;

    /**
    * \attribute sf::Sprite _effet
    * \brief Sprite pour les effets du champions
    *
    * Sprite pour les attaques spéciales ou l'apparition
    */
    sf::Sprite _effet;

    /**
    * \attribute sf::Sprite _portrait
    * \brief Sprite pour le portrait du champion
    *
    * Sprite pour le portrait du champion dans la barre d'info en haut de l'écran
    */
    sf::Sprite _portrait;

    /**
    * \attribute sf::Sprite _barreInfos
    * \brief Sprite pour la barre d'info
    *
    * Sprite pour la barre d'info structurant l'affichage de la barre de vie et d'énergie
    */
    sf::Sprite _barreInfos;

    /**
    * \attribute sf::Texture _textureBI
    * \brief Sprite pour la barre d'info
    *
    * Texture destinée à être chargé par le sprite de la barre d'info
    */
    sf::Texture _textureBI;

    /**
    * \attribute int _PV
    * \brief points de vie du joueur
    *
    * Points de vie du joueur permettant la fin du combat lorsque cette variable est à 0
    */
    int _PV;

    /**
    * \attribute std::vector<sf::RectangleShape> _barrePV
    * \brief tableau des barres de vie
    *
    * Contient deux barres de vie, une pour les points de vie restant et une autre pour afficher ceux qu'ils manquent en fond
    */
    std::vector<sf::RectangleShape> _barrePV;

    /**
    * \attribute int _energie
    * \brief points d'énergie du joueur
    *
    * Points d'énergie du joueur lui permettant d'utiliser ses attaques spéciales
    */
    int _energie;

    /**
    * \attribute int _sauvegardeEnergie
    * \brief points d'énergie du joueur avant une attaque qu'il ne peut lancer
    *
    * Points d'énergie du joueur avant qu'il lance une attaque dont il n'a pas l'énergie suffisante. Cette variable permet l'affichage de la barre d'énergie manquante.
    */
    int _sauvegardeEnergie;

    /**
    * \attribute sf::Clock _clockPasAssez
    * \brief clock permet de remettre la barre d'énergie de fond dans sa couleur de base
    *
    * Clock qui permet de gérer le temps que la barre de d'énergie reste en rouge lorsqu'une attaque nécessitant plus d'énergie que possédé est lancée
    */
    sf::Clock _clockPasAssez;

    /**
    * \attribute std::vector<sf::RectangleShape> _barreEnergie
    * \brief tableau des barres d'énergie
    *
    * Contient deux barres d'énergie, une pour les points d'énergie restant et une autre pour afficher un fond ou les points manquants
    */
    std::vector<sf::RectangleShape> _barreEnergie;


    /**
    * \attribute float joystick0_axisX
    * \brief position de joystick de la manette 0 selon l'axe X
    *
    * Représente la position en X du joystick gauche sur la manette 0
    */
    float joystick0_axisX;

    /**
    * \attribute float joystick0_axisY
    * \brief position de joystick de la manette 0 selon l'axe Y
    *
    * Représente la position en Y du joystick gauche sur la manette 0
    */
    float joystick0_axisY;

    /**
    * \attribute float joystick0_axisZ
    * \brief position de la gachette gauche de la manette 0
    *
    * Représente la position de la gachette arrière gauche de la manette 0
    */
    float joystick0_axisZ;

    /**
    * \attribute float joystick0_axisR
    * \brief position de la gachette droite de la manette 0
    *
    * Représente la position de la gachette arrière droite de la manette 0
    */
    float joystick0_axisR;

    /**
    * \attribute float joystick0_axisX
    * \brief position de joystick de la manette 1 selon l'axe X
    *
    * Représente la position en X du joystick gauche sur la manette 1
    */
    float joystick1_axisX;

    /**
    * \attribute float joystick0_axisY
    * \brief position de joystick de la manette 0 selon l'axe Y
    *
    * Représente la position en Y du joystick gauche sur la manette 1
    */
    float joystick1_axisY;
    /**
    * \attribute float joystick0_axisZ
    * \brief position de la gachette gauche de la manette 0
    *
    * Représente la position de la gachette arrière gauche de la manette 0
    */
    float joystick1_axisZ;
    /**
    * \attribute float joystick0_axisR
    * \brief position de la gachette droite de la manette 0
    *
    * Représente la position de la gachette arrière droite de la manette 0
    */
    float joystick1_axisR;

    /**
    * \attribute int _posHorizontale
    * \brief deplacement horizontal à effectuer par le champion
    *
    * Permet de définir le deplacement horizontal à effectuer par le champion (-1:reculer,0:statique,1:avancer).
    * Permet aussi la gestion de l'ordre de priorité des commandes et des actions a effectuer.
    */
    int _posHorizontale;

    /**
    * \attribute int _posVerticale
    * \brief deplacement vertical à effectuer par le champion
    *
    * Permet de définir le deplacement vertical à effectuer par le champion (-1:accroupir,0:statique,1:sauter).
    * Permet aussi la gestion de l'ordre de priorité des commandes et des actions a effectuer.
    */
    int _posVerticale;

    /**
    * \attribute int _action
    * \brief action à effectuer par le champion
    *
    * Permet de définir l'action à effectuer par le champion:
    *-1 - rien
    * 0 - garde
    * 1 - punch
    * 2 - punchSP
    * 3 - kick
    * 4 - kickSP
    * 5 - SP
    * Permet aussi la gestion de l'ordre de priorité des commandes et des actions a effectué.
    */
    int _action;

    /**
    * \attribute int _prendCoup
    * \brief indique que le joueur à pris un coup
    *
    * Permet de déterminer quand un joueur prend un coup ainsi que les dégats qu'il prend
    */
    int _prendCoup;

    /**
    * \attribute bool _actionFini
    * \brief indique que le champion n'effectue aucune action
    *
    * Permet de déterminer quand le champion n'effectue aucune action et l'autorise donc à en effectuer une nouvelle
    */
    bool _actionFini;

    /**
    * \attribute std::vector<bool> _tabActions;
    * \brief indique l'action demandée par le joueur
    *
    * Permet de définir l'action demandée par le joueur et va permettre 2 choses:
    * La gestion des actions entre transformant ce tableau en les 3 booléens _posHorizontale, _posVerticale, _action
    * 0 - avancer
    * 1 - reculer
    * 2 - accroupi
    * 3 - saut
    * 4 - sautAvant
    * 5 - sautArriere
    * 6 - garde
    * 7 - punch
    * 8 - punchSP
    * 9 - kick
    * 10 - kickSP
    * 11 - SP
    *
    * La gestion de l'anti spam en initialisant le tableau _tabPeutAction
    */
    std::vector<bool> _tabActions;

    /**
    * \attribute std::vector<bool> _tabPeutAction;
    * \brief tableau définissant qu'elles attaques peuvent être lancée
    *
    * Permet de savoir qu'elle attaque peut être lancée dans le but de bloquer le spam lorsque l'on garde une touche appuyée
    * 0 - peut Punch
    * 1 - peut PunchSP
    * 2 - peut Kick
    * 3 - peut KickSP
    * 4 - peut Sp
    */
    std::vector<bool> _tabPeutAction;

public:
    /***************	Initialisation du joueur 	***************/

    /**
    * \fn Player(int,sf::RenderWindow&)
    * \brief Constructeur de la classe Player
    *
    * Constructeur de la classe player  qui représente un joueur
    */
    Player(int,sf::RenderWindow&);

    /**
    * \fn resetPlayer()
    * \brief reinitialise les données d'un joueur
    *
    * Reinitiliase les données d'un joueur en début de partie notamment la vie, l'énergie et les attributs de position
    */
    void resetPlayer();

    /**
    * \fn resetAttributs()
    * \brief reinitialise les attributs d'un joueur
    *
    * Reinitiliase les attributs de position d'un joueur
    */
    void resetAttributs();

    /**
    * \fn setChampion()
    * \brief définir le champion
    *
    * Permet de définir le champion du joueur après sa sélection
    */
    void setChampion(Personnage*);


    /***************	Commandes J1 	***************/

    /**
    * \fn peutAttaquerP1(sf::Event&, sf::RenderWindow&)
    * \brief défini si le joueur 1 peut attaquer ou non
    *
    * Permet de bloquer le spam d'attaques lorsqu'un touche reste appuyée à partir du vector _tabPeutAction
    */
    void peutAttaquerP1(sf::Event&, sf::RenderWindow&);

    /**
    * \fn recuperationCommandesP1(Player&)
    * \brief récupère les entrées clavier / manette du joueur 1
    *
    * Permet de récuperer les entrées clavier du joueur 1 pour les entrer dans le vector _tabActions afin qu'elles soient traitées
    */
    void recuperationCommandesP1(Player&);


    /***************	Commandes J2 	***************/

    /**
    * \fn peutAttaquerP2(sf::Event&, sf::RenderWindow&)
    * \brief défini si le joueur 2 peut attaquer ou non
    *
    * Permet de bloquer le spam d'attaques lorsqu'un touche reste appuyée à partir du vector _tabPeutAction
    */
    void peutAttaquerP2(sf::Event&, sf::RenderWindow&);

    /**
    * \fn recuperationCommandesP2(Player&)
    * \brief récupère les entrées clavier / manette du joueur 2
    *
    * Permet de récuperer les entrées clavier du joueur 2 pour les entrer dans le vector _tabActions afin qu'elles soient traitées
    */
    void recuperationCommandesP2(Player&);


    /***************	Gestion actions 	***************/

    /**
    * \fn recuperationAttaqueLancee()
    * \brief récupère la dernière attaque lancée
    *
    * Permet de remplir le vector _tabPeutAction à partir du vector _tabActions pour gérer l'anti spam
    */
    void recuperationAttaqueLancee();

    /**
    * \fn gestionDesCommandes(Player&)
    * \brief gère l'ordre d'importance des actions
    *
    * Permet de gérer les actions à traiter en priorité et celles à bloquer lorsque d'autres sont éxécutées
    */
    void gestionDesCommandes(Player&);


    /***************	Lancement des actions 	***************/

    /**
    * \fn lancerActions()
    * \brief lance les actions du champion
    *
    * Lance l'action du champion demandée par le joueur une fois le traitement des entrées clavier effectué
    */
    bool lancerActions(Player&);

    /**
    * \fn lancerApparition()
    * \brief lance l'animation de début de combat
    *
    * Lance l'animation de début de combat durant laquelle le joueur ne peut rien faire
    */
    bool lancerApparition();

    /**
    * \fn finpartie()
    * \brief lance l'animation de fin de combat
    *
    * Lance l'animation de fin de combat qui sera "mort" si le joueur a 0 points de vie ou victoire dans le reste des cas
    */
    bool finPartie();


    /***************	Affichages 	***************/

    /**
    * \fn afficherInfos(sf::RenderWindow&)
    * \brief affiche les barres de points de vie et d'énergie
    *
    * Affiche les différentes barres de points de vie et d'énergie en fonction de la valeur actuelle de ces attributs
    */
    void afficherInfos(sf::RenderWindow&);

    /**
    * \fn affichageChampion(sf::RenderWindow&)
    * \brief affiche le champion et les effets
    *
    * Affiche le champion et les effets (peut également servir à afficher la hurtbox, la hitbox et la gardebox si les lignes sont décommentées)
    */
    void affichageChampion(sf::RenderWindow&);

    /**
    * \fn afficherHitspark(sf::RenderWindow& window)
    * \brief affichage de l'étincelle lorsqu'un joueur prend des dégats
    *
    * Affichage d'un petite étincelle lorsqu'un joueur inflige des dégats à son adversaire
    */
    void afficherHitspark(sf::RenderWindow& window);


    /***************	Accesseurs / Setteurs 	***************/

    /**
    * \fn getPV()
    * \brief accesseur des points de vie
    *
    * Permet de récuperer les points de vie du joueur pour savoir quand lancer les animations de fin de combat
    */
    int getPV();

    /**
    * \fn setDegats(int))
    * \brief inflige des dégats au joueur
    *
    * Décremente les points de vie du joueur par un entier passer en paramètre
    */
    void setDegats(int);

    /**
    * \fn getAction()
    * \brief accesseur de l'attribut _action
    *
    * Permet de récuper l'action en cours du champion pour pouvoir lancer la garde automatiquement quand le jouer adverse attaque et le notre recule
    */
    int getAction();

    /**
    * \fn getPrendCoup
    * \brief accesseur de l'attribut _prendCoup
    *
    * Permet d'avoir accès à l'attribut _prendCoup de l'adversaire pour lui infliger des degats
    */
    int* getPrendCoup();

    /**
    * \fn getChampion()
    * \brief accesseur du champion
    *
    * Permet de récuperer le champion notamment pour la gestion des collisions
    */
    Personnage* getChampion();
};

#endif
