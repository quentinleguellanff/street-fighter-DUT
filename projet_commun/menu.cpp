#include <iostream>
#include "menu.h"

using namespace std;

MenuPrincipal::MenuPrincipal(float width,float height){

    if(!font.loadFromFile("OCRAEXT.ttf")) {
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
    spriteMenu[0].setScale(0.7f, 0.7f);

    spriteMenu[1].setPosition(sf::Vector2f(700,580));
    spriteMenu[1].setTexture(textureCase);
    spriteMenu[1].setTextureRect(sf::IntRect(10, 337, 779, 180));
    spriteMenu[1].setScale(0.7f, 0.7f);

    spriteMenu[2].setPosition(sf::Vector2f(700,810));
    spriteMenu[2].setTexture(textureCase);
    spriteMenu[2].setTextureRect(sf::IntRect(10,656, 779, 180));
    spriteMenu[2].setScale(0.7f, 0.7f);

    spriteMenu[3].setPosition(sf::Vector2f(700,350));
    spriteMenu[3].setTexture(textureCase);
    spriteMenu[3].setTextureRect(sf::IntRect(816, 12, 779, 180));
    spriteMenu[3].setScale(0.7f, 0.7f);

    spriteMenu[4].setPosition(sf::Vector2f(700,580));
    spriteMenu[4].setTexture(textureCase);
    spriteMenu[4].setTextureRect(sf::IntRect(816, 337, 779, 180));
    spriteMenu[4].setScale(0.7f, 0.7f);

    spriteMenu[5].setPosition(sf::Vector2f(700,810));
    spriteMenu[5].setTexture(textureCase);
    spriteMenu[5].setTextureRect(sf::IntRect(816,656, 779, 180));
    spriteMenu[5].setScale(0.7f, 0.7f);

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
void MenuPrincipal::bouger(int& selecEcran, sf::Event event,sf::RenderWindow &window)
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
            else if(sf::Joystick::isButtonPressed(0, 0) && (_selection==0))
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
    hauteurPerso=window.getSize().y*0.8;
    hauteurTexte=window.getSize().y*0.83;

    if (!textureVS.loadFromFile("background/VS.png"))
    {
        cout << "ERREUR : chargement d'image VS" << endl;
    }
    spriteVS.setTexture(textureVS);
    spriteVS.setPosition(sf::Vector2f(window.getSize().x*0.44,window.getSize().y*0.42));
    spriteVS.setTextureRect(sf::IntRect(0,0,324,277));

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
    spriteP1.setTextureRect(sf::IntRect(26,27,109,127));
    spriteP1.setScale(sf::Vector2f(3.5,3.5));

    spriteP2.setTexture(texturePersos);
    spriteP2.setPosition(sf::Vector2f(window.getSize().x*0.85, hauteurPerso-220*1.8));
    spriteP2.setTextureRect(sf::IntRect(205,19,141,220));
    spriteP2.setScale(sf::Vector2f(-1.8,1.8));

    if((choixJ1 == -1) || (choixJ2 == -1)) {
        //texte : sélection des personnages
        titre.setFont(fontMenu);
        titre.setString("Selection des personnages");
        titre.setCharacterSize(50);
        titre.setFillColor(sf::Color::White);
        titre.setStyle(sf::Text::Bold);
        titre.setPosition(sf::Vector2f(720,50));

        //texte : Joueur 1
        j1.setFont(fontMenu);
        j1.setString("Joueur 1");
        j1.setCharacterSize(60);
        j1.setFillColor(sf::Color::White);
        j1.setStyle(sf::Text::Bold);
        j1.setPosition(sf::Vector2f(window.getSize().x*0.20,window.getSize().y*0.25));

        //texte : Joueur 2
        j2.setFont(fontMenu);
        j2.setString("Joueur 2");
        j2.setCharacterSize(60);
        j2.setFillColor(sf::Color::White);
        j2.setStyle(sf::Text::Bold);
        j2.setPosition(sf::Vector2f(window.getSize().x*0.71,window.getSize().y*0.25));

        //texte : nomPersoJ1
        nomPersoJ1.setFont(fontMenu);
        nomPersoJ1.setString("Jotaro");
        nomPersoJ1.setCharacterSize(40);
        nomPersoJ1.setFillColor(sf::Color::White);
        nomPersoJ1.setStyle(sf::Text::Bold);
        nomPersoJ1.setPosition(sf::Vector2f(window.getSize().x*0.21, hauteurTexte));

        //texte : nomPersoJ2
        nomPersoJ2.setFont(fontMenu);
        nomPersoJ2.setString("Dhalsim");
        nomPersoJ2.setCharacterSize(40);
        nomPersoJ2.setFillColor(sf::Color::White);
        nomPersoJ2.setStyle(sf::Text::Bold);
        nomPersoJ2.setPosition(sf::Vector2f(window.getSize().x*0.72,hauteurTexte));
    }
}

void MenuSelection::draw(sf::RenderWindow &window) {
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
        spriteP1.setScale(sf::Vector2f(1.8,1.8));
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
        spriteP1.setTextureRect(sf::IntRect(26,27,109,127));
        spriteP1.setScale(sf::Vector2f(3.5,3.5));
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
        spriteP2.setScale(sf::Vector2f(-1.8,1.8));
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
        spriteP2.setTextureRect(sf::IntRect(26,27,109,127));
        spriteP2.setScale(sf::Vector2f(-3.5,3.5));
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
        spriteP1.setTextureRect(sf::IntRect(205,19,141,220));
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
        spriteP2.setTextureRect(sf::IntRect(205,19,141,220));
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
        if(sf::Event::KeyReleased && event.key.code == sf::Keyboard::D)
            persoSuivant_P1(etatPersoJ1,window);

        if(sf::Event::KeyReleased && event.key.code == sf::Keyboard::Q)
            persoPrecedent_P1(etatPersoJ1,window);

        switch(etatPersoJ1)
        {
            case 0: nomPersoJ1.setString("Jotaro");
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
        if(sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right)
            persoSuivant_P2(etatPersoJ2,window);

        if(sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left)
            persoPrecedent_P2(etatPersoJ2,window);

        switch(etatPersoJ2)
        {
            case 0: nomPersoJ2.setString("Jotaro");
                    break;
            case 1: nomPersoJ2.setString("Dhalsim");
                    break;
            case 2: nomPersoJ2.setString("Ryu");
                    break;
        }
    }

    //Retours
    if((sf::Event::KeyReleased && event.key.code == sf::Keyboard::B) && choixJ1 >= 0)
    {
        choixJ1 = -1;
        nomPersoJ1.setFillColor(sf::Color::White);
        annulerChoixJ1.setString("");
    }

    if((sf::Event::KeyReleased && event.key.code == sf::Keyboard::BackSpace) && choixJ2 >= 0)
    {
        choixJ2 = -1;
        nomPersoJ2.setFillColor(sf::Color::White);
        annulerChoixJ2.setString("");
    }
}


int MenuSelection::validationPerso(sf::Event event,int& selecChamp_P1, int& selecChamp_P2)
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
             annulerChoixJ1.setPosition(sf::Vector2f(650,hauteurTexte+15));

            if (!_effetSon.openFromFile("musique/perso_selec.ogg")){
                    std::cout<<"erreur musique";
            }
            _effetSon.play();
     }

    //Validation du choix de personage pour Joueur 2
    if(sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
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
    else if((sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) && choixJ1 == -1 && choixJ2 == -1)
    {
        if (!_effetSon.openFromFile("musique/menu_retour.ogg")){
                std::cout<<"erreur musique";
        }
        _effetSon.play();
        return 0;
    }

    else return 1;
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


MenuCommandes::MenuCommandes() 
{
    if(!menuFond.loadFromFile("background/menu.png")){
        std::cout<<"erreur fond"<<endl;
    }

    spriteFond.setTexture(menuFond);

    if (!fontCommandes.loadFromFile("OCRAEXT.ttf"))
    {
        cout << "ERREUR : chargement de police ocr.ttf" << endl;
    }
    /*if(!textureManette.loadFromFile("sprites/manette.png")) {
        std::cout<<"erreur manette";
    }*/
    if(!textureClavier.loadFromFile("sprites/clavier.png")) {
        std::cout<<"erreur clavier";
    }


    spriteCommandes[0].setPosition(sf::Vector2f(300,150));
    spriteCommandes[0].setTexture(textureClavier);
    spriteCommandes[0].setTextureRect(sf::IntRect(0, 5, 1350, 700));

    retour.setFont(fontCommandes);
    retour.setString("Appuyez sur echap pour revenir au menu");
    retour.setCharacterSize(20);
    retour.setFillColor(sf::Color::White);
    retour.setStyle(sf::Text::Italic);
    retour.setPosition(sf::Vector2f(750,900));
}
void MenuCommandes::retourMenu(int& selecEcran,sf::Event event)
{
    if(sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape){
        selecEcran=0;
    }else if (sf::Joystick::isConnected(0))
    {
        if(sf::Joystick::isButtonPressed(0, 1))
            selecEcran=0;
    }
}
void MenuCommandes::draw(sf::RenderWindow &window)
{
        window.draw(spriteFond);
        window.draw(spriteCommandes[0]);
        window.draw(retour);
}

MenuBackground::MenuBackground(sf::RenderWindow& window)
{

    selection=0;

    if(!menuFond.loadFromFile("background/menu.png")){
        std::cout<<"erreur fond"<<endl;
    }

    spriteFond.setTexture(menuFond);

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
    if(!bg[4].loadFromFile("background/brazil.jpg")) {
        std::cout<<"erreur fond brazil";
    }

    spritebg[0].setTexture(bg[0]);
    spritebg[0].setPosition(sf::Vector2f(window.getSize().x*0.1,window.getSize().y*0.3));
    spritebg[0].setScale(0.2f,0.2f);

    spritebg[1].setTexture(bg[1]);
    spritebg[1].setPosition(sf::Vector2f(window.getSize().x*0.4,window.getSize().y*0.3));
    spritebg[1].setScale(0.2f,0.2f);

    spritebg[2].setTexture(bg[2]);
    spritebg[2].setPosition(sf::Vector2f(window.getSize().x*0.7,window.getSize().y*0.7));
    spritebg[2].setScale(0.2f,0.2f);

    spritebg[3].setTexture(bg[3]);
    spritebg[3].setPosition(sf::Vector2f(window.getSize().x*0.1,window.getSize().y*0.7));
    spritebg[3].setScale(0.2f,0.2f);

    spritebg[4].setTexture(bg[4]);
    spritebg[4].setPosition(sf::Vector2f(window.getSize().x*0.4,window.getSize().y*0.7));
    spritebg[4].setScale(0.2f,0.2f);


    titre.setFont(fontBackground);
    titre.setString("Choix de la Map");
    titre.setCharacterSize(50);
    titre.setFillColor(sf::Color(255,0,0));
    titre.setPosition(sf::Vector2f(window.getSize().x*0.3,window.getSize().y*0.1));

    retour.setFont(fontBackground);
    retour.setString("Appuyez sur echap pour revenir au menu");
    retour.setCharacterSize(30);
    retour.setFillColor(sf::Color::White);
    retour.setStyle(sf::Text::Italic);
    retour.setPosition(sf::Vector2f(window.getSize().x*0.40, window.getSize().y*0.9));

    for(int i=0; i<6;i++){
        rect[i].setSize(sf::Vector2f(window.getSize().x*0.22,window.getSize().y*0.22));
        rect[i].setFillColor(sf::Color(255,0,0));

    }
    rect[0].setPosition(sf::Vector2f(window.getSize().x*0.09,window.getSize().y*0.29));
    rect[1].setPosition(sf::Vector2f(window.getSize().x*0.39,window.getSize().y*0.29));
    rect[2].setPosition(sf::Vector2f(window.getSize().x*0.69,window.getSize().y*0.29));
    rect[3].setPosition(sf::Vector2f(window.getSize().x*0.09,window.getSize().y*0.69));
    rect[4].setPosition(sf::Vector2f(window.getSize().x*0.39,window.getSize().y*0.69));

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
        window.draw(retour);
        window.draw(titre);
    }

void MenuBackground::retourMenu2(int& selecEcran,sf::Event event,MenuSelection& m,sf::RenderWindow& window)
{
    if(sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
    {
        selecEcran=1;
        m.reset(window);
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
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(peutDroite)
        {
            moveRight();
            peutDroite = false;
        }
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(peutGauche)
        {
            moveLeft();
            peutGauche = false;
        }
    }
}

void MenuBackground::moveRight()
{
    if (selection<4) 
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
void MenuBackground::selectionner(sf::Event event, sf::RenderWindow& window, int& selecEcran, Scene& s/*, Dhalsim& d, Jotaro& j*/)
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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if(go)
        {
            valider(window, selecEcran,s);
            go = false;
        }
    }

}

void MenuBackground::valider(sf::RenderWindow& window, int& selecEcran, Scene& s/*, Dhalsim& d, Jotaro& j*/)
{
       if (selection==0)
            s.chargementToit();
        if (selection==1)
            s.chargementFutur();
        if (selection==2)
            s.chargementXenoverse();
        if (selection==3)
            s.chargementSkulls();
        if (selection==4)
            s.chargementBrazil(window);
        selecEcran=2;
        //j.setTout(-1,s);
        //d.setTout(1,s);

}