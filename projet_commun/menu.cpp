#include <iostream>
#include"menu.h"

using namespace std;

Menu::Menu(float width,float height){
    if(!font.loadFromFile("Amatic-Bold.ttf")) {
        std::cout<<"erreur police";
    }
    if(!menuFond.loadFromFile("background/menu.png")){
        std::cout<<"erreur fond"<<endl;
    }

    spriteFond.setTexture(menuFond);

// Titre du jeu

    if (!font.loadFromFile("OCRAEXT.TTF")){
        std::cout<<"erreur texte";
    }
    titre.setFont(font);

    titre.setString("La Bagarre");
    titre.setFillColor(sf::Color::White);
    titre.setStyle(sf::Text::Bold);
    titre.setCharacterSize(120);
    titre.setPosition(sf::Vector2f(600,50));



// Tableau de sprites avec toutes les cases utilisables

    if(!textureCase.loadFromFile("sprites/spriteMenu.png")) {
        std::cout<<"erreur case";
    }
    textureCase.setSmooth(true);

    spriteMenu[0].setPosition(sf::Vector2f(700,350));
    spriteMenu[0].setTexture(textureCase);
    spriteMenu[0].setTextureRect(sf::IntRect(13, 12, 779, 180));
    spriteMenu[0].scale(0.7f, 0.7f);

    spriteMenu[1].setPosition(sf::Vector2f(700,580));
    spriteMenu[1].setTexture(textureCase);
    spriteMenu[1].setTextureRect(sf::IntRect(10, 337, 779, 180));
    spriteMenu[1].scale(0.7f, 0.7f);

    spriteMenu[2].setPosition(sf::Vector2f(700,810));
    spriteMenu[2].setTexture(textureCase);
    spriteMenu[2].setTextureRect(sf::IntRect(10,656, 779, 180));
    spriteMenu[2].scale(0.7f, 0.7f);

    spriteMenu[3].setPosition(sf::Vector2f(700,350));
    spriteMenu[3].setTexture(textureCase);
    spriteMenu[3].setTextureRect(sf::IntRect(816, 12, 779, 180));
    spriteMenu[3].scale(0.7f, 0.7f);

    spriteMenu[4].setPosition(sf::Vector2f(700,580));
    spriteMenu[4].setTexture(textureCase);
    spriteMenu[4].setTextureRect(sf::IntRect(816, 337, 779, 180));
    spriteMenu[4].scale(0.7f, 0.7f);

    spriteMenu[5].setPosition(sf::Vector2f(700,810));
    spriteMenu[5].setTexture(textureCase);
    spriteMenu[5].setTextureRect(sf::IntRect(816,656, 779, 180));
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
        window.draw(spriteFond);
        window.draw(titre);
        window.draw(spriteMenux[0]);
        window.draw(spriteMenux[1]);
        window.draw(spriteMenux[2]);
    }

// Recupérer les intructions de l'utilisateur
void Menu::bouger(int& selecEcran, sf::Event event) 
{
    if (sf::Joystick::isConnected(0)) 
    {
        sf::Time elapsed = clockAttente.getElapsedTime();
        int timeAttente = elapsed.asMilliseconds();
        if(timeAttente>150)
        {
            joystick0_axisX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
            joystick0_axisY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

            if( (joystick0_axisX>-80 && joystick0_axisX<80) && (joystick0_axisY<-30))
                moveUp();
            else if( (joystick0_axisX>-80 && joystick0_axisX<80) && (joystick0_axisY>30))
                moveDown();
            else if(sf::Joystick::isButtonPressed(0, 0) && (_selection==0))
                selecEcran=1;
            else if(sf::Joystick::isButtonPressed(0, 0) && (_selection==2))
                selecEcran=-1;
            clockAttente.restart();
        }
    }else
    {
        if(event.type==sf::Event::KeyReleased && event.key.code==sf::Keyboard::Z)
        moveUp();

        else if (event.type==sf::Event::KeyReleased && event.key.code==sf::Keyboard::S)
            moveDown();

        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && (_selection==0))
            selecEcran=1;

        else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && (_selection==2))
            selecEcran=-1;
    }
}

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

