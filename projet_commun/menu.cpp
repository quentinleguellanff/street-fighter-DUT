#include <iostream>
#include "menu.h"

using namespace std;

MenuPrincipal::MenuPrincipal(float width,float height){


    if(!menuFond.loadFromFile("background/menu.jpg")){
        std::cout<<"erreur fond"<<endl;
    }

    spriteFond.setTexture(menuFond);
    spriteFond.setScale(sf::Vector2f(width/1920.f,height/1080.f));

// Titre du jeu

    if (!font.loadFromFile("BebasNeue-Regular.ttf")){
        std::cout<<"erreur texte";
    }
    titre.setFont(font);
    titre.setString("La Bagarre");
    titre.setFillColor(sf::Color(220,40,40));
    titre.setStyle(sf::Text::Bold);
    titre.setCharacterSize(170);
    titre.setLetterSpacing (0.8);
    titre.setOutlineColor(sf::Color::Black);
    titre.setOutlineThickness (1);
    titre.setScale((width/1920)*2.5f,(height/1080)*1.f);
    titre.setPosition(sf::Vector2f(width/10,height/21.6));



// Tableau de sprites avec toutes les cases utilisables

    if(!textureCase.loadFromFile("sprites/spriteMenu.png")) {
        std::cout<<"erreur case";
    }
    textureCase.setSmooth(true);

    spriteMenu[0].setPosition(sf::Vector2f(width/2.74,height/3.08));
    spriteMenu[0].setTexture(textureCase);
    spriteMenu[0].setTextureRect(sf::IntRect(13, 12, 779, 180));
    spriteMenu[0].setScale((width/1920)*0.7f,(height/1080)*0.7f);

    spriteMenu[1].setPosition(sf::Vector2f(width/2.74,height/1.86));
    spriteMenu[1].setTexture(textureCase);
    spriteMenu[1].setTextureRect(sf::IntRect(10, 337, 779, 180));
    spriteMenu[1].setScale((width/1920)*0.7f,(height/1080)*0.7f);

    spriteMenu[2].setPosition(sf::Vector2f(width/2.74,height/1.33));
    spriteMenu[2].setTexture(textureCase);
    spriteMenu[2].setTextureRect(sf::IntRect(10,656, 779, 180));
    spriteMenu[2].setScale((width/1920)*0.7f,(height/1080)*0.7f);

    spriteMenu[3].setPosition(sf::Vector2f(width/2.9,height/3.10));
    spriteMenu[3].setTexture(textureCase);
    spriteMenu[3].setTextureRect(sf::IntRect(816, 12, 779, 180));
    spriteMenu[3].setScale((width/1920)*0.8f,(height/1080)*0.8f);

    spriteMenu[4].setPosition(sf::Vector2f(width/2.9,height/1.88));
    spriteMenu[4].setTexture(textureCase);
    spriteMenu[4].setTextureRect(sf::IntRect(816, 337, 779, 180));
    spriteMenu[4].setScale((width/1920)*0.8f,(height/1080)*0.8f);

    spriteMenu[5].setPosition(sf::Vector2f(width/2.9,height/1.35));
    spriteMenu[5].setTexture(textureCase);
    spriteMenu[5].setTextureRect(sf::IntRect(816,656, 779, 180));
    spriteMenu[5].setScale((width/1920)*0.8f,(height/1080)*0.8f);

// Les sprites des cases utilisées à l'ouverture du menu

    spriteMenux[0]=spriteMenu[3];

    spriteMenux[1]=spriteMenu[1];

    spriteMenux[2]=spriteMenu[2];

    _selection=0;
}

MenuPrincipal::~MenuPrincipal(){
}

void MenuPrincipal::draw(sf::RenderWindow &window){
        window.draw(spriteFond);
        window.draw(titre);
        window.draw(spriteMenux[0]);
        window.draw(spriteMenux[1]);
        window.draw(spriteMenux[2]);
    }

// Recupérer les intructions de l'utilisateur
void MenuPrincipal::bouger(int& selecEcran, sf::Event event,sf::RenderWindow& window)
{
    bool peutmonter = true, peutdescendre = true;
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
            else if(sf::Joystick::isButtonPressed(0,0) && (_selection==0))
                selecEcran=1;
            else if(sf::Joystick::isButtonPressed(0, 0) && (_selection==1))
                selecEcran=3;
            else if(sf::Joystick::isButtonPressed(0, 0) && (_selection==2))
                selecEcran=-1;
            clockAttente.restart();
        }
    }else
    {
        while (window.pollEvent(event))
        {
            switch ( event.type ){

            case sf::Event::Closed:
                    window.close( );
                    break;
            case sf::Event::KeyReleased:
                switch (event.key.code){
                case sf::Keyboard::Z:
                  peutmonter = true;
                  break;
                case sf::Keyboard::S:
                    peutdescendre=true;
                    break;}
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(peutmonter){
                moveUp();
                peutmonter = false;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(peutdescendre){
                moveDown();
                peutdescendre = false;
            }
        }else if ((event.type==sf::Event::KeyReleased && event.key.code==sf::Keyboard::Enter) && (_selection==0))
        {
            selecEcran=1;
            if (!_effetSon.openFromFile("musique/menu_selec.ogg")){
                    std::cout<<"erreur musique";
            }
            _effetSon.play();

        }else if ((event.type==sf::Event::KeyReleased && event.key.code==sf::Keyboard::Enter) && (_selection==1))
        {
            selecEcran=3;
            if (!_effetSon.openFromFile("musique/menu_selec.ogg")){
                    std::cout<<"erreur musique";
            }
            _effetSon.play();

        }else if ((event.type==sf::Event::KeyReleased && event.key.code==sf::Keyboard::Enter) && (_selection==2))
        {
            if (!_effetSon.openFromFile("musique/menu_retour.ogg")){
                    std::cout<<"erreur musique";
            }
            _effetSon.play();
            window.close();
        }
    }

}

//Monter dans le menu
void MenuPrincipal::moveUp(){
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
void MenuPrincipal::moveDown()
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



MenuSelection::MenuSelection(sf::RenderWindow& window)
{
    if(!menuFond.loadFromFile("background/menu.jpg")){
        std::cout<<"erreur fond"<<endl;
    }

    spriteFond.setTexture(menuFond);
    spriteFond.setScale(sf::Vector2f(window.getSize().x/1920.f,window.getSize().y/1080.f));
    hauteurPerso=window.getSize().y*0.8;
    hauteurTexte=window.getSize().y*0.83;

    if (!textureVS.loadFromFile("background/VS.png"))
    {
        cout << "ERREUR : chargement d'image VS" << endl;
    }
    spriteVS.setTexture(textureVS);
    spriteVS.setPosition(sf::Vector2f(window.getSize().x*0.44,window.getSize().y*0.42));
    spriteVS.setTextureRect(sf::IntRect(0,0,324,277));
    //spriteVS.scale(window.getSize().x/1920.f,window.getSize().x/1080.f);

    if (!fontMenu.loadFromFile("MenuSelection/atari.ttf"))
    {
        cout << "ERREUR : chargement de police atari.ttf" << endl;
    }

    if (!texturePersos.loadFromFile("sprites/menuSelection.png"))
    {
        cout << "ERREUR : chargement d'image personnage : browli.png" << endl;
    }

    spriteP1.setTexture(texturePersos);
    spriteP1.setPosition(sf::Vector2f(window.getSize().x*0.15, hauteurPerso-127*3.5));
    spriteP1.setTextureRect(sf::IntRect(293,315,117,241));
    spriteP1.setScale(sf::Vector2f(2,2));

    spriteP2.setTexture(texturePersos);
    spriteP2.setPosition(sf::Vector2f(window.getSize().x*0.85, hauteurPerso-220*1.8));
    spriteP2.setTextureRect(sf::IntRect(205,19,141,220));
    spriteP2.setScale(sf::Vector2f(-1.9,1.9));

    if((choixJ1 == -1) || (choixJ2 == -1)) {
        //texte : sélection des personnages
        titre.setFont(fontMenu);
        titre.setString("Selection des personnages");
        titre.setCharacterSize(90);
        titre.setFillColor(sf::Color::Red);
        titre.setPosition(sf::Vector2f(window.getSize().x*0.3,window.getSize().y*0.05));
        titre.setScale(window.getSize().x/1920.f,window.getSize().x/1080.f);

    if((choixJ1 == -1) || (choixJ2 == -1)) {

        //texte : Joueur 1
        j1.setFont(fontMenu);
        j1.setString("Joueur 1");
        j1.setCharacterSize(60);
        j1.setFillColor(sf::Color::White);
        j1.setStyle(sf::Text::Bold);
        j1.setPosition(sf::Vector2f(window.getSize().x*0.20,window.getSize().y*0.25));
        j1.setScale(window.getSize().x/1920.f,window.getSize().x/1080.f);

        //texte : Joueur 2
        j2.setFont(fontMenu);
        j2.setString("Joueur 2");
        j2.setCharacterSize(60);
        j2.setFillColor(sf::Color::White);
        j2.setStyle(sf::Text::Bold);
        j2.setPosition(sf::Vector2f(window.getSize().x*0.71,window.getSize().y*0.25));
        j2.setScale(window.getSize().x/1920.f,window.getSize().x/1080.f);


        //texte : nomPersoJ1
        nomPersoJ1.setFont(fontMenu);
        nomPersoJ1.setString("Greg");
        nomPersoJ1.setCharacterSize(40);
        nomPersoJ1.setFillColor(sf::Color::White);
        nomPersoJ1.setStyle(sf::Text::Bold);
        nomPersoJ1.setPosition(sf::Vector2f(window.getSize().x*0.21, hauteurTexte));
        nomPersoJ1.setScale(window.getSize().x/1920.f,window.getSize().x/1080.f);


        //texte : nomPersoJ2
        nomPersoJ2.setFont(fontMenu);
        nomPersoJ2.setString("Dhalsim");
        nomPersoJ2.setCharacterSize(40);
        nomPersoJ2.setFillColor(sf::Color::White);
        nomPersoJ2.setStyle(sf::Text::Bold);
        nomPersoJ2.setPosition(sf::Vector2f(window.getSize().x*0.72,hauteurTexte));
        nomPersoJ2.setScale(window.getSize().x/1920.f,window.getSize().x/1080.f);
    }
}

void MenuSelection::draw(sf::RenderWindow &window)
{
        window.draw(spriteFond);
        window.draw(titre);
        window.draw(j1);
        window.draw(j2);
        window.draw(spriteVS);
        window.draw(spriteP1);
        window.draw(spriteP2);
        window.draw(nomPersoJ1);
        window.draw(nomPersoJ2);
        window.draw(annulerChoixJ1);
        window.draw(annulerChoixJ2);

}

void MenuSelection::persoSuivant_P1(int& etatPerso,sf::RenderWindow& window)
{
    switch(etatPerso)
    {
    case 0:
        etatPersoJ1 = 1;
        spriteP1.setTextureRect(sf::IntRect(205,19,141,220));
        spriteP1.setScale(sf::Vector2f(1.9,1.9));
        spriteP1.setPosition(sf::Vector2f(window.getSize().x*0.15, hauteurPerso-220*1.8));
        break;
    case 1:
        etatPersoJ1 = 2;
        spriteP1.setTextureRect(sf::IntRect(367,25,123,245));
        spriteP1.setScale(sf::Vector2f(1.8,1.8));
        spriteP1.setPosition(sf::Vector2f(window.getSize().x*0.15, hauteurPerso-220*1.8));
        break;
    case 2:
        etatPersoJ1 = 0;
        spriteP1.setTextureRect(sf::IntRect(293,315,117,241));
        spriteP1.setScale(sf::Vector2f(1.8,1.8));
        spriteP1.setPosition(sf::Vector2f(window.getSize().x*0.15, hauteurPerso-127*3.5));
        break;
    }
}

void MenuSelection::persoSuivant_P2(int& etatPerso,sf::RenderWindow& window)
{
    switch(etatPerso)
    {
    case 0:
        etatPersoJ2 = 1;
        spriteP2.setTextureRect(sf::IntRect(205,19,141,220));
        spriteP2.setScale(sf::Vector2f(-1.9,1.9));
        spriteP2.setPosition(sf::Vector2f(window.getSize().x*0.85, hauteurPerso-220*1.8));
        break;
    case 1:
        etatPersoJ2 = 2;
        spriteP2.setTextureRect(sf::IntRect(367,25,123,245));
        spriteP2.setScale(sf::Vector2f(-1.8,1.8));
        spriteP2.setPosition(sf::Vector2f(window.getSize().x*0.85, hauteurPerso-220*1.8));
        break;
    case 2:
        etatPersoJ2 = 0;
        spriteP2.setTextureRect(sf::IntRect(293,315,117,241));
        spriteP2.setScale(sf::Vector2f(-1.8,1.8));
        spriteP2.setPosition(sf::Vector2f(window.getSize().x*0.85, hauteurPerso-127*3.5));
        break;
    }
}

void MenuSelection::persoPrecedent_P1(int& etatPerso,sf::RenderWindow& window)
{
    switch(etatPerso)
    {
    case 0:
        etatPersoJ1 = 2;
        spriteP1.setTextureRect(sf::IntRect(367,25,123,245));
        spriteP1.setScale(sf::Vector2f(1.8,1.8));
        spriteP1.setPosition(sf::Vector2f(window.getSize().x*0.15, hauteurPerso-220*1.8));
        break;
    case 1:
        etatPersoJ1 = 0;
        spriteP1.setTextureRect(sf::IntRect(26,27,109,127));
        spriteP1.setScale(sf::Vector2f(3.5,3.5));
        spriteP1.setPosition(sf::Vector2f(window.getSize().x*0.15, hauteurPerso-127*3.5));
        break;
    case 2:
        etatPersoJ1 = 1;
        spriteP1.setTextureRect(sf::IntRect(293,315,117,241));
        spriteP1.setScale(sf::Vector2f(1.8,1.8));
        spriteP1.setPosition(sf::Vector2f(window.getSize().x*0.15, hauteurPerso-220*1.8));
        break;
    }
}

void MenuSelection::persoPrecedent_P2(int& etatPerso,sf::RenderWindow& window)
{
    switch(etatPerso)
    {
    case 0:
        etatPersoJ2 = 2;
        spriteP2.setTextureRect(sf::IntRect(367,25,123,245));
        spriteP2.setScale(sf::Vector2f(-1.8,1.8));
        spriteP2.setPosition(sf::Vector2f(window.getSize().x*0.85, hauteurPerso-220*1.8));
        break;
    case 1:
        etatPersoJ2 = 0;
        spriteP2.setTextureRect(sf::IntRect(26,27,109,127));
        spriteP2.setScale(sf::Vector2f(-3.5,3.5));
        spriteP2.setPosition(sf::Vector2f(window.getSize().x*0.85, hauteurPerso-127*3.5));
        break;
    case 2:
        etatPersoJ2 = 1;
        spriteP2.setTextureRect(sf::IntRect(293,315,117,241));
        spriteP2.setScale(sf::Vector2f(-1.8,1.8));
        spriteP2.setPosition(sf::Vector2f(window.getSize().x*0.85, hauteurPerso-220*1.8));
        break;
    }
}

// Recupérer les intructions de l'utilisateur
void MenuSelection::bouger(sf::Event event,sf::RenderWindow& window)
{
    //Selection j1
    if(choixJ1 == -1)
    {
        if (sf::Joystick::isConnected(0))
        {
            sf::Time elapsed = clockAttenteJoystick.getElapsedTime();
            int timeAttente = elapsed.asMilliseconds();
            if(timeAttente>150)
            {
                joystick0_axisX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
                joystick0_axisY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

                if( (joystick0_axisX > 40) && (joystick0_axisY < 70 && joystick0_axisY > -55))
                    persoSuivant_P1(etatPersoJ1,window);
                else if( (joystick0_axisX < -40) && (joystick0_axisY < 70 && joystick0_axisY > -40))
                    persoPrecedent_P1(etatPersoJ1,window);

                clockAttenteJoystick.restart();
            }
        }else
        {
                bool peutGauche = true, peutDroite = true;

            while (window.pollEvent(event))
            {
                switch ( event.type )
                {
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Right:
                      peutDroite = true;
                      break;
                    case sf::Keyboard::Left:
                        peutGauche=true;
                        break;
                    }
                }
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                if(peutDroite)
                {
                    persoSuivant_P1(etatPersoJ1,window);
                    peutDroite = false;
                }
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                if(peutGauche)
                {
                    persoPrecedent_P1(etatPersoJ1,window);
                    peutGauche = false;
                }
            }
        }



        switch(etatPersoJ1)
        {
            case 0: nomPersoJ1.setString("Greg");
                    break;
            case 1: nomPersoJ1.setString("Dhalsim");
                    break;
            case 2: nomPersoJ1.setString("Ryu");
                    break;
        }
    }

    //Selection j2
    if(choixJ2 == -1)
    {
        if (sf::Joystick::isConnected(1))
        {
            sf::Time elapsed = clockAttenteJoystick.getElapsedTime();
            int timeAttente = elapsed.asMilliseconds();
            if(timeAttente>150)
            {
                joystick0_axisX = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
                joystick0_axisY = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);

                if( (joystick0_axisX > 40) && (joystick0_axisY < 70 && joystick0_axisY > -55))
                    persoPrecedent_P2(etatPersoJ2,window);
                else if( (joystick0_axisX < -40) && (joystick0_axisY < 70 && joystick0_axisY > -40))
                    persoSuivant_P2(etatPersoJ2,window);

                clockAttenteJoystick.restart();
            }
        }else
        {
            bool peutGauche2 = true, peutDroite2 = true;

            while (window.pollEvent(event))
            {
                switch ( event.type )
                {
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::D:
                      peutDroite2 = true;
                      break;
                    case sf::Keyboard::Q:
                        peutGauche2=true;
                        break;
                    }
                }
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if(peutDroite2)
                {
                    persoSuivant_P2(etatPersoJ2,window);
                    peutDroite2 = false;
                }
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if(peutGauche2)
                {
                    persoPrecedent_P2(etatPersoJ2,window);
                    peutGauche2 = false;
                }
            }
        }

        switch(etatPersoJ2)
        {
            case 0: nomPersoJ2.setString("Greg");
                    break;
            case 1: nomPersoJ2.setString("Dhalsim");
                    break;
            case 2: nomPersoJ2.setString("Ryu");
                    break;
        }
    }

    //Retours
    if( ( (sf::Event::KeyReleased && event.key.code == sf::Keyboard::B) || appuiBouttonManette(0,1,clockAttenteBoutton) ) && choixJ1 >= 0)
    {
        choixJ1 = -1;
        nomPersoJ1.setFillColor(sf::Color::White);
        annulerChoixJ1.setString("");
    }

    if(sf::Joystick::isButtonPressed(1, 1))
    {
        choixJ1 = -1;
        nomPersoJ1.setFillColor(sf::Color::White);
        annulerChoixJ1.setString("");
    }else if( ( (sf::Event::KeyReleased && event.key.code == sf::Keyboard::BackSpace) || appuiBouttonManette(1,1,clockAttenteBoutton) ) && choixJ2 >= 0)
    {
        choixJ2 = -1;
        nomPersoJ2.setFillColor(sf::Color::White);
        annulerChoixJ2.setString("");
    }
}


int MenuSelection::validationPerso(sf::Event event,int& selecChamp_P1, int& selecChamp_P2)
{
     //Validation du choix de personage pour Joueur 1

    if( (sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) || appuiBouttonManette(0,0,clockAttenteBoutton))
    {
        choixJ1 = etatPersoJ1;

        nomPersoJ1.setFillColor(sf::Color::Red);

        //texte : annulation du choix J1
        annulerChoixJ1.setFont(fontMenu);
        annulerChoixJ1.setString("Touche B pour annuler la selection");
        annulerChoixJ1.setCharacterSize(20);
        annulerChoixJ1.setFillColor(sf::Color::White);
        annulerChoixJ1.setStyle(sf::Text::Italic);
        annulerChoixJ1.setPosition(sf::Vector2f(650,hauteurTexte+15));

        if (!_effetSon.openFromFile("musique/perso_selec.ogg")){
                std::cout<<"erreur musique";
        }
        _effetSon.play();
    }

    //Validation du choix de personage pour Joueur 2
    if( (sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) || appuiBouttonManette(1,0,clockAttenteBoutton))
    {
            choixJ2 = etatPersoJ2;

            nomPersoJ2.setFillColor(sf::Color::Red);

            //texte : annulation du choix J1
            annulerChoixJ2.setFont(fontMenu);
            annulerChoixJ2.setString("Touche BackSpace pour annuler la selection");
            annulerChoixJ2.setCharacterSize(20);
            annulerChoixJ2.setFillColor(sf::Color::White);
            annulerChoixJ2.setStyle(sf::Text::Italic);
            annulerChoixJ2.setPosition(sf::Vector2f(1000,hauteurTexte+15));

            if (!_effetSon.openFromFile("musique/perso_selec.ogg")){
                    std::cout<<"erreur musique";
            }
            _effetSon.play();
    }

    if(choixJ1 != -1 && choixJ2 != -1)
    {
        selecChamp_P1=choixJ1;
        selecChamp_P2=choixJ2;
        return 4;
    }
    else if( ( (sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) || appuiBouttonManette(0,3,clockAttenteBoutton) ) && choixJ1 == -1 && choixJ2 == -1)
    {
        if (!_effetSon.openFromFile("musique/menu_retour.ogg")){
                std::cout<<"erreur musique";
        }
        _effetSon.play();
        return 0;
    }else
        return 1;
}

void MenuSelection::reset(sf::RenderWindow& window)
{
    choixJ1=-1;choixJ2=-1;
    etatPersoJ1=0;etatPersoJ2=1;

    annulerChoixJ1.setString("");
    annulerChoixJ2.setString("");

    nomPersoJ1.setFillColor(sf::Color::White);
    nomPersoJ1.setString("Jotaro");
    nomPersoJ2.setFillColor(sf::Color::White);
    nomPersoJ2.setString("Dhalsim");

    spriteP1.setPosition(sf::Vector2f(window.getSize().x*0.15, hauteurPerso-127*3.5));
    spriteP1.setTextureRect(sf::IntRect(26,27,109,127));
    spriteP1.setScale(sf::Vector2f(3.5,3.5));

    spriteP2.setPosition(sf::Vector2f(window.getSize().x*0.85, hauteurPerso-220*1.8));
    spriteP2.setTextureRect(sf::IntRect(205,19,141,220));
    spriteP2.setScale(sf::Vector2f(-1.8,1.8));
}

void MenuSelection::initValidationPerso()
{
    choixJ2 = -1;
    nomPersoJ2.setFillColor(sf::Color::White);
    annulerChoixJ2.setString("");
}

void MenuSelection::resetClock()
{
    clockAttenteJoystick.restart();
    clockAttenteBoutton.restart();
}


MenuCommandes::MenuCommandes(sf::RenderWindow& window)
{

    if(!menuFond.loadFromFile("background/menu.jpg")){
        std::cout<<"erreur fond"<<endl;
    }

    spriteFond.setTexture(menuFond);
    spriteFond.setScale(sf::Vector2f(window.getSize().x/1920.f,window.getSize().y/1080.f));

    if (!fontCommandes.loadFromFile("MenuSelection/atari.ttf"))
    {
        cout << "ERREUR : chargement de police atari.ttf" << endl;
    }
    if(!texturej1.loadFromFile("sprites/commandej1.png")) {
        std::cout<<"erreur manette";
    }
    if(!texturej2.loadFromFile("sprites/commandej2.png")) {
        std::cout<<"erreur clavier";
    }
    j1.setFont(fontCommandes);
    j1.setString("Joueur 1");
    j1.setCharacterSize(50);
    j1.setFillColor(sf::Color(255,0,0));
    j1.setPosition(sf::Vector2f(100,100));
    j1.setScale(sf::Vector2f(window.getSize().x/1920.f,window.getSize().y/1080.f));


    j2.setFont(fontCommandes);
    j2.setString("Joueur 2");
    j2.setCharacterSize(50);
    j2.setFillColor(sf::Color(255,0,0));
    j2.setPosition(sf::Vector2f(1000,100));
    j2.setScale(sf::Vector2f(window.getSize().x/1920.f,window.getSize().y/1080.f));


    spriteCommandes[0].setPosition(sf::Vector2f(window.getSize().x*0.2, window.getSize().y*0.2));
    spriteCommandes[0].setTexture(texturej1);
    spriteCommandes[0].setTextureRect(sf::IntRect(0, 0, 515, 515));
    spriteCommandes[0].setScale(sf::Vector2f(window.getSize().x/1920.f,window.getSize().y/1080.f));

    spriteCommandes[1].setPosition(sf::Vector2f(window.getSize().x*0.55, window.getSize().y*0.2));
    spriteCommandes[1].setTexture(texturej2);
    spriteCommandes[1].setTextureRect(sf::IntRect(0, 0, 679, 415));
    spriteCommandes[1].setScale(sf::Vector2f(window.getSize().x/1920.f,window.getSize().y/1080.f));

    retour.setFont(fontCommandes);
    retour.setString("Appuyez sur echap pour revenir au menu");
    retour.setCharacterSize(30);
    retour.setFillColor(sf::Color::White);
    retour.setStyle(sf::Text::Italic);
    retour.setPosition(sf::Vector2f(window.getSize().x*0.40, window.getSize().y*0.9));
    retour.setScale(sf::Vector2f(window.getSize().x/1920.f,window.getSize().y/1080.f));

    //ligne delim
    ligneDelim.setSize(sf::Vector2f(window.getSize().x*0.005,window.getSize().y*0.6));
    ligneDelim.setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y/5));
}

void MenuCommandes::retourMenu(int& selecEcran,sf::Event event)
{
    if( (sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) || appuiBouttonManette(0,3,clockAttenteBoutton) )
    {
        selecEcran=0;
    }
}

void MenuCommandes::draw(sf::RenderWindow &window)
{
    window.draw(spriteFond);
    window.draw(spriteCommandes[0]);
    window.draw(spriteCommandes[1]);
    window.draw(retour);
    window.draw(j1);
    window.draw(j2);
    window.draw(ligneDelim);
}

MenuBackground::MenuBackground(sf::RenderWindow& window)
{

    selection=0;

    if(!menuFond.loadFromFile("background/menu.jpg")){
        std::cout<<"erreur fond"<<endl;
    }

    spriteFond.setTexture(menuFond);
    spriteFond.setScale(sf::Vector2f(window.getSize().x/1920.f,window.getSize().y/1080.f));

    if (!fontBackground.loadFromFile("MenuSelection/atari.ttf"))
    {
        cout << "ERREUR : chargement de police atari.ttf" << endl;
    }
    if(!bg[0].loadFromFile("background/toit.png")) {
        std::cout<<"erreur fond toit";
    }
    if(!bg[1].loadFromFile("background/futur.jpg")) {
        std::cout<<"erreur fond futur";
    }
    if(!bg[2].loadFromFile("background/ring_xenoverse_V2.jpg")) {
        std::cout<<"erreur fond xenorverse";
    }
    if(!bg[3].loadFromFile("background/skulls.jpg")) {
        std::cout<<"erreur fond skulls";
    }
    if(!bg[4].loadFromFile("background/SanFran.png")) {
        std::cout<<"erreur fond brazil";
    }
    if(!bg[5].loadFromFile("background/avion.png")) {
        std::cout<<"erreur fond brazil";
    }

    spritebg[0].setTexture(bg[0]);
    spritebg[0].setPosition(sf::Vector2f(window.getSize().x*0.025,window.getSize().y*0.25));
    spritebg[0].setScale(0.3f,0.3f);
    spritebg[0].scale(window.getSize().x/1920.f,window.getSize().y/1080.f);

    spritebg[1].setTexture(bg[1]);
    spritebg[1].setPosition(sf::Vector2f(window.getSize().x*0.35,window.getSize().y*0.25));
    spritebg[1].setScale(0.3f,0.3f);
    spritebg[1].scale(window.getSize().x/1920.f,window.getSize().y/1080.f);

    spritebg[2].setTexture(bg[2]);
    spritebg[2].setPosition(sf::Vector2f(window.getSize().x*0.675,window.getSize().y*0.25));
    spritebg[2].setScale(0.3f,0.3f);
    spritebg[2].scale(window.getSize().x/1920.f,window.getSize().y/1080.f);

    spritebg[3].setTexture(bg[3]);
    spritebg[3].setPosition(sf::Vector2f(window.getSize().x*0.025,window.getSize().y*0.61));
    spritebg[3].setScale(0.3f,0.3f);
    spritebg[3].scale(window.getSize().x/1920.f,window.getSize().y/1080.f);

    spritebg[4].setTexture(bg[4]);
    spritebg[4].setPosition(sf::Vector2f(window.getSize().x*0.35,window.getSize().y*0.61));
    spritebg[4].setScale(0.3f,0.3f);
    spritebg[4].scale(window.getSize().x/1920.f,window.getSize().y/1080.f);

    spritebg[5].setTexture(bg[5]);
    spritebg[5].setPosition(sf::Vector2f(window.getSize().x*0.675,window.getSize().y*0.61));
    spritebg[5].setScale(0.3f,0.3f);
    spritebg[5].scale(window.getSize().x/1920.f,window.getSize().y/1080.f);



    titre.setFont(fontBackground);
    titre.setString("Choix de la Map");
    titre.setCharacterSize(90);
    titre.setFillColor(sf::Color::Red);
    titre.setPosition(sf::Vector2f(window.getSize().x*0.38,window.getSize().y*0.05));
    titre.setScale(window.getSize().x/1920.f,window.getSize().y/1080.f);

    retour.setFont(fontBackground);
    retour.setString("Appuyez sur echap pour revenir au menu");
    retour.setCharacterSize(30);
    retour.setFillColor(sf::Color::White);
    retour.setStyle(sf::Text::Italic);
    retour.setPosition(sf::Vector2f(window.getSize().x*0.40, window.getSize().y*0.9));
    retour.setScale(sf::Vector2f(window.getSize().x/1920.f,window.getSize().y/1080.f));

    for(int i=0; i<6;i++){
        rect[i].setSize(sf::Vector2f(window.getSize().x*0.32,window.getSize().y*0.32));
        rect[i].setFillColor(sf::Color(255,0,0));

    }
    rect[0].setPosition(sf::Vector2f(window.getSize().x*0.015,window.getSize().y*0.24));
    rect[1].setPosition(sf::Vector2f(window.getSize().x*0.34,window.getSize().y*0.24));
    rect[2].setPosition(sf::Vector2f(window.getSize().x*0.665,window.getSize().y*0.24));
    rect[3].setPosition(sf::Vector2f(window.getSize().x*0.015,window.getSize().y*0.6));
    rect[4].setPosition(sf::Vector2f(window.getSize().x*0.34,window.getSize().y*0.6));
    rect[5].setPosition(sf::Vector2f(window.getSize().x*0.665,window.getSize().y*0.6));

}

void MenuBackground::draw(sf::RenderWindow& window)
{
        window.draw(spriteFond);
        window.draw(rect[selection]);
        window.draw(spritebg[0]);
        window.draw(spritebg[1]);
        window.draw(spritebg[2]);
        window.draw(spritebg[3]);
        window.draw(spritebg[4]);
        window.draw(spritebg[5]);
        window.draw(retour);
        window.draw(titre);
    }

void MenuBackground::retourMenu2(int& selecEcran,sf::Event event,MenuSelection& m,sf::RenderWindow& window)
{
    if( (sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) || appuiBouttonManette(0,3,clockAttenteBoutton) )
    {
        selecEcran=1;
        m.initValidationPerso();
    }
    return;
}

void MenuBackground::bouger(sf::Event event, sf::RenderWindow& window)
{
    bool peutGauche = true, peutDroite = true;

    while (window.pollEvent(event))
    {
        switch ( event.type )
        {
        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
            case sf::Keyboard::Right:
              peutDroite = true;
              break;
            case sf::Keyboard::Left:
                peutGauche=true;
                break;
            }
        }
    }

    if(sf::Joystick::isConnected(0))
    {
        sf::Time elapsed = clockAttenteJoystick.getElapsedTime();
        int timeAttente = elapsed.asMilliseconds();
        if(timeAttente>150)
        {
            joystick0_axisX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
            joystick0_axisY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

            if( (joystick0_axisX > 40) && (joystick0_axisY < 70 && joystick0_axisY > -55))
                moveRight();
            else if( (joystick0_axisX < -40) && (joystick0_axisY < 70 && joystick0_axisY > -40))
                moveLeft();

            clockAttenteJoystick.restart();
        }

    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(peutDroite)
        {
            moveRight();
            peutDroite = false;
        }
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(peutGauche)
        {
            moveLeft();
            peutGauche = false;
        }
    }
    if ((selection>=0) && (selection<3) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
        selection=selection+3;

    if ((selection>=3) && (selection<6) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
        selection=selection-3;
}

void MenuBackground::moveRight()
{
    if (selection<5)
    {
        selection=selection+1;
    }
}

void MenuBackground::moveLeft(){
    if (selection>0)
    {
        selection=selection-1;
    }

}
void MenuBackground::selectionner(sf::Event event, sf::RenderWindow& window, int& selecEcran, Scene& s,sf::Music& son)
{
    bool go = true;
    while (window.pollEvent(event))
    {
        if(sf::Event::KeyReleased && event.key.code==sf::Keyboard::Enter)
        {
            go=true;
            break;
        }
    }

    if(sf::Joystick::isConnected(0))
    {
        if(appuiBouttonManette(0,0,clockAttenteBoutton))
            valider(window,selecEcran,s,son);
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if(go)
        {
            valider(window, selecEcran, s,son);
            go = false;
        }
    }

}

void MenuBackground::valider(sf::RenderWindow& window, int& selecEcran, Scene& s,sf::Music& son)
{
       if (selection==0)
            s.chargementToit(son);
        if (selection==1)
            s.chargementFutur(son);
        if (selection==2)
            s.chargementXenoverse(son);
        if (selection==3)
            s.chargementSkulls(son);
        if (selection==4)
            s.chargementSanFran(window,son);
        if (selection==5)
            s.chargementAvion(son);
        selecEcran=2;
}


bool appuiBouttonManette(int numJoy,int numBoutton,sf::Clock& clockAttente)
{
    sf::Time elapsed = clockAttente.getElapsedTime();
    int timeAttente = elapsed.asMilliseconds();
    if(timeAttente>150)
    {
        if (sf::Joystick::isButtonPressed(numJoy,numBoutton))
        {
            clockAttente.restart();
            return true;
        }
    }
    return false;
}
