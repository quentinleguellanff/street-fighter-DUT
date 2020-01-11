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

	sf::Vector2f _tailleSprite;		//taille du personnage sous la forme d'un vector de float à 2 dimensions
	Scene _scene;					//la scene sur laquelle se passe le combat

	sf::RectangleShape _hurtbox;	//zone de prise de dégats
	sf::RectangleShape _hitbox;		//zone de mise de dégats
	sf::RectangleShape _gardebox;	//zone de parade

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
	int _cptSP;						//compteur pour les effets sur les animations spéciales
public:
	Personnage(){};		//constructeur vide
	~Personnage(){};
    void setTout(const Scene&);
	sf::Sprite getSprite();
	void setSprite(int, int, int, int);		//permet de définir le sprite du personnage ainsi que de mettre à jour sa taille
	sf::Sprite getIcone();

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

	virtual bool victoire(std::vector<sf::Clock>&,sf::Music&){return true;};
	virtual bool mort(std::vector<sf::Clock>& clockAnim){return true;};

	virtual bool prendCoup(std::vector<sf::Clock>&,int*,sf::Sprite&,int&){return true;};	//animation de prise de coup
	virtual bool parade(std::vector<sf::Clock>&,int*,sf::Sprite&){return true;};


	virtual void statique(std::vector<sf::Clock>&,Personnage&){};	//animation au repos
	virtual void garde(std::vector<sf::Clock>&){};			//animation de garde debout				--> gestion de la garde à faire
	virtual void avancer(std::vector<sf::Clock>&,Personnage&){};		//animation de marche vers l'avant
	virtual void reculer(std::vector<sf::Clock>&){};		//animation de marche vers l'arrière

	void collisionsaut(Personnage&,int&);
	virtual bool sauter(std::vector<sf::Clock>&,int&,Personnage&,int*,int&){return true;};		//animation de saut
	virtual bool sauterAvant(std::vector<sf::Clock>&,Personnage&){return true;};		//animation de saut vers l'arrière
	virtual bool sauterArriere(std::vector<sf::Clock>&,Personnage&){return true;};		//animation de saut vers l'arrière
	virtual void accroupi(std::vector<sf::Clock>&,bool){};		//animation accroupi
	virtual bool seLever(std::vector<sf::Clock>& clockAnim){return true;};		//animation de fin d'accroupissement

	virtual bool apparition(std::vector<sf::Clock>&,sf::Sprite&){return true;};	//animation de début de combat
	virtual bool punch(std::vector<sf::Clock>&,Personnage&,int*,int&){return true;};				//animation de coup de poing
	virtual bool punchSP(std::vector<sf::Clock>&,sf::Sprite&,Personnage&,int*,sf::Music&,int&){return true;};	//animation de coup de poing spécial
	virtual bool sautPunch(std::vector<sf::Clock>&,Personnage&,int*,int&){return true;};			//animation de coup de poing en saut
	virtual bool kick(std::vector<sf::Clock>&,Personnage&,int*,int&){return true;};					//animation de coup de pied
	virtual bool sautKick(std::vector<sf::Clock>&,Personnage&,int*,int&){return true;};				//animation de coup de pied en saut
	virtual bool kickSP(std::vector<sf::Clock>&,Personnage&,int*,int&){return true;};
	virtual bool SP(std::vector<sf::Clock>&,sf::Sprite&,Personnage&,int*,sf::Music&,int&){return true;};		//animation de coup spécial
};

class Jotaro : public Personnage
{
private:
	std::vector<std::vector<int> > _tabSP{};	//tableau pour stocker les coordonnées des sprites pour les animations spéciales (SP)
	bool _SPChargee;				//indicateur pour ne génerer le _tabSP qu'un seule fois par attaque

public:
    Jotaro(){};
	Jotaro(int);
    void setTout(const Scene& s);

	bool apparition(std::vector<sf::Clock>&,sf::Sprite&) override;
	void ajouterTexture(int,int,int,int);	//permet de remplir le tableau _tabSP
	void resetTexture();	//permet de reinitialiser le tableau pour le réutiliser sur les différents attaques spéciales

	bool victoire(std::vector<sf::Clock>&,sf::Music&) override;
	bool mort(std::vector<sf::Clock>& clockAnim) override;

	bool prendCoup(std::vector<sf::Clock>&,int*,sf::Sprite&,int&) override;
	bool parade(std::vector<sf::Clock>&,int*,sf::Sprite&) override;

	void statique(std::vector<sf::Clock>&,Personnage&) override;
	void garde(std::vector<sf::Clock>&) override;
	void avancer(std::vector<sf::Clock>&,Personnage&) override;
	void reculer(std::vector<sf::Clock>&) override;

	bool sauter(std::vector<sf::Clock>&,int&,Personnage&,int*,int&) override;
	bool sauterAvant(std::vector<sf::Clock>&,Personnage&) override;
	bool sauterArriere(std::vector<sf::Clock>&,Personnage&) override;
	void accroupi(std::vector<sf::Clock>&,bool) override;
	bool seLever(std::vector<sf::Clock>& clockAnim) override;


	bool punch(std::vector<sf::Clock>&,Personnage&,int*,int&) override;
	bool sautPunch(std::vector<sf::Clock>&,Personnage&,int*,int&) override;
	bool punchSP(std::vector<sf::Clock>&,sf::Sprite&,Personnage&,int*,sf::Music&,int&) override;

	bool kick(std::vector<sf::Clock>&,Personnage&,int*,int&) override;
	bool sautKick(std::vector<sf::Clock>&,Personnage&,int*,int&) override;
	bool kickSP(std::vector<sf::Clock>&,Personnage&,int*,int&) override;

	bool SP(std::vector<sf::Clock>&,sf::Sprite&,Personnage&,int*,sf::Music&,int&) override;
};

class Dhalsim : public Personnage
{
public:
	Dhalsim(){};
	Dhalsim(int);
	void setTout(const Scene&);

	bool apparition(std::vector<sf::Clock>&,sf::Sprite&) override;
	bool victoire(std::vector<sf::Clock>&,sf::Music&) override;
	bool mort(std::vector<sf::Clock>& clockAnim) override;

	bool prendCoup(std::vector<sf::Clock>&,int*,sf::Sprite&,int&) override;
	bool parade(std::vector<sf::Clock>&,int*,sf::Sprite&) override;

	void statique(std::vector<sf::Clock>&,Personnage&) override;
	void garde(std::vector<sf::Clock>&) override;
	void avancer(std::vector<sf::Clock>&,Personnage&) override;
	void reculer(std::vector<sf::Clock>&) override;

	bool sauter(std::vector<sf::Clock>&,int&,Personnage&,int*,int&) override;
	bool sauterAvant(std::vector<sf::Clock>&,Personnage&) override;
	bool sauterArriere(std::vector<sf::Clock>&,Personnage&) override;
	void accroupi(std::vector<sf::Clock>&,bool) override;


	bool punch(std::vector<sf::Clock>&,Personnage&,int*,int&) override;
	bool sautPunch(std::vector<sf::Clock>&,Personnage&,int*,int&) override;
	bool punchSP(std::vector<sf::Clock>&,sf::Sprite&,Personnage&,int*,sf::Music&,int&) override;

	bool kick(std::vector<sf::Clock>&,Personnage&,int*,int&) override;
	bool sautKick(std::vector<sf::Clock>&,Personnage&,int*,int&) override;
	bool kickSP(std::vector<sf::Clock>&,Personnage&,int*,int&) override;

	bool SP(std::vector<sf::Clock>&,sf::Sprite&,Personnage&,int*,sf::Music&,int&) override;
};

class Ryu : public Personnage
{
public:
	Ryu(){};
	Ryu(int);
	void setTout(const Scene&);

	bool apparition(std::vector<sf::Clock>&,sf::Sprite&) override;
	bool victoire(std::vector<sf::Clock>&,sf::Music&) override;
	bool mort(std::vector<sf::Clock>& clockAnim) override;

	bool prendCoup(std::vector<sf::Clock>&,int*,sf::Sprite&,int&) override;
	bool parade(std::vector<sf::Clock>&,int*,sf::Sprite&) override;

	void statique(std::vector<sf::Clock>&,Personnage&) override;
	void garde(std::vector<sf::Clock>&) override;
	void avancer(std::vector<sf::Clock>&,Personnage&) override;
	void reculer(std::vector<sf::Clock>&) override;

	bool sauter(std::vector<sf::Clock>&,int&,Personnage&,int*,int&) override;
	bool sauterAvant(std::vector<sf::Clock>&,Personnage&) override;
	bool sauterArriere(std::vector<sf::Clock>&,Personnage&) override;
	void accroupi(std::vector<sf::Clock>&,bool) override;

	bool punch(std::vector<sf::Clock>&,Personnage&,int*,int&) override;
	bool sautPunch(std::vector<sf::Clock>&,Personnage&,int*,int&) override;
	bool punchSP(std::vector<sf::Clock>&,sf::Sprite&,Personnage&,int*,sf::Music&,int&) override;

	bool kick(std::vector<sf::Clock>&,Personnage&,int*,int&) override;
	bool sautKick(std::vector<sf::Clock>&,Personnage&,int*,int&) override;
	bool kickSP(std::vector<sf::Clock>&,Personnage&,int*,int&) override;

	bool SP(std::vector<sf::Clock>&,sf::Sprite&,Personnage&,int*,sf::Music&,int&) override;
};

#endif
