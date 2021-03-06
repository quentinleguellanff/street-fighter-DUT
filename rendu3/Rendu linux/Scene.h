/**
 * \file Scene.h
 * \brief Classe Scene
 * \author Team La Bagarre
 *
 * Classe permettant de gérer la scène de combat
 */

#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Scene
{
private:
	/**
    * \attribute sf::Texture _textureScene
    * \brief Texture de la scène
	*
    */
	sf::Texture _textureScene;

	/**
    * \attribute sf::Sprite _spriteScene
    * \brief Sprite de la scène
	*
    */
	sf::Sprite _spriteScene;

	/**
    * \attribute sf::Vector2u _tailleWindow
    * \brief Taille de la fenêtre
	*
    */
	sf::Vector2u _tailleWindow;

	/**
    * \attribute sf::RectangleShape _solScene
    * \brief Rectangle de délimitation du sol
	*
    */
	sf::RectangleShape _solScene;

	/**
    * \attribute sf::RectangleShape _wallLeft
    * \brief Rectangle de délimitation du mur gauche
	*
    */
	sf::RectangleShape _wallLeft;

	/**
    * \attribute sf::RectangleShape _wallRight
    * \brief Rectangle de délimitation du mur droit
	*
    */
	sf::RectangleShape _wallRight;

	/**
    * \attribute int _hauteurSol
    * \brief Hauteur du sol
	*
    */
	int _hauteurSol;

	/**
    * \attribute int _limiteSol
    * \brief Limite du sol
	*
    */
	int _limiteSol;

	/**
    * \attribute int _largeurWindow
    * \brief Largeur de la fenêtre
	*
    */
	int _largeurWindow;

public:
   /**
    * \fn Scene(){}
    * \brief Constructeur de scene
	*
    */
	Scene(){};

	/**
    * \fn Scene(){}
    * \brief Constructeur de scene
	*
    */
	Scene(sf::RenderWindow&);

	/**
    * \fn void chargementXenoverse(sf::Music&)
    * \brief Chargement de scène
	*
	* Chargement de la scène Xenoverse
    */
	void chargementXenoverse(sf::Music&);

	/**
    * \fn void chargementFutur(sf::Music&)
    * \brief Chargement de scène
	*
	* Chargement de la scène Futur
    */
	void chargementFutur(sf::Music&);
	/**
    * \fn void chargementToit(sf::Music&)
    * \brief Chargement de scène
	*
	* Chargement de la scène Toit
    */
	void chargementToit(sf::Music&);

	/**
    * \fn void chargementSkulls(sf::Music&)
    * \brief Chargement de scène
	*
	* Chargement de la scène Skulls
    */
	void chargementSkulls(sf::Music&);

	/**
    * \fn void chargementSanFran(sf::Music&)
    * \brief Chargement de scène
	*
	* Chargement de la scène SanFran
    */
	void chargementSanFran(sf::RenderWindow&,sf::Music&);

	/**
    * \fn chargementAvion(sf::Music&)
    * \brief Chargement de scène
	*
	* Chargement de la scène SanFran
    */
	void chargementAvion(sf::Music&);

	/**
    * \fn sf::Sprite getSprite() const
    * \brief Retourne la scène
	*
    */
	sf::Sprite getSprite() const;

	/**
    * \fn int getBottom() const
    * \brief Obtenir la limite de la scène
	*
    */
	int getBottom() const;

	/**
    * \fn int getLeftLimit() const
    * \brief Obtenir la limite gauche de la scène
	*
    */
	int getLeftLimit() const;

	/**
    * \fn int getRightLimit() const
    * \brief  Obtenir la limite droite de la scène
	*
    */
	int getRightLimit() const;

	/**
    * \fn sf::RectangleShape getSol() const
    * \brief Obtenir le rectangle de délimitation du sol
	*
    */
	sf::RectangleShape getSol() const;
};

#endif
