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
	const int SCALE=3;
	int _orientation;
	sf::Texture _texture;

	sf::Vector2f _tailleSprite;
	Scene _scene;

	sf::RectangleShape _hurtbox;
	sf::RectangleShape _hitbox;

	float _posX;                   //Position X du perso
    float _posY;                   //Position Y du perso

	int _cptAvancer;
	int _cptReculer;
	int _cptStatic;
	int _cptAccroupi;

	int _cptSauter;

	int _cptApparition;
	int _cptAction;
	int _cptGarde;

	int _tabSP[25][4];
	int _indexTab;
	int _cptSP;
	bool _SPChargee;
public:
	Jotaro(){};
	Jotaro(int,const Scene&);
	void setSprite(int, int, int, int);
	void ajouterTexture(int,int,int,int);
	void resetTexture();

	sf::RectangleShape getHurtbox();
	sf::RectangleShape getHitbox();

	void keepInWalls();
	sf::Sprite getSprite() const;
	int getOrientation() const;
	
	void reset();
	void resetAccroupi();
	void rotate(const sf::Sprite&);
	bool prendCoup(sf::Clock&);

	void statique(sf::Clock&,const sf::Sprite&);
	void garde(sf::Clock&);
	bool finGarde(sf::Clock&);
	void avancer(sf::Clock&,const sf::Sprite&);
	void reculer(sf::Clock&);

	bool sauter(sf::Clock&,sf::Clock&);
	bool sauterAvant(sf::Clock&,const sf::Sprite&);
	bool sauterArriere(sf::Clock&);
	void accroupi(sf::Clock&,bool);
	bool seLever(sf::Clock& clockAnim);

	bool apparition(sf::Clock&,sf::Sprite&);
	bool punch(sf::Clock&);
	bool punchSP(sf::Clock&,sf::Sprite&);
	bool sautPunch(sf::Clock&){return true;};
	bool kick(sf::Clock&);
	bool sautKick(sf::Clock&);
	bool SP(sf::Clock&,sf::Sprite&);
	
};

#endif