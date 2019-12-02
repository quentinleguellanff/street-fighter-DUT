#include <iostream>
#include"menu.h"

using namespace std;

Menu::Menu(float width,float height){

// Fond d'écran du menu

    if(!fond.loadFromFile("menufond.jpg")) {
        std::cout<<"erreur image fond";
    }

    sfond.setTexture(fond);
    sfond.setTextureRect(sf::IntRect(0, 0, 1920,1080));

// Titre du jeu

    if (!font.loadFromFile("OCRAEXT.TTF")){
        std::cout<<"erreur texte";
    }
    titre.setFont(font);

    titre.setString("La Bagarre");
    titre.setColor(sf::Color::White);
    titre.setStyle(sf::Text::Bold);
    titre.setCharacterSize(120);
    titre.setPosition(sf::Vector2f(600,50));



// Tableau de sprites avec toutes les cases utilisables

    if(!textureCase.loadFromFile("spriteMenu.png")) {
        std::cout<<"erreur case";
    }
    textureCase.setSmooth(true);

    spriteMenu[0].setPosition(sf::Vector2f(700,350));
    spriteMenu[0].setTexture(textureCase);
    spriteMenu[0].setTextureRect(sf::IntRect(10, 10, 800, 200));
    spriteMenu[0].scale(0.7f, 0.7f);

    spriteMenu[1].setPosition(sf::Vector2f(700,580));
    spriteMenu[1].setTexture(textureCase);
    spriteMenu[1].setTextureRect(sf::IntRect(10, 320, 800, 200));
    spriteMenu[1].scale(0.7f, 0.7f);

    spriteMenu[2].setPosition(sf::Vector2f(700,810));
    spriteMenu[2].setTexture(textureCase);
    spriteMenu[2].setTextureRect(sf::IntRect(10,630, 800, 200));
    spriteMenu[2].scale(0.7f, 0.7f);

    spriteMenu[3].setPosition(sf::Vector2f(700,350));
    spriteMenu[3].setTexture(textureCase);
    spriteMenu[3].setTextureRect(sf::IntRect(815, 10, 800, 200));
    spriteMenu[3].scale(0.7f, 0.7f);

    spriteMenu[4].setPosition(sf::Vector2f(700,580));
    spriteMenu[4].setTexture(textureCase);
    spriteMenu[4].setTextureRect(sf::IntRect(815, 320, 800, 200));
    spriteMenu[4].scale(0.7f, 0.7f);

    spriteMenu[5].setPosition(sf::Vector2f(700,810));
    spriteMenu[5].setTexture(textureCase);
    spriteMenu[5].setTextureRect(sf::IntRect(815,630, 800, 200));
    spriteMenu[5].scale(0.7f, 0.7f);

// Les sprites des cases utilisées à l'ouverture du menu

    spriteMenux[0]=spriteMenu[3];

    spriteMenux[1]=spriteMenu[1];

    spriteMenux[2]=spriteMenu[2];

    _selection=0;


}

Menu::~Menu(){
}


void Menu::draw(sf::RenderWindow &window){
        //window.draw(sfond);
        window.draw(titre);
        window.draw(spriteMenux[0]);
        window.draw(spriteMenux[1]);
        window.draw(spriteMenux[2]);
    }

int Menu::getSelection(){
return _selection;}

//Monter dans le menu
void Menu::moveUp(){
    if (_selection==1){
            spriteMenux[_selection]=spriteMenu[1];
            _selection=_selection -1;
            spriteMenux[_selection]=spriteMenu[3];

    }
    if (_selection==2){
            spriteMenux[_selection]=spriteMenu[2];
            _selection=_selection -1;
            spriteMenux[_selection]=spriteMenu[4];

    }
}

//Descendre dans le menu
void Menu::moveDown()
{
    if (_selection==1){
            spriteMenux[_selection]=spriteMenu[1];
            _selection=_selection+1;
            spriteMenux[_selection]=spriteMenu[5];
    }
    if (_selection==0){
            spriteMenux[0]=spriteMenu[0];
            _selection=1;
            spriteMenux[1]=spriteMenu[4];

    }



}

