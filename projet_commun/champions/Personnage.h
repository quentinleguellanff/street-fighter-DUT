/**
 * \file Personnage.h
 * \brief Classe Mère Personnage et classes filles
 * \author Team La Bagarre
 *
 * Classe Mère et classes filles des différents personnages du jeu
 * Par soucis pratique on a rassemblé classe mere et fille
 */


#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "../IncludeManager.h"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>


class Personnage
{
protected:
    /**
   * \attribute sf::Texture _texture
   * \brief permet de stocker la texture du sprite du personnage
   *
   * les textures rassembleront les principaux sprites d'action des personnages on la chargera avec un fichier
   */
    sf::Texture _texture;
    /**
   * \attribute sf::Sprite _sprite
   * \brief permet de stocker le sprite du personnage
   *
   * cela permet d'afficher les animations du personnages, on pourra jouer sur sa position
   */
    sf::Sprite _sprite;
    /**
   * \attribute sf::Sprite _icone
   * \brief permet de stocker le sprite de l'icone du personnage
   *
   * cela permet d'afficher l'icone du personnage en haut a cote de la barre de vie lors d'un combat
   */
    sf::Sprite _icone;
    /**
   * \attribute sf::Clock _clockEffet
   * \brief clock qui permet de cadencer les animations de l'effet hitspark
   *
   */
    sf::Clock _clockEffet;
    /**
   * \attribute sf::Clock _clockAnim
   * \brief clock qui permet de cadencer les animations de changement de sprite sur la texture (textureRect)
   *
   */
    sf::Clock _clockAnim;
    /**
   * \attribute sf::Clock _clockMove
   * \brief clock qui permet de cadencer les movement de personnage soit les evolutions de la position
   *
   */
    sf::Clock _clockMove;
    /**
   * \attribute sf::Vector2f _tailleSprite
   * \brief vecteur qui permet de stocker la taille du sprite du personnage
   *
   */
    sf::Vector2f _tailleSprite;		//taille du personnage sous la forme d'un vector de float à 2 dimensions
    /**
   * \attribute Scene _scene
   * \brief objet de la classe Scene dont l'adresse est passé par réference dans le constructeur
   *    permet de recuperer le sol et adapté les deplacement et la position du sprite du personnage en fonction
   */
    Scene _scene;					//la scene sur laquelle se passe le combat
    /**
   * \attribute sf::RectangleShape _hurtbox
   * \brief Rectangle de detection de prise de coup et de collision
   *    permet de définir une zone de collision qui pourra se déplacer et prendre une taille différente en fonction du sprite
   *    du personnage, permet aussi de detecter les collisions avec la hitbox de l'ennemi.
   */
    sf::RectangleShape _hurtbox;	//zone de prise de dégats
    /**
   * \attribute sf::RectangleShape _hitbox
   * \brief Rectangle de coup
   *    permet de définir une zone de collision qui pourra se déplacer et prendre une taille différente en fonction du sprite
   *    du personnage, permet également de placer une zone permettant de donner des dégats à l'adversaire en fonction de la hurtbox de l'ennemi
   */
    sf::RectangleShape _hitbox;		//zone de mise de dégats
    /**
   * \attribute sf::RectangleShape _garedebox
   * \brief Rectangle de garde
   *    permet de detecter les collisions lorsque le personnage est en garde, il pourra alors se proteger des coups de l'ennemi.
   */
    sf::RectangleShape _gardebox;	//zone de parade
    /**
   * \attribute float _scale
   * \brief permet de définir le scale du personnage
   *
   * le scale peut nous permettre d'effectuer un "mirroir" du sprite lorsque qu'on l'utilise avec setScale
   * et qu'il a une valeur négative
   */
    float _scale;
    /**
   * \attribute float _posX
   * \brief permet de définir la position du sprite du personnage dans la fenêtre sur l'axe X
   *
   */
    float _posX;
    /**
   * \attribute float _posY
   * \brief permet de définir la position du sprite du personnage dans la fenêtre sur l'axe Y
   *
   */
    float _posY;                    //Position Y du perso
    /**
   * \attribute float _vsaut
   * \brief permet de dénfinir la vitesse de saut d'un personnage
   *    cette vitesse est généralement négative et permet au personnage d'avoir un mouvement verticale,
   *    lors d'un saut elle est soustraite à la vitesse de gravité.
   */
    float _vsaut;
    /**
   * \attribute int _cptAvancer
   * \brief compteur pour l'animation Avancer
   *
   *    compte le nombre de restart d'une clock pour l'animation du sprite, permet de changer de sprite à chaque iteration
   *
   */
    int _cptAvancer;				//compteur pour l'animation avancer
    /**
   * \attribute int _cptReculer
   * \brief compteur pour l'animation Reculer
   *
   *    compte le nombre de restart d'une clock pour l'animation du sprite, permet de changer de sprite à chaque iteration
   *
   */
    int _cptReculer;				//compteur pour l'animation reculer
    /**
   * \attribute int _cptStatic
   * \brief compteur pour l'animation Static
   *
   *    compte le nombre de restart d'une clock pour l'animation du sprite, permet de changer de sprite à chaque iteration
   *
   */
    int _cptStatic;					//compteur pour l'animation de repos
    /**
   * \attribute int _cptAccroupi
   * \brief compteur pour l'animation Static
   *
   *   compte le nombre de restart d'une clock pour l'animation du sprite, permet de changer de sprite à chaque iteration
   *
   */
    int _cptAccroupi;				//compteur pour l'animation	accroupi
    /**
   * \attribute int _cptSauter
   * \brief compteur pour l'animation Sauter
   *
   *   compte le nombre de restart d'une clock pour l'animation du sprite, permet de changer de sprite à chaque iteration
   *
   */
    int _cptSauter;					//compteur pour les animations de saut
    /**
   * \attribute int _cptApparition
   * \brief compteur pour l'animation Apparition
   *
   *   compte le nombre de restart d'une clock pour l'animation du sprite, permet de changer de sprite à chaque iteration
   *
   */
    int _cptApparition;				//compteur pour l'animation de début de combat
    /**
   * \attribute int _cptAction
   * \brief compteur pour l'animation Action
   *
   *   compte le nombre de restart d'une clock pour l'animation du sprite, permet de changer de sprite à chaque iteration
   *
   */
    int _cptAction;					//compteur pour les animations de type attaques
    /**
   * \attribute int _cptPrendCoup
   * \brief compteur pour l'animation de prise de coup
   *
   *   compte le nombre de restart d'une clock pour l'animation du sprite, permet de changer de sprite à chaque iteration
   *
   */
    int _cptPrendCoup;
    /**
   * \attribute int _cptGarde
   * \brief compteur pour l'animation de garde
   *
   *   compte le nombre de restart d'une clock pour l'animation du sprite, permet de changer de sprite à chaque iteration
   *
   */
    int _cptGarde;					//compteur pour l'animation de garde debout
    /**
   * \attribute int _cptSP
   * \brief compteur pour l'animation de d'attaques spéciales
   *
   *   compte le nombre de restart d'une clock pour l'animation du sprite, permet de changer de sprite à chaque iteration
   *
   */
    int _cptSP;						//compteur pour les effets sur les animations spéciales
    /**
   * \attribute int _orientation
   * \brief permet de définir l'orientation du personnage 1 ou -1
   *
   *   si le personnage regarde vers la gauche, il a une orientation de -1 et inversement 1 si il regarde a droite
   *
   */
    int _orientation;		//orientation du personnage (-1 : personnage à gauche)
    /**
   * \attribute bool _hitspark
   * \brief permet d'activer l'animation de hitspark (explosion lors d'un coup)
   *
   *   est mis à true lorsqu'un personnage touche son adversaire avec une attaque
   *
   */
    bool _hitSpark;
    /**
   * \attribute bool _peutHitSpark
   * \brief permet de gerer les permissions d'animations du hitSpark
   *
   *   deux hitspark ne peuvent être lancés en même temps, il passe a false lorsqu'un hitspark est en cours.
   *
   */
    bool _peutHitSpark;
    /**
   * \attribute  sf::Music _effetSonore;
   * \brief permet de stocker les effets sonores pour les jouer ensuite
   *
   *   ils seront appellés lors des animations
   *
   */
    sf::Music _effetSonore;
    /**
   * \attribute  bool _effetEnCours
   * \brief permet de determiner si un hitspark est en Cours
   *
   */
    bool _effetEnCours;
    /**
   * \attribute int _cptAnimEffet
   * \brief compteur pour l'animation d'effet type hitspark
   *
   *   compte le nombre de restart d'une clock pour l'animation du sprite, permet de changer de sprite à chaque iteration
   *
   */
    int _cptAnimEffet;
    /**
   * \attribute sf::Texture _textureEffet
   * \brief texture du sprite du hitspark
   *
   *   compte le nombre de restart d'une clock pour l'animation du sprite, permet de changer de sprite à chaque iteration
   *
   */
    sf::Texture _textureEffet;
    /**
   * \attribute sf::Sprite _spriteHitSpark
   * \brief sprite du hitspark
   *
   *   permet l'affichage du hitspark
   *
   */
    sf::Sprite _spriteHitSpark;

public:
    /**
   * \fn Personnage()
   * \brief Constructeur vide de Personnage()
   *
   */
    Personnage();
    /**
   * \fn ~Personnage()
   * \brief destructeur de Personnage()
   *
   */
    ~Personnage() {};
    /**
   * \fn void setScene(const Scene&)
   * \brief setteur de l'attribut _scene
   *
   */
    void setScene(const Scene&);
    /**
   * \fn     sf::Sprite getSprite()
   * \brief getteur de l'attribut _sprite
   *
   */
    sf::Sprite getSprite();
    /**
   * \fn     void setSprite()
   * \brief permet de selectionner un rectangle de selection de la texture du sprite (position x, position y, largeur , longueur)
   *
   */
    void setSprite(int, int, int, int);		//permet de définir le sprite du personnage ainsi que de mettre à jour sa taille
    /**
   * \fn     sf::Sprite getIcone()
   * \brief getteur du sprite _icone
   *
   */
    sf::Sprite getIcone();
    /**
   * \fn     sf::RectangleShape getHurtbox()
   * \brief getteur de la hurtbox du personnage
   *
   */
    sf::RectangleShape getHurtbox();	//permet de récupérer la zone de prise de dégats
    /**
   * \fn     sf::RectangleShape getHitbox()
   * \brief getteur de la hitbox du personnage
   *
   */
    sf::RectangleShape getHitbox();		//permet de récupérer la zone de mise de dégats
    /**
   * \fn     sf::RectangleShape getGardebox()
   * \brief getteur de la Gardebox du personnage
   *
   */
    sf::RectangleShape getGardebox();	//permet de récupérer la zone de parade
    /**
   * \fn     int getOrientation()
   * \brief getteur de l'orientation du personnage
   *
   */
    int getOrientation() const;		//récupérer l'orientation du personnage
    /**
   * \fn     void setPosX(int)
   * \brief setteur de la position en X du personnage
   *
   */
    void setPosX(int);
    /**
   * \fn     int getPosX(int)
   * \brief getteur de la position en X du personnage
   *
   */
    int getPosX();
    /**
   * \fn     void setPosY(int)
   * \brief setteur de la position en Y du personnage
   *
   */
    void setPosY(int);
    /**
   * \fn     int getPosY(int)
   * \brief getteur de la position en Y du personnage
   *
   */
    int getPosY();
    /**
   * \fn     void affichageEffet(sf::RenderWindow& window)
   * \brief méthode permettant d'afficher le hitspark
   *
   *        lorsque que _hitspark est true
   *        utilise une clock et affiche, cadencé à une certaine vitesse, un enchainement de sprite
   *        présent sur la feuille de texture du sprite correspondant. affiche une fois le traitement efféctué.
   *
   */
    void affichageEffet(sf::RenderWindow& window);
    /**
   * \fn     void collision(Personnage&, int&)
   * \brief méthode permettant de gerer les collisions de deux personnages sur un meme axe X
   *
   *        Lorsque le sprite du personnage cible rencontre le personnage passé en paramètre, le deplacement des deux personnages tombe à 0,
   *        les deux personnages ne se traversent donc pas. On compare la position droite du sprite avec la position gauche de la hurtbox de l'ennemi avant le deplacement.
   *        la valeur du deplacement est passé en parametre.
   *
   */
    void collision(Personnage&, int&);	//permet de bloquer le fait que les deux personnages puis se croiser
    /**
   * \fn     void collisionCoup(Personnage&, int&)
   * \brief méthode permettant de gerer les collisions de deux personnages sur un meme axe X
   *
   *        Lorsque le sprite du personnage cible rencontre le personnage passé en paramètre, le deplacement des deux personnages tombe à 0,
   *        les deux personnages ne se traversent donc pas. On compare la position droite du sprite avec la position gauche de la hurtbox de l'ennemi avant le deplacement.
   *        la valeur du deplacement est passé en parametre.
   *
   */
    bool collisionCoup(Personnage&);		//permet de gérer la prise de coups
    void keepInWalls();		//permet de maintenir les personnages entre les limites de la carte
    void rotate(Personnage&);		//gère la rotation des personnages quand ils se dépassent
    void resetCptAccroupi();	//reinitialise le compteur pour l'animation accroupi
    void resetHitbox();
    bool auSol();
    virtual bool victoire()
    {
        return true;
    };
    virtual bool mort()
    {
        return true;
    };

    virtual bool prendCoup(int*,sf::Sprite&,int&)
    {
        return true;
    };	//animation de prise de coup
    virtual bool parade(int*,sf::Sprite&)
    {
        return true;
    };


    virtual void statique(Personnage&) {};	//animation au repos
    virtual void garde() {};			//animation de garde debout				--> gestion de la garde à faire
    virtual void avancer(Personnage&) {};		//animation de marche vers l'avant
    virtual void reculer() {};		//animation de marche vers l'arrière

    void collisionsaut(Personnage&,int&);
    virtual bool sauter(int&,Personnage&,int*,int&)
    {
        return true;
    };		//animation de saut
    virtual bool sauterAvant(Personnage&)
    {
        return true;
    };		//animation de saut vers l'arrière
    virtual bool sauterArriere(Personnage&)
    {
        return true;
    };		//animation de saut vers l'arrière
    virtual void accroupi(bool) {};		//animation accroupi

    virtual bool apparition(sf::Sprite&)
    {
        return true;
    };	//animation de début de combat
    virtual bool punch(Personnage&,int*,int&)
    {
        return true;
    };				//animation de coup de poing
    virtual bool punchSP(sf::Sprite&,Personnage&,int*,int&)
    {
        return true;
    };	//animation de coup de poing spécial
    virtual bool sautPunch(Personnage&,int*,int&)
    {
        return true;
    };			//animation de coup de poing en saut
    virtual bool kick(Personnage&,int*,int&)
    {
        return true;
    };					//animation de coup de pied
    virtual bool sautKick(Personnage&,int*,int&)
    {
        return true;
    };				//animation de coup de pied en saut
    virtual bool kickSP(Personnage&,int*,int&)
    {
        return true;
    };
    virtual bool SP(sf::Sprite&,Personnage&,int*,int&)
    {
        return true;
    };		//animation de coup spécial
};

class Dhalsim : public Personnage
{
public:
    Dhalsim() {};
    Dhalsim(int,Scene&,sf::RenderWindow&);

    bool apparition(sf::Sprite&) override;
    bool victoire() override;
    bool mort( ) override;

    bool prendCoup(int*,sf::Sprite&,int&) override;
    bool parade(int*,sf::Sprite&) override;

    void statique(Personnage&) override;
    void garde() override;
    void avancer(Personnage&) override;
    void reculer() override;

    bool sauter(int&,Personnage&,int*,int&) override;
    bool sauterAvant(Personnage&) override;
    bool sauterArriere(Personnage&) override;
    void accroupi(bool) override;


    bool punch(Personnage&,int*,int&) override;
    bool sautPunch(Personnage&,int*,int&) override;
    bool punchSP(sf::Sprite&,Personnage&,int*,int&) override;

    bool kick(Personnage&,int*,int&) override;
    bool sautKick(Personnage&,int*,int&) override;
    bool kickSP(Personnage&,int*,int&) override;

    bool SP(sf::Sprite&,Personnage&,int*,int&) override;
};

class Ryu : public Personnage
{
public:
    Ryu() {};
    Ryu(int,Scene&,sf::RenderWindow&);

    bool apparition(sf::Sprite&) override;
    bool victoire() override;
    bool mort( ) override;

    bool prendCoup(int*,sf::Sprite&,int&) override;
    bool parade(int*,sf::Sprite&) override;

    void statique(Personnage&) override;
    void garde() override;
    void avancer(Personnage&) override;
    void reculer() override;

    bool sauter(int&,Personnage&,int*,int&) override;
    bool sauterAvant(Personnage&) override;
    bool sauterArriere(Personnage&) override;
    void accroupi(bool) override;

    bool punch(Personnage&,int*,int&) override;
    bool sautPunch(Personnage&,int*,int&) override;
    bool punchSP(sf::Sprite&,Personnage&,int*,int&) override;

    bool kick(Personnage&,int*,int&) override;
    bool sautKick(Personnage&,int*,int&) override;
    bool kickSP(Personnage&,int*,int&) override;

    bool SP(sf::Sprite&,Personnage&,int*,int&) override;
};

class Greg : public Personnage
{
public:
    Greg() {};
    Greg(int,Scene&,sf::RenderWindow&);

    bool apparition(sf::Sprite&) override;
    bool victoire() override;
    bool mort( ) override;

    bool prendCoup(int*,sf::Sprite&,int&) override;
    bool parade(int*,sf::Sprite&) override;

    void statique(Personnage&) override;
    void garde() override;
    void avancer(Personnage&) override;
    void reculer() override;

    bool sauter(int&,Personnage&,int*,int&) override;
    bool sauterAvant(Personnage&) override;
    bool sauterArriere(Personnage&) override;
    void accroupi(bool) override;

    bool punch(Personnage&,int*,int&) override;
    bool sautPunch(Personnage&,int*,int&) override;
    bool punchSP(sf::Sprite&,Personnage&,int*,int&) override;

    bool kick(Personnage&,int*,int&) override;
    bool sautKick(Personnage&,int*,int&) override;
    bool kickSP(Personnage&,int*,int&) override;

    bool SP(sf::Sprite&,Personnage&,int*,int&) override;
};

#endif
