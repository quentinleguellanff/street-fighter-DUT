#include "Scene.h"

using namespace std;

Scene::Scene(sf::RenderWindow& w,int n)
{
	_tailleWindow=w.getSize();
	switch (n) // Début de Gestionnaire de map
	{
		case 1:
			chargementXenoverse();
	}
}

void Scene::chargementXenoverse()
{
	if(!_textureScene.loadFromFile("background/ring_xenoverse_V2.jpg")){cout<<"Erreur chargement de Scene"<<endl;}
	else{
		_textureScene.setSmooth(true);
		_spriteScene.setTexture(_textureScene);
	}
	_hauteurSol=75.f;
	_limiteSol=_tailleWindow.y-_hauteurSol;
	_largeurWindow=_tailleWindow.x;

	_solScene.setSize(sf::Vector2f(1920.f, _hauteurSol));
	_solScene.setPosition(0.f, _limiteSol);
	_solScene.setFillColor(sf::Color(250,250,250,0));
	//_solScene.setOutlineThickness(2.f);
	//_solScene.setOutlineColor(sf::Color(250, 130, 1));

	_wallLeft.setSize(sf::Vector2f(5.f, _tailleWindow.y));
	_wallLeft.setPosition(0.f, 0.f);
	_wallLeft.setFillColor(sf::Color(50,250,60,1));
	
	_wallRight.setSize(sf::Vector2f(5.f, _tailleWindow.y));
	_wallRight.setPosition(_tailleWindow.x-5, 0.f);
	_wallRight.setFillColor(sf::Color(50,250,60,1));
}

sf::Sprite Scene::getSprite() const
{
	return _spriteScene;
}


int Scene::getBottom() const
{
	return _limiteSol;
}

int Scene::getLeftLimit() const
{
	return _wallLeft.getSize().x;
}

int Scene::getRightLimit() const
{
	return _largeurWindow-_wallRight.getSize().x;
}