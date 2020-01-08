#ifndef JOTARO_H
#define JOTARO_H

#include "../IncludeManager.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


class Jotaro : public sf::Sprite
{
private:
	const float SCALE=3.7;		//échelle d'agrandissement du champion
	int _orientation;		//orientation du personnage (-1 : personnage à gauche)
	sf::Texture _texture;	//texture du personnage

	sf::Vector2f _tailleSprite;		//taille du personnage sous la forme d'un vector de float à 2 dimensions
	Scene _scene;					//la scene sur laquelle se passe le combat

	sf::RectangleShape _hurtbox;	//zone de prise de dégats
	sf::RectangleShape _hitbox;		//zone de mise de dégats

	float _posX;                    //Position X du perso
    float _posY;                    //Position Y du perso

	int _cptAvancer;				//compteur pour l'animation avancer
	int _cptReculer;				//compteur pour l'animation reculer
	int _cptStatic;					//compteur pour l'animation de repos
	int _cptAccroupi;				//compteur pour l'animation	accroupi

	int _cptSauter;					//compteur pour les animations de saut

	int _cptApparition;				//compteur pour l'animation de début de combat
	int _cptAction;					//compteur pour les animations de type attaques
	int _cptPrendCoup;
	int _cptGarde;					//compteur pour l'animation de garde debout

	int _tabSP[25][4];				//tableau pour stocker les coordonnées des sprites pour les animations spéciales (SP)
	int _indexTab;					//index permettant de remplir le tableau
	int _cptSP;						//compteur pour les effets sur les animations spéciales
	bool _SPChargee;				//indicateur pour ne génerer le _tabSP qu'un seule fois par attaque
public:
	Jotaro(){};		//constructeur vide
	void setTout(int,const Scene&);	//constructeur du champion

	void setSprite(int, int, int, int);		//permet de définir le sprite du personnage ainsi que de mettre à jour sa taille
	sf::Sprite getSprite() const;	//recupérer le sprite du personnage pour l'afficher

	void ajouterTexture(int,int,int,int);	//permet de remplir le tableau _tabSP
	void resetTexture();		//permet de reinitialiser le tableau pour le réutiliser sur les différents attaques spéciales

	sf::RectangleShape getHurtbox();	//permet de récupérer la zone de prise de dégats notamment pour pouvoir l'afficher
	sf::RectangleShape getHitbox();		//permet de récupérer la zone de mise de dégats notamment pour pouvoir l'afficher
	bool collisioncorps(sf::RectangleShape);	//permet de bloquer le fait que les deux personnages puis se croiser
	bool collisioncoup(sf::RectangleShape);		//permet de gérer la prise de coups

	void keepInWalls();		//permet de maintenir les personnages entre les limites de la carte
	int getOrientation() const;		//récupérer l'orientation du personnage

	void resetCptAccroupi();	//reinitialise le compteur pour l'animation accroupi
	void rotate(const sf::Sprite&);		//gère la rotation des personnages quand ils se dépassent
	bool prendCoup(sf::Clock&,bool&,sf::Sprite&);	//animation de prise de coup

	void statique(sf::Clock&,const sf::Sprite&);	//animation au repos
	void garde(sf::Clock&);			//animation de garde debout				--> gestion de la garde à faire
	bool finGarde(sf::Clock&);		//animation de fin de garde
	void avancer(sf::Clock&,const sf::Sprite&);		//animation de marche vers l'avant
	void reculer(sf::Clock&);		//animation de marche vers l'arrière

	bool sauter(sf::Clock&,sf::Clock&);		//animation de saut
	bool sauterAvant(sf::Clock&,const sf::Sprite&);		//animation de saut vers l'arrière
	bool sauterArriere(sf::Clock&);		//animation de saut vers l'arrière
	void accroupi(sf::Clock&,bool);		//animation accroupi
	bool seLever(sf::Clock& clockAnim);		//animation de fin d'accroupissement

	bool apparition(sf::Clock&,sf::Sprite&);	//animation de début de combat
	bool punch(sf::Clock&,sf::RectangleShape,bool&,Player&);				//animation de coup de poing
	bool punchSP(sf::Clock&,sf::Sprite&,sf::RectangleShape,bool&,Player&);	//animation de coup de poing spécial
	bool sautPunch(sf::Clock&,sf::RectangleShape,bool&,Player&);			//animation de coup de poing en saut
	bool kick(sf::Clock&,sf::RectangleShape,bool&,Player&);					//animation de coup de pied
	bool sautKick(sf::Clock&,sf::RectangleShape,bool&,Player&);				//animation de coup de pied en saut
	bool SP(sf::Clock&,sf::Sprite&,sf::RectangleShape,bool&,Player&);		//animation de coup spécial

};

#endif
