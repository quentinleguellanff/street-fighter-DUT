#include <iostream>
#include"menu.h"

using namespace std;

Menu::Menu(float width,float height){
    if(!font.loadFromFile("Amatic-Bold.ttf")) {
        std::cout<<"erreur police";
    }
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Jouer");
    menu[0].setPosition(sf::Vector2f(width/2, height/(nbcase + 1)*1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Commandes");
    menu[1].setPosition(sf::Vector2f(width/2, height/(nbcase + 1)*2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Quitter");
    menu[2].setPosition(sf::Vector2f(width/2, height/(nbcase + 1)*3));

    _selection=0;
    /*_monter=0;
    _descendre=0;*/

}

Menu::~Menu(){
}

void Menu::draw(sf::RenderWindow &window){
        window.draw(menu[0]);
        window.draw(menu[1]);
        window.draw(menu[2]);
    }


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


void Menu::moveUp(){
    if (_selection >0){
            menu[_selection].setFillColor(sf::Color::White);
            _selection=_selection -1;
            menu[_selection].setFillColor(sf::Color::Red);
    }
}
void Menu::moveDown()
{
    if (_selection <nbcase-1){
            menu[_selection].setFillColor(sf::Color::White);
            _selection=_selection+1;
            menu[_selection].setFillColor(sf::Color::Red);
    }
}
