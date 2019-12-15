#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "../IncludeManager.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>


class Personnage
{
protected:
	float SCALE;
	int _orientation;		//orientation du personnage (-1 : personnage à gauche)
	sf::Texture _texture;	//texture du personnage
	sf::Sprite _sprite;

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
	Personnage(){};		//constructeur vide

	//void operator=(Dhalsim);
	sf::Sprite getSprite();
	void setSprite(int, int, int, int);		//permet de définir le sprite du personnage ainsi que de mettre à jour sa taille

	sf::RectangleShape getHurtbox();	//permet de récupérer la zone de prise de dégats notamment pour pouvoir l'afficher
	sf::RectangleShape getHitbox();		//permet de récupérer la zone de mise de dégats notamment pour pouvoir l'afficher
	bool collisioncorps(sf::RectangleShape);	//permet de bloquer le fait que les deux personnages puis se croiser
	bool collisioncoup(sf::RectangleShape);		//permet de gérer la prise de coups

	void keepInWalls();		//permet de maintenir les personnages entre les limites de la carte
	int getOrientation() const;		//récupérer l'orientation du personnage

	virtual void ajouterTexture(int,int,int,int){};	//permet de remplir le tableau _tabSP
	virtual void resetTexture(){};		//permet de reinitialiser le tableau pour le réutiliser sur les différents attaques spéciales
	
	void resetCptAccroupi();	//reinitialise le compteur pour l'animation accroupi
	void rotate(Personnage&);		//gère la rotation des personnages quand ils se dépassent
	virtual bool prendCoup(sf::Clock&,bool&,sf::Sprite&){return true;};	//animation de prise de coup

	virtual void statique(sf::Clock&,Personnage&){};	//animation au repos
	virtual void garde(sf::Clock&){};			//animation de garde debout				--> gestion de la garde à faire
	virtual bool finGarde(sf::Clock&){return true;};		//animation de fin de garde
	virtual void avancer(sf::Clock&,Personnage&){};		//animation de marche vers l'avant
	virtual void reculer(sf::Clock&){};		//animation de marche vers l'arrière

	virtual bool sauter(sf::Clock&,sf::Clock&){return true;};		//animation de saut
	virtual bool sauterAvant(sf::Clock&,Personnage&){return true;};		//animation de saut vers l'arrière
	virtual bool sauterArriere(sf::Clock&){return true;};		//animation de saut vers l'arrière
	virtual void accroupi(sf::Clock&,bool){};		//animation accroupi
	virtual bool seLever(sf::Clock& clockAnim){return true;};		//animation de fin d'accroupissement

	virtual bool apparition(sf::Clock&,sf::Sprite&){return true;};	//animation de début de combat
	virtual bool punch(sf::Clock&,sf::RectangleShape,bool&,Player&){return true;};				//animation de coup de poing
	virtual bool punchSP(sf::Clock&,sf::Sprite&,sf::RectangleShape,bool&,Player&){return true;};	//animation de coup de poing spécial
	virtual bool sautPunch(sf::Clock&,sf::RectangleShape,bool&,Player&){return true;};			//animation de coup de poing en saut
	virtual bool kick(sf::Clock&,sf::RectangleShape,bool&,Player&){return true;};					//animation de coup de pied
	virtual bool sautKick(sf::Clock&,sf::RectangleShape,bool&,Player&){return true;};				//animation de coup de pied en saut
	virtual bool SP(sf::Clock&,sf::Sprite&,sf::RectangleShape,bool&,Player&,sf::Music&){return true;};		//animation de coup spécial
};

class Jotaro : public Personnage
{
private:

	
public:
	Jotaro(){};		//constructeur vide
	Jotaro(int,const Scene&);	//constructeur du champion

	void ajouterTexture(int,int,int,int) override;	//permet de remplir le tableau _tabSP
	void resetTexture() override;		//permet de reinitialiser le tableau pour le réutiliser sur les différents attaques spéciales

	bool prendCoup(sf::Clock&,bool&,sf::Sprite&) override;	//animation de prise de coup

	void statique(sf::Clock&,Personnage&) override;	//animation au repos
	void garde(sf::Clock&) override;			//animation de garde debout				--> gestion de la garde à faire
	bool finGarde(sf::Clock&) override;		//animation de fin de garde
	void avancer(sf::Clock&,Personnage&) override;		//animation de marche vers l'avant
	void reculer(sf::Clock&) override;		//animation de marche vers l'arrière

	bool sauter(sf::Clock&,sf::Clock&) override;		//animation de saut
	bool sauterAvant(sf::Clock&,Personnage&) override;		//animation de saut vers l'arrière
	bool sauterArriere(sf::Clock&) override;		//animation de saut vers l'arrière
	void accroupi(sf::Clock&,bool) override;		//animation accroupi
	bool seLever(sf::Clock& clockAnim) override;		//animation de fin d'accroupissement

	bool apparition(sf::Clock&,sf::Sprite&) override;	//animation de début de combat
	bool punch(sf::Clock&,sf::RectangleShape,bool&,Player&) override;				//animation de coup de poing
	bool punchSP(sf::Clock&,sf::Sprite&,sf::RectangleShape,bool&,Player&) override;	//animation de coup de poing spécial
	bool sautPunch(sf::Clock&,sf::RectangleShape,bool&,Player&) override;			//animation de coup de poing en saut
	bool kick(sf::Clock&,sf::RectangleShape,bool&,Player&) override;					//animation de coup de pied
	bool sautKick(sf::Clock&,sf::RectangleShape,bool&,Player&) override;				//animation de coup de pied en saut
	bool SP(sf::Clock&,sf::Sprite&,sf::RectangleShape,bool&,Player&,sf::Music&) override;		//animation de coup spécial
};

class Dhalsim : public Personnage
{
public:
	Dhalsim(){};	//constructeur vide
	Dhalsim(int,const Scene&);		//constructeur du champion
	
	bool prendCoup(sf::Clock&,bool&,sf::Sprite&) override;	//animation de prise de coup

	void statique(sf::Clock&,Personnage&) override;	//animation au repos
	void garde(sf::Clock&) override;			//animation de garde debout				--> gestion de la garde à faire
	bool finGarde(sf::Clock&) override;		//animation de fin de garde
	void avancer(sf::Clock&,Personnage&) override;		//animation de marche vers l'avant
	void reculer(sf::Clock&) override;		//animation de marche vers l'arrière

	bool sauter(sf::Clock&,sf::Clock&) override;		//animation de saut
	bool sauterAvant(sf::Clock&,Personnage&) override;		//animation de saut vers l'arrière
	bool sauterArriere(sf::Clock&) override;		//animation de saut vers l'arrière
	void accroupi(sf::Clock&,bool) override;		//animation accroupi

	bool apparition(sf::Clock&,sf::Sprite&) override;	//animation de début de combat
	bool punch(sf::Clock&,sf::RectangleShape,bool&,Player&) override;				//animation de coup de poing
	bool sautPunch(sf::Clock&,sf::RectangleShape,bool&,Player&) override;			//animation de coup de poing en saut
	bool kick(sf::Clock&,sf::RectangleShape,bool&,Player&) override;					//animation de coup de pied
	bool sautKick(sf::Clock&,sf::RectangleShape,bool&,Player&) override;				//animation de coup de pied en saut
	bool SP(sf::Clock&,sf::Sprite&,sf::RectangleShape,bool&,Player&,sf::Music&) override;		//animation de coup spécial
};

class Ryu : public Personnage
{
public:
	Ryu(){};	//constructeur vide
	Ryu(int,const Scene&);		//constructeur du champion
	
	bool prendCoup(sf::Clock&,bool&,sf::Sprite&) override;	//animation de prise de coup

	void statique(sf::Clock&,Personnage&) override;	//animation au repos
	void garde(sf::Clock&) override;			//animation de garde debout				--> gestion de la garde à faire
	bool finGarde(sf::Clock&) override;		//animation de fin de garde
	void avancer(sf::Clock&,Personnage&) override;		//animation de marche vers l'avant
	void reculer(sf::Clock&) override;		//animation de marche vers l'arrière

	bool sauter(sf::Clock&,sf::Clock&) override;		//animation de saut
	bool sauterAvant(sf::Clock&,Personnage&) override;		//animation de saut vers l'arrière
	bool sauterArriere(sf::Clock&) override;		//animation de saut vers l'arrière
	void accroupi(sf::Clock&,bool) override;		//animation accroupi

	bool apparition(sf::Clock&,sf::Sprite&) override;	//animation de début de combat
	bool punch(sf::Clock&,sf::RectangleShape,bool&,Player&) override;				//animation de coup de poing
	bool sautPunch(sf::Clock&,sf::RectangleShape,bool&,Player&) override;			//animation de coup de poing en saut
	bool kick(sf::Clock&,sf::RectangleShape,bool&,Player&) override;					//animation de coup de pied
	bool sautKick(sf::Clock&,sf::RectangleShape,bool&,Player&) override;				//animation de coup de pied en saut
	bool SP(sf::Clock&,sf::Sprite&,sf::RectangleShape,bool&,Player&,sf::Music&) override;		//animation de coup spécial
};

#endif