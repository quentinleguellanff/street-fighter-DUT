#include "Combat.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"
#include "joueur.h"

Combat::Combat(Joueur& joueur1, Joueur& joueur2,sf::RectangleShape& sol)
{
    _joueur1 = joueur1;
    _joueur2 = joueur2;
    _sol = sol;
    if(!_TextureBackground.loadFromFile("sprite/background1.jpg")){
        cout << "erreur de chargement de texture de la scene" << endl;
    }

    if (!_Texturehitspark.loadFromFile("sprite/hitspark_SF3.png"))//load de la texture du personnage
    {
        cout << "erreur de chargement de texture des effets visuels" << endl;
    }
    _spriteBackground.setTexture(_TextureBackground);
    _spriteBackground.setScale(0.75,0.83);
     _spritehitspark.setTexture(_Texturehitspark);
     _spritehitspark.setTextureRect(sf::IntRect(0,22,103,96));
     _spritehitspark.setScale(-1,1);
     _spritehitspark.setScale(0.7,0.7);
     _spritehitspark.setOrigin(_spritehitspark.getGlobalBounds().width,_spritehitspark.getPosition().y);
     hitspark = false;
     _cptanim = 0;
}

Combat::~Combat()
{
    //dtor
}

bool Combat::partie(sf::RenderWindow& window,bool& toucheJ1, bool& toucheJ2){

            window.clear();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                _joueur1.antiSpam(event);
                _joueur2.antiSpam(event);
            }
            window.draw(_spriteBackground);

            _joueur1.recupCommande();
            _joueur2.recupCommande();

            _joueur1.saut(window,_joueur2.getHurtbox(),_joueur2.getEtat());
            _joueur2.saut(window,_joueur1.getHurtbox(),_joueur1.getEtat());

            _joueur1.statique(window,_joueur2.getHurtbox());
            _joueur2.statique(window,_joueur1.getHurtbox());

            _joueur1.avancedroite(window,_joueur2.getHurtbox());
            _joueur2.avancedroite(window,_joueur1.getHurtbox());

            _joueur1.avancegauche(window,_joueur2.getHurtbox());
            _joueur2.avancegauche(window,_joueur1.getHurtbox());

            _joueur1.prendCoup(toucheJ1,window);
            _joueur2.prendCoup(toucheJ2,window);

            _joueur1.coupDePoing(_joueur2.getHurtbox(),toucheJ2,window);
            _joueur2.coupDePoing(_joueur1.getHurtbox(),toucheJ1,window);

            //window.draw(_joueur2.getHitbox());
            //window.draw(_sol);
            window.draw(_joueur1.getBarreVie());
            window.draw(_joueur2.getBarreVie());
            //window.draw(_joueur1.getHurtbox());
            //window.draw(_joueur2.getHurtbox());
            if(toucheJ1){
                hitspark = true;
            }
            if(hitspark){
                hitspark = hitGraphique(window);
                cout << "ok" << endl;
            }
            else if(toucheJ2){
                window.draw(_joueur1.getHitbox());
            }
            window.display();
            return true;
}

bool Combat::hitGraphique(sf::RenderWindow& window){
    _spritehitspark.setPosition(_joueur2.getHitbox().getPosition().x + _joueur2.getHitbox().getGlobalBounds().width/2,_joueur2.getHitbox().getPosition().y - _joueur2.getHitbox().getGlobalBounds().height );
    sf::Time elapsed = _clock.getElapsedTime();
    int timeanim = elapsed.asMilliseconds();
    if(timeanim > 40)
    {
        _cptanim +=1;
        _clock.restart();
    }
    if(_cptanim == 0){
        _spritehitspark.setTextureRect(sf::IntRect(0,22,103,96));
    }
    else if(_cptanim == 1){
        _spritehitspark.setTextureRect(sf::IntRect(0,22,103,96));

    }
    else if(_cptanim == 2){
        _spritehitspark.setTextureRect(sf::IntRect(141,11,124,120));
    }
    else if(_cptanim == 3){
        _spritehitspark.setTextureRect(sf::IntRect(304,3,151,136));
    }
    else if(_cptanim == 4){
        _spritehitspark.setTextureRect(sf::IntRect(497,0,142,142));
    }
    else if(_cptanim == 5){
        _spritehitspark.setTextureRect(sf::IntRect(678,35,148,93));
    }
    else{
        _cptanim = 0;
        return false;
    }
    window.draw(_spritehitspark);
    return true;
}
