#include <iostream>
#include"menu.h"

using namespace std;

Menu::Menu(float width,float height){

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

        else if ((event.type==sf::Event::KeyReleased && event.key.code==sf::Keyboard::Enter) && (_selection==0))
            selecEcran=1;

        else if ((event.type==sf::Event::KeyReleased && event.key.code==sf::Keyboard::Enter) && (_selection==2))
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



MenuSelection::MenuSelection(float width,float height){
        if (!fontMenu.loadFromFile("MenuSelection/atari.ttf"))
                {
                    cout << "ERREUR : chargement de police atari.ttf" << endl;
                }

              if (!perso1.loadFromFile("MenuSelection/browli.png"))
                {
                    cout << "ERREUR : chargement d'image personnage : browli.png" << endl;
                }

              if (!perso2.loadFromFile("MenuSelection/dhalsim.png"))
                {
                    cout << "ERREUR : chargement d'image personnage : dhalsim.png" << endl;
                }

              spriteP1J1.setTexture(perso1);
              spriteP1J1.scale(sf::Vector2f(-1.8,1.8));
              spriteP1J1.setPosition(sf::Vector2f(630.f, HAUTEURPERSO));

              spriteP2J1.setTexture(perso2);
              spriteP2J1.scale(sf::Vector2f(1.8,1.8));
              spriteP2J1.setPosition(sf::Vector2f(-970.f, HAUTEURPERSO));

              spriteP1J2.setTexture(perso1);
              spriteP1J2.scale(sf::Vector2f(1.8,1.8));
              spriteP1J2.setPosition(sf::Vector2f(1250.f, HAUTEURPERSO));

              spriteP2J2.setTexture(perso2);
              spriteP2J2.scale(sf::Vector2f(-1.8,1.8));
              spriteP2J2.setPosition(sf::Vector2f(2200.f, HAUTEURPERSO));

              if((choixJ1 == -1) || (choixJ2 == -1)) {
                        //texte : sélection des personnages
                        titre.setFont(fontMenu);
                        titre.setString("Selection des personnages");
                        titre.setCharacterSize(50);
                        titre.setFillColor(sf::Color::White);
                        titre.setStyle(sf::Text::Bold);
                        titre.setPosition(sf::Vector2f(720,50));

                        //ligne delim
                        ligneDelim.setSize(sf::Vector2f(5, 600));
                        ligneDelim.setPosition(sf::Vector2f(960, 300));

                        //texte : Joueur 1
                        j1.setFont(fontMenu);
                        j1.setString("Joueur 1");
                        j1.setCharacterSize(60);
                        j1.setFillColor(sf::Color::White);
                        j1.setStyle(sf::Text::Bold);
                        j1.setPosition(sf::Vector2f(420,200));

                        //texte : Joueur 2
                        j2.setFont(fontMenu);
                        j2.setString("Joueur 2");
                        j2.setCharacterSize(60);
                        j2.setFillColor(sf::Color::White);
                        j2.setStyle(sf::Text::Bold);
                        j2.setPosition(sf::Vector2f(1250,200));

                        //texte : nomPersoJ1
                        nomPersoJ1.setFont(fontMenu);
                        nomPersoJ1.setString("Broly");
                        nomPersoJ1.setCharacterSize(40);
                        nomPersoJ1.setFillColor(sf::Color::White);
                        nomPersoJ1.setStyle(sf::Text::Bold);
                        nomPersoJ1.setPosition(sf::Vector2f(480, HAUTEURTEXTE));

                        //texte : nomPersoJ2
                        nomPersoJ2.setFont(fontMenu);
                        nomPersoJ2.setString("Broly");
                        nomPersoJ2.setCharacterSize(40);
                        nomPersoJ2.setFillColor(sf::Color::White);
                        nomPersoJ2.setStyle(sf::Text::Bold);
                        nomPersoJ2.setPosition(sf::Vector2f(1310,HAUTEURTEXTE));


            }
}

void MenuSelection::draw(sf::RenderWindow &window) {
        window.draw(titre);
        window.draw(j1);
        window.draw(j2);
        window.draw(ligneDelim);
        window.draw(spriteP1J1);
        window.draw(spriteP2J1);
        window.draw(spriteP1J2);
        window.draw(spriteP2J2);
        window.draw(nomPersoJ1);
        window.draw(nomPersoJ2);
        window.draw(annulerChoixJ1);
}

// Recupérer les intructions de l'utilisateur
void MenuSelection::bouger(sf::Event event)
{
    if((sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right) && etatPersoJ2 == 0)
    {
        etatPersoJ2 = 1;
        spriteP1J2.move(sf::Vector2f(950,0));
        spriteP2J2.move(sf::Vector2f(-750,0));
    }


    if((sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left) && etatPersoJ2 == 1)
    {
        etatPersoJ2 = 0;
        spriteP2J2.move(sf::Vector2f(750,0));
        spriteP1J2.move(sf::Vector2f(-950,0));
    }

    if((sf::Event::KeyReleased && event.key.code == sf::Keyboard::D) && etatPersoJ1 == 0)
    {
        etatPersoJ1 = 1;
        spriteP1J1.move(sf::Vector2f(-1600,0));
        spriteP2J1.move(sf::Vector2f(1400,0));
    }

    if((sf::Event::KeyReleased && event.key.code == sf::Keyboard::Q) && etatPersoJ1 == 1)
    {
        etatPersoJ1 = 0;
        spriteP2J1.move(sf::Vector2f(-1400,0));
        spriteP1J1.move(sf::Vector2f(1600,0));
    }

    switch(etatPersoJ1)
    {
        case 0: nomPersoJ1.setString("Broly");
                break;
        case 1: nomPersoJ1.setString("Dhalsim");
                break;
    }

    switch(etatPersoJ2)
    {
        case 0: nomPersoJ2.setString("Broly");
                break;
        case 1: nomPersoJ2.setString("Dhalsim");
                break;
    }
}


int MenuSelection::validationPerso(sf::Event event)
{
     //Validation du choix de personage pour Joueur 1
     if(sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
     {
            choixJ1 = etatPersoJ1;

             nomPersoJ1.setFillColor(sf::Color::Red);
             //texte : annulation du choix J1
             annulerChoixJ1.setFont(fontMenu);
             annulerChoixJ1.setString("Touche B pour annuler la selection");
             annulerChoixJ1.setCharacterSize(20);
             annulerChoixJ1.setFillColor(sf::Color::White);
             annulerChoixJ1.setStyle(sf::Text::Italic);
             annulerChoixJ1.setPosition(sf::Vector2f(400,900));

     }

    //Validation du choix de personage pour Joueur 2
    if(sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
    {
            choixJ2 = etatPersoJ2;
    }

    if(choixJ1 != -1 && choixJ2 != -1) return 2;
    else return 1;
}
