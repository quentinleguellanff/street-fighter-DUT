#include "IncludeManager.h"

using namespace std;

Scene::Scene(sf::RenderWindow& w)
{
    _tailleWindow=w.getSize();
}

void Scene::chargementXenoverse(sf::Music& sonScene)
{
<<<<<<< HEAD
    if(!_textureScene.loadFromFile("background/ring_xenoverse_V2.jpg"))
    {
        cout<<"Erreur chargement de Scene"<<endl;
    }
    else
    {
        _textureScene.setSmooth(true);
        _spriteScene.setTexture(_textureScene);
        _spriteScene.setScale(_tailleWindow.x/1920.f,_tailleWindow.y/1080.f);
    }

    _hauteurSol=75.f;
    _limiteSol=_tailleWindow.y-_hauteurSol;
    _largeurWindow=_tailleWindow.x;

    _solScene.setSize(sf::Vector2f(1920.f, _hauteurSol));
    _solScene.setPosition(0.f, _limiteSol);
    _solScene.setFillColor(sf::Color(250,250,250,0));
    _solScene.setOutlineThickness(2.f);
    _solScene.setOutlineColor(sf::Color(250, 130, 1));

    _wallLeft.setSize(sf::Vector2f(5.f, _tailleWindow.y));
    _wallLeft.setPosition(0.f, 0.f);
    _wallLeft.setFillColor(sf::Color(50,250,60,1));

    _wallRight.setSize(sf::Vector2f(5.f, _tailleWindow.y));
    _wallRight.setPosition(_tailleWindow.x-5, 0.f);
    _wallRight.setFillColor(sf::Color(50,250,60,1));

    if (!sonScene.openFromFile("musique/World_tournament_arena_stage.ogg"))
    {
        std::cout<<"erreur musique";
=======
	if(!_textureScene.loadFromFile("background/ring_xenoverse_V2.jpg")){cout<<"Erreur chargement de Scene"<<endl;}
	else{
		_textureScene.setSmooth(true);
		_spriteScene.setTexture(_textureScene);
		_spriteScene.setScale(_tailleWindow.x/1920.f,_tailleWindow.y/1080.f);
	}

	_hauteurSol=75.f*(_tailleWindow.y/1920);
	_limiteSol=_tailleWindow.y-_hauteurSol;
	_largeurWindow=_tailleWindow.x;

	_solScene.setSize(sf::Vector2f(1920.f, _hauteurSol));
	_solScene.setPosition(0.f, _limiteSol);
	_solScene.setFillColor(sf::Color(250,250,250,0));
	_solScene.setOutlineThickness(2.f);
	_solScene.setOutlineColor(sf::Color(250, 130, 1));

	_wallLeft.setSize(sf::Vector2f(5.f, _tailleWindow.y));
	_wallLeft.setPosition(0.f, 0.f);
	_wallLeft.setFillColor(sf::Color(50,250,60,1));

	_wallRight.setSize(sf::Vector2f(5.f, _tailleWindow.y));
	_wallRight.setPosition(_tailleWindow.x-5, 0.f);
	_wallRight.setFillColor(sf::Color(50,250,60,1));

	if (!sonScene.openFromFile("musique/World_tournament_arena_stage.ogg")){
            std::cout<<"erreur musique";
>>>>>>> 92cebf194d27f339310248da35774fd6246e6ba6
    }
    sonScene.play();
    sonScene.setVolume(40.f) ;
    sonScene.setLoop(true);
}

void Scene::chargementFutur(sf::Music& sonScene)
{
    if(!_textureScene.loadFromFile("background/futur.jpg"))
    {
        cout<<"Erreur chargement de Scene"<<endl;
    }
    else
    {
        _textureScene.setSmooth(true);
        _spriteScene.setTexture(_textureScene);
        _spriteScene.setScale(_tailleWindow.x/1920.f,_tailleWindow.y/1080.f);
    }

<<<<<<< HEAD
    _hauteurSol=75.f;
    _limiteSol=_tailleWindow.y-_hauteurSol;
    _largeurWindow=_tailleWindow.x;
=======
	double temp=_tailleWindow.x;

	_hauteurSol=75.f*(temp/1920);
	_limiteSol=_tailleWindow.y-_hauteurSol;
	_largeurWindow=_tailleWindow.x;
>>>>>>> 92cebf194d27f339310248da35774fd6246e6ba6

    _solScene.setSize(sf::Vector2f(1920.f, _hauteurSol));
    _solScene.setPosition(0.f, _limiteSol);
    _solScene.setFillColor(sf::Color(250,250,250,0));
    _solScene.setOutlineThickness(2.f);
    _solScene.setOutlineColor(sf::Color(250, 130, 1));

    _wallLeft.setSize(sf::Vector2f(5.f, _tailleWindow.y));
    _wallLeft.setPosition(0.f, 0.f);
    _wallLeft.setFillColor(sf::Color(50,250,60,1));

    _wallRight.setSize(sf::Vector2f(5.f, _tailleWindow.y));
    _wallRight.setPosition(_tailleWindow.x-5, 0.f);
    _wallRight.setFillColor(sf::Color(50,250,60,1));

    if (!sonScene.openFromFile("musique/theme_future.ogg"))
    {
        std::cout<<"erreur musique";
    }
    sonScene.play();
    sonScene.setVolume(40.f) ;
    sonScene.setLoop(true);
}
void Scene::chargementToit(sf::Music& sonScene)
{
    if(!_textureScene.loadFromFile("background/toit.png"))
    {
        cout<<"Erreur chargement de Scene"<<endl;
    }
    else
    {
        _textureScene.setSmooth(true);
        _spriteScene.setTexture(_textureScene);
        _spriteScene.setScale(_tailleWindow.x/1920.f,_tailleWindow.y/1080.f);
<<<<<<< HEAD
    }
    _hauteurSol=200.f;
    _limiteSol=_tailleWindow.y-_hauteurSol;
    _largeurWindow=_tailleWindow.x;

    _solScene.setSize(sf::Vector2f(1920.f, _hauteurSol));
    _solScene.setPosition(0.f, _limiteSol);
    _solScene.setFillColor(sf::Color(250,250,250,0));
    _solScene.setOutlineThickness(2.f);
    _solScene.setOutlineColor(sf::Color(250, 130, 1));

    _wallLeft.setSize(sf::Vector2f(5.f, _tailleWindow.y));
    _wallLeft.setPosition(0.f, 0.f);
    _wallLeft.setFillColor(sf::Color(50,250,60,1));

    _wallRight.setSize(sf::Vector2f(5.f, _tailleWindow.y));
    _wallRight.setPosition(_tailleWindow.x-5, 0.f);
    _wallRight.setFillColor(sf::Color(50,250,60,1));

    if (!sonScene.openFromFile("musique/theme_japon.ogg"))
    {
        std::cout<<"erreur musique";
=======
	}

	double temp=_tailleWindow.x;

	_hauteurSol=200.f*(temp/1920);
	_limiteSol=_tailleWindow.y-_hauteurSol;
	_largeurWindow=_tailleWindow.x;

	_solScene.setSize(sf::Vector2f(1920.f, _hauteurSol));
	_solScene.setPosition(0.f, _limiteSol);
	_solScene.setFillColor(sf::Color(250,250,250,0));
	_solScene.setOutlineThickness(2.f);
	_solScene.setOutlineColor(sf::Color(250, 130, 1));

	_wallLeft.setSize(sf::Vector2f(5.f, _tailleWindow.y));
	_wallLeft.setPosition(0.f, 0.f);
	_wallLeft.setFillColor(sf::Color(50,250,60,1));

	_wallRight.setSize(sf::Vector2f(5.f, _tailleWindow.y));
	_wallRight.setPosition(_tailleWindow.x-5, 0.f);
	_wallRight.setFillColor(sf::Color(50,250,60,1));

	if (!sonScene.openFromFile("musique/theme_japon.ogg")){
            std::cout<<"erreur musique";
>>>>>>> 92cebf194d27f339310248da35774fd6246e6ba6
    }
    sonScene.play();
    sonScene.setVolume(40.f) ;
    sonScene.setLoop(true);
}
void Scene::chargementSanFran(sf::RenderWindow& window,sf::Music& sonScene)
{
    if(!_textureScene.loadFromFile("background/SanFran.png"))
    {
        cout<<"Erreur chargement de Scene"<<endl;
    }
    else
    {
        _textureScene.setSmooth(true);
        _spriteScene.setTexture(_textureScene);
        _spriteScene.setScale(_tailleWindow.x/1920.f,_tailleWindow.y/1080.f);
    }

<<<<<<< HEAD
    _hauteurSol=70.f;
    _limiteSol=_tailleWindow.y-_hauteurSol;
    _largeurWindow=_tailleWindow.x;
=======
	double temp=_tailleWindow.x;

	_hauteurSol=70.f*(temp/1920);
	_limiteSol=_tailleWindow.y-_hauteurSol;
	_largeurWindow=_tailleWindow.x;
>>>>>>> 92cebf194d27f339310248da35774fd6246e6ba6

    _solScene.setSize(sf::Vector2f(1920.f, _hauteurSol));
    _solScene.setPosition(0.f, _limiteSol);
    _solScene.setFillColor(sf::Color(250,250,250,0));
    _solScene.setOutlineThickness(2.f);
    _solScene.setOutlineColor(sf::Color(250, 130, 1));

    _wallLeft.setSize(sf::Vector2f(5.f, _tailleWindow.y));
    _wallLeft.setPosition(0.f, 0.f);
    _wallLeft.setFillColor(sf::Color(50,250,60,1));

    _wallRight.setSize(sf::Vector2f(5.f, _tailleWindow.y));
    _wallRight.setPosition(_tailleWindow.x-5, 0.f);
    _wallRight.setFillColor(sf::Color(50,250,60,1));

    if (!sonScene.openFromFile("musique/theme_brazil.ogg"))
    {
        std::cout<<"erreur musique";
    }
    sonScene.play();
    sonScene.setVolume(40.f) ;
    sonScene.setLoop(true);
}
void Scene::chargementSkulls(sf::Music& sonScene)
{
    if(!_textureScene.loadFromFile("background/skulls.jpg"))
    {
        cout<<"Erreur chargement de Scene"<<endl;
    }
    else
    {
        _textureScene.setSmooth(true);
        _spriteScene.setTexture(_textureScene);
        _spriteScene.setScale(_tailleWindow.x/1920.f,_tailleWindow.y/1080.f);
<<<<<<< HEAD
    }
    _hauteurSol=75.f;
    _limiteSol=_tailleWindow.y-_hauteurSol;
    _largeurWindow=_tailleWindow.x;

    _solScene.setSize(sf::Vector2f(1920.f, _hauteurSol));
    _solScene.setPosition(0.f, _limiteSol);
    _solScene.setFillColor(sf::Color(250,250,250,0));
    _solScene.setOutlineThickness(2.f);
    _solScene.setOutlineColor(sf::Color(250, 130, 1));

    _wallLeft.setSize(sf::Vector2f(5.f, _tailleWindow.y));
    _wallLeft.setPosition(0.f, 0.f);
    _wallLeft.setFillColor(sf::Color(50,250,60,1));

    _wallRight.setSize(sf::Vector2f(5.f, _tailleWindow.y));
    _wallRight.setPosition(_tailleWindow.x-5, 0.f);
    _wallRight.setFillColor(sf::Color(50,250,60,1));

    if (!sonScene.openFromFile("musique/theme_skulls.ogg"))
    {
        std::cout<<"erreur musique";
=======
	}

	double temp=_tailleWindow.x;

	_hauteurSol=75.f*(temp/1920);
	_limiteSol=_tailleWindow.y-_hauteurSol;
	_largeurWindow=_tailleWindow.x;

	_solScene.setSize(sf::Vector2f(1920.f, _hauteurSol));
	_solScene.setPosition(0.f, _limiteSol);
	_solScene.setFillColor(sf::Color(250,250,250,0));
	_solScene.setOutlineThickness(2.f);
	_solScene.setOutlineColor(sf::Color(250, 130, 1));

	_wallLeft.setSize(sf::Vector2f(5.f, _tailleWindow.y));
	_wallLeft.setPosition(0.f, 0.f);
	_wallLeft.setFillColor(sf::Color(50,250,60,1));

	_wallRight.setSize(sf::Vector2f(5.f, _tailleWindow.y));
	_wallRight.setPosition(_tailleWindow.x-5, 0.f);
	_wallRight.setFillColor(sf::Color(50,250,60,1));

	if (!sonScene.openFromFile("musique/theme_skulls.ogg")){
            std::cout<<"erreur musique";
>>>>>>> 92cebf194d27f339310248da35774fd6246e6ba6
    }
    sonScene.play();
    sonScene.setVolume(40.f) ;
    sonScene.setLoop(true);
}

void Scene::chargementAvion(sf::Music& sonScene)
{
    if(!_textureScene.loadFromFile("background/avion.png"))
    {
        cout<<"Erreur chargement de Scene"<<endl;
    }
    else
    {
        _textureScene.setSmooth(true);
        _spriteScene.setTexture(_textureScene);
        _spriteScene.setScale(_tailleWindow.x/1920.f,_tailleWindow.y/1080.f);
<<<<<<< HEAD
    }
    _hauteurSol=50.f;
    _limiteSol=_tailleWindow.y-_hauteurSol;
    _largeurWindow=_tailleWindow.x;

    _solScene.setSize(sf::Vector2f(1920.f, _hauteurSol));
    _solScene.setPosition(0.f, _limiteSol);
    _solScene.setFillColor(sf::Color(250,250,250,0));
    _solScene.setOutlineThickness(2.f);
    _solScene.setOutlineColor(sf::Color(250, 130, 1));

    _wallLeft.setSize(sf::Vector2f(5.f, _tailleWindow.y));
    _wallLeft.setPosition(0.f, 0.f);
    _wallLeft.setFillColor(sf::Color(50,250,60,1));

    _wallRight.setSize(sf::Vector2f(5.f, _tailleWindow.y));
    _wallRight.setPosition(_tailleWindow.x-5, 0.f);
    _wallRight.setFillColor(sf::Color(50,250,60,1));

    if (!sonScene.openFromFile("musique/theme_skulls.ogg"))
    {
        std::cout<<"erreur musique";
=======
	}

	double temp=_tailleWindow.x;
	
	_hauteurSol=50.f*(temp/1920);
	_limiteSol=_tailleWindow.y-_hauteurSol;
	_largeurWindow=_tailleWindow.x;

	_solScene.setSize(sf::Vector2f(1920.f, _hauteurSol));
	_solScene.setPosition(0.f, _limiteSol);
	_solScene.setFillColor(sf::Color(250,250,250,0));
	_solScene.setOutlineThickness(2.f);
	_solScene.setOutlineColor(sf::Color(250, 130, 1));

	_wallLeft.setSize(sf::Vector2f(5.f, _tailleWindow.y));
	_wallLeft.setPosition(0.f, 0.f);
	_wallLeft.setFillColor(sf::Color(50,250,60,1));

	_wallRight.setSize(sf::Vector2f(5.f, _tailleWindow.y));
	_wallRight.setPosition(_tailleWindow.x-5, 0.f);
	_wallRight.setFillColor(sf::Color(50,250,60,1));

	if (!sonScene.openFromFile("musique/theme_skulls.ogg")){
            std::cout<<"erreur musique";
>>>>>>> 92cebf194d27f339310248da35774fd6246e6ba6
    }
    sonScene.play();
    sonScene.setVolume(40.f) ;
    sonScene.setLoop(true);
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

sf::RectangleShape Scene::getSol() const
{
    return _solScene;
}
