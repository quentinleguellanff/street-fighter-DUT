#include "Combat.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"
#include "joueur.h"


using namespace std;

Combat::Combat(Joueur& joueur1, Joueur& joueur2,sf::RectangleShape& sol)
{
    _joueur1 = joueur1;
    _joueur2 = joueur2;
    _sol = sol;
    if(!_TextureBackground.loadFromFile("sprite/background1.jpg")){
        cout << "erreur de chargement de texture de la scene" << endl;
    }

    if (!_Texturehitspark.loadFromFile("sprite/hitsparks.png"))//load de la texture du personnage
    {
        cout << "erreur de chargement de texture des effets visuels" << endl;
    }
    _spriteBackground.setTexture(_TextureBackground);
    _spriteBackground.setScale(0.75,0.83);
     _spritehitspark.setTexture(_Texturehitspark);
     _spritehitspark.setTextureRect(sf::IntRect(0,22,103,96));
     //_spritehitspark.setScale(-1,1);
     //_spritehitspark.setScale(0.9,0.9);
    hitspark1 = false;
    hitspark2 = false;
     _spritehitspark.setOrigin(_spritehitspark.getGlobalBounds().width,_spritehitspark.getPosition().y);
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

            _joueur1.avancedroite(window,_joueur2.getHurtbox());
            _joueur2.avancedroite(window,_joueur1.getHurtbox());

            _joueur1.avancegauche(window,_joueur2.getHurtbox());
            _joueur2.avancegauche(window,_joueur1.getHurtbox());

            _joueur1.statique(window,_joueur2.getHurtbox());
            _joueur2.statique(window,_joueur1.getHurtbox());

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
            //window.draw(_joueur2.getHitbox());
            //cout << _joueur2.getHitbox().getPosition().x << endl;
            if(toucheJ1){
                hitspark1 = true;
            }
            if(toucheJ2){
                hitspark2 = true;
            }
            hitGraphique(window,hitspark1,_joueur2);
            hitGraphique(window,hitspark2,_joueur1);
            window.display();
            return true;
}

void Combat::hitGraphique(sf::RenderWindow& window, bool& hitspark,Joueur& joueur){
    if(hitspark){
        int Orientation = joueur.getOrientation();
        //cout << Orientation << endl;
        float positionHitboxX;
        if(Orientation == -1){
            _spritehitspark.setScale(-1,1);
            positionHitboxX = joueur.getHitbox().getPosition().x - joueur.getHitbox().getGlobalBounds().width;
        }
        else if(Orientation == 1){
            _spritehitspark.setScale(1,1);
            positionHitboxX = joueur.getHitbox().getGlobalBounds().left +  joueur.getHitbox().getGlobalBounds().width; //+ 286;
        }
        //cout << positionHitboxX << endl;
        //float positionHitboxX = _joueur2.getHitbox().getPosition().x - _joueur2.getHitbox().getGlobalBounds().width/2;
        float positionHitboxY = joueur.getHitbox().getPosition().y - joueur.getHitbox().getGlobalBounds().height*1.5;


        vector<vector<int>> tabTexture = {{},
                                          {0,1,143,220},
                                          {146,1,146,220},
                                          {295,1,197,220},
                                          {495,1,197,220},
                                          {695,1,197,220},
                                          {895,1,185,220}
                                         };

        vector<sf::Vector2f> tabPosition = {sf::Vector2f(positionHitboxX,positionHitboxY),
                                            sf::Vector2f(positionHitboxX,positionHitboxY),
                                            sf::Vector2f(positionHitboxX-10*Orientation,positionHitboxY),
                                            sf::Vector2f(positionHitboxX-40*Orientation,positionHitboxY),
                                            sf::Vector2f(positionHitboxX-20*Orientation,positionHitboxY),
                                            sf::Vector2f(positionHitboxX-5*Orientation,positionHitboxY),
                                            sf::Vector2f(positionHitboxX+40*Orientation,positionHitboxY),
                                           };
        sf::Time elapsed = _clock.getElapsedTime();
        int timeanim = elapsed.asMilliseconds();
        if(timeanim > 15)//30 bonne valeur
        {
            _cptanim +=1;
            _clock.restart();
        }
        if(_cptanim >= 1 && _cptanim <= 6){
            _spritehitspark.setTextureRect(sf::IntRect(tabTexture[_cptanim][0],tabTexture[_cptanim][1],tabTexture[_cptanim][2],tabTexture[_cptanim][3]));
            _spritehitspark.setPosition(tabPosition[_cptanim]);
            window.draw(_spritehitspark);
        }
        else if(_cptanim > 6){
            _cptanim = 0;
            hitspark = false;
        }
    }
}
