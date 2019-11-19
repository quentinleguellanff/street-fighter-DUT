#include <iostream>
#include"menu.h"
using namespace std;

Menu::Menu(float width,float height){
    if(!font.loadFromFile("Amatic-Bold.ttf")) {
        std::cout<<"erreur police";
    }
    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Red);
    menu[0].setString("Jouer");
    menu[0].setPosition(sf::Vector2f(width/2, height/(nbcase + 1)*1));

    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Commandes");
    menu[1].setPosition(sf::Vector2f(width/2, height/(nbcase + 1)*2));

    menu[2].setFont(font);
    menu[2].setColor(sf::Color::White);
    menu[2].setString("Quitter");
    menu[2].setPosition(sf::Vector2f(width/2, height/(nbcase + 1)*3));

    _selection=0;

}

Menu::~Menu(){
}

void Menu::draw(sf::RenderWindow &window){
    for (int i=0; i<nbcase; i++){
        window.draw(menu[i]);
    }
}

int Menu::getSelection(){
return _selection;}

void Menu::moveUp(){
    if (_selection >0){
            menu[_selection].setColor(sf::Color::White);
            _selection=_selection -1;
            menu[_selection].setColor(sf::Color::Red);

    }
}
void Menu::moveDown()
{
    if (_selection <nbcase){
            menu[_selection].setColor(sf::Color::White);
            _selection=_selection+1;
            menu[_selection].setColor(sf::Color::Red);

    }
}
