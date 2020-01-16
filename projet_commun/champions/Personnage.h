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
	float SCALE;
	int _orientation;		//orientation du personnage (-1 : personnage à gauche)
	sf::Texture _texture;	//texture du personnage
	sf::Sprite _sprite;
	sf::Sprite _icone;

	sf::Clock _clockEffet;
	sf::Clock _clockAnim;
	sf::Clock _clockMove;

	sf::Vector2f _tailleSprite;		//taille du personnage sous la forme d'un vector de float à 2 dimensions
	Scene _scene;					//la scene sur laquelle se passe le combat

	sf::RectangleShape _hurtbox;	//zone de prise de dégats
	sf::RectangleShape _hitbox;		//zone de mise de dégats
	sf::RectangleShape _gardebox;	//zone de parade

	float _posX;                    //Position X du perso
    float _posY;                    //Position Y du perso

    float _vsaut;

	int _cptAvancer;				//compteur pour l'animation avancer
	int _cptReculer;				//compteur pour l'animation reculer
	int _cptStatic;					//compteur pour l'animation de repos
	int _cptAccroupi;				//compteur pour l'animation	accroupi

	int _cptSauter;					//compteur pour les animations de saut

	int _cptApparition;				//compteur pour l'animation de début de combat
	int _cptAction;					//compteur pour les animations de type attaques
	int _cptPrendCoup;
	int _cptGarde;					//compteur pour l'animation de garde debout
	int _cptSP;						//compteur pour les effets sur les animations spéciales

	bool _hitSpark;
	bool _peutHitSpark;

	sf::Music _effetSonore;

	bool _effetEnCours;
	int _cptAnimEffet;
	sf::Texture _textureEffet;
	sf::Sprite _spriteHitSpark;

public:
	Personnage();		//constructeur vide
	~Personnage(){};
    void setScene(const Scene&);
	sf::Sprite getSprite();
	void setSprite(int, int, int, int);		//permet de définir le sprite du personnage ainsi que de mettre à jour sa taille
	sf::Sprite getIcone();

	bool getPeutHitspark();

    bool getHitspark();

    void setHitspark(bool val);

    void setPeuthitspark(bool val);

	sf::RectangleShape getHurtbox();	//permet de récupérer la zone de prise de dégats
	sf::RectangleShape getHitbox();		//permet de récupérer la zone de mise de dégats
	void resetHitbox();
	sf::RectangleShape getGardebox();	//permet de récupérer la zone de parade

	void collision(Personnage&, int&);	//permet de bloquer le fait que les deux personnages puis se croiser
	bool collisioncoup(Personnage&);		//permet de gérer la prise de coups

	void keepInWalls();		//permet de maintenir les personnages entre les limites de la carte
	int getOrientation() const;		//récupérer l'orientation du personnage
	void setPosX(int);
	int getPosX();
	void setPosY(int);
	int getPosY();

	void resetCptAccroupi();	//reinitialise le compteur pour l'animation accroupi
	void rotate(Personnage&);		//gère la rotation des personnages quand ils se dépassent
	bool auSol();

	void affichageEffet(sf::RenderWindow& window);

	virtual bool victoire(){return true;};
	virtual bool mort(){return true;};

	virtual bool prendCoup(int*,sf::Sprite&,int&){return true;};	//animation de prise de coup
	virtual bool parade(int*,sf::Sprite&){return true;};


	virtual void statique(Personnage&){};	//animation au repos
	virtual void garde(){};			//animation de garde debout				--> gestion de la garde à faire
	virtual void avancer(Personnage&){};		//animation de marche vers l'avant
	virtual void reculer(){};		//animation de marche vers l'arrière

	void collisionsaut(Personnage&,int&);
	virtual bool sauter(int&,Personnage&,int*,int&){return true;};		//animation de saut
	virtual bool sauterAvant(Personnage&){return true;};		//animation de saut vers l'arrière
	virtual bool sauterArriere(Personnage&){return true;};		//animation de saut vers l'arrière
	virtual void accroupi(bool){};		//animation accroupi

	virtual bool apparition(sf::Sprite&){return true;};	//animation de début de combat
	virtual bool punch(Personnage&,int*,int&){return true;};				//animation de coup de poing
	virtual bool punchSP(sf::Sprite&,Personnage&,int*,int&){return true;};	//animation de coup de poing spécial
	virtual bool sautPunch(Personnage&,int*,int&){return true;};			//animation de coup de poing en saut
	virtual bool kick(Personnage&,int*,int&){return true;};					//animation de coup de pied
	virtual bool sautKick(Personnage&,int*,int&){return true;};				//animation de coup de pied en saut
	virtual bool kickSP(Personnage&,int*,int&){return true;};
	virtual bool SP(sf::Sprite&,Personnage&,int*,int&){return true;};		//animation de coup spécial
};

class Dhalsim : public Personnage
{
public:
	Dhalsim(){};
	Dhalsim(int,Scene&);

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
	Ryu(){};
	Ryu(int,Scene&);

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
	Greg(){};
	Greg(int,Scene&);

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
