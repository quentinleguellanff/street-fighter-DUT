#include "collisionmanager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Broly.h"
#include "joueur.h"


using namespace std;

collisionmanager::collisionmanager()
{
}

void collisionmanager::collisionpersonnage(Joueur& joueur1, Joueur& joueur2){
    bool collision = joueur1.getHurtbox().getGlobalBounds().intersects(joueur2.getHurtbox().getGlobalBounds());
    //cout << joueur1.getHurtbox().getPosition().x << endl;
    if(collision){
        joueur1.deplacer(-joueur1.getVitesseX());
        cout << joueur1.getVitesseX() << endl;
    }
}
collisionmanager::~collisionmanager()
{
    //dtor
}
