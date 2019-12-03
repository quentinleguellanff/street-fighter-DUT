#ifndef MENUSELECT_H_INCLUDED
#define MENUSELECT_H_INCLUDED

    sf::Font fontMenu;

    //texte : sélection des personnages
    sf::Text titre;

    //texte : Joueur 1
    sf::Text j1;

    //texte : Joueur 2
    sf::Text j2;

    //texte : Joueur 2
    sf::Text nomPersoJ1;
    //texte : Joueur 2
    sf::Text nomPersoJ2;

    //délimitation entre la zone de selection j1 et j2
    sf::RectangleShape ligneDelim(sf::Vector2f(5, 700));


    //image perso1
    sf::Texture perso1;
    sf::Sprite spriteP1J1;
    sf::Sprite spriteP1J2;

    //image perso2
    sf::Texture perso2;
    sf::Sprite spriteP2J1;
    sf::Sprite spriteP2J2;

    bool etat = 0;
    int etatPersoJ1 = 0;
    int etatPersoJ2 = 0;
    int choixJ1 = -1;
    int choixJ2 = -1;


#endif // MENUSELECT_H_INCLUDED
